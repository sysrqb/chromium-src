/*
 * This file is part of the WebKit open source project.
 * This file has been generated by generate-bindings.pl. DO NOT MODIFY!
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#import "config.h"
#import "DOMInternal.h"

#import "DOMTestObj.h"

#import "DOMBlobInternal.h"
#import "DOMCSSRuleInternal.h"
#import "DOMCSSValueInternal.h"
#import "DOMEventInternal.h"
#import "DOMNodeInternal.h"
#import "DOMStyleSheetInternal.h"
#import "DOMTestObjInternal.h"
#import "ExceptionHandlers.h"
#import "KURL.h"
#import "TestObj.h"
#import "ThreadCheck.h"
#import "WebCoreObjCExtras.h"
#import "WebScriptObjectPrivate.h"
#import <wtf/GetPtr.h>

#define IMPL reinterpret_cast<WebCore::TestObj*>(_internal)

@implementation DOMTestObj

- (void)dealloc
{
    if (WebCoreObjCScheduleDeallocateOnMainThread([DOMTestObj class], self))
        return;

    if (_internal)
        IMPL->deref();
    [super dealloc];
}

- (void)finalize
{
    if (_internal)
        IMPL->deref();
    [super finalize];
}

- (int)readOnlyIntAttr
{
    return IMPL->readOnlyIntAttr();
}

- (NSString *)readOnlyStringAttr
{
    return IMPL->readOnlyStringAttr();
}

- (DOMTestObj *)readOnlyTestObjAttr
{
    return kit(WTF::getPtr(IMPL->readOnlyTestObjAttr()));
}

- (int)intAttr
{
    return IMPL->intAttr();
}

- (void)setIntAttr:(int)newIntAttr
{
    IMPL->setIntAttr(newIntAttr);
}

- (NSString *)stringAttr
{
    return IMPL->stringAttr();
}

- (void)setStringAttr:(NSString *)newStringAttr
{
    IMPL->setStringAttr(newStringAttr);
}

- (DOMTestObj *)testObjAttr
{
    return kit(WTF::getPtr(IMPL->testObjAttr()));
}

- (void)setTestObjAttr:(DOMTestObj *)newTestObjAttr
{
    ASSERT(newTestObjAttr);

    IMPL->setTestObjAttr(core(newTestObjAttr));
}

- (int)attrWithException
{
    return IMPL->attrWithException();
}

- (void)setAttrWithException:(int)newAttrWithException
{
    IMPL->setAttrWithException(newAttrWithException);
}

- (int)attrWithSetterException
{
    return IMPL->attrWithSetterException();
}

- (void)setAttrWithSetterException:(int)newAttrWithSetterException
{
    IMPL->setAttrWithSetterException(newAttrWithSetterException);
}

- (int)attrWithGetterException
{
    return IMPL->attrWithGetterException();
}

- (void)setAttrWithGetterException:(int)newAttrWithGetterException
{
    IMPL->setAttrWithGetterException(newAttrWithGetterException);
}

- (int)customAttr
{
    return IMPL->customAttr();
}

- (void)setCustomAttr:(int)newCustomAttr
{
    IMPL->setCustomAttr(newCustomAttr);
}

- (void)voidMethod
{
    IMPL->voidMethod();
}

- (void)voidMethodWithArgs:(int)intArg strArg:(NSString *)strArg objArg:(DOMTestObj *)objArg
{
    IMPL->voidMethodWithArgs(intArg, strArg, core(objArg));
}

- (int)intMethod
{
    return IMPL->intMethod();
}

- (int)intMethodWithArgs:(int)intArg strArg:(NSString *)strArg objArg:(DOMTestObj *)objArg
{
    return IMPL->intMethodWithArgs(intArg, strArg, core(objArg));
}

- (DOMTestObj *)objMethod
{
    return kit(WTF::getPtr(IMPL->objMethod()));
}

- (DOMTestObj *)objMethodWithArgs:(int)intArg strArg:(NSString *)strArg objArg:(DOMTestObj *)objArg
{
    return kit(WTF::getPtr(IMPL->objMethodWithArgs(intArg, strArg, core(objArg))));
}

- (void)methodWithException
{
    WebCore::ExceptionCode ec = 0;
    IMPL->methodWithException(ec);
    WebCore::raiseOnDOMError(ec);
}

- (void)customMethod
{
    IMPL->customMethod();
}

- (void)customMethodWithArgs:(int)intArg strArg:(NSString *)strArg objArg:(DOMTestObj *)objArg
{
    IMPL->customMethodWithArgs(intArg, strArg, core(objArg));
}

- (void)methodWithOptionalArg:(int)opt
{
    IMPL->methodWithOptionalArg(opt);
}

- (void)methodWithNonOptionalArgAndOptionalArg:(int)nonOpt opt:(int)opt
{
    IMPL->methodWithNonOptionalArgAndOptionalArg(nonOpt, opt);
}

- (void)methodWithNonOptionalArgAndTwoOptionalArgs:(int)nonOpt opt1:(int)opt1 opt2:(int)opt2
{
    IMPL->methodWithNonOptionalArgAndTwoOptionalArgs(nonOpt, opt1, opt2);
}

@end

WebCore::TestObj* core(DOMTestObj *wrapper)
{
    return wrapper ? reinterpret_cast<WebCore::TestObj*>(wrapper->_internal) : 0;
}

DOMTestObj *kit(WebCore::TestObj* value)
{
    { DOM_ASSERT_MAIN_THREAD(); WebCoreThreadViolationCheckRoundOne(); };
    if (!value)
        return nil;
    if (DOMTestObj *wrapper = getDOMWrapper(value))
        return [[wrapper retain] autorelease];
    DOMTestObj *wrapper = [[DOMTestObj alloc] _init];
    wrapper->_internal = reinterpret_cast<DOMObjectInternal*>(value);
    value->ref();
    addDOMWrapper(wrapper, value);
    return [wrapper autorelease];
}
