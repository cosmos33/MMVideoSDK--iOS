// 2017-02-09
// zhang.shengkai@immomo.com

#pragma once

#include <MomoCVCore/api_base/momocv_api.h>
#include <vector>
#include <string>
#include <map>

namespace mmcv
{

class MMCV_EXPORT BodyLandmarkParams : public BaseParams
{
public:
    BodyLandmarkParams();
    virtual ~BodyLandmarkParams();

#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/bodylandmark/BodyLandmarkParams");
#endif
    

    bool Parse(const std::string& params_str);
    std::string Dump();


    // [0, 1]
    // 0 - old algorithm
    // 1 - new algorithm
    // default is 0
    int version_;

    // [false, true]
    // default is true
    bool use_tracking_;

    // [false, true]
    bool debug_on_;

    // debug file destination path.
    std::string debug_output_;
    // [false, true]
    // default is false
    bool use_cpu_only_;
    bool detect_single_frame_;
    
    // proj matrix; row major;
    // must be one of this
    // [ A  0  0  0
    //   0  B  0  0
    //   0  0  C  D
    //   0  0  E  0]
    std::vector<float> proj_matrix_;
    
};

class MMCV_EXPORT BodyLandmarkPreInfo
{
public:
    BodyLandmarkPreInfo();
    

    bool Parse(const std::string& params_str);
    std::string Dump();

    int src_width_;
    int src_height_;
    int src_format_;
    int src_step_;

    float scale_src_dst_;
    float scale_dst_src_;

    bool use_tracking;

    std::vector<float> image_data_;
};

class MMCV_EXPORT BodyLandmarkPostInfo
{
public:

#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/bodylandmark/BodyLandmarkPostInfo");
#endif
    

    bool Parse(const std::string& params_str);
    std::string Dump();


    std::vector<std::vector<MMJoint>> multi_person_;       //原始2D 人体关机点坐标
    std::vector<std::vector<float>> multi_body_3dparams_;                //3D 模型的参数(欧拉角)
    std::vector<std::vector<MMJoint>> multi_body_3dto2d_;                //3D 关键点投影到2D 图像的坐标
};

class MMCV_EXPORT BodyLandmark
{
public:
    BodyLandmark();
    ~BodyLandmark();
    
    bool load_model(const std::vector<uint8_t>& model_buf);
    bool load_model(const std::string& model_path);
    bool load_model(const uint8_t* model_vec, int model_len);
    
    bool load_model_async(const std::vector<uint8_t>& model_buf);
    bool load_model_async(const std::string& model_path);
    bool load_model_async(const uint8_t* model_vec, int model_len);
    
    bool load_coreml_model(const std::string& model_path, bool is_compiled);
    bool load_caffe_models_raw(const std::string& proto_path, const std::string& model_path);
    bool load_mace_models_raw(const std::string& proto_path, const std::string& model_path);

    bool process_frame(const MMFrame& _frame, const BodyLandmarkParams& _params, BodyLandmarkPostInfo& _result);

    //void pre_process(const MMFrame &_frame, const BodyLandmarkParams& _params, BodyLandmarkPreInfo& _result);

    void post_process(const float* _vec_data, const float* _heat_data, const BodyLandmarkPreInfo& _pre_result, BodyLandmarkPostInfo& _result);

private:
    void* person_pose_estimation_;
    bool inited_;
};
    
}
