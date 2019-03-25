// 2017-08-29
// zhang.shengkai@immomo.com

#ifndef _MOMOCV_API_H_
#define _MOMOCV_API_H_

#include <stdint.h>
#include <cfloat>
#include <climits>
#include <vector>
#include <string.h>
#include <string>
#include <cmath>
#include <assert.h>
#include <memory>
#include <iostream>
#ifdef BUILD_JNI
#include <MomoCVCore/api_base/jni_interface/jni_bridge.h>
#endif

#undef MMCV_EXPORT
#undef MMCV_HIDDEN
#if defined _WIN32 || defined __CYGWIN__
#if defined(MMCV_EXPORTS) && defined(DLL_PROJECT)
#ifdef __GNUC__
#define MMCV_EXPORT __attribute__ ((dllexport))
#else
#define MMCV_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#elif defined(DLL_PROJECT)
#ifdef __GNUC__
#define MMCV_EXPORT __attribute__ ((dllimport))
#else
#define MMCV_EXPORT __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#define MMCV_EXPORT
#endif
#define MMCV_HIDDEN
#else
#if __GNUC__ >= 4
#define MMCV_EXPORT
#define MMCV_HIDDEN __attribute__ ((visibility ("hidden")))
#else
#define MMCV_EXPORT
#define MMCV_HIDDEN
#endif
#endif

//model version


//#define FACE_RECOGNITION_MODEL_VERSION 20
//#define FACE_RECOGNITION_MODEL_NUMBER 1
//#define FACE_RECOGNITION_MODEL_NAME_BIN "facerecog_new"

//0b: 01-->16bit, 00-->32bit
#undef HALF_FLOAT
#undef FULL_FLOAT
#undef HALF_MASK
#undef VERSION_MASK
#define HALF_FLOAT (1 << 30)
#define FULL_FLOAT 0
#define HALF_MASK 0xFFFF0000
#define VERSION_MASK 0x0000FFFF

#define FACE_RECOGNITION_MODEL_VERSION (HALF_FLOAT | 20)
#define FACE_RECOGNITION_MODEL_NAME_NUM 1
#define FACE_RECOGNITION_MODEL_NAME_BIN "facerecog_new"

// Forward 引擎的类型
#define FORWARD_ENGINE_MMFORWARD 0
#define FORWARD_ENGINE_MACE (1 << 24)
#define FORWARD_ENGINE_COREML (2 << 24)

#define FACEPROCESSOR_MODEL_VERSION 1  
#define FACEPROCESSOR_MODEL_NAME_NUM 4
#define FACEPROCESSOR_MODEL_NAME_BIN "fd"

#define FACEATTRIBUTES_MODEL_VERSION 1
#define FACEATTRIBUTES_MODEL_NAME_NUM 5
#define FACEATTRIBUTES_MODEL_NAME_BIN "fa"
    
#define OBJECTDETECT_MODEL_VERSION 2 // 20181125 update
#define OBJECTDETECT_MODEL_NAME_NUM 6
#define OBJECTDETECT_MODEL_NAME_BIN "od"
    
#define BARENESS_MODEL_VERSION 1
#define BARENESS_MODEL_NAME_NUM 7
#define BARENESS_MODEL_NAME_BIN "bd"
    
#define SEGMENT_MODEL_VERSION 1
#define SEGMENT_MODEL_NAME_NUM 8
#define SEGMENT_MODEL_NAME_BIN "sg"
#define SEGMENT_MODEL_NAME_BIN_MACE_GPU "mace_gpu.sg"
#define SEGMENT_MODEL_NAME_BIN_MACE_CPU "mace_cpu.sg"
    
#define DR_MODEL_VERSION 14
#define DR_MODEL_NAME_NUM 9
#define DR_MODEL_NAME_BIN "data_recycle"
    
#define RECOG4PET_MODEL_VERSION 2
#define RECOG4PET_MODEL_NAME_NUM 10
#define RECOG4PET_MODEL_NAME_BIN "gp"

#define FACERIG_MODEL_VERSION 1
#define FACERIG_MODEL_NAME_NUM 11
#define FACERIG_MODEL_NAME_BIN "frecog"
    
#define RMBDETECT_MODEL_VERSION 2
#define RMBDETECT_MODEL_NAME_NUM 12
#define RMBDETECT_MODEL_NAME_BIN "rmbd"

