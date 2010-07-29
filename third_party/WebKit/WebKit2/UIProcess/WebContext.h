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

#ifndef WebContext_h
#define WebContext_h

#include "APIObject.h"
#include "PluginInfoStore.h"
#include "ProcessModel.h"
#include "WebContextInjectedBundleClient.h"
#include "WebHistoryClient.h"
#include "WebProcessProxy.h"
#include <WebCore/PlatformString.h>
#include <wtf/Forward.h>
#include <wtf/HashSet.h>
#include <wtf/PassRefPtr.h>
#include <wtf/RefPtr.h>

struct WKContextStatistics;

namespace WebKit {

class WebPageNamespace;
class WebPageProxy;
class WebPreferences;

class WebContext : public APIObject {
public:
    static WebContext* sharedProcessContext();
    static WebContext* sharedThreadContext();

    static PassRefPtr<WebContext> create(const WebCore::String& injectedBundlePath)
    {
        return adoptRef(new WebContext(ProcessModelSecondaryProcess, injectedBundlePath));
    }

    ~WebContext();

    void initializeInjectedBundleClient(WKContextInjectedBundleClient*);
    void initializeHistoryClient(WKContextHistoryClient*);

    ProcessModel processModel() const { return m_processModel; }
    WebProcessProxy* process() const { return m_process.get(); }

    WebPageProxy* createWebPage(WebPageNamespace*);

    void reviveIfNecessary();

    WebPageNamespace* createPageNamespace();
    void pageNamespaceWasDestroyed(WebPageNamespace*);

    void setPreferences(WebPreferences*);
    WebPreferences* preferences() const;
    void preferencesDidChange();

    const WebCore::String& injectedBundlePath() const { return m_injectedBundlePath; }

    // InjectedBundle client
    void didReceiveMessageFromInjectedBundle(const WebCore::String&);
    void postMessageToInjectedBundle(const WebCore::String&);

    // History client
    void didNavigateWithNavigationData(WebFrameProxy*, const WebNavigationDataStore&); 
    void didPerformClientRedirect(WebFrameProxy*, const WebCore::String& sourceURLString, const WebCore::String& destinationURLString);
    void didPerformServerRedirect(WebFrameProxy*, const WebCore::String& sourceURLString, const WebCore::String& destinationURLString);
    void didUpdateHistoryTitle(WebFrameProxy*, const WebCore::String& title, const WebCore::String& url);
    void populateVisitedLinks();
    
    void getStatistics(WKContextStatistics* statistics);
    void setAdditionalPluginPath(const WebCore::String&);

    PluginInfoStore* pluginInfoStore() { return &m_pluginInfoStore; }
    WebCore::String applicationCacheDirectory();
    
    void registerURLSchemeAsEmptyDocument(const WebCore::String&);

private:
    WebContext(ProcessModel, const WebCore::String& injectedBundlePath);

    virtual Type type() const { return TypeContext; }

    void ensureWebProcess();
    bool hasValidProcess() const { return m_process && m_process->isValid(); }

    ProcessModel m_processModel;
    
    // FIXME: In the future, this should be one or more WebProcessProxies.
    RefPtr<WebProcessProxy> m_process;

    HashSet<WebPageNamespace*> m_pageNamespaces;
    RefPtr<WebPreferences> m_preferences;

    WebCore::String m_injectedBundlePath;
    WebContextInjectedBundleClient m_injectedBundleClient;

    WebHistoryClient m_historyClient;

    PluginInfoStore m_pluginInfoStore;
};

} // namespace WebKit

#endif // WebContext_h
