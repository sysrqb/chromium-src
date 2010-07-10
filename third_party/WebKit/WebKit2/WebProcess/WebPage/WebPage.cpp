/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "WebPage.h"

#include "Arguments.h"
#include "DrawingArea.h"
#include "InjectedBundle.h"
#include "MessageID.h"
#include "WebBackForwardControllerClient.h"
#include "WebBackForwardListProxy.h"
#include "WebChromeClient.h"
#include "WebContextMenuClient.h"
#include "WebCoreArgumentCoders.h"
#include "WebDragClient.h"
#include "WebEditorClient.h"
#include "WebEvent.h"
#include "WebEventConversion.h"
#include "WebFrame.h"
#include "WebInspectorClient.h"
#include "WebPageMessageKinds.h"
#include "WebPageProxyMessageKinds.h"
#include "WebPreferencesStore.h"
#include "WebProcess.h"
#include <WebCore/BackForwardList.h>
#include <WebCore/EventHandler.h>
#include <WebCore/FocusController.h>
#include <WebCore/Frame.h>
#include <WebCore/FrameLoaderTypes.h>
#include <WebCore/FrameView.h>
#include <WebCore/KeyboardEvent.h>
#include <WebCore/Page.h>
#include <WebCore/PlatformKeyboardEvent.h>
#include <WebCore/RenderTreeAsText.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/Settings.h>
#include <runtime/JSLock.h>
#include <runtime/JSValue.h>

#ifndef NDEBUG
#include <wtf/RefCountedLeakCounter.h>
#endif

using namespace JSC;
using namespace WebCore;