#define CLIPSEG_MODEL_VERSION 1
#define CLIPSEG_MODEL_NAME_NUM 13
#define CLIPSEG_MODEL_NAME_BIN "clipseg"

#define GENDER_MODEL_VERSION 3
#define GENDER_MODEL_NAME_NUM 14
#define GENDER_MODEL_NAME_BIN "gender"

#define HAIRSEG_MODEL_VERSION 1
#define HAIRSEG_MODEL_NAME_NUM 15
#define HAIRSEG_MODEL_NAME_BIN "hairseg"

#define FEATUREEXTRACT_MODEL_VERSION 1
#define FEATUREEXTRACT_MODEL_NAME_NUM 16
#define FEATUREEXTRACT_MODEL_NAME_BIN "featureextract"

#define AGE_MODEL_VERSION 3
#define AGE_MODEL_NAME_NUM 17
#define AGE_MODEL_NAME_BIN "age"

#define BODYLANDMARK_MODEL_VERSION 2
#define BODYLANDMARKBLACK_MODEL_VERSION 1
#define BODYLANDMARK_MODEL_NAME_NUM 18
#define BODYLANDMARK_MODEL_NAME_BIN "bodylandmark"
#define BODYLANDMARK_MODEL_NAME_BIN_MACE_GPU "mace_gpu.bodylandmark"
#define BODYLANDMARK_MODEL_NAME_BIN_MACE_CPU "mace_cpu.bodylandmark"

#define BODYLANDMARKBLACK_MODEL_NAME_BIN "bodylandmarkblack"

#define HANDLANDMARK_MODEL_VERSION 1
#define HANDLANDMARK_MODEL_NAME_NUM 19
#define HANDLANDMARK_MODEL_NAME_BIN "handlandmark"
#define HANDLANDMARK_MODEL_NAME_BIN_MACE "mace-handlandmark"
#define HANDLANDMARK_MODEL_NAME_BIN_MACE_GPU "mace_gpu.handlandmark"
#define HANDLANDMARK_MODEL_NAME_BIN_MACE_CPU "mace_cpu.handlandmark"

#define EXPRESS_MODEL_VERSION 1
#define EXPRESS_MODEL_NAME_NUM 20
#define EXPRESS_MODEL_NAME_BIN "express"

#define PINCHFACE_MODEL_VERSION 1
#define PINCHFACE_MODEL_NAME_NUM 21
#define PINCHFACE_MODEL_NAME_BIN "pinchface"

#define AESTHETICS_MODEL_VERSION 1
#define AESTHETICS_MODEL_NAME_NUM 22
#define AESTHETICS_MODEL_NAME_BIN "aesthetics"

#define WOWO_FACEPROCESSOR_MODEL_VERSION 1
#define WOWO_FACEPROCESSOR_MODEL_NAME_NUM 24
#define WOWO_FACEPROCESSOR_MODEL_NAME_BIN "wowofd"

#define BEAUTYSCORE_MODEL_VERSION 2
#define BEAUTYSCORE_MODEL_NAME_NUM 25
#define BEAUTYSCORE_MODEL_NAME_BIN "beautyscore"

#define FACERIGV2_MODEL_VERSION 1
#define FACERIGV2_MODEL_NAME_NUM 26
#define FACERIGV2_MODEL_NAME_BIN "facerigv2"

#define FACEPROCESSOR_FACERIG_MODEL_VERSION 1
#define FACEPROCESSOR_FACERIG_MODEL_NAME_NUM 27
#define FACEPROCESSOR_FACERIG_MODEL_NAME_BIN "fd-87-model"

#define ARPET_MODEL_VERSION 1
#define ARPET_MODEL_NAME_NUM 28
#define ARPET_MODEL_NAME_BIN "arpet"

#define HANDGESTURE_MODEL_VERSION 2
#define HANDGESTURE_MODEL_NAME_NUM 30
#define HANDGESTURE_MODEL_NAME_BIN "handgesture"

#define MULTIGLASS_MODEL_VERSION 1
#define MULTIGLASS_MODEL_NAME_NUM 31
#define MULTIGLASS_MODEL_NAME_BIN "multiglass"

#define FACEQUALITY_MODEL_VERSION 1
#define FACEQUALITY_MODEL_NAME_NUM 32
#define FACEQUALITY_MODEL_NAME_BIN "facequality"

