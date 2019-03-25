// 2016-11-15
// zhang.shengkai@immomo.com

#pragma once
#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{

    class MMCV_EXPORT ObjectDetectParams : public BaseParams
    {
    public:
        ObjectDetectParams();
        
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject object_detect_params, std::string cname = "com/momocv/objectdetect/ObjectDetectParams");
#endif
        bool Parse(const std::string& params_str);
        std::string Dump();
        
        bool detect_all_;
        int object_num_;
    };

    class MMCV_EXPORT ObjectDetectInfo
    {
    public:
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret_object_detect_info, std::string cname = "com/momocv/objectdetect/ObjectDetectInfo");
#endif
        
        bool Parse(const std::string& params_str);
        std::string Dump();
        std::vector<MMBox> detect_results_;
    };

    class MMCV_EXPORT ObjectDetect
    {
    public:
        ObjectDetect();
        ~ObjectDetect();

        bool load_model(const std::vector<uint8_t>& model_buf);

        bool load_model(const std::string& model_path);

        bool load_model_raw(const std::string& proto_path, const std::string& model_path);

        bool process_frame(const MMFrame &_frame, const ObjectDetectParams &_params, ObjectDetectInfo &_ret);
        
    private:
        void* od_impl_;
    };
}
