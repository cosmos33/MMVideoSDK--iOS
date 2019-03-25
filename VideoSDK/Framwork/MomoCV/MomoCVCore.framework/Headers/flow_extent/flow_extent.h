// 2016-03-01
// zhang.shengkai@immomo.com

#pragma once
#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{
    class MMCV_EXPORT FlowExtentInfo
    {
    public:
        FlowExtentInfo() : global_(0), local_(0)
        {
        }

#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject flow_extent_info, std::string cname = "com/momocv/flowextent/FlowExtentInfo");
#endif
        
        int global_;
        int local_;
    };

    class MMCV_EXPORT FlowExtent
    {
    public:
        FlowExtent();
        virtual ~FlowExtent();

        bool process_frame(const MMFrame& _frame, const BaseParams& _params, FlowExtentInfo& _ret);
    private:
        void* fl_ptr_;
    };

}
