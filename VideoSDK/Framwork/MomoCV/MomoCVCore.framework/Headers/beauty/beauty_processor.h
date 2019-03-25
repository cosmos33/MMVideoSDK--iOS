#pragma once
#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>
#include <MomoCVCore/face_processor/face_processor.h>

namespace mmcv {

    enum WarpType {
        NONE = 0,
        THIN_FACE_BIG_EYE = 1,
        SHORT_FACE_BIG_EYE = 2,
        AWL_FACE_BIG_EYE = 3,
        BIG_HEAD = 4,

        TINY_FACE_BIG_EYE = 5,
        SMALL_FACE_BIG_EYE = 6,
        RECTANGLE_FACE_SMALL_FEATURE = 7,
        PEAR_FACE_SMALL_EYE_BIG_MOUTH = 8,
        THIN_FACE_BIG_EYE1 = 9,
        XCAMERA = 10,
        THIN_FACE_BIG_EYE2 = 11,
        ROUND_FACE = 12,
        NEW_BIG_HEAD = 13,
        FAT_FACE_FAT_LIP = 14,
        WARP_TYPE_SIZE,
    };
/**************************** Face warping ******************************/
    class MMCV_EXPORT XCameraWarpLevelParams
    {
    public:
        XCameraWarpLevelParams();

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/beauty/XCameraWarpLevelParams");
#endif

        bool Parse(const std::string& params_str);
        std::string Dump();

        // Params below means the corresponding facial part's warping strengh.
        // when setting their value to 0, there's no related warping effect
        float face_width_;    // [-1, 1], width of face outer contour's horizonal warp(outer landmarks of each face),
        // including eyebrows, nose and mouth
        
        float chin_size_;     // [-1.3, 1.8], 4-14 landmark points' circular warp from inner center
        
        float chin_length_;   // [-0.1, 0.1], 4-14 landmark points' vertical warp(ups/downs) to adjust chin's length
        
        float chin_width_;    // [-1.2, 1.2], 1-17 landmark points' horizonal warp(wider/narrower)
        // to adjust chin's width
        
        float eye_size_;      // [-1.2, 1.6], 39-62 landmark points' circular warp from each eye's center
        
        float nose_lift_;     // [-1.5, 1.5], 63-66, 71-74 landmark points' vertical warp(ups/downs)
        // from 63 and 74 landmark points as their centers to lift up or down
        
        float lip_thickness_; // [-2, 2], 76-95 lip landmark points' vertical warp(ups/downs)
        // from various center points of mouth's landmark points
        
        float lip_size_;      // [-2, 2], 76-95 lip landmark points' circular warp
        // from one center point of mouth's landmark points
        
        float eye_tilt_ratio_; // [-0.2 ,0.18], radian value for eyes' tilt,
        // 39-62 landmark points' rotation from each eye's center
        
        float eye_distance_;   // [-4.8, 4.8], eyes' distance from each other
        
        float nose_size_; // [-0.6, 0.6], whole nose's size, both vertical and horizonal
        
        float nose_width_; // [-0.2, 0.2], root's width of nose
        
        float nose_ridge_width_; // [-0.3, 0.3], nose's ridge width
        
        float nose_tip_size_; // [-0.38, 0.28], nose's tip size
        
        float forehead_ud_; // [-0.1, 0.1], forehead's ups & downs
        
        float mm_thin_face_; // [0, 1], warp effect to make face thinner, same as the warping effect used in Momo
        
        float brows_thickness_; // [-1, 1], brows' vertical thickness, do nothing when set to 0
        
        float short_face_; // [0, 1], special warp effect to make face comical shorter
        
        float fat_face_; // [0, 1], special warp effect to make face fatter
        
    };
    
    class MMCV_EXPORT BeautyWarpParams : public BaseParams
    {
    public:
        BeautyWarpParams();

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/beauty/BeautyWarpParams");
#endif
        
        bool Parse(const std::string& params_str);
        std::string Dump();

