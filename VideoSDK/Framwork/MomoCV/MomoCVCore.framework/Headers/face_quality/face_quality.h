#pragma once

#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>
#include <MomoCVCore/face_features/face_features.h>

namespace mmcv
{

class MMCV_EXPORT SingleFaceQualityInfo
{
public:
    SingleFaceQualityInfo();
    
    //[0~1]
    //default is -1
    float quality_score;
   
    /*
     -1: defaut
     0: unknown, empty img
     1: perfect
     2: brighspot
     3: clarity error
     4: brightness error
     5: contrast error
     6: face out of screnn
     */
    int face_qality_flag;
    
    /*
     -1: defaut
     0: good frontal face
     1: samll degree side face
     2: big degree side face
     */
    int faceposetype_;
    
    /*
     -1: default
     0: no occlusion
     1: has occlusion
     */
    int occflag_;
    
    /*
     liveness detect result
     -1: default
     0: not livesness
     1: liveness
     */
    int liveness_;
    
    /*
     -1: uninted,default
      0: clear
      1: blur
     */
    int motion_blur_;
    
    int tracking_id_;
    
    float SpotRatio;
    float Brightness;
    float Clarity;
    
    float SpotScore;
    float BrightnessScore;
    float ClarityScore;
    float motion_blur_score_;
};

class MMCV_EXPORT FaceQualityInfo
{
public:
    
#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/facequality/FaceQualityInfo");
#endif
    
    std::vector<SingleFaceQualityInfo> facesqualityinfo_;
};

    
    
class MMCV_EXPORT FaceQualityParams : public BaseParams
{
public:
    FaceQualityParams();
    virtual ~FaceQualityParams();

#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/facequality/FaceQualityParams");
#endif
    
    //default is true
    bool strict_quality_switch_;
    bool liveness_detect_switch_;
    bool motion_blur_detect_switch_;
    bool face_occlusion_switch_;
   
    // [0~1]
    //default is 0.5
    float motion_blur_result_threshold_;
    
    std::vector<int> multi_tracking_id_;
    std::vector<std::vector<float> > multi_euler_angles_ ;
    std::vector<std::vector<float> > multi_origin_landmarks_96_;
};

class MMCV_EXPORT FaceQuality
{
public:
    FaceQuality();
    virtual ~FaceQuality();

    bool load_model(const std::string& fq_path);
    
    bool load_model(const std::vector<uint8_t>& fq_buf);

    bool process_frame(const MMFrame& _frame, const FaceQualityParams& params, FaceQualityInfo& _ret);

    bool reset();

private:
    void* face_quality_impl_;
};

}
