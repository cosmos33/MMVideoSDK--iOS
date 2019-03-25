#ifndef _FACE_RECOG4PET_H_
#define _FACE_RECOG4PET_H_

#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>
#include <MomoCVCore/video_processor/video_processor.h>

namespace mmcv
{

    
class MMCV_EXPORT FaceRecog4PetInfo
{
    
public:
    FaceRecog4PetInfo();
    
#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject facerecog4petinfo, std::string facerecog4petinfo_cname = "com/momocv/facerecog4pet/FaceRecog4PetInfo");
#endif
    
    int ret_state_;

    
};
    
    
class MMCV_EXPORT FaceRecog4Pet
{
public:
	FaceRecog4Pet();
	virtual ~FaceRecog4Pet();

public:
    
#ifdef MOMO_ANDROID
    bool load_model(const std::vector<uint8_t>& model_buf);
    bool load_model(const std::string& model_path);
#endif
    
    bool load_model(const std::vector<uint8_t>& model_buf, const std::vector<uint8_t>& fd_model_buf,const std::vector<uint8_t>& fa_model_buf);
    bool load_model(const std::string& model_path,const std::string& fd_model_path,const std::string& fa_model_path);
    
    // frame 需要设置的参数 frame_data, width, height, step, is_front_camera, rotate_degree
    //facerecog4petinfo.ret_state_ ：状态码（0：合格，-1：未检测到人脸，-2：多个人脸，-3： 人脸姿态不正，-4：闭眼，-5：人脸太小，-6：模型未初始化, -7: 前两次检测到正脸 ）
    bool process_frame(const MMFrame& _frame,const VideoParams& params, FaceRecog4PetInfo& facerecog4petinfo);
    bool getFeature(std::vector<uint8_t>& ret_buf);
    
    void Reset();
public:
    // 返回 Mask 的旋转角度
    int restore_degree;
    
private:
    size_t frame_counter_;
    void* face_recong_ptr_;
    std::shared_ptr< VideoProcessor > video_process_ptr_;
    void* gd_ptr_;
    
    bool video_process_inited_;
    bool face_recong_inited_;
    bool gd_inited_;

    std::vector<void*> cache_;
    std::vector< std::vector<float> > relative_kpnts_;
    std::vector< std::vector<float> > kpnts_;
    
    float max_clarity;
    int clarity_count;
    
    void Rect2Cache(const uint8_t* img_ptr, int img_len, int width, int height, const std::vector<float>& landmark, int format, int step, int index = 0, float yaw = 0);
    
    
};

}

#endif
