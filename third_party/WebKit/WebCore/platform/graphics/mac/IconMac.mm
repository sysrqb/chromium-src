/*
 * Copyright (C) 2006, 2007 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#import "config.h"
#import "Icon.h"

#import "GraphicsContext.h"
#import "LocalCurrentGraphicsContext.h"
#import "PlatformString.h"
#import <wtf/PassRefPtr.h>

namespace WebCore {

Icon::Icon()
{
}

Icon::Icon(NSImage *image)
    : m_nsImage(image)
{
    // Need this because WebCore uses AppKit's flipped coordinate system exclusively.
    [image setFlipped:YES];
}

Icon::~Icon()
{
}

PassRefPtr<Icon> Icon::newIconForFile(const String& filename)
{
    // Don't pass relative filenames -- we don't want a result that depends on the current directory.
    // Need 0U here to disambiguate String::operator[] from operator(NSString*, int)[]
    if (filename.isEmpty() || filename[0U] != '/')
        return 0;

    NSImage* image = [[NSWorkspace sharedWorkspace] iconForFile:filename];
    if (!image)
        return 0;

    return new Icon(image);
}

void Icon::paint(GraphicsContext* context, const IntRect& rect)
{
    if (context->paintingDisabled())
        return;

    LocalCurrentGraphicsContext localCurrentGC(context);

    [m_nsImage.get() drawInRect:rect
        fromRect:NSMakeRect(0, 0, [m_nsImage.get() size].width, [m_nsImage.get() size].height)
        operation:NSCompositeSourceOver fraction:1.0];
}

}
