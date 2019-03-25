#pragma once

#include <MomoCVCore/api_base/momocv_api.h>
#ifdef BUILD_JNI
#include <MomoCVCore/api_base/jni_interface/jni_bridge.h>
#endif

namespace mmcv
{

class MMCV_EXPORT ImageLoaderParams
{
public:
    ImageLoaderParams();
    virtual ~ImageLoaderParams();

#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/imgloader/ImageLoaderParams");
#endif

    // dst image format
    // default is FMT_NONE
    int dst_format_;

    // dst image max length
    // default is 0, means do nothing.
    int max_length_;

};

class MMCV_EXPORT ImageLoaderInfo
{
public:
    ImageLoaderInfo();
    virtual ~ImageLoaderInfo();

#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/imgloader/ImageLoaderInfo");
#endif

    MMFrame mmframe_;

    float scale_ratio_;
};

MMCV_EXPORT bool img_loader(const std::string filepath, const ImageLoaderParams params, ImageLoaderInfo &ret);

}