//
//  IFCachedTextRenderer.h
//  WebKit
//
//  Created by Darin Adler on Thu May 02 2002.
//  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
//

#import <IFTextRenderer.h>
#import <QD/ATSUnicodePriv.h>

typedef float IFGlyphWidth;

@interface IFCachedTextRenderer : NSObject <IFTextRenderer>
{
    NSFont *font;
    int ascent;
    int descent;
    int lineSpacing;
    
    ATSStyleGroupPtr styleGroup;
    ATSGlyphVector glyphVector;
    unsigned int widthCacheSize;
    IFGlyphWidth *widthCache;
    ATSGlyphRef *characterToGlyph;
}

- initWithFont:(NSFont *)font;

@end
