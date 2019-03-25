//
//  face_gender.hpp
//  MomoCVBase
//
//  Created by zhuwei on 2018/3/21.
//

#ifndef face_gender_hpp
#define face_gender_hpp

#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{
    
class MMCV_EXPORT FaceGenderParams : public BaseParams
{
public:
    FaceGenderParams();

    //96point  x1, x2, x3, ......, y1, y2,y3,......
    std::vector<float> coord_96pt_;
#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/faceattributes/FaceGenderParams");
#endif
};

class MMCV_EXPORT FaceGenderInfo
{
public:
    FaceGenderInfo();
    //0 is boy, 1 is girl
    int ret_state_;
#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/faceattributes/FaceGenderInfo");
#endif
};



class MMCV_EXPORT FaceGender
{
public:
    FaceGender();
    virtual ~FaceGender();
    
    bool load_model(const std::string& gender_path);
    bool load_model(const std::vector<uint8_t>& gender_buf);
    
    //_FaceGenderInfo.ret_state_  = 0 is boy, 1 is girl
    bool process_frame(const MMFrame& _frame,const FaceGenderParams& _params, FaceGenderInfo& _FaceGenderInfo);
    
private:

    void* gd_ptr_;
    bool gd_inited_;

    bool init_func();

};
    
}

#endif /* face_gender_hpp */