#define FACERIGV3_MODEL_VERSION 1
#define FACERIGV3_MODEL_NAME_NUM 33
#define FACERIGV3_MODEL_NAME_BIN "facerigv3"

#define SCENECLASSIFY_MODEL_VERSION 1
#define SCENECLASSIFY_MODEL_NAME_NUM 34
#define SCENECLASSIFY_MODEL_NAME_BIN "sceneclassify"

namespace mmcv
{
    enum MMFormat
    {
        FMT_NONE  = 0,
        FMT_GRAY  = 2,
        FMT_RGBA  = 4,
        FMT_BGRA  = 5,
        FMT_NV21  = 17,
        FMT_NV12  = 18,
        FMT_NV21_SEP = 19,
        FMT_NV12_SEP = 20,
        FMT_BGR   = 24,
        FMT_RGB   = 25,
        FMT_RGB565 = 27,
        FMT_BGR565 = 28,
    };

    enum MMRotateType
    {
        ROTATE0 = 0,        // No rotation.
        ROTATE90 = 90,      // Rotate 90 degrees clockwise.
        ROTATE180 = 180,    // Rotate 180 degrees.
        ROTATE270 = 270,    // Rotate 270 degrees clockwise.
    };
    
    struct MMCV_EXPORT MMFrame
    {
        MMFrame() : width_(0), height_(0), format_(FMT_NONE), 
            step_(0), data_len_(0), data_ptr_(nullptr),
            y_step_(0), y_len_(0), y_ptr_(nullptr),
            uv_step_(0), uv_len_(0), uv_ptr_(nullptr)
        {
        }
        
        int width_;
        int height_;
        int format_;

        // y.u.v data are continuous
        // other format is continuous
        int step_;
        int data_len_;
        uint8_t* data_ptr_;

        // y.uv data are seperated
        // format_ == FMT_NV21_SEP or format_ == FMT_NV12_SEP
        int y_step_;
        int y_len_;
        uint8_t* y_ptr_;
        int uv_step_;
        int uv_len_;
        uint8_t* uv_ptr_;
		friend std::ostream& operator<<(std::ostream& out, const MMFrame& frame)
        {
            out << "width_: " << frame.width_ << "\n"
            << "height_:  "<< frame.height_ << "\n"
            << "format_:  "<< frame.format_ << "\n"
            << "step_:  "<< frame.step_ << "\n"
            << "data_len_:  "<< frame.data_len_ << "\n"
            << "y_step_:  "<< frame.y_step_ << "\n"
            << "y_len_:  "<< frame.y_len_ << "\n"
            << "uv_step_:  "<< frame.uv_step_ << "\n"
            << "uv_len_:  "<< frame.uv_len_ << "\n";
            return out;
        }
        std::shared_ptr<std::vector<uint8_t> > private_data_;
		

        std::shared_ptr<std::vector<uint8_t> > private_y_;
        std::shared_ptr<std::vector<uint8_t> > private_uv_;

        bool Parse(const std::string& params_str);
        std::string Dump();

    };

    struct MMCV_EXPORT MMSize
    {
        MMSize() : width_(0), height_(0) {}

        MMSize(int _width, int _height)
        {
            width_ = _width;
            height_ = _height;
        }

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/MMSize");

        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/MMSize");
#endif

        int width_;
        int height_;

        bool Parse(const std::string& params_str);
        std::string Dump();

    };
    
    struct MMCV_EXPORT MMPoint
    {
        MMPoint() : x_(0), y_(0) {}

        MMPoint(int _x, int _y)
        {
            x_ = _x;
            y_ = _y;
        }

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/MMPoint");

        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/MMPoint");
#endif
        bool Parse(const std::string& params_str);
        std::string Dump();

        int x_;
        int y_;
    };
	
	struct MMCV_EXPORT MMPoint3f
    {
        MMPoint3f() : x_(0), y_(0), z_(0) {}

        MMPoint3f(float _x, float _y, float _z)
        {
            x_ = _x;
            y_ = _y;
            z_ = _z;
        }

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/MMPoint3f");

        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/MMPoint3f");
#endif

        float x_;
        float y_;
        float z_;
    };
    
    struct MMCV_EXPORT MMRect
    {
        MMRect() : x_(0), y_(0), width_(0), height_(0) {}

        MMRect(int _x, int _y, int _width, int _height)
        {
            x_ = _x;
            y_ = _y;
            width_ = _width;
            height_ = _height;
        }

