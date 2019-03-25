// 2017-02-11
// zhang.shengkai@immomo.com

#pragma once
#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{

    struct MMTag {
        MMTag(const std::string& name, int idx = 0, float scr = 0) :tag_name(name), index(idx), score(scr) {}
        MMTag(int idx = 0, float scr = 0) : index(idx), score(scr) {}
        std::string tag_name;
        int index;
        float score;
    };

    class VideoTag
    {
    public:
        VideoTag(bool auto_reset = true);
        ~VideoTag();

    public:
        bool load_model(const std::vector<uint8_t>& model_buf);
        bool load_model(const std::string& model_path);
        bool load_model_raw(const std::string& proto_path, const std::string& model_path);

        std::vector<MMTag> reset();
        std::vector<MMTag> get_overall_tags();

        std::vector<MMTag> update(const std::vector<uint8_t>& img_buf, int width, int height, int step = -1, MMFormat format = MMFormat::FMT_NV21, int rot_deg = 0, bool flip = false);
        std::vector<MMTag> update(const uint8_t* img_buf, int img_len, int width, int height, int step = -1, MMFormat format = MMFormat::FMT_NV21, int rot_deg = 0, bool flip = false);

        std::vector<std::string> get_support_tags();

    private:
        bool auto_reset_;
        std::vector<std::string> class_names_;
        //std::vector<float> debug_info_;

        void* fd_ptr_;

        size_t frame_counter_;
        int frame_num_;

        std::vector<float> feat_buf_;
        std::vector<float> swap_buf_;
        int feature_dim_;

        int tags_buf_len_;
        std::vector< std::vector<MMTag> > tags_buf_;
        std::vector<MMTag> tmp_tags_;
        
        float tag_threshold_;
        float section_threshold_;
    private:
        void init();
        bool inited_;
    };
}
