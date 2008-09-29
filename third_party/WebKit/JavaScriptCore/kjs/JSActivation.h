/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#ifndef JSActivation_h
#define JSActivation_h

#include "CodeBlock.h"
#include "JSVariableObject.h"
#include "RegisterFile.h"
#include "SymbolTable.h"
#include "nodes.h"

namespace JSC {

    class Arguments;
    class Register;
    
    class JSActivation : public JSVariableObject {
        typedef JSVariableObject Base;
    public:
        JSActivation(ExecState* exec, PassRefPtr<FunctionBodyNode>, Register*);
        virtual ~JSActivation();
        
        virtual void mark();

        virtual bool isActivationObject() const;
        virtual bool isDynamicScope() const;

        virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);

        inline void uncheckedSymbolTableGet(int index, PropertySlot& slot)
        {
            slot.setRegisterSlot(&registerAt(index));
        }

        inline JSValue* uncheckedSymbolTableGetValue(int index)
        {
            return registerAt(index).getJSValue();
        }

        virtual void put(ExecState*, const Identifier&, JSValue*, PutPropertySlot&);

        inline void uncheckedSymbolTablePut(int index, JSValue* value)
        {
            registerAt(index) = value;
        }

        virtual void putWithAttributes(ExecState*, const Identifier&, JSValue*, unsigned attributes);
        virtual bool deleteProperty(ExecState*, const Identifier& propertyName);

        virtual JSObject* toThisObject(ExecState*) const;

        void copyRegisters();
        
        virtual const ClassInfo* classInfo() const { return &info; }
        static const ClassInfo info;

        NEVER_INLINE Arguments* createArgumentsObject(ExecState*);

    private:
        struct JSActivationData : public JSVariableObjectData {
            JSActivationData(PassRefPtr<FunctionBodyNode> functionBody_, Register* registers)
                : JSVariableObjectData(&functionBody_->symbolTable(), registers)
                , functionBody(functionBody_)
            {
            }

            RefPtr<FunctionBodyNode> functionBody; // Owns the symbol table and code block
        };
        
        static JSValue* argumentsGetter(ExecState*, const Identifier&, const PropertySlot&);
        NEVER_INLINE PropertySlot::GetValueFunc getArgumentsGetter();

        JSActivationData* d() const { return static_cast<JSActivationData*>(JSVariableObject::d); }
    };
    
    inline void JSActivation::copyRegisters()
    {
        ASSERT(!d()->registerArray);

        size_t numParametersMinusThis = d()->functionBody->generatedByteCode().numParameters - 1;
        size_t numVars = d()->functionBody->generatedByteCode().numVars;
        size_t numLocals = numVars + numParametersMinusThis;

        if (!numLocals)
            return;

        int registerOffset = numParametersMinusThis + RegisterFile::CallFrameHeaderSize;
        size_t registerArraySize = numLocals + RegisterFile::CallFrameHeaderSize;

        Register* registerArray = copyRegisterArray(d()->registers - registerOffset, registerArraySize);
        setRegisters(registerArray + registerOffset, registerArray);
    }

} // namespace JSC

#endif // JSActivation_h
