// 2018-03-15

#pragma once
#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{
    
    class MMCV_EXPORT HairSegInfo
    {
    public:
        bool Parse(const std::string& params_str);
        std::string Dump();
        std::vector<uint8_t> hair_mask_;
        
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/hairseg/HairSegInfo");
#endif
        
    };
    
    
    class MMCV_EXPORT HairSegParams : public BaseParams
    {
    public:
        HairSegParams();
        virtual ~HairSegParams();
        
        virtual void transform_params_by_device();
        
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/hairseg/HairSegParams");
#endif
        bool Parse(const std::string& params_str);
        std::string Dump();
        // [false, true]
        // default is false
        bool debug_on_;
        
        // debug file destination path.
        // default is "momocv_debug.log"
        std::string debug_output_;
    };
    
    
	class MMCV_EXPORT HairSeg
	{
		public:
            HairSeg();
            ~HairSeg();
        
            bool load_model(const std::string& hairseg_model_path);
            bool load_model(const std::vector<uint8_t>& hairseg_model_buf);
            bool load_model_raw(const std::string& prototxt_path,const std::string& model_path);
            bool process_frame(const MMFrame& _frame, const HairSegParams& _hairsegparams, HairSegInfo& _ret);
		
        private:
            void* hairseg_forward_;
            bool hairseg_init_;
	};
}
