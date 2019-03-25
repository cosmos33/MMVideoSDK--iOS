//
//  manga_face.h
//  beauty_momocv2
//
//  Created by spectrum on 2018/10/18.
//  Copyright © 2018年 zhangt. All rights reserved.
//

#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv {
    
    /********* INPUT MangaFaceParams *********/
    class MMCV_EXPORT MangaFaceParams
    {
    public:
        MangaFaceParams();
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject manga_face_params, std::string cname = "com/momocv/mangaface/MangaFaceParams");
#endif
        
        int image_width_; //camera's width
        int image_height_; //camera's height
        
        int manga_width_; //comic's width
        int manga_height_; //comic's height
        
        // [x0, x1..., x95, y0, y1..., y95], 96 keypoints of an individual, could be achieved from video_processor.faceinfo
        std::vector<float> landmarks96_;
        
        // [pitch, yaw, roll], eular angles of an individual, could be achieved from video_processor.faceinfo
        std::vector<float> euler_angles_;
        
        // [x0, y0, x1, y1, ...], keypoints of the manga face, of value ranging [0, 1], achieved from external files
        std::vector<float> manga_landmarks_; 
    };
    
    /********** OUTPUT MangaFaceInfo **********/
    class MMCV_EXPORT MangaFaceInfo
    {
    public:
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject manga_face_info, std::string cname = "com/momocv/mangaface/MangaFaceInfo");
#endif
        
        std::vector<float> src_points_;
        
        std::vector<float> dst_points_;
        
        std::vector<float> landmarks96_plus4_pts_; // User's 96 landmarks + 4 rotated bbox corner points
        
        std::vector<float> manga_tex_points_;
        
        std::vector<float> sq_tl; //up-left corner points of the body part of manga, [x, y]
        
        std::vector<float> sq_br; //down-right corner points of the body part of manga, [x, y]
    };
    
    /********** manga face function **********/
    class MMCV_EXPORT MangaFace
    {
    public:
        MangaFace();
        virtual ~MangaFace();

        bool manga_face(const MangaFaceParams& param,
                            MangaFaceInfo& info);
    private:
        void* manga_face_impl_;
    };
}

