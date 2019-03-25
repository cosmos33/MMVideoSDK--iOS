//
//  MMMangaFaceProcessing.h
//  MomoCV
//
//  Created by momo783 on 2018/10/23.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@interface MMMangaFaceInputOptions : NSObject

@property (nonatomic, assign) NSInteger width;
@property (nonatomic, assign) NSInteger height;

@property (nonatomic, assign) NSInteger mangaWidth;
@property (nonatomic, assign) NSInteger mangaHeight;

@property (nonatomic, strong) NSArray<NSValue *>* landmarks96;

@property (nonatomic, strong) NSArray<NSNumber *>* eulerAngles;

@property (nonatomic, strong) NSArray<NSValue *>* mangaLandmarks;

@end

@interface MMMangaFaceProcessResult : NSObject

@property (nonatomic, strong, readonly) NSArray<NSValue *>* sourcePoints;

@property (nonatomic, strong, readonly) NSArray<NSValue *>* destinationPoints;

@property (nonatomic, strong, readonly) NSArray<NSValue *>* landmarks96Plus4CornerPoints;

@property (nonatomic, strong, readonly) NSArray<NSValue *>* mangaTexturePoints;

@property (nonatomic, readonly) CGPoint mangaUpleftCornerPoint;

@property (nonatomic, readonly) CGPoint mangaDownrightCornerPoint;


@end

@interface MMMangaFaceProcessing : NSObject

- (nullable MMMangaFaceProcessResult *)process:(MMMangaFaceInputOptions *)options;

@end

NS_ASSUME_NONNULL_END
