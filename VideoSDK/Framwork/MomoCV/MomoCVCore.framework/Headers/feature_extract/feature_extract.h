//data 2017-9-13 v1.0.0 

#ifndef BARENESS_DETECT_H_
#define BARENESS_DETECT_H_

#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>
#include <array>

namespace mmcv
{

    class MMCV_EXPORT FeatureExtractInfo
    {
        
    public:
        FeatureExtractInfo();
        std::vector<float> features_;
        
    };
    
    class MMCV_EXPORT FeatureExtract
    {
    public:
        FeatureExtract();
        ~FeatureExtract();
        
    public:
        bool load_model(const std::vector<uint8_t>& _model_buf);
        bool load_model(const std::string& _model_path);
        
        bool load_halfmodel(const std::vector<uint8_t>& _half_model_buf);
        bool load_halfmodel(const std::string& _half_model_path);
        
        
        bool process_frame(const MMFrame& _frame, const BaseParams& _baseparams, FeatureExtractInfo& _featuresinfo);
        
    private:
        void* naked_ptr_;
        bool naked_inited_;
        
    };
}

#endif
