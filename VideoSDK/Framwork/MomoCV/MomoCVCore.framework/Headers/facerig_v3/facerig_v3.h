#pragma once

#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{
    
    class MMCV_EXPORT FacerigV3Params : public BaseParams
    {
    public:
        FacerigV3Params();
        virtual ~FacerigV3Params();
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/facerigv3/FacerigV3Params");
#endif
        std::vector<float> orig_landmarks_87_;

        std::vector<float> orig_landmarks_96_;

		std::vector<float> face_processor_eulers_;

		/* default is true */
		bool use_stable_;

		/* default is 3. Range [0, 100] */
		float stable_coef_;
    };
    
    class MMCV_EXPORT FacerigV3Info
    {
        
    public:
        FacerigV3Info();
        virtual ~FacerigV3Info();
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string FacerigV3Info_cname = "com/momocv/facerigv3/FacerigV3Info");
#endif
		/* face stable eulers. In radius */
		std::vector<float> facerigV3_eulers_;

		/* blendshape params. Range [0, 1] */
        std::vector<float> facerigV3_scores_;
    };
    
    class MMCV_EXPORT FaceRigV3
    {
    public:
        FaceRigV3();
        virtual ~FaceRigV3();
        
        bool load_model(const std::string& FaceRigV3_path) ;
        bool load_model(const std::vector<uint8_t>& FaceRigV3);
        bool load_coreml_model_raw(const std::string& FaceRigV3_path, bool is_compiled = false);
        
        bool process_frame(const MMFrame& _frame, const FacerigV3Params& facerigv3_params, FacerigV3Info& ret_info);
    private:
        void* animoji_ptr_;
        bool animoji_init_;
        int tracking_id;

		std::vector<float> pre_eulers_;
		std::vector<float> pre_socres_;
		std::vector<float> pre_brow_scores_;
    };
    
}