namespace WebKit {

#ifndef NDEBUG
static WTF::RefCountedLeakCounter webPageCounter("WebPage");
#endif

PassRefPtr<WebPage> WebPage::create(uint64_t pageID, const IntSize& viewSize, const WebPreferencesStore& store, DrawingArea::Type drawingAreaType)
{
    return adoptRef(new WebPage(pageID, viewSize, store, drawingAreaType));
}

WebPage::WebPage(uint64_t pageID, const IntSize& viewSize, const WebPreferencesStore& store, DrawingArea::Type drawingAreaType)
    : m_page(new Page(new WebChromeClient(this), new WebContextMenuClient(this), new WebEditorClient(this), new WebDragClient(this), new WebInspectorClient(this), 0, 0, 0, new WebBackForwardControllerClient(this)))
    , m_viewSize(viewSize)
    , m_drawingArea(DrawingArea::create(drawingAreaType, this))
    , m_canGoBack(false)
    , m_canGoForward(false)
    , m_pageID(pageID)
{
    ASSERT(m_pageID);

    m_page->settings()->setJavaScriptEnabled(store.javaScriptEnabled);
    m_page->settings()->setLoadsImagesAutomatically(store.loadsImagesAutomatically);
    m_page->settings()->setPluginsEnabled(store.pluginsEnabled);
    m_page->settings()->setMinimumFontSize(store.minimumFontSize);
    m_page->settings()->setMinimumLogicalFontSize(store.minimumLogicalFontSize);
    m_page->settings()->setDefaultFontSize(store.defaultFontSize);
    m_page->settings()->setDefaultFixedFontSize(store.defaultFixedFontSize);
    m_page->settings()->setStandardFontFamily(store.standardFontFamily);
    m_page->settings()->setCursiveFontFamily(store.cursiveFontFamily);
    m_page->settings()->setFantasyFontFamily(store.fantasyFontFamily);
    m_page->settings()->setFixedFontFamily(store.fixedFontFamily);
    m_page->settings()->setSansSerifFontFamily(store.sansSerifFontFamily);
    m_page->settings()->setSerifFontFamily(store.serifFontFamily);

    platformInitialize();

    m_mainFrame = WebFrame::createMainFrame(this);
    WebProcess::shared().connection()->send(WebPageProxyMessage::DidCreateMainFrame, m_pageID, CoreIPC::In(m_mainFrame->frameID()));

    if (WebProcess::shared().injectedBundle())
        WebProcess::shared().injectedBundle()->didCreatePage(this);

#ifndef NDEBUG
    webPageCounter.increment();
#endif
}

WebPage::~WebPage()
{
    ASSERT(!m_page);
#ifndef NDEBUG
    webPageCounter.decrement();
#endif
}

void WebPage::initializeInjectedBundleLoaderClient(WKBundlePageLoaderClient* client)
{
    m_loaderClient.initialize(client);
}

void WebPage::initializeInjectedBundleUIClient(WKBundlePageUIClient* client)
{
    m_uiClient.initialize(client);
}

String WebPage::renderTreeExternalRepresentation() const
{
    return externalRepresentation(m_mainFrame->coreFrame(), RenderAsTextBehaviorNormal);
}

WebFrame* WebPage::webFrame(uint64_t frameID) const
{
    return m_frameMap.get(frameID);
}

void WebPage::addWebFrame(uint64_t frameID, WebFrame* frame)
{
    m_frameMap.set(frameID, frame);
}

void WebPage::removeWebFrame(uint64_t frameID)
{
    m_frameMap.remove(frameID);
}

void WebPage::close()
{
    if (WebProcess::shared().injectedBundle())
        WebProcess::shared().injectedBundle()->willDestroyPage(this);

    m_mainFrame->coreFrame()->loader()->detachFromParent();

    delete m_page;
    m_page = 0;

    WebProcess::shared().removeWebPage(m_pageID);
}

void WebPage::tryClose()
{
    if (!m_mainFrame->coreFrame()->loader()->shouldClose())
        return;

    WebProcess::shared().connection()->send(WebPageProxyMessage::ClosePage, m_pageID, CoreIPC::In());
}

void WebPage::loadURL(const String& url)
{
    m_mainFrame->coreFrame()->loader()->load(ResourceRequest(KURL(KURL(), url)), false);
}

void WebPage::stopLoading()
{
    m_mainFrame->coreFrame()->loader()->stopForUserCancel();
}

void WebPage::reload(bool reloadFromOrigin)
{
    m_mainFrame->coreFrame()->loader()->reload(reloadFromOrigin);
}

void WebPage::goForward()
{
    m_page->goForward();
}

void WebPage::goBack()
{
    m_page->goBack();
}

void WebPage::goToBackForwardItem(uint64_t backForwardItemID)
{
    HistoryItem* item = WebBackForwardListProxy::itemForID(backForwardItemID);
    m_page->goToItem(item, FrameLoadTypeIndexedBackForward);
}

void WebPage::layoutIfNeeded()
{
    if (m_mainFrame->coreFrame()->view())
        m_mainFrame->coreFrame()->view()->layoutIfNeededRecursive();
}

void WebPage::setSize(const WebCore::IntSize& viewSize)
{
    if (m_viewSize == viewSize)
        return;

    Frame* frame = m_page->mainFrame();
    
    frame->view()->resize(viewSize);
    frame->view()->setNeedsLayout();
    m_drawingArea->setNeedsDisplay(IntRect(IntPoint(0, 0), viewSize));
    
    m_viewSize = viewSize;
}

void WebPage::drawRect(GraphicsContext& graphicsContext, const IntRect& rect)
{
    graphicsContext.save();
    graphicsContext.clip(rect);
    m_mainFrame->coreFrame()->view()->paint(&graphicsContext, rect);
    graphicsContext.restore();
}

// Events 

void WebPage::mouseEvent(const PlatformMouseEvent& event)
{
    if (!m_mainFrame->coreFrame()->view())
        return;

    switch (event.eventType()) {
        case WebCore::MouseEventPressed:
            m_mainFrame->coreFrame()->eventHandler()->handleMousePressEvent(event);
            break;
        case WebCore::MouseEventReleased:
            m_mainFrame->coreFrame()->eventHandler()->handleMouseReleaseEvent(event);
            break;
        case WebCore::MouseEventMoved:
            m_mainFrame->coreFrame()->eventHandler()->mouseMoved(event);
            break;
        default:
            ASSERT_NOT_REACHED();
            break;
    }
}

void WebPage::wheelEvent(PlatformWheelEvent& event)
{
    if (!m_mainFrame->coreFrame()->view())
        return;

    m_mainFrame->coreFrame()->eventHandler()->handleWheelEvent(event);
}

void WebPage::keyEvent(const PlatformKeyboardEvent& event)
{
    if (!m_mainFrame->coreFrame()->view())
        return;

    m_page->focusController()->focusedOrMainFrame()->eventHandler()->keyEvent(event);
}

void WebPage::setActive(bool isActive)
{
    m_page->focusController()->setActive(isActive);
}

void WebPage::setFocused(bool isFocused)
{
    m_page->focusController()->setFocused(isFocused);
}

void WebPage::setIsInWindow(bool isInWindow)
{
    if (!isInWindow) {
        m_page->setCanStartMedia(false);
        m_page->willMoveOffscreen();
    } else {
        m_page->setCanStartMedia(true);
        m_page->didMoveOnscreen();
    }
}

void WebPage::didReceivePolicyDecision(WebFrame* frame, uint64_t listenerID, WebCore::PolicyAction policyAction)
{
    if (!frame)
        return;
    frame->didReceivePolicyDecision(listenerID, policyAction);
}

void WebPage::show()
{
    WebProcess::shared().connection()->send(WebPageProxyMessage::ShowPage, m_pageID, CoreIPC::In());
}

void WebPage::runJavaScriptInMainFrame(const WebCore::String& script, uint64_t callbackID)
{
    // NOTE: We need to be careful when running scripts that the objects we depend on don't
    // disappear during script execution.

    JSLock lock(SilenceAssertionsOnly);
    JSValue resultValue = m_mainFrame->coreFrame()->script()->executeScript(script, true).jsValue();
    String resultString = ustringToString(resultValue.toString(m_mainFrame->coreFrame()->script()->globalObject(mainThreadNormalWorld())->globalExec()));

    WebProcess::shared().connection()->send(WebPageProxyMessage::DidRunJavaScriptInMainFrame, m_pageID, CoreIPC::In(resultString, callbackID));
}

void WebPage::getRenderTreeExternalRepresentation(uint64_t callbackID)
{
    String resultString = renderTreeExternalRepresentation();
    WebProcess::shared().connection()->send(WebPageProxyMessage::DidGetRenderTreeExternalRepresentation, m_pageID, CoreIPC::In(resultString, callbackID));
}

void WebPage::preferencesDidChange(const WebPreferencesStore& store)
{
    m_page->settings()->setJavaScriptEnabled(store.javaScriptEnabled);
    m_page->settings()->setLoadsImagesAutomatically(store.loadsImagesAutomatically);
}

bool WebPage::handleEditingKeyboardEvent(KeyboardEvent* evt)
{
    Node* node = evt->target()->toNode();
    ASSERT(node);
    Frame* frame = node->document()->frame();
    ASSERT(frame);

    const PlatformKeyboardEvent* keyEvent = evt->keyEvent();
    if (!keyEvent)
        return false;

    Editor::Command command = frame->editor()->command(interpretKeyEvent(evt));

    if (keyEvent->type() == PlatformKeyboardEvent::RawKeyDown) {
        // WebKit doesn't have enough information about mode to decide how commands that just insert text if executed via Editor should be treated,
        // so we leave it upon WebCore to either handle them immediately (e.g. Tab that changes focus) or let a keypress event be generated
        // (e.g. Tab that inserts a Tab character, or Enter).
        return !command.isTextInsertion() && command.execute(evt);
    }

     if (command.execute(evt))
        return true;

    // Don't insert null or control characters as they can result in unexpected behaviour
    if (evt->charCode() < ' ')
        return false;

    return frame->editor()->insertText(evt->keyEvent()->text(), evt);
}

void WebPage::didReceiveMessage(CoreIPC::Connection* connection, CoreIPC::MessageID messageID, CoreIPC::ArgumentDecoder& arguments)
{
    if (messageID.is<CoreIPC::MessageClassDrawingArea>()) {
        ASSERT(m_drawingArea);
        m_drawingArea->didReceiveMessage(connection, messageID, arguments);
        return;
    }

    switch (messageID.get<WebPageMessage::Kind>()) {
        case WebPageMessage::SetActive: {
            bool active;
            if (!arguments.decode(active))
                return;
         
            setActive(active);
            break;
        }
        case WebPageMessage::SetFocused: {
            bool focused;
            if (!arguments.decode(focused))
                return;
            
            setFocused(focused);
            break;
        }
        case WebPageMessage::SetIsInWindow: {
            bool isInWindow;
            if (!arguments.decode(isInWindow))
                return;
            
            setIsInWindow(isInWindow);
            break;
        }
        case WebPageMessage::MouseEvent: {
            WebMouseEvent event;
            if (!arguments.decode(event))
                return;
            connection->send(WebPageProxyMessage::DidReceiveEvent, m_pageID, CoreIPC::In((uint32_t)event.type()));
            PlatformMouseEvent platformEvent = platform(event);
            mouseEvent(platformEvent);
            break;
        }
        case WebPageMessage::WheelEvent: {
            WebWheelEvent event;
            if (!arguments.decode(event))
                return;
            connection->send(WebPageProxyMessage::DidReceiveEvent, m_pageID, CoreIPC::In((uint32_t)event.type()));
            PlatformWheelEvent platformEvent = platform(event);
            wheelEvent(platformEvent);
            break;
        }
        case WebPageMessage::KeyEvent: {
            WebKeyboardEvent event;
            if (!arguments.decode(event))
                return;
            connection->send(WebPageProxyMessage::DidReceiveEvent, m_pageID, CoreIPC::In((uint32_t)event.type()));
            PlatformKeyboardEvent platformEvent = platform(event);
            keyEvent(platformEvent);
            break;
        }
        case WebPageMessage::LoadURL: {
            String url;
            if (!arguments.decode(url))
                return;
            
            loadURL(url);
            break;
        }
        case WebPageMessage::StopLoading:
            stopLoading();
            break;
        case WebPageMessage::Reload:
            bool reloadFromOrigin;
            if (!arguments.decode(CoreIPC::Out(reloadFromOrigin)))
                return;

            reload(reloadFromOrigin);
            break;
        case WebPageMessage::GoForward:
            goForward();
            break;
        case WebPageMessage::GoBack:
            goBack();
            break;
        case WebPageMessage::GoToBackForwardItem: {
            uint64_t backForwardItemID;
            if (!arguments.decode(CoreIPC::Out(backForwardItemID)))
                return;
            goToBackForwardItem(backForwardItemID);
            break;
        }
        case WebPageMessage::DidReceivePolicyDecision: {
            uint64_t frameID;
            uint64_t listenerID;
            uint32_t policyAction;
            if (!arguments.decode(CoreIPC::Out(frameID, listenerID, policyAction)))
                return;
            didReceivePolicyDecision(webFrame(frameID), listenerID, (WebCore::PolicyAction)policyAction);
            break;
        }
        case WebPageMessage::RunJavaScriptInMainFrame: {
            String script;
            uint64_t callbackID;
            if (!arguments.decode(CoreIPC::Out(script, callbackID)))
                return;
            runJavaScriptInMainFrame(script, callbackID);
            break;
        }
        case WebPageMessage::GetRenderTreeExternalRepresentation: {
            uint64_t callbackID;
            if (!arguments.decode(callbackID))
                return;
            getRenderTreeExternalRepresentation(callbackID);
            break;
        }
        case WebPageMessage::Close: {
            close();
            break;
        }
        case WebPageMessage::TryClose: {
            tryClose();
            break;
        }
        default:
            ASSERT_NOT_REACHED();
            break;
    }
}

} // namespace WebKit
