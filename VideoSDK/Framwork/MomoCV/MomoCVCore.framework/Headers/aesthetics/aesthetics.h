// 2018-05-16
// zhu.wei@immomo.com

#pragma once
#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{

enum aesthclassify
{
    ANIMAL = 0,
    NATURE= 1,
    PEOPLE = 2,
};

class MMCV_EXPORT AestheticsParams : public BaseParams
{
public:
    AestheticsParams();
    virtual ~AestheticsParams();
    

#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/aesthetics/AestheticsParams");
#endif

    bool people_switch_;
    bool aesth_switch_;
    bool txt_switch_;
    
    // [false, true]
    // default is false
    bool debug_on_;
    
    // debug file destination path.
    // default is "momocv_debug.log"
    std::string debug_output_;
};

class MMCV_EXPORT AestheticsInfo
{
public:

#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/aesthetics/AestheticsInfo");
#endif
    
    //animal, nature, people
    int class_result_ ;
    
    //[0, 10]
    float aesth_score_ ;
    
    //0为文本，1为证件，2负样本
    int txt_result_ ;
};

    
    
class MMCV_EXPORT Aesthetics
{
public:
    Aesthetics();
    ~Aesthetics();

    
    bool load_model(const std::string& model_path);
    
    bool load_model(const std::vector<uint8_t>& model_buf);
    bool load_model_raw(const std::string& prototxt_path,const std::string& model_path);

    

    bool process_frame(const MMFrame &_frame, const AestheticsParams &params, AestheticsInfo &_ret);

    
private:

    void* cl_forward_;
    void* ae_forward_;
    void* txt_forward_;

    void init_func();
    bool assert_func();
    bool cl_inited_;
    bool ae_inited_;
    bool txt_inited_;
    bool inited_;
    int max_side_;
    int short_side_;

};

}

