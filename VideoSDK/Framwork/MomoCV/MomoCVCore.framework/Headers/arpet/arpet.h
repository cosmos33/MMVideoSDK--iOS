#pragma once
#include <string>
#include <vector>
#include <memory>
#include <MomoCVCore/video_processor/video_processor.h>
#include <MomoCVCore/bareness_detect/bareness_detect.h>

namespace mmcv
{

    enum quality_arpet {
        SHARPNESS_LOW = 0,
        SHARPNESS_HIGH = 1,
        BRIGHTNESS_LOW = 2,
        BLACKSCREEN = 3,
        QUALITY_OK = 4,
    };

    enum groupphoto {
        GROUP_SINGLE = 0,
        GROUP_MULITY = 1,

    };

    enum upwardshot {
        UPWARD_BAD = 1,
        UPWARD_GOOD = 0,

    };

    enum exposed {
        EXPOSED_FALSE = 0,
        EXPOSED_TRUE = 1,
    };

    enum photostation {
        STATE_OTHER = 0,
        STATE_BED = 2,
        STATE_SMOKE = 1,
    };



    enum scenary {
        SCENE_OTHER = 0,
        SCENE_BUILDING = 1,
        SCENE_LANDSCAPE = 2,
        SCENE_OUTDOOR = 3,
    };

    class MMCV_EXPORT ArpetParams : public VideoParams
    {
    public:
        ArpetParams();
        virtual ~ArpetParams();
        
        bool quality_switch_;
        bool face_detect_switch_;
        bool photostation_switch_;
        bool scenary_switch_;
        bool exposed_switch_;
        float face_ratio_;
        float face_anguler_;
        float clarity_top_;
        float clarity_down_;
        float brightness_down_;



#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/arpet/ArpetParams");
#endif


    };



    class MMCV_EXPORT ArpetInfo : public VideoInfo

    {
    public:

#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/arpet/ArpetInfo");
#endif

        quality_arpet quality_arpet_;
        groupphoto groupphoto_;
        upwardshot upwardshot_;
        photostation photostation_;
        scenary scenary_;
        exposed exposed_;
    };

    class MMCV_EXPORT Arpet
    {
    public:
        Arpet();
        virtual ~Arpet();

        bool load_model(const std::string& _arpet_path, const std::string& _fd_path, const std::string& _bareness_path);
        bool load_model(const std::vector<uint8_t>& _arpet_buf, const std::vector<uint8_t>& _fd_buf, const std::vector<uint8_t>& _bareness_buf);


        bool process_frame(const MMFrame& _frame, const ArpetParams& _arpet_params, ArpetInfo& _ret_arpet);




    private:

        std::shared_ptr<VideoProcessor> video_processor_;
        std::shared_ptr<BarenessDetect> bareness_detect_;
        bool vp_inited_;
        bool br_inited_;

        void * phostation_ptr_;
        bool phostation_inited_;
        void * scenary_ptr_;
        bool scenary_inited_;


    };

}
