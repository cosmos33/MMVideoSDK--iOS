#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <MomoCVCore/video_processor/video_processor.h>

namespace mmcv
{

enum CaptureType
{
    CAPTURE_FRONT_FACE = 0,
    CAPTURE_UNFRONT_FACE = 1,
};

class MMCV_EXPORT RegisterParams : public VideoParams
{
public:
    RegisterParams();
    virtual ~RegisterParams();

#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/faceregister/RegisterParams");
#endif

    bool do_capture_;

    int capture_type_;
};

enum RegisterType
{
    FRONT_FACE = 0,
    LEFT_FACE = 1,
    RIGHT_FACE = 2,
    TOP_FACE = 3,
    BOTTOM_FACE = 4,
};

struct MMCV_EXPORT SingleRegisterInfo
{
    int register_type_;

    int tracking_id_;

    float face_prob_;

    std::vector<float> face_rect_;

    std::vector<float> landmarks_96_;
    
    std::vector<float> orig_landmarks_96_;

    std::vector<float> euler_angles_;

    std::vector<uint8_t> features_;

    int features_quality_;
};

class MMCV_EXPORT RegisterInfo : public VideoInfo
{
public:

#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/faceregister/RegisterInfo");
#endif

    std::map<int, SingleRegisterInfo> register_infos_;
};

class MMCV_EXPORT FaceRegister
{
public:
    FaceRegister();
    virtual ~FaceRegister();

    bool load_model(const std::string& fd_path);
    
    bool load_model(const std::string& fd_path, const std::string& fa_path);

    bool load_model(const std::vector<uint8_t>& fd_buf);

    bool load_model(const std::vector<uint8_t>& fd_buf, const std::vector<uint8_t>& fa_buf);

    bool process_frame(const MMFrame& _frame, const RegisterParams& register_params, RegisterInfo& _ret_register);

    bool reset();

private:
    std::shared_ptr<VideoProcessor> video_processor_;
    std::map<int, SingleRegisterInfo> register_infos_;
};

}
