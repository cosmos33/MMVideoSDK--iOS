#ifndef _MM_FACE_RIG_H_
#define _MM_FACE_RIG_H_

#include <string>
#include <vector>
#include <map>
#include <MomoCVCore/face_processor/face_processor.h>

namespace mmcv
{

    

    
class MMCV_EXPORT FacerigInfo : public FacesInfo
{
    
public:
    FacerigInfo();
    virtual ~FacerigInfo();
    
#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string faceriginfo_cname = "com/momocv/facerig/FaceRigInfo");
#endif

    int mean_state_;
    int ret_state_;
    std::vector <float> facerig_scores_;
    std::vector <uint8_t> facerig_feature_;


    
};
    
class MMCV_EXPORT FaceRig
{
public:
    FaceRig();
    virtual ~FaceRig();
    
    bool load_model(const std::string& facerecog_path, const std::string& fd_path, const std::string& fa_path) ;
    bool load_model(const std::vector<uint8_t>& facerecog_buf, const std::vector<uint8_t>& fd_buf, const std::vector<uint8_t>& fa_buf);

    // return：状态码ret_info.mean_state_ ,(0 为校准成功, 开始执行Proc）-100为默认值, 1为模型初始化失败, 2为没检测到人脸,  3为闭眼, 4位姿态不正, 5离摄像头太远, 6离摄像头太近, 7提取人脸识别特征失败, 8计算基准点失败
    // DetectMeanFace() 未返回 0 之前调用 Proc() 会失败
    //将ret_info 里面新的facerig_feature保存至本地
    bool DetectMeanFace(const MMFrame& _frame, const FaceParams& face_params, FacerigInfo& ret_info);
    

    // 返回值的解释见 https://moji.wemomo.com/wiki/28788

    //初次使用先调用Proc函数, ret_info.ret_state_ = -1, 表示需要校准 ,调用DetectMeanFace函数, ret_info.ret_state_ = 0, 表示计算成功. 校准的本地校准特征需要先读进 facerig_feature . facerig表情分数值放在FacerigInfo facerig_ascores,
    bool Proc(const MMFrame& _frame, const FaceParams& face_params,const std::vector <uint8_t> &facerig_feature, FacerigInfo& ret_info);


private:
    void* es_ptr_;

    std::shared_ptr<FaceProcessor> face_processor_;
    
    std::vector<float> mean_eular_;
    std::vector<float> min_eular_;
    std::vector<float> mean_landmarks_;
    
    const float angle2radians_ ;
    int tracking_id_ ;
    size_t no_face_count_ ;
    bool first_proc_ ;
    bool facerecog_switch_ ;
    size_t face_recognition_count_ ;
    bool face_processor_init_;
    bool cal_facerig_ ;
    int leye_close_counter_;
    int reye_close_counter_;
    
};

}

#endif
