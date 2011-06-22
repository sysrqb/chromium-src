/*
 * Copyright (C) Research In Motion Limited 2011. All rights reserved.
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

#if ENABLE(SVG) && ENABLE(SVG_ANIMATION)
#include "SVGAnimatedType.h"

#include "FloatRect.h"
#include "SVGAngle.h"
#include "SVGLength.h"
#include "SVGParserUtilities.h"

namespace WebCore {

SVGAnimatedType::SVGAnimatedType(AnimatedAttributeType type)
    : m_type(type)
{
}

SVGAnimatedType::~SVGAnimatedType()
{
    switch (m_type) {
    case AnimatedAngle:
        delete m_data.angle;
        break;
    case AnimatedLength:
        delete m_data.length;
        break;
    case AnimatedNumber:
        delete m_data.number;
        break;
    case AnimatedRect:
        delete m_data.rect;
        break;
    default:
        ASSERT_NOT_REACHED();
        break;
    }
}

PassOwnPtr<SVGAnimatedType> SVGAnimatedType::createAngle(SVGAngle* angle)
{
    ASSERT(angle);
    OwnPtr<SVGAnimatedType> animatedType = adoptPtr(new SVGAnimatedType(AnimatedAngle));
    animatedType->m_data.angle = angle;
    return animatedType.release();
}

PassOwnPtr<SVGAnimatedType> SVGAnimatedType::createLength(SVGLength* length)
{
    ASSERT(length);
    OwnPtr<SVGAnimatedType> animatedType = adoptPtr(new SVGAnimatedType(AnimatedLength));
    animatedType->m_data.length = length;
    return animatedType.release();
}

PassOwnPtr<SVGAnimatedType> SVGAnimatedType::createNumber(float* number)
{
    ASSERT(number);
    OwnPtr<SVGAnimatedType> animatedType = adoptPtr(new SVGAnimatedType(AnimatedNumber));
    animatedType->m_data.number = number;
    return animatedType.release();
}

PassOwnPtr<SVGAnimatedType> SVGAnimatedType::createRect(FloatRect* rect)
{
    ASSERT(rect);
    OwnPtr<SVGAnimatedType> animatedType = adoptPtr(new SVGAnimatedType(AnimatedRect));
    animatedType->m_data.rect = rect;
    return animatedType.release();
}

SVGAngle& SVGAnimatedType::angle()
{
    ASSERT(m_type == AnimatedAngle);
    return *m_data.angle;
}

SVGLength& SVGAnimatedType::length()
{
    ASSERT(m_type == AnimatedLength);
    return *m_data.length;
}

float& SVGAnimatedType::number()
{
    ASSERT(m_type == AnimatedNumber);
    return *m_data.number;
}

FloatRect& SVGAnimatedType::rect()
{
    ASSERT(m_type == AnimatedRect);
    return *m_data.rect;
}

String SVGAnimatedType::valueAsString()
{
    switch (m_type) {
    case AnimatedAngle:
        ASSERT(m_data.angle);
        return m_data.angle->valueAsString();
    case AnimatedLength:
        ASSERT(m_data.length);
        return m_data.length->valueAsString();
    case AnimatedNumber:
        ASSERT(m_data.number);
        return String::number(*m_data.number);
    case AnimatedRect:
        ASSERT(m_data.rect);
        return String::number(m_data.rect->x()) + ' ' + String::number(m_data.rect->y()) + ' '
             + String::number(m_data.rect->width()) + ' ' + String::number(m_data.rect->height());
    default:
        break;
    }
    ASSERT_NOT_REACHED();
    return String();
}

bool SVGAnimatedType::setValueAsString(const QualifiedName& attrName, const String& value)
{
    ExceptionCode ec = 0;
    switch (m_type) {
    case AnimatedAngle:
        ASSERT(m_data.angle);
        m_data.angle->setValueAsString(value, ec);
        break;
    case AnimatedLength:
        ASSERT(m_data.length);
        m_data.length->setValueAsString(value, SVGLength::lengthModeForAnimatedLengthAttribute(attrName), ec);
        break;
    case AnimatedNumber:
        ASSERT(m_data.number);
        parseNumberFromString(value, *m_data.number);
        break;
    case AnimatedRect:
        ASSERT(m_data.rect);
        parseRect(value, *m_data.rect);
        break;
    default:
        ASSERT_NOT_REACHED();
        break;
    }
    return !ec;
}

} // namespace WebCore

#endif // ENABLE(SVG) && ENABLE(SVG_ANIMATION)
