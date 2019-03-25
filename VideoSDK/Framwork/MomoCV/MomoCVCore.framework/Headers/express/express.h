#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{

enum eyetype
{
    EYEDEFAULT = -1,
    CLOSE = 0,
    OPEN = 1,


};

    
enum mouthtype
{
    MOUTHDEFAULT = -1,
    MOUTHNOTIONG = 0,
    DUZUI = 1,
    SMILE = 2,
    OPENMOUTH = 3,
};
    
enum headtype
{
    HEADDEFAULT = -1,
    HEADMIDDLE = 0,
    HEADLEFT = 1,
    HEADRIGHT = 2,
    HEADDOWN = 3,
};
    
enum necktype
{
    NECKDEFAULT = -1,
    NECKMIDDLE = 0,
    NECKLEFT = 1,
    NECKRIGHT = 2,

};

    

class MMCV_EXPORT ExpressParams : public BaseParams
{
public:
    ExpressParams();
    virtual ~ExpressParams();
    bool eyes_switch_;
    bool mouth_switch_;
    bool head_switch_;
    bool neck_switch_;
    
#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/express/ExpressParams");
#endif
    
    std::vector<std::vector<float> > origin_landmarks96_;
    std::vector<std::vector<float> > orig_face_rect_;



};


struct MMCV_EXPORT SingleExpressInfo
{
    eyetype lefteye_ = eyetype::EYEDEFAULT;
    eyetype righteye_ = eyetype::EYEDEFAULT;
    mouthtype mouth_ = mouthtype::MOUTHDEFAULT;
    headtype head_ = headtype::HEADDEFAULT;
    necktype neck_ = necktype::NECKDEFAULT;


};

class MMCV_EXPORT ExpressInfo
{
public:

#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/express/ExpressInfo");
#endif

    std::vector< SingleExpressInfo > express_infos_;
};

class MMCV_EXPORT Express
{
public:
    Express();
    virtual ~Express();

    bool load_model(const std::string& express_model_path);
    bool load_model(const std::vector<uint8_t>& express_model_buf);


    bool process_frame(const MMFrame& _frame, const ExpressParams& _express_params, ExpressInfo& _ret_express);




private:


    void* eyes_ptr_;
    void* mouth_ptr_;
    void* head_ptr_;
    void* neck_ptr_;

    bool eyes_inited_;
    bool mouth_inited_;
    bool head_inited_;
    bool neck_inited_;
    
    int eye_width_;
    int eye_height_;
    int mouth_width_;
    int mouth_height_;
    int head_width_;
    int head_height_;
    int neck_width_;
    int neck_height_;
    
    
    bool truly_inited_;

    
};

}