        std::vector<std::vector<float> > landmarks104_;
        
        std::vector<std::vector<float> > euler_angle_;

        int image_width_;

        int image_height_;

        bool is_stable_;
        
        // warp type
        int warp_type_;
        
        // multi face beauty
        bool multifaces_switch_;
        
        // thin face
        //roundface warp_level1_ should set [0, 1.0]
        std::vector<float> warp_level1_;

        // big eye
        std::vector<float> warp_level2_;
        
        // ext params
        std::vector<XCameraWarpLevelParams> warp_level_group_;
        
        
        // 脸部变形渐变开关
        // Set this switch to "true" to turn gradual warp on
        bool face_warp_gradual_switch_;
        
        // 脸部渐变总帧数(表示渐变在这个数量的帧内完成, 控制渐变的快慢)
        // the total frames for gradually warpping
        // (means gradual warp'd finish in the frames of this num, controlling the speed of gradual warp)
        int face_warp_gradual_thresh_;
    };
/**************************** Facial beauty info ******************************/
    class MMCV_EXPORT BeautyWarpInfo
    {
    public:

#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/beauty/BeautyWarpInfo");
#endif
        
        bool Parse(const std::string& params_str);
        std::string Dump();

        std::vector<std::vector<float> > warped_landmarks68_;

        std::vector<std::vector<float> > warped_landmarks96_;

        std::vector<std::vector<float> > warped_landmarks104_;

        std::vector<float> src_warp_points_;

        std::vector<float> dst_warp_points_;
        
        std::vector<float> frame_rect_; //(x, y, width, height)
    };

    /**************************** Body warping ******************************/
    class MMCV_EXPORT BodyWarpGroup
    {
    public:
        BodyWarpGroup();
        
#ifdef BUILD_JNI
        void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/beauty/BodyWarpGroup");
#endif
        
        bool Parse(const std::string& params_str);
        std::string Dump();
        
        // Params below means the corresponding facial part's warping strengh.
        // when setting their value to 0, there's no related warping effect
        float body_width_;    // [0, 1], width of upper body
        
        float up_body_scale_factor_; //上半身与下半身系数的比值
        
        float legs_length_;     // [0, 1], 4-14 landmark points' circular warp from inner center
    };
    
    class MMCV_EXPORT BodyWarpParams : public BaseParams
    {
    public:
        BodyWarpParams();
        
#ifdef BUILD_JNI
        void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/beauty/BodyWarpParams");
#endif

        bool Parse(const std::string& params_str);
        std::string Dump();
        
        std::vector<std::vector<MMJoint> > body_keypoints_;
        
        
        int image_width_;
        
        int image_height_;
        
        bool body_warp_gradual_switch_;
        
        float body_warp_gradual_thresh_; // [0, 1]
        
        std::vector<BodyWarpGroup> body_warp_params_group_;
    };
    
    /**************************** Body info ******************************/
    class MMCV_EXPORT BodyWarpInfo
    {
    public:
        
#ifdef BUILD_JNI
        void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/beauty/BodyWarpInfo");
#endif
        
        bool Parse(const std::string& params_str);
        std::string Dump();
  
//        std::vector<std::vector<float> > warped_body_key_points14_;
        
        std::vector<float> src_warp_points_;
        
        std::vector<float> dst_warp_points_;
    };
    
    
    
/**************************** Both face & body ******************************/
    class MMCV_EXPORT BeautyProcessor
    {
    public:
        BeautyProcessor();
        virtual ~BeautyProcessor();

        bool get_warp_key_points(const BeautyWarpParams& _params, BeautyWarpInfo& _info);
        
        bool get_warped_body_points(const BodyWarpParams& _params, BodyWarpInfo& _info);

        bool get_skin_threshold(const MMFrame &_frame, const std::vector<std::vector<float> > landmarks_96, std::vector<std::vector<int> >& skin_threshold);
    private:
        void* bp_impl_;

    };
}
