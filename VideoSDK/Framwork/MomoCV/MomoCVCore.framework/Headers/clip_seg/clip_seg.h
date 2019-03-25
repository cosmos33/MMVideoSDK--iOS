// 2018-03-15
// long.peng@immomo.com

#pragma once
#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>
#include <MomoCVCore/face_processor/face_processor.h>
#include <cstdio>
#include <cmath>

namespace mmcv
{
    
    class MMCV_EXPORT SingleLipMaskRect{
        public:
            SingleLipMaskRect() : resize_width_(0), x_(0), y_(0), width_(0), height_(0), data_len_(0)
            {
            }
            int resize_width_;
            int x_;
            int y_;
            int width_;
            int height_;
            int data_len_;
            std::vector<uint8_t> mask_data_;
            std::vector<uint8_t> rgba_mask_data_;
    };
    
    class MMCV_EXPORT ClipSegInfo 
    {
    public:
        
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/clipseg/ClipSegInfo");
#endif
        std::vector<SingleLipMaskRect> lipmasks_;
    };
    
    
    class MMCV_EXPORT ClipSegParmas : public BaseParams
    {
        public:
        ClipSegParmas();
        ~ClipSegParmas();
        
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/lipseg/ClipSegParmas");
#endif
        std::vector<std::vector<float> > landmarks96_;
        std::vector<std::vector<float> > euler_angles_;
        
    };
    
    
	class MMCV_EXPORT ClipSeg
	{
		public:
            ClipSeg();
            ~ClipSeg();
        
            bool load_model(const std::string& lipseg_model_path = "");
            bool load_model(const std::vector<uint8_t>& lipseg_model_buf = std::vector<uint8_t>());
            bool process_frame(const MMFrame& _frame, const ClipSegParmas& _lipsegparams, ClipSegInfo& _ret);
		private:
            void* cs_impl_;
	};
}
