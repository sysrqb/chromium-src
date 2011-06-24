/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CCLayerTreeHostImpl_h
#define CCLayerTreeHostImpl_h

#include "cc/CCThread.h"
#include <wtf/RefPtr.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebCore {

// Provides scheduling infrastructure for a CCLayerTreeHostImpl
class CCLayerTreeHostImplClient  {
public:
    virtual void postDrawLayersTaskOnCCThread() = 0;
    virtual void requestFrameAndCommitOnCCThread(double frameBeginTime) = 0;

protected:
    virtual ~CCLayerTreeHostImplClient() { }
};

// CCLayerTreeHostImpl owns the CCLayerImpl tree as well as associated rendering state
class CCLayerTreeHostImpl {
    WTF_MAKE_NONCOPYABLE(CCLayerTreeHostImpl);
public:
    explicit CCLayerTreeHostImpl(CCLayerTreeHostImplClient*);
    virtual ~CCLayerTreeHostImpl();

    virtual void beginCommit();
    virtual void commitComplete();

    void drawLayers();
    virtual void drawLayersAndPresent() = 0;

    int frameNumber() const { return m_frameNumber; }

    void setNeedsRedraw();
    void setNeedsCommitAndRedraw();

    int sourceFrameNumber() const { return m_sourceFrameNumber; }
    void setSourceFrameNumber(int frameNumber) { m_sourceFrameNumber = frameNumber; }

protected:
    int m_sourceFrameNumber;
    int m_frameNumber;

private:
    CCLayerTreeHostImplClient* m_client;
    bool m_commitPending;
    bool m_redrawPending;
};

};

#endif