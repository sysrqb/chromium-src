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

#include "TestController.h"

#include <fcntl.h>
#include <io.h>
#include <WebKit2/WKStringCF.h>
#include <wtf/RetainPtr.h>

namespace WTR {

#if !defined(NDEBUG) && (!defined(DEBUG_INTERNAL) || defined(DEBUG_ALL))
const LPWSTR testPluginDirectoryName = L"TestNetscapePlugin_Debug";
#else
const LPWSTR testPluginDirectoryName = L"TestNetscapePlugin";
#endif

void TestController::platformInitialize()
{
    _setmode(1, _O_BINARY);
    _setmode(2, _O_BINARY);
}

void TestController::initializeInjectedBundlePath()
{
    CFStringRef exeContainerPath = CFURLCopyFileSystemPath(CFURLCreateCopyDeletingLastPathComponent(0, CFBundleCopyExecutableURL(CFBundleGetMainBundle())), kCFURLWindowsPathStyle);
    CFMutableStringRef bundlePath = CFStringCreateMutableCopy(0, 0, exeContainerPath);
#ifdef DEBUG_ALL
    CFStringAppendCString(bundlePath, "\\InjectedBundle_debug.dll", kCFStringEncodingWindowsLatin1);
#else
    CFStringAppendCString(bundlePath, "\\InjectedBundle.dll", kCFStringEncodingWindowsLatin1);
#endif
    
    m_injectedBundlePath.adopt(WKStringCreateWithCFString(bundlePath));
}

void TestController::initializeTestPluginDirectory()
{
    RetainPtr<CFURLRef> bundleURL(AdoptCF, CFBundleCopyExecutableURL(CFBundleGetMainBundle()));
    RetainPtr<CFURLRef> bundleDirectoryURL(AdoptCF, CFURLCreateCopyDeletingLastPathComponent(0, bundleURL.get()));
    RetainPtr<CFStringRef> testPluginDirectoryNameString(AdoptCF, CFStringCreateWithCharacters(0, reinterpret_cast<const UniChar*>(testPluginDirectoryName), wcslen(testPluginDirectoryName)));
    RetainPtr<CFURLRef> testPluginDirectoryURL(AdoptCF, CFURLCreateCopyAppendingPathComponent(0, bundleDirectoryURL.get(), testPluginDirectoryNameString.get(), true));
    RetainPtr<CFStringRef> testPluginDirectoryPath(AdoptCF, CFURLCopyFileSystemPath(testPluginDirectoryURL.get(), kCFURLWindowsPathStyle));
    m_testPluginDirectory.adopt(WKStringCreateWithCFString(testPluginDirectoryPath.get()));
}

} // namespace WTR
