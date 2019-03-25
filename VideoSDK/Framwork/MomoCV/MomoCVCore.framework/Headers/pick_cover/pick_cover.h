// 2017-03-23
// wang.shanhu@immomo.com

#ifndef MMPICKCOVER_HPP
#define MMPICKCOVER_HPP
#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>
#include <MomoCVCore/video_processor/video_processor.h>

namespace mmcv
{
    
    class MMCV_EXPORT PickerCoverInfo
    {
        
    public:
        PickerCoverInfo();
        
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject pickercoverinfo, std::string pickercoverinfo_cname = "com/momocv/pickercover/PickerCoverInfo");
#endif
        bool Parse(const std::string& params_str);
        std::string Dump();
        float ret_state_;
    };
    
    class MMCV_EXPORT PickerCover
    {
    public:
        PickerCover();
        virtual ~PickerCover();
        
        bool load_model(const std::vector<uint8_t>& fd_model_buf, const std::vector<uint8_t>& fa_model_buf);

        bool load_model(const std::string& fd_model_path, const std::string& fa_model_path);

        bool process_frame(const MMFrame& _frame,const VideoParams& params, PickerCoverInfo& pickercoverinfo);

    private:
        void* vp_ptr_;
        bool vp_inited_;
        int rotate_degree_;
    };
}


#endif /* MMPICKCOVER_HPP */
