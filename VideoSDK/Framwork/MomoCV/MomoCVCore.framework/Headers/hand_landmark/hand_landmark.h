#pragma once

#include <MomoCVCore/api_base/momocv_api.h>
#include <vector>
#include <string>
#include <map>

namespace mmcv
{

class MMCV_EXPORT HandLandmarkParams : public BaseParams
{
public:
    HandLandmarkParams();
    virtual ~HandLandmarkParams();
    
#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/handlandmark/HandLandmarkParams");
#endif

    // [0, 1]
    // 0 - old algorithm
    // 1 - new algorithm
    // default is 0
    int version_;

    // [false, true]
    // default is false
    bool use_tracking_;
    
    // [false, true]
    // default is false
    bool detect3d_switch_;

    // [false, true]
    bool debug_on_;

    // debug file destination path.
    std::string debug_output_;
    
    // [false, true]
    // default is false
    bool use_cpu_only_;
    
    // [false, true]
    // default is false
    bool detect_single_frame_;

    // proj matrix; row major;
    // must be one of this
    // [ A  0  0  0
    //   0  B  0  0
    //   0  0  C  D
    //   0  0  E  0]
    std::vector<float> proj_matrix_;
};

class MMCV_EXPORT HandLandmarkInfo
{
public:
    
#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/handlandmark/HandLandmarkPostInfo");
    jfieldID fieldID_string = NULL;
    
#endif
    
    std::vector<MMJoint> single_hand_;
    std::vector<MMPoint3f> single_hand_3d_;
    std::vector<float> single_hand_3dparams_;
    std::vector<MMJoint> single_hand_3dto2d_;
};

class MMCV_EXPORT HandLandmark
{
public:
    HandLandmark();
    ~HandLandmark();

    bool load_model(const std::vector<uint8_t>& model_buf);
    bool load_model(const std::string& model_path);
    bool load_coreml_model(const std::string& model_path, bool is_compiled);
    
    bool load_model_async(const std::vector<uint8_t>& model_buf);
    bool load_model_async(const std::string& model_path);
    bool load_model_async(const uint8_t* model_vec, int model_len);
    
    bool load_caffe_models_raw(const std::string& proto_path, const std::string& model_path);
    bool load_coreml_models_raw(const std::string& model_path, bool is_compiled = true);
    bool load_mace_models_raw(const std::string& proto_path, const std::string& model_path);

    bool process_frame(const MMFrame& _frame, const HandLandmarkParams& _params, HandLandmarkInfo& _result);

private:
    void* hand_pose_estimation_;
    bool inited_;
};
    
}
