#ifndef BARENESS_DETECT_H_
#define BARENESS_DETECT_H_

#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>
#include <array>
namespace mmcv
{

    class MMCV_EXPORT BarenessDetectInfo
    {
        
    public:
        BarenessDetectInfo();
        
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject barenessdetectinfo, std::string barenessdetectinfo_cname = "com/momocv/barenessdetect/BarenessDetectInfo");
#endif
        bool Parse(const std::string& params_str);
        std::string Dump();
        int ret_state_;
        
        
    };

    class MMCV_EXPORT BarenessDetect
    {
    public:
        BarenessDetect();
        ~BarenessDetect();
        
    public:
        bool load_model(const std::vector<uint8_t>& _model_buf);
        bool load_model(const std::string& _model_path);
        bool process_frame(const MMFrame& _frame, const BaseParams& _baseparams, BarenessDetectInfo& _barenessinfo);
        void reset();
        const std::array<int, 3>  get_frame2result() const ;
        
    private:
        int counter_ ;
        void* naked_ptr_;
        bool naked_inited_;
        int  result_pre_ ;
		std::array<int, 3> frame2_result_;
        
    };
}

#endif
