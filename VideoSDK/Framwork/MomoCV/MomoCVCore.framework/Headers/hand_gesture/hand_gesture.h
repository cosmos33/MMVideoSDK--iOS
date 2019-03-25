#ifndef HAND_GESTURE_H_
#define HAND_GESTURE_H_
#include <vector>
#include <array>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{
    class MMCV_EXPORT HandGestureParams : public BaseParams
    {
    public:
        enum HandGestureType {
            HG_ControlRain = 0,
            HG_HandDance = 1,
            HG_DrawRainBow = 2,
            HG_DrawLine = 3,
        };
        
        HandGestureParams();
        
        bool detect_all_;
        
        // default is true
        bool ansyc_detect_;
        
        // default is HG_ControlRain
        HandGestureType handgesture_type_;
        
        //if set true, support two hands, defalut is false
        bool use2hands_;
        
        //skip frames for detection ,defalut is 2
        int skip4det_;
        
        // [false, true]
        bool debug_on_;

        // debug file destination path.
        std::string debug_output_;
        
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject hand_gesture_params, std::string cname = "com/momocv/handgesture/HandGestureParams");
#endif
    };
    
    
    class MMCV_EXPORT HandGestureInfo
    {
    public:
        HandGestureInfo();
        
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret_gesture_detect_info, std::string cname = "com/momocv/handgesture/HandGestureInfo");
#endif
        
        std::vector<MMBox> hand_gesture_results_;
    };

    class MMCV_EXPORT HandGesture
    {
    public:
        HandGesture();
        ~HandGesture();
        
    public:
        bool load_model(const std::vector<uint8_t>& model_buf, bool multi_thread = false);
        
        bool load_model(const std::string& model_path, bool multi_thread = false);
        
        bool process_frame(const MMFrame& _frame, const HandGestureParams& _hand_gesture_params, HandGestureInfo& _hand_gesture_info);
        
        bool reset();
        
    private:
        class Impl;
        std::shared_ptr<Impl> base_engine_;
        
    };
}

#endif