        MMRect(const std::vector<float>& rect)
        {
            x_ = rect[0];
            y_ = rect[1];
            width_ = rect[2];
            height_ = rect[3];
        }

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/MMRect");

        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/MMRect");
#endif

        bool Parse(const std::string& params_str);
        std::string Dump();

        int x_;
        int y_;
        int width_;
        int height_;

    };
    
    struct MMCV_EXPORT MMBox : public MMRect
    {
        MMBox() : score_(0), class_index_(0), class_name_("NAN") {}

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/MMBox");

        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/MMBox");
#endif


        bool Parse(const std::string& params_str);
        std::string Dump();

        
        float score_;
        int class_index_;
        std::string class_name_;

    };
    
    struct MMCV_EXPORT MMJoint : public MMPoint
    {
        MMJoint() : score_(0) {}

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/MMJoint");

        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/MMJoint");
#endif
        bool Parse(const std::string& params_str);
        std::string Dump();
        float score_;
    };

    class MMCV_EXPORT BaseParams
    {
    public:
        BaseParams();
        virtual ~BaseParams();

        virtual void transform_params_by_device();

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/BaseParams");
#endif

        bool Parse(const std::string& params_str);
        std::string Dump();

        // [0, 90, 180 270]
        // face rotate degree in input coordinate.(clockwise degree)
        int rotate_degree_;

        // [0, 90, 180 270]
        // transform results to screen coordinate system.(clockwise degree)
        int restore_degree_;

        // [false, true] 
        // flip results or not. flip is after restore_degree_ rotation.
        bool fliped_show_;
		
		friend std::ostream& operator<<(std::ostream& out, const BaseParams& baseparams)
        {
            out << "BaseParams.rotate_degree_: " << baseparams.rotate_degree_ << "\n"
                << "BaseParams.restore_degree_:  "<< baseparams.restore_degree_ << "\n"
                << "BaseParams.fliped_show_:  "<< baseparams.fliped_show_ << "\n" ;
            return out;
        }

    protected:
        int transform_count_;
    };

    MMCV_EXPORT bool supported_format(int format);

    MMCV_EXPORT bool supported_frame(const MMFrame &_frame);

    MMCV_EXPORT bool coreml_available();
    
    namespace event_tracking
    {
        struct MMCV_EXPORT ClientInfo {
            std::string user_id_;
            std::string user_name_;
            std::string mobile_phone_type_;
            std::string cpu_type_;
            std::string gpu_type_;
            
#ifdef BUILD_JNI
            void from_java(JNIEnv *jenv, jobject info_obj, std::string cname = "com/momocv/ClientInfo");
#endif
            std::string Dump();
        };
        
        enum EventStatus {
            MMCV_ALG_UNKNOW = 0,
            MMCV_ALG_CREATE = 1,
            MMCV_ALG_RELEASE = 2,
            MMCV_ALG_LOADMODEL = 3,
            MMCV_ALG_RESET = 4,
            MMCV_ALG_PROCESSFRAME = 5,
        };
        
        class MMCV_EXPORT EventMessage {
        public:
            EventMessage(const std::string& name = "UNKNOW", int index = -1, EventStatus status = EventStatus::MMCV_ALG_CREATE);
            ~EventMessage();
            std::string mmcv_module_name;
            int mmcv_module_id;
            EventStatus mmcv_module_status;
            std::string mmcv_module_time;
            std::string mmcv_module_compile_time;
            
            int mmcv_create_return;
            int mmcv_release_return;
            int mmcv_reset_return;
            
            float mmcv_loadmodel_time;
            int mmcv_loadmodel_size;
            int mmcv_loadmodel_return;
            std::string mmcv_loadmodel_md5;
            std::string mmcv_loadmodel_type;
            std::string mmcv_loadmodel_message;
            
            int mmcv_processframe_return;
            float mmcv_processframe_time;
            std::string mmcv_processframe_frame;
            std::string mmcv_processframe_params;
            std::string mmcv_processframe_info;
            std::string mmcv_processframe_message;
            
            std::string Dump ();
        };
        
        class MMCV_EXPORT BaseMessageSystem {
        public:
            static void SetClientInfo(const ClientInfo& client_info);
            static void SetEventTrackingCallback(void* _callback);
            static void Release();
            static void Enable();
            static void Disable();
            static std::string GetCurrentTime();
        };
    }
}

#endif
