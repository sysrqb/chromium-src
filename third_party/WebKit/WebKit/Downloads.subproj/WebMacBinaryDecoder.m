//
//  WebMacBinaryDecoder.m
//
//  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
//

// This decoder decodes MacBinary II and might also work for MacBinary III.
// There's also MacBinary I, which we do not attempt to support.

#import <WebKit/WebMacBinaryDecoder.h>

#import <WebFoundation/WebAssertions.h>
#import <WebFoundation/WebNSFileManagerExtras.h>

#import <WebKit/WebDownloadDecoder.h>

#import "crc16.h"

#define HEADER_SIZE 128

@implementation WebMacBinaryDecoder

// Returns YES if the decoder can decode headerData, NO otherwise.
// Header data is the first 8KB or larger chunk of received data.
+ (BOOL)canDecodeHeaderData:(NSData *)headerData
{
    if ([headerData length] < HEADER_SIZE) {
        return NO;
    }
    const u_int8_t *header = [headerData bytes];

    // Version must be 0, also the zero fill bytes at 74 and 82,
    // and the last two bytes of the header.
    if (header[0] || header[74] || header[82] || header[126] || header[127]) {
        return NO;
    }

    // Name length must be a reasonable value (between 1 and 63).
    if (!header[1] || header[1] > 63) {
        return NO;
    }

    // And the CRC is the most important check.
    if (((header[124] << 8) | header[125]) == CRC16(header, 124, 0)) {
        // CRC matches, so we have MacBinary II or III.
        
        // Version 129 is MacBinary II, and MacBinary III is compatible.
        // If we see a higher value here, it's something newer that we can't handle.
        if (header[123] > 129) {
            return NO;
        }
        
        return YES;
    }
    
    // MacBinary I doesn't have a CRC. So now we have to see if we have a MacBinary I file.

    // Bytes 99-127 must be 0 in MacBinary I (already checked 126 and 127 above).
    int i;
    for (i = 99; i <= 125; i++) {
        if (header[i]) {
            return NO;
        }
    }
    
    // FIXME: The specification recommends also reality-checking the file lengths.

    return YES;
}

// Decodes data and sets dataForkData and resourceForkData with the decoded data.
// dataForkData and/or resourceForkData and can be set to nil if there is no data to decode.
// This method will be called repeatedly with every chunk of received data. 
// Returns YES if no errors have occurred, NO otherwise.
- (BOOL)decodeData:(NSData *)data dataForkData:(NSData **)dataForkData resourceForkData:(NSData **)resourceForkData
{
    ASSERT(data);
    ASSERT([data length]);
    ASSERT(dataForkData);
    ASSERT(resourceForkData);
    ASSERT(_offset + [data length] >= HEADER_SIZE);

    *dataForkData = nil;
    *resourceForkData = nil;
    
    int dataLength = [data length];
    
    // Handle the header by extracting the fields we want, in an endian-independent way.
    if (_offset == 0) {
        const u_int8_t *header = [data bytes];
        
        ASSERT(header[1] < sizeof(_name));
        memcpy(_name, header + 1, header[1] + 1);
        
        _fileType = (((((header[65] << 8) | header[66]) << 8) | header[67]) << 8) | header[68];
        _fileCreator = (((((header[69] << 8) | header[70]) << 8) | header[71]) << 8) | header[72];
        _dataForkLength = (((((header[83] << 8) | header[84]) << 8) | header[85]) << 8) | header[86];
        _resourceForkLength = (((((header[87] << 8) | header[88]) << 8) | header[89]) << 8) | header[90];
        _creationDate = (((((header[91] << 8) | header[92]) << 8) | header[93]) << 8) | header[94];
        _modificationDate = (((((header[95] << 8) | header[96]) << 8) | header[97]) << 8) | header[98];
        _finderFlags = (header[73] << 8) | header[101];
        _extendedFinderFlags = header[107];

        // Clear reserved bits or bits not applicable after transfer as defined in Finder.h.
        _finderFlags &= kColor | kIsShared | kHasCustomIcon | kIsStationery | kHasBundle | kIsAlias;
        _extendedFinderFlags &= kExtendedFlagHasCustomBadge | kExtendedFlagHasRoutingInfo;
        
        // MacBinary III.
        if (header[102] == 'm' && header[103] == 'B' && header[104] == 'I' && header[105] == 'N') {
            _scriptCode = header[106];
        }
    }
    
    int dataForkStart = HEADER_SIZE;
    int dataForkEnd = dataForkStart + _dataForkLength;
    int resourceForkStart = (dataForkEnd + 0x7F) & ~0x7F;
    int resourceForkEnd = resourceForkStart + _resourceForkLength;

    // Check for a piece of available data fork.
    if (_dataForkLength && _offset < dataForkEnd && _offset + dataLength > dataForkStart) {
        int start = MAX(dataForkStart - _offset, 0);
        int end = MIN(dataForkEnd - _offset, dataLength);
        ASSERT(end > start);
        *dataForkData = [data subdataWithRange:NSMakeRange(start, end - start)];
    }

    // Check for a piece of available resource fork.
    if (_resourceForkLength && _offset < resourceForkEnd && _offset + dataLength > resourceForkStart) {
        int start = MAX(resourceForkStart - _offset, 0);
        int end = MIN(resourceForkEnd - _offset, dataLength);
        ASSERT(end > start);
        *resourceForkData = [data subdataWithRange:NSMakeRange(start, end - start)];
    }
    
    _offset += dataLength;

    return YES;
}

// Returns YES if decoding successfully finished, NO otherwise.
- (BOOL)finishDecoding
{
    int dataForkStart = HEADER_SIZE;
    int dataForkEnd = dataForkStart + _dataForkLength;
    int resourceForkStart = (dataForkEnd + 0x7F) & ~0x7F;
    int resourceForkEnd = resourceForkStart + _resourceForkLength;
    return _offset >= resourceForkEnd;
}

// Returns a dictionary of 4 file attributes. The attributes (as defined in NSFileManager.h) are:
// NSFileModificationDate, NSFileHFSCreatorCode, NSFileHFSTypeCode, NSFileCreationDate
// fileAttributes is called after finishDecoding.
- (NSDictionary *)fileAttributes
{
    ASSERT(_offset >= HEADER_SIZE);
    
    return [NSDictionary dictionaryWithObjectsAndKeys:
        [NSDate dateWithTimeIntervalSinceReferenceDate:kCFAbsoluteTimeIntervalSince1904 + _creationDate], NSFileCreationDate,
        [NSDate dateWithTimeIntervalSinceReferenceDate:kCFAbsoluteTimeIntervalSince1904 + _modificationDate], NSFileModificationDate,
        [NSNumber numberWithUnsignedLong:_fileType], NSFileHFSTypeCode,
        [NSNumber numberWithUnsignedLong:_fileCreator], NSFileHFSCreatorCode,
        [NSNumber numberWithUnsignedShort:_finderFlags], WebFinderFlags,
        [NSNumber numberWithUnsignedShort:_extendedFinderFlags], WebExtendedFinderFlags,
        nil];
}

- (NSString *)filename
{
    // FIXME: We pass _scriptCode in here, but does CFString know how to handle all the script
    // codes? What about when we have a bad script code? Is it OK to just return nil here?
    return [(NSString *)CFStringCreateWithPascalString(NULL, _name, _scriptCode) autorelease];
}

@end
