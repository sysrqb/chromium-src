/*
 * Copyright (C) 2005 Apple Computer, Inc.  All rights reserved.
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


#include "config.h"
#import "QuartzSupport.h"

#import "KCanvasMatrix.h"
#import "KCanvasResourcesQuartz.h"
#import "KRenderingFillPainter.h"
#import "KRenderingStrokePainter.h"
#import "kxmlcore/Assertions.h"

#import "SVGRenderStyle.h"


CFStringRef CFStringFromCGAffineTransform(CGAffineTransform t)
{
    return CFStringCreateWithFormat(0, 0, CFSTR("a: %f b: %f c: %f d: %f tx: %f ty: %f"), t.a, t.b, t.c, t.d, t.tx, t.ty);
}

CGAffineTransform CGAffineTransformMakeMapBetweenRects(CGRect source, CGRect dest)
{
    CGAffineTransform transform = CGAffineTransformMakeTranslation(dest.origin.x - source.origin.x, dest.origin.y - source.origin.y);
    transform = CGAffineTransformScale(transform, dest.size.width/source.size.width, dest.size.height/source.size.height);
    return transform;
}

typedef struct {
    CGAffineTransform transform;
    CGMutablePathRef resultPath;
} CGPathTransformCallbackData;

void CGPathTransformCallback(void *info, const CGPathElement *element)
{
    CGPathTransformCallbackData *data = (CGPathTransformCallbackData *)info;
    CGAffineTransform transform = data->transform;
    CGMutablePathRef resultPath = data->resultPath;

    CGPoint *points = element->points;

    switch (element->type) {
    case kCGPathElementMoveToPoint:
        CGPathMoveToPoint(resultPath, &transform, points[0].x, points[0].y);
        break;
    case kCGPathElementAddLineToPoint:
        CGPathAddLineToPoint(resultPath, &transform, points[0].x, points[0].y);
        break;
    case kCGPathElementAddQuadCurveToPoint:
        CGPathAddQuadCurveToPoint(resultPath, &transform, points[0].x, points[0].y, points[1].x, points[1].y);
        break;
    case kCGPathElementAddCurveToPoint:
        CGPathAddCurveToPoint(resultPath, &transform, points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y);
    case kCGPathElementCloseSubpath:
        CGPathCloseSubpath(resultPath);
    }
}

// FIXME: HACK this should be replace by a call to
// CGPathAddPath(<#CGMutablePathRef path1#>,<#const CGAffineTransform * m#>,<#CGPathRef path2#>)
CGPathRef CGPathApplyTransform(CGPathRef path, CGAffineTransform transform)
{
    CGPathTransformCallbackData data;
    data.transform = transform;
    data.resultPath = CGPathCreateMutable();
    CGPathApply(path, &data, CGPathTransformCallback);
    return data.resultPath;
}

void applyStrokeStyleToContext(CGContextRef context, KSVG::KCanvasRenderingStyle *style)
{
    /* Shouldn't all these be in the stroke painter? */
    CGContextSetLineWidth(context, style->strokePainter()->strokeWidth());

    KCCapStyle capStyle = style->strokePainter()->strokeCapStyle();
    CGContextSetLineCap(context, CGLineCapFromKC(capStyle));

    KCJoinStyle joinStyle = style->strokePainter()->strokeJoinStyle();
    CGContextSetLineJoin(context, CGLineJoinFromKC(joinStyle));

    CGContextSetMiterLimit(context, style->strokePainter()->strokeMiterLimit());

    KCDashArray dashes = style->strokePainter()->dashArray();
    if (dashes.count()) {
        size_t dashCount = dashes.count();
        float *lengths = (float *)malloc(dashCount * sizeof(float));
        for (unsigned int x = 0; x < dashCount; x++)
            lengths[x] = dashes[x];
        CGContextSetLineDash(context, style->strokePainter()->dashOffset(), lengths, dashes.count());
        free(lengths);
    }
}

void CGPathToCFStringApplierFunction(void *info, const CGPathElement *element)
{
    CFMutableStringRef string = (CFMutableStringRef)info;
    CFStringRef typeString = CFSTR("");
    CGPoint *points = element->points;
    switch(element->type) {
    case kCGPathElementMoveToPoint:
        CFStringAppendFormat(string, 0, CFSTR("M%.2f,%.2f"), points[0].x, points[0].y);
        break;
    case kCGPathElementAddLineToPoint:
        CFStringAppendFormat(string, 0, CFSTR("L%.2f,%.2f"), points[0].x, points[0].y);
        break;
    case kCGPathElementAddQuadCurveToPoint:
        CFStringAppendFormat(string, 0, CFSTR("Q%.2f,%.2f,%.2f,%.2f"),
                points[0].x, points[0].y, points[1].x, points[1].y);
        break;
    case kCGPathElementAddCurveToPoint:
        CFStringAppendFormat(string, 0, CFSTR("C%.2f,%.2f,%.2f,%.2f,%.2f,%.2f"),
                points[0].x, points[0].y, points[1].x, points[1].y,
                points[2].x, points[2].y);
        break;
    case kCGPathElementCloseSubpath:
        typeString = CFSTR("X"); break;
    }
}

CFStringRef CFStringFromCGPath(CGPathRef path)
{
    if (!path)
        return 0;

    CFMutableStringRef string = CFStringCreateMutable(NULL, 0);
    CGPathApply(path, string, CGPathToCFStringApplierFunction);

    return string;
}

