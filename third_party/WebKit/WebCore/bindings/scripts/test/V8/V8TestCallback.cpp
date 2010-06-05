/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include "config.h"
#include "V8TestCallback.h"

#if ENABLE(DATABASE)

#include "ScriptExecutionContext.h"
#include "V8Class1.h"
#include "V8Class2.h"
#include "V8CustomVoidCallback.h"
#include "V8DOMString.h"

#include <wtf/Assertions.h>

namespace WebCore {

V8TestCallback::V8TestCallback(v8::Local<v8::Object> callback)
    : m_callback(v8::Persistent<v8::Object>::New(callback))
    , m_worldContext(UseCurrentWorld)
{
}

V8TestCallback::~V8TestCallback()
{
    m_callback.Dispose();
}

// Functions

bool V8TestCallback::callbackWithClass1Param(ScriptExecutionContext* context, Class1* class1Param)
{
    v8::HandleScope handleScope;

    v8::Handle<v8::Context> v8Context = toV8Context(context, m_worldContext);
    if (v8Context.IsEmpty())
        return true;

    v8::Context::Scope scope(v8Context);

    v8::Handle<v8::Value> class1ParamHandle = toV8(class1Param);
    if (class1ParamHandle.IsEmpty()) {
        CRASH();
        return true;
    }

    v8::Handle<v8::Value> argv[] = {
        class1ParamHandle
    };

    bool callbackReturnValue = false;
    return !invokeCallback(m_callback, 1, argv, callbackReturnValue, context);
}

bool V8TestCallback::callbackWithClass2Param(ScriptExecutionContext* context, Class2* class2Param, const String& strArg)
{
    v8::HandleScope handleScope;

    v8::Handle<v8::Context> v8Context = toV8Context(context, m_worldContext);
    if (v8Context.IsEmpty())
        return true;

    v8::Context::Scope scope(v8Context);

    v8::Handle<v8::Value> class2ParamHandle = toV8(class2Param);
    if (class2ParamHandle.IsEmpty()) {
        CRASH();
        return true;
    }
    v8::Handle<v8::Value> strArgHandle = toV8(strArg);
    if (strArgHandle.IsEmpty()) {
        CRASH();
        return true;
    }

    v8::Handle<v8::Value> argv[] = {
        class2ParamHandle,
        strArgHandle
    };

    bool callbackReturnValue = false;
    return !invokeCallback(m_callback, 2, argv, callbackReturnValue, context);
}

} // namespace WebCore

#endif // ENABLE(DATABASE)
