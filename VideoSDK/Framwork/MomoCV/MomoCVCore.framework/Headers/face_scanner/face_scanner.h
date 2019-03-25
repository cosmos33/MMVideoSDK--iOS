#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <MomoCVCore/object_tracker/object_tracker.h>
#include <MomoCVCore/video_processor/video_processor.h>


namespace mmcv
{

struct MMCV_EXPORT SingleScannerInfo
{
    int tracking_id_;

    float face_prob_;

    std::vector<float> face_rect_;

    std::vector<float> stable_face_bounds_;

    std::vector<float> landmarks_96_;
    
    std::vector<float> orig_landmarks_96_;
    
    std::vector<float> orig_landmarks_137_;
    
    std::vector<float> landmarks_137_;

    std::vector<float> euler_angles_;

    std::vector<uint8_t> features_;

    int features_quality_;
    
    int face_id_; //Only for track in Wowo Scanner
};

class MMCV_EXPORT ScannerInfo : public VideoInfo
{
public:

#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/facescanner/ScannerInfo");
#endif

    std::map<int, SingleScannerInfo> scanner_infos_;
    
    std::vector<SingleScannerInfo> list_scanner_infos_;
};

class MMCV_EXPORT FaceScanner
{
public:
    FaceScanner();
    virtual ~FaceScanner();
    
    void reset();

    bool load_model(const std::string& fd_path);

    bool load_model(const std::vector<uint8_t>& fd_buf);

    bool process_frame(const MMFrame& _frame, const VideoParams& video_params, ScannerInfo& _ret_register);
    
    

private:
    bool is_same_bounds(const MMRect& a_, const MMRect& b_);

    std::vector<float> pre_box_lengths_;
    std::vector<std::vector<float> > pre_center_pts_;

    std::shared_ptr<VideoProcessor> video_processor_;

    std::map<int, SingleScannerInfo> scanner_infos_;
    std::map<int, MMRect> stable_face_bounds_;
    
    std::vector<SingleScannerInfo> list_scanner_infos_;
    std::vector<MMRect> list_stable_face_bounds_;
    
    int faceIdCnt = 0;
    std::map<int, int> trackId2FaceId;
    mmcv::ObjectTracker *pObjectTracker;
    mmcv::ObjectTrackerParams base_params;
    mmcv::ObjectTrackerInfo ret;
    mmcv::MMRect faceRectToTrack;
    mmcv::MMRect trackRect;
    int trackFaceId;
    bool needTrack;
    bool needInit;
    bool trackRectValid;
};

}
