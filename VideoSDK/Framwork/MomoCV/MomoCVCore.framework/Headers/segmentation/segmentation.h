#pragma once

#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{

class MMCV_EXPORT SegmentationParams : public BaseParams
{
public:
    SegmentationParams();
    virtual ~SegmentationParams();
    
    virtual void transform_params_by_device();

#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/segmentation/SegmentationParams");
#endif
    bool Parse(const std::string& params_str);
    std::string Dump();

    bool reset_;

    // [0, 1]
    // 1 is video mode, 0 is picture mode.
    // default is 1
    bool video_mode_;

    // [0, INF]
    // process frame with internal pass_frame_count_
    int pass_frame_count_;
    
    // [false, true]
    // default is false
    bool debug_on_;

    // (0, 1)
    // default is 0.125
    // 分割目标占原图的比例，默认小于原图 1/8 的目标会过滤掉
    float min_object_ratio_;
    
    // debug file destination path.
    // default is "momocv_debug.log"
    std::string debug_output_;
};

class MMCV_EXPORT SegmentationInfo
{
public:

#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/segmentation/SegmentationInfo");
#endif
    bool Parse(const std::string& params_str);
    std::string Dump();

    std::vector<uint8_t> mask_;
};

class MMCV_EXPORT Segmentation
{
public:
    Segmentation();
    ~Segmentation();

    bool load_model(const std::vector<uint8_t>& model_buf);
    bool load_model_async(const std::vector<uint8_t>& model_buf);
    bool load_model(const std::string& model_path);
    bool load_model_async(const std::string& model_path);
    
    bool load_caffe_models_raw(const std::string& proto_path, const std::string& model_path);
    bool load_half_models_raw(const std::string& proto_path, const std::string& model_path);
    bool load_mace_models_raw(const std::string& proto_path, const std::string& model_path);
    bool load_coreml_models_raw(const std::string& proto_path, bool is_compiled = true);
    
    bool load_halfmodel(const std::vector<uint8_t>& half_model_buf);
    bool load_halfmodel(const std::string& half_model_path);

    bool process_frame(const MMFrame &_frame, const SegmentationParams &params, SegmentationInfo &_ret);

    void reset();
    
private:
    void* sg_impl_;
};

}

