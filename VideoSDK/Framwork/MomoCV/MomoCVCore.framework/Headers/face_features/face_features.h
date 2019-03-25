#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{

struct MMCV_EXPORT Feature
{
    std::vector<uint8_t> features_;
    /*
       -1: has not extract features
        0: unknown, empty img
        1: perfect
        2: brighspot
        3: clarity error
        4: brightness error
        5: contrast error
    */
    int quality_;
};

class MMCV_EXPORT FaceFeaturesParams
{
public:
    enum BigFeatureVersion { V0 = 0x5f3759df, V1 = 0x5f3759ee , V2 = 0x5f3759ab};

    FaceFeaturesParams();

#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/facefeatures/FaceFeaturesParams");
#endif

    int big_features_version_;

    bool feature_strict_;

    //default is true;
    // if you have ues FaceQuality before extract feature, please set false
    bool quality_detect_switch_;

    std::vector<std::vector<float> > multi_landmarks_96_;
    std::vector<int> multi_tracking_id_;
    std::vector<std::vector<float> > multi_euler_angles_ ;
    std::vector<float > constraint_euler_angles_ ;
    std::vector<std::vector<float>> middle_face_rect_;
};

class MMCV_EXPORT FaceFeaturesInfo
{
public:
#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/facefeatures/FaceFeaturesInfo");
#endif

    std::vector<std::vector<float> > features_small_features_;

    std::vector<std::vector<uint8_t> > featuers_big_features_;

    std::vector<bool> features_quality_;
};

class MMCV_EXPORT FaceFeatures
{
public:
    FaceFeatures();
    virtual ~FaceFeatures();

    bool load_model(const std::string& fd_path);
    bool load_model(const std::vector<uint8_t>& fd_buf);
    
    bool load_halfmodel(const std::string& fd_path);
    bool load_halfmodel(const std::vector<uint8_t>& fd_buf);

    int get_model_version();

    // img --> small_features
    bool extract_features(const MMFrame& _frame, const FaceFeaturesParams& _single_face_info, FaceFeaturesInfo &_ret_info);

    // img --> big_features  //
    bool extract_features_big_features(const MMFrame& _frame, const FaceFeaturesParams& _single_face_info, FaceFeaturesInfo &_ret_info);

    // big_features --> small_features
    std::vector<float> extract_features(const uint8_t* features, int features_len);
    std::vector<float> extract_features(const std::vector<uint8_t> &features);

    static float calc_cos_distance(const std::vector<float> &feature_a, const std::vector<float> &feature_b);

    static float calc_cos_distance(const float* feature_a, int feature_a_len, const float* feature_b, int feature_b_len);

    static bool parse_big_features_to_imgbuf(const uint8_t* features, int features_len, std::vector<uint8_t> &imgbuf);

    static bool parse_big_features_to_imgbuf(const std::vector<uint8_t> &features, std::vector<uint8_t> &imgbuf);


private:
    void* features_net_;
    bool init_;
};

}
