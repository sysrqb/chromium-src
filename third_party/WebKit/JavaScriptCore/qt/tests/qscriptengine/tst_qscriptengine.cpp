/*
    Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies)

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
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "qscriptengine.h"
#include "qscriptprogram.h"
#include "qscriptvalue.h"
#include <QtTest/qtest.h>

class tst_QScriptEngine : public QObject {
    Q_OBJECT

public:
    tst_QScriptEngine() {}
    virtual ~tst_QScriptEngine() {}

public slots:
    void init() {}
    void cleanup() {}

private slots:
    void evaluate();
    void collectGarbage();
    void nullValue();
    void undefinedValue();
    void evaluateProgram();
};

/* Evaluating a script that throw an unhandled exception should return an invalid value. */
void tst_QScriptEngine::evaluate()
{
    QScriptEngine engine;
    QVERIFY2(engine.evaluate("1+1").isValid(), "the expression should be evaluated and an valid result should be returned");
    QVERIFY2(engine.evaluate("ping").isValid(), "Script throwing an unhandled exception should return an exception value");
}

/* Test garbage collection, at least try to not crash. */
void tst_QScriptEngine::collectGarbage()
{
    QScriptEngine engine;
    QScriptValue foo = engine.evaluate("( function foo() {return 'pong';} )");
    QVERIFY(foo.isFunction());
    engine.collectGarbage();
    QCOMPARE(foo.call().toString(), QString::fromAscii("pong"));
}

void tst_QScriptEngine::nullValue()
{
    QScriptEngine engine;
    QScriptValue value = engine.nullValue();
    QVERIFY(value.isValid());
    QVERIFY(value.isNull());
}

void tst_QScriptEngine::undefinedValue()
{
    QScriptEngine engine;
    QScriptValue value = engine.undefinedValue();
    QVERIFY(value.isValid());
    QVERIFY(value.isUndefined());
}

void tst_QScriptEngine::evaluateProgram()
{
    QScriptEngine eng;
    {
        QString code("1 + 2");
        QString fileName("hello.js");
        int lineNumber = 123;
        QScriptProgram program(code, fileName, lineNumber);
        QVERIFY(!program.isNull());
        QCOMPARE(program.sourceCode(), code);
        QCOMPARE(program.fileName(), fileName);
        QCOMPARE(program.firstLineNumber(), lineNumber);

        QScriptValue expected = eng.evaluate(code);
        for (int x = 0; x < 10; ++x) {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(ret.equals(expected));
        }

        // operator=
        QScriptProgram sameProgram = program;
        QVERIFY(sameProgram == program);
        QVERIFY(eng.evaluate(sameProgram).equals(expected));

        // copy constructor
        QScriptProgram sameProgram2(program);
        QVERIFY(sameProgram2 == program);
        QVERIFY(eng.evaluate(sameProgram2).equals(expected));

        QScriptProgram differentProgram("2 + 3");
        QVERIFY(differentProgram != program);
        QVERIFY(!eng.evaluate(differentProgram).equals(expected));
    }

    // Program that accesses variable in the scope
    {
        QScriptProgram program("a");
        QVERIFY(!program.isNull());
        {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(ret.isError());
            QCOMPARE(ret.toString(), QString::fromLatin1("ReferenceError: Can't find variable: a"));
        }
        {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(ret.isError());
        }
        eng.evaluate("a = 456");
        {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(!ret.isError());
            QCOMPARE(ret.toNumber(), 456.0);
        }
    }

    // Program that creates closure
    {
        QScriptProgram program("(function() { var count = 0; return function() { return count++; }; })");
        QVERIFY(!program.isNull());
        QScriptValue createCounter = eng.evaluate(program);
        QVERIFY(createCounter.isFunction());
        QScriptValue counter = createCounter.call();
        QVERIFY(counter.isFunction());
        {
            QScriptValue ret = counter.call();
            QVERIFY(ret.isNumber());
        }
        QScriptValue counter2 = createCounter.call();
        QVERIFY(counter2.isFunction());
        QVERIFY(!counter2.equals(counter));
        {
            QScriptValue ret = counter2.call();
            QVERIFY(ret.isNumber());
        }
    }

    // Same program run in different engines
    {
        QString code("1 + 2");
        QScriptProgram program(code);
        QVERIFY(!program.isNull());
        double expected = eng.evaluate(program).toNumber();
        for (int x = 0; x < 2; ++x) {
            QScriptEngine eng2;
            for (int y = 0; y < 2; ++y) {
                double ret = eng2.evaluate(program).toNumber();
                QCOMPARE(ret, expected);
            }
        }
    }

    // No program
    {
        QScriptProgram program;
        QVERIFY(program.isNull());
        QScriptValue ret = eng.evaluate(program);
        QVERIFY(!ret.isValid());
    }
}

QTEST_MAIN(tst_QScriptEngine)
#include "tst_qscriptengine.moc"
