// 2017-01-18
// zhang.shengkai@immomo.com

#pragma once
#include <MomoCVCore/api_base/momocv_api.h>
#include <list>

namespace mmcv
{

    class MMCV_EXPORT ObjectTrackerParams
    {
    public:
        ObjectTrackerParams();

#ifdef BUILD_JNI
        virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/objecttracker/ObjectTrackerParams");
#endif

        MMRect rect_;

        bool update_model_;
    };

    class MMCV_EXPORT ObjectTrackerInfo
    {
    public:

#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/objecttracker/ObjectTrackerInfo");
#endif

        MMRect rect_;
    };

    class MMCV_EXPORT ObjectTracker
    {
    public:
        ObjectTracker(int num_orientation = 2, bool enable_detect_scale = true, bool enable_detect_loss = false, int n = 2, int N = 10);

        virtual ~ObjectTracker();

        bool reinit(const MMFrame& _frame, const ObjectTrackerParams& _params);

        bool update(const MMFrame& _frame, const ObjectTrackerParams& _params, ObjectTrackerInfo &_ret);

    private:
        void* kcf_ptr_;
        int step_;
        int n_;
        int N_;
        std::list<bool> stat_list_;
        int false_count_;
        MMSize window_;
    };
    
}
