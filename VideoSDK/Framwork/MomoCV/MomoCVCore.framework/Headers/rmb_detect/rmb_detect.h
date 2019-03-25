//
//  rmb_detect.h
//  mac_all_demo
//
//  Created by zhuwei on 2018/1/2.
//  Copyright © 2018年 MOMO. All rights reserved.
//

#ifndef rmb_detect_h
#define rmb_detect_h


#pragma once
#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{
    class MMCV_EXPORT RMBDetectInfo
    {
    public:
#ifdef BUILD_JNI
        virtual void to_java(JNIEnv *jenv, jobject ret_rmb_detect_info, std::string cname = "com/momocv/rmbdetect/RMBDetectInfo");
#endif
        std::vector<MMBox> detect_results_;
    };

    class MMCV_EXPORT RMBDetect
    {
    public:
        RMBDetect();
        ~RMBDetect();

        bool load_model(const std::vector<uint8_t>& model_buf);

        bool load_model(const std::string& model_path);

        bool load_model_raw(const std::string& proto_path, const std::string& model_path);

        bool process_frame(const MMFrame &_frame, const BaseParams &_params, RMBDetectInfo &_ret);

        std::vector<std::string> get_support_classes();
        
        float get_threshold();
        
    private:
        
        std::vector<std::string> class_names_;
        float threshold_;
        void* forward_;
        
        void init();
        bool inited_;
    };
}


#endif /* rmb_detect_h */
