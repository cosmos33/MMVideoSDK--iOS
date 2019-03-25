//
//  MMCVCGImageUtilities.h
//  MomoCV
//
//  Created by Yu Ao on 2018/5/18.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>

NS_ASSUME_NONNULL_BEGIN

/// Create a CVPixelBuffer with pixel format type kCVPixelFormatType_32BGRA from a CGImage.
FOUNDATION_EXPORT CVReturn MMCVCreateCVPixelBufferFromCGImage(CGImageRef image, CF_RETURNS_RETAINED _Nullable CVPixelBufferRef * _Nonnull pixelBufferOut);

NS_ASSUME_NONNULL_END
