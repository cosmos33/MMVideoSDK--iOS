#ifndef STYLE_TRANSFER_H_
#define STYLE_TRANSFER_H_

#include <vector>
#include <string>
#include <MomoCVCore/api_base/momocv_api.h>

namespace mmcv
{
    
    

class MMCV_EXPORT StyleTransfer
{
public:
    StyleTransfer();
    ~StyleTransfer();
    
public:
    bool load_model(const std::vector<uint8_t>& model_buf);
    bool load_model(const std::string& model_path);
    bool LoadModelRaw(const std::string& proto_path, const std::string& model_path);
    
    void process_frame(const std::vector<uint8_t>& img_buf, int width, int height, int step, std::vector<uint8_t>& ret, int format = MMFormat::FMT_NV21, int rot_deg = 0, bool flip = false);
    void process_frame(const uint8_t* img_ptr, int img_len, int width, int height, int step, std::vector<uint8_t>& ret, int format = MMFormat::FMT_NV21, int rot_deg = 0, bool flip = false);
    
public:
    // 返回 Mask 的旋转角度
    int restore_degree;
    
private:
    size_t frame_counter_;
    void* forward_;
    void* smooth_;
    
    void Init();
    bool Assert();
    bool inited_;
    int max_side_;
};

}

#endif
