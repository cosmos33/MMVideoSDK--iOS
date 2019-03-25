//
//  MMCVFaceQualityState.h
//  Pods
//
//  Created by Yu Ao on 14/03/2018.
//

typedef NS_ENUM(NSInteger, MMFaceQuality) {
    MMFaceQualityUnknown = 0,
    MMFaceQualityGood = 1,      //合格
    MMFaceQualityBadBrightness = 2,  //太暗或太亮
    MMFaceQualityBadClarity = 3,     //模糊
    MMFaceQualityBadContrast = 4,     //对比
};

typedef NS_ENUM(NSInteger, MMFaceQualityCode) {
    MMFaceQualityCodeDefault            = -1,
    MMFaceQualityCodeUnkown             = 0,
    MMFaceQualityCodePerfect            = 1,
    MMFaceQualityCodeBrighspot          = 2,
    MMFaceQualityCodeClarityError       = 3,
    MMFaceQualityCodeBrightnessError    = 4,
    MMFaceQualityCodeContrastError      = 5,
    MMFaceQualityCodeFaceOutOfScreen    = 6,
};

typedef NS_ENUM(NSInteger, MMFacePoseType) {
    MMFacePoseTypeDefault               = -1,
    MMFacePoseTypeGooodFrontalFace      = 0,
    MMFacePoseTypeSamllDegreeSideFace   = 1,
    MMFacePoseTypeBigDegreeSideFace     = 2,
};

typedef NS_ENUM(NSInteger, MMFaceOcclusionType) {
    MMFaceOcclusionTypeDefault      = -1,
    MMFaceOcclusionTypeNoOcclusion  = 0,
    MMFaceOcclusionTypeHasOcclusion = 1,
};

typedef NS_ENUM(NSInteger, MMFaceLivenessType) {
    MMFaceLivenessTypeDefault       = -1,
    MMFaceLivenessTypeNoLivesness   = 0,
    MMFaceLivenessTypeLivesness     = 1,
};

typedef NS_ENUM(NSInteger, MMFaceMotionBlurType) {
    MMFaceMotionBlurTypeDefault = -1,
    MMFaceMotionBlurTypeClear   = 0,
    MMFaceMotionBlurTypeBlur    = 1,
};
