/*
    Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies)

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

#include <QScopedPointer>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include "webviewabstraction.h"
#include "../util.h"

class tst_CommonViewTests : public QObject {
    Q_OBJECT
private slots:
    void init();
    void cleanup();

    void baseUrl();
    void loadEmptyUrl();
    void loadEmptyPageViewVisible();
    void loadEmptyPageViewHidden();

    void show();
private:
    QScopedPointer<WebViewAbstraction> viewAbstraction;
};

void tst_CommonViewTests::init()
{
    viewAbstraction.reset(new WebViewAbstraction);
}

void tst_CommonViewTests::cleanup()
{
    viewAbstraction.reset();
}

void tst_CommonViewTests::baseUrl()
{
    // Test the url is in a well defined state when instanciating the view, but before loading anything.
    QUrl url;
    QVERIFY(viewAbstraction->url(url));
    QVERIFY(url.isEmpty());
}

void tst_CommonViewTests::loadEmptyUrl()
{
    viewAbstraction->load(QUrl());
    viewAbstraction->load(QUrl(QLatin1String("")));
}

void tst_CommonViewTests::loadEmptyPageViewVisible()
{
    viewAbstraction->show();
    loadEmptyPageViewHidden();
}

void tst_CommonViewTests::loadEmptyPageViewHidden()
{
    QSignalSpy loadStartedSpy(viewAbstraction.data(), SIGNAL(loadStarted()));

    viewAbstraction->load(QUrl::fromLocalFile(QLatin1String(TESTS_SOURCE_DIR "/html/basic_page.html")));
    QVERIFY(waitForSignal(viewAbstraction.data(), SIGNAL(loadSucceeded())));

    QCOMPARE(loadStartedSpy.size(), 1);
}

void tst_CommonViewTests::show()
{
    // This should not crash.
    viewAbstraction->show();
    QTest::qWait(200);
    viewAbstraction->hide();
}

QTEST_MAIN(tst_CommonViewTests)

#include "tst_commonviewtests.moc"
