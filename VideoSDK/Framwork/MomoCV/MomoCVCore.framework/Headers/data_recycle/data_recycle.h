//data 2017-9-14

#ifndef SK_SEGMENTATION_H_
#define SK_SEGMENTATION_H_

#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>
#include <array>

namespace mmcv
{
    
    enum DataRecyleType {
        DR_NONE = 0, //  未检到
        DR_NAKED = 1, // 光膀子
        DR_SMILE = 2, // 微笑
        DR_POUT = 3,  // 嘟嘴
    };
    
    class MMCV_EXPORT DataRecycleInfo {
        public:
        
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/datarecycle/DataRecycleInfo");
#endif
        
        DataRecycleInfo();
        int type_; // 数据的类别
        float score_; // 置信度
        std::vector<uint8_t> datum_buf_; // 需要回传的数据
        std::string info_; // 回传的附加信息
    };
    
    class MMCV_EXPORT DataRecyle
    {
    public:
        DataRecyle();
        ~DataRecyle();
        
    public:
        bool load_model(const std::vector<uint8_t>& _model_buf);
        bool load_model(const std::string& _model_path);
    
        bool process_frame(const MMFrame& _frame, const BaseParams& _baseparams, DataRecycleInfo& ret);
        
    private:
        void* vp_ptr_;
        void* naked_ptr_;
        
        bool vp_inited_;
        bool naked_inited_;
        
        std::array<int, 3> frame2_result_;//前两次的预测结果放在数组frame2_result中
        
    private:
        bool EncodeImage(const void* _input, std::vector<uint8_t>& output);
    };
    
}

#endif
