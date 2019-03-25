// 2016-10-17
// zhang.shengkai@immomo.com

#pragma once
#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>
#include <MomoCVCore/face_processor/face_processor.h>
#include <MomoCVCore/beauty/beauty_processor.h>

namespace mmcv {

    class MMCV_EXPORT VideoParams : public FaceParams
    {
    public:
        VideoParams();

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/videoprocessor/VideoParams");
#endif

        // detect expression
        // default is false
        bool expression_switch_;

        // detect eye status
        // default is false
        bool eye_classify_switch_;
        
        // beauty switch
        // default is false
        bool beauty_switch_;

        // warp type
        // default is NONE
        int warp_type_;

        // multi face beauty
        // default is false
        bool multifaces_switch_;

        // thin face
        // default is 0
        float warp_level1_;

        // big eye
        // default is 0
        float warp_level2_;

        // ext params
        XCameraWarpLevelParams warp_level_group_;

        // calc skin threshold switch
        // default is false
        bool skin_switch_;
        
        // Set this switch to "true" to turn gradual warp on
        // default is false
        bool face_warp_gradual_switch_;
        
        // the total frames for gradually warpping
        // (means gradual warp'd finish in the frames of this num, controlling the speed of gradual warp)
        // default is 10
        int face_warp_gradual_thresh_;
        
        // track switch
        // default is false
        bool track_switch_;
        
        // for live_720p 25fps
        //default is 1
        int video_processor_frame_skip_;
    };

    class MMCV_EXPORT FaceAttribute
    {
    public:
        FaceAttribute();

        float left_eye_close_prob_;

        float right_eye_close_prob_;

        // -1: unknown, 0: other, 1: duzhui, 2:smile
        int expression_;

        // skin threshold
        std::vector<int> skin_threshold_;

        // output warp landmarks
        std::vector<float> warped_landmarks68_;

        std::vector<float> warped_landmarks96_;

        std::vector<float> warped_landmarks104_;
    };

    class MMCV_EXPORT VideoInfo : public FacesInfo
    {
    public:
        VideoInfo();

#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/videoprocessor/VideoInfo");
#endif

        std::vector<FaceAttribute> faces_attributes_;

        std::vector<float> src_warp_points_;

        std::vector<float> dst_warp_points_;
        
        std::vector<float> frame_rect_; //fixed size consisting of 4 float (x, y, width, height)
    };
  
    class MMCV_EXPORT VideoProcessor
    {
    public:
        VideoProcessor();

        virtual ~VideoProcessor();

        bool load_model(const std::string& _fd_path, const std::string& _fa_path = "");

        bool load_model(const std::vector<uint8_t>& _fd_buf, const std::vector<uint8_t>& _fa_buf = std::vector<uint8_t>());

        bool process_frame(const MMFrame& _frame, const VideoParams& _params, VideoInfo& _ret);
    private:
        void* vp_impl_;
    };

}
