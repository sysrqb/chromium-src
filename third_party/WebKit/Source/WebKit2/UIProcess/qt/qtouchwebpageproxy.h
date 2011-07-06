/*
 * Copyright (C) 2010, 2011 Nokia Corporation and/or its subsidiary(-ies)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef qtouchwebpageproxy_h
#define qtouchwebpageproxy_h

#include "QtWebPageProxy.h"
#include "DrawingAreaProxy.h"
#include <wtf/PassOwnPtr.h>
#include "qtouchwebpage.h"
#include "TouchViewInterface.h"

using namespace WebKit;

class QTouchWebPageProxy : public QtWebPageProxy
{
public:
    QTouchWebPageProxy(TouchViewInterface*, QWKContext*, WKPageGroupRef = 0);

    virtual bool handleEvent(QEvent*);

protected:
    virtual void paintContent(QPainter* painter, const QRect& area);

private:
    virtual PassOwnPtr<DrawingAreaProxy> createDrawingAreaProxy();
    virtual void setViewportArguments(const WebCore::ViewportArguments&);

    TouchViewInterface* touchViewInterface() const { return static_cast<TouchViewInterface*>(m_viewInterface); }
    QTouchWebPage* pageView() const { return static_cast<QTouchWebPage*>(touchViewInterface()->pageView()); }

    void touchEvent(QTouchEvent*);

    WebCore::ViewportArguments m_viewportArguments;
};

#endif /* qtouchwebpageproxy_h */