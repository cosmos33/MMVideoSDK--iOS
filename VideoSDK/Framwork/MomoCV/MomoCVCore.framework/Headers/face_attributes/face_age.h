//
//  face_gender.hpp
//  MomoCVBase
//
//  Created by zhuwei on 2018/3/21.
//

#ifndef face_age_hpp
#define face_age_hpp

#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{
    class MMCV_EXPORT FaceAgeParams : public BaseParams
    {
    public:
        FaceAgeParams();
        //96point  x1, x2, x3, ......, y1, y2,y3,......
        std::vector<float> coord_96pt_;
        
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/faceattributes/FaceAgeParams");
#endif
    };
    
    class MMCV_EXPORT FaceAgeInfo
    {
    public:
        FaceAgeInfo();
        //返回值代表预测的年龄
        int ret_age_;
        
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/faceattributes/FaceAgeInfo");
#endif
    };
    
    class MMCV_EXPORT FaceAge
    {
    public:
        FaceAge();
        virtual ~FaceAge();
        
        bool load_model(const std::string& age_path);
        bool load_model(const std::vector<uint8_t>& age_buf);
        
        bool load_model(const std::vector<uint8_t>& age_buf, bool needcheck);
        //_FaceGenderInfo.ret_state_  = 0 is boy, 1 is girl
        bool process_frame(const MMFrame& _frame,const FaceAgeParams& _params, FaceAgeInfo& _FaceAgeInfo);
        
    private:
        void* age_ptr_;
        bool age_inited_;
        bool init_func();
    };
    
}

#endif /* face_gender_hpp */
