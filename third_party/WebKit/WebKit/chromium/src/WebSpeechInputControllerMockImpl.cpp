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
#include "WebSpeechInputControllerMockImpl.h"

#include "PlatformString.h"
#include "SpeechInputClientMock.h"

namespace WebKit {

WebSpeechInputControllerMock* WebSpeechInputControllerMock::create(WebSpeechInputListener* listener)
{
    return new WebSpeechInputControllerMockImpl(listener);
}

WebSpeechInputControllerMockImpl::WebSpeechInputControllerMockImpl(
    WebSpeechInputListener* listener)
    : m_webcoreMock(new WebCore::SpeechInputClientMock())
    , m_listener(listener)
{
}

void WebSpeechInputControllerMockImpl::setMockRecognitionResult(const WebString& result)
{
    m_webcoreMock->setRecognitionResult(result);
}

void WebSpeechInputControllerMockImpl::didCompleteRecording()
{
    m_listener->didCompleteRecording();
}

void WebSpeechInputControllerMockImpl::didCompleteRecognition()
{
    m_listener->didCompleteRecognition();
}

void WebSpeechInputControllerMockImpl::setRecognitionResult(const WebCore::String& result)
{
    m_listener->setRecognitionResult(result);
}

bool WebSpeechInputControllerMockImpl::startRecognition()
{
    return m_webcoreMock->startRecognition(this);
}

void WebSpeechInputControllerMockImpl::cancelRecognition()
{
    m_webcoreMock->cancelRecognition();
}

void WebSpeechInputControllerMockImpl::stopRecording()
{
    m_webcoreMock->stopRecording();
}

} // namespace WebKit
