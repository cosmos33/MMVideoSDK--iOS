//
//  Created by zhourunnan on 2018/5/28.
//

#ifndef beauty_score_hpp
#define beauty_score_hpp

#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{
    
class MMCV_EXPORT BeautyScoreParams : public BaseParams
{
public:
    BeautyScoreParams();
    //96point  x1, x2, x3, ......, y1, y2,y3,......
    std::vector<float> coord_96pt_;
    
#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/beautyscore/BeautyScoreParams");
#endif

   
    
    bool Parse(const std::string& params_str);
    std::string Dump();
};

class MMCV_EXPORT BeautyScoreInfo
{
public:
    BeautyScoreInfo();
    
    //0~2
    //default -1
    float beauty_score;
    
    //0,1,2
    int beauty_type;
    
#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/beautyscore/BeautyScoreInfo");
#endif
    
    bool Parse(const std::string& params_str);
    std::string Dump();
};


class MMCV_EXPORT BeautyScore
{
public:
    BeautyScore();
    virtual ~BeautyScore();
    
    bool load_model(const std::string& path);
    bool load_model(const std::vector<uint8_t>& buf);
   
    bool load_model(const std::vector<uint8_t>& buf, bool needcheck);
    bool process_frame(const MMFrame& _frame, const BeautyScoreParams& _params, BeautyScoreInfo& _info);
    
private:

    void* ptr_;
    bool inited_;

    bool init_func();

};
    
}

#endif /* beauty_score_hpp */
