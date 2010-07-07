/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include "GLES2Context.h"
#include "WebGLES2Context.h"
#include "WebKit.h"
#include "WebKitClient.h"
#include "WebViewImpl.h"
#include <wtf/OwnPtr.h>

// There are two levels of delegation in this file:
//
//   1. GLES2Context delegates to GLES2ContextInternal. This is done
//      so that we have some place to store data members common among
//      implementations.
//
//   2. GLES2ContextInternal delegates to an implementation of
//      WebGLES2Context. This is done so we have a place to inject an
//      implementation which creates the GL ES context.

using namespace WebKit;

namespace WebCore {

class GLES2ContextInternal {
public:
    GLES2ContextInternal() {}
    ~GLES2ContextInternal() {}

    bool initializeOnscreen(Page*);
    bool initializeOffscreen(GLES2Context*);

    WebGLES2Context* getWebGLES2Context() { return m_impl; }

private:
    WebGLES2Context* m_impl;
};

bool GLES2ContextInternal::initializeOnscreen(Page* page)
{
    ASSERT(page);
    WebViewImpl* webView = WebViewImpl::fromPage(page);
    m_impl = webView->gles2Context();
    if (!m_impl)
        return false;

    return true;
}

bool GLES2ContextInternal::initializeOffscreen(GLES2Context* parent)
{
    m_impl = webKitClient()->createGLES2Context();
    if (!m_impl)
        return false;
    if (!m_impl->initialize(0, parent ? parent->m_internal->m_impl : 0)) {
        delete m_impl;
        return false;
    }
    return true;
}

PassOwnPtr<GLES2Context> GLES2Context::createOnscreen(Page* page)
{
    GLES2ContextInternal* internal = new GLES2ContextInternal();
    if (!internal->initializeOnscreen(page)) {
        delete internal;
        return 0;
    }
    PassOwnPtr<GLES2Context> result = new GLES2Context();
    result->m_internal.set(internal);
    return result;
}

PassOwnPtr<GLES2Context> GLES2Context::createOffscreen(GLES2Context* parent)
{
    GLES2ContextInternal* internal = new GLES2ContextInternal();
    if (!internal->initializeOffscreen(parent)) {
        delete internal;
        return 0;
    }
    PassOwnPtr<GLES2Context> result = new GLES2Context();
    result->m_internal.set(internal);
    return result;
}


GLES2Context::~GLES2Context()
{
}

bool GLES2Context::makeCurrent()
{
    WebGLES2Context* webContext = m_internal->getWebGLES2Context();
    if (!webContext)
        return false;
    return webContext->makeCurrent();
}

bool GLES2Context::destroy()
{
    WebGLES2Context* webContext = m_internal->getWebGLES2Context();
    if (!webContext)
        return false;
    return webContext->destroy();
}

bool GLES2Context::swapBuffers()
{
    WebGLES2Context* webContext = m_internal->getWebGLES2Context();
    if (!webContext)
        return false;
    return webContext->swapBuffers();
}

}  // namespace WebCore
