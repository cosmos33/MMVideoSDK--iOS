//
//  rff.h
//  beauty_momocv2
//
//  Created by spectrum on 2018/4/24.
//  Copyright © 2018年 zhangt. All rights reserved.
//

#include <MomoCVCore/api_base/momocv_api.h>
#include <MomoCVCore/face_processor/face_processor.h>

namespace mmcv {
    
    /********** EstFaceParams **********/
    class MMCV_EXPORT EFParams
    {
    public:
        EFParams();
        
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/beauty/EFParams");
#endif
        
        std::vector<float> EFRect;
        
        float EFRollDeg;
    };
    
    class MMCV_EXPORT EstFaceParams : public BaseParams
    {
    public:
        EstFaceParams();
        
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/beauty/EstFaceParams");
#endif
        
        int image_width_;
        
        int image_height_;
        
        // containing Rect & Roll Degree
        EFParams EFParamsGroup;
    };
    
    /********** ResFaceParams **********/    
    class MMCV_EXPORT ResFaceParams : public BaseParams
    {
    public:
        ResFaceParams();
        
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/beauty/ResFaceParams");
#endif
        
        // containing Rect & Roll Degree
        SingleFaceInfo SingleFacesGroup;
    };
    
    /********** ResFaceInfo **********/
    class MMCV_EXPORT ResFaceInfo
    {
    public:
        
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/beauty/ResFaceInfo");
#endif
        
        SingleFaceInfo SingleFacesAttr_;
    };

    /********** RotateFace **********/
    class MMCV_EXPORT RotateFace
    {
    public:
        RotateFace();
        virtual ~RotateFace();

        bool rotate_face(const MMFrame& frame_src,
                                const EstFaceParams& EFParams,
                                MMFrame& frames_ret);
        
        bool restore_rotated_face(const EstFaceParams& EFParams,
                                         const ResFaceParams& RTParams,
                                         ResFaceInfo& info);
    private:
        void* rotate_face_impl_;
        void* restore_rotated_face_impl_;
    };
}

