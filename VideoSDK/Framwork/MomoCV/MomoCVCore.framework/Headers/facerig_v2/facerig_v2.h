#ifndef _MM_FACERIGV2_H_
#define _MM_FACERIGV2_H_


#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>



namespace mmcv
{
    
    class MMCV_EXPORT FacerigV2Params : public BaseParams
    {
    public:
        FacerigV2Params();
        virtual ~FacerigV2Params();
        
        
#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/facerigv2/FacerigV2Params");
#endif
        
        std::vector<float> orig_landmarks_87_;
//        std::vector<float> orig_landmarks_137_;
        int tracking_id;
    };
    
    
    
    class MMCV_EXPORT FacerigV2Info
    {
        
    public:
        FacerigV2Info();
        virtual ~FacerigV2Info();
        
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string facerigv2info_cname = "com/momocv/facerigv2/FacerigV2Info");
#endif
        
        std::vector <float> facerigV2_scores_;
        
        //    std::vector <float> facerigv2_part_scores_;
        
        
        
    };
    
    class MMCV_EXPORT FaceRigV2
    {
    public:
        FaceRigV2();
        virtual ~FaceRigV2();
        
        bool load_model(const std::string& facerigv2_path) ;
        bool load_model(const std::vector<uint8_t>& facerigv2);
        
        bool process_frame(const MMFrame& _frame, const FacerigV2Params& facerigv2_params, FacerigV2Info& ret_info);
        //        bool process_eyebrow(const MMFrame& _frame, const FacerigV2Params& facerigv2_params,std::vector<float> & ret_scores);
        
    private:
        void* facefit_ptr_;
        bool facefit_init_;
        
        std::vector<float> euler_angles_cur_;
        std::vector<float> euler_angles_pre_;
        std::vector<float> eyebrow_scores_pre_;
        std::vector<float> outeyebrow_scores_pre_;
        std::vector<float> ineyebrow_scores_pre_;
        std::vector<float> eyelid_scores_pre_;
        std::vector<float> downineyebrow_scores_pre_;
//        std::vector<float> scores_pre_;
        
        bool adjust_flag;     //判断是否记录眉毛系数
        unsigned int record_frame;   //记录前几秒眉毛的帧数
        std::vector<float> downeyebrow_coeff;  //记录眉毛系数
        std::vector<float> upouteyebrow_coeff;
        std::vector<float> upineyebrow_coeff;
        float downeyebrow_mean;
        float upouteyebrow_mean;
        float upineyebrow_mean;
        int tracking_id;
        unsigned int count_landmarks_87_;
        
        bool process_eyebrow(const MMFrame& _frame, const FacerigV2Params& facerigv2_params,std::vector<float> euler_new, std::vector<float> & ret_scores);
        bool isNan(float &fN);
    };
    
}

#endif
