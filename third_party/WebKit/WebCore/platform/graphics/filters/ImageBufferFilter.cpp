/*
 * Copyright (C) 2009 Dirk Schulze <krit@webkit.org>
 * Copyright (C) 2009 Brent Fulgham <bfulgham@webkit.org>
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
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"

#if ENABLE(FILTERS)
#include "ImageBufferFilter.h"

#include "FloatSize.h"

namespace WebCore {

ImageBufferFilter::ImageBufferFilter(const FloatRect& sourceImageRect)
    : Filter()
    , m_sourceImageRect(sourceImageRect)
{
    setFilterResolution(FloatSize(1, 1));
}

PassRefPtr<ImageBufferFilter> ImageBufferFilter::create(const FloatRect& sourceImageRect)
{
    return adoptRef(new ImageBufferFilter(sourceImageRect));
}

} // namespace WebCore

#endif // ENABLE(FILTERS)
