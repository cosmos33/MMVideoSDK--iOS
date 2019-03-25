#pragma once

#include <string>
#include <vector>
#include <MomoCVCore/api_base/momocv_api.h>
#include <MomoCVCore/face_features/face_features.h>

namespace mmcv
{

class MMCV_EXPORT SingleFaceInfo
{
public:
    SingleFaceInfo();
    
#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/SingleFaceInfo");
#endif

    int tracking_id_;
    float face_prob_;
    /*
        0: unknown
        1: perfect
        2: brightness error
        3: clarity error
        4: contrast error
    */
    int quality_;

    /* original coordinates */
    float orig_face_rotate_degree_2d_;
    std::vector<float> orig_face_rect_;
    std::vector<float> orig_landmarks_68_;
    std::vector<float> orig_landmarks_87_;
    std::vector<float> orig_landmarks_96_;
    std::vector<float> orig_landmarks_104_;
    std::vector<float> orig_landmarks_106_;
    std::vector<float> orig_landmarks_137_;

    /* transformed coordinates */
    float face_rotate_degree_2d_;
    std::vector<float> face_rect_;
    std::vector<float> landmarks_68_;
    std::vector<float> landmarks_87_;
    std::vector<float> landmarks_96_;
    std::vector<float> landmarks_104_;
    std::vector<float> landmarks_106_;
    std::vector<float> landmarks_137_;

    // big_features features
    std::vector<uint8_t> features_;
    /*
     -1: has not extract features
     0: unknown, empty img
     1: perfect
     2: brighspot
     3: clarity error
     4: brightness error
     5: contrast error
     */
    int features_quality_;
    
    /*
    -1: model init failed
     0: good frontal face,can be used to register for temporary account
     1: samll degree side face,can be used for face Face Recognition，cann not be used for registration
     2: big degree side face, can not be used Face Recognition
     */
    int facepose_type_;
    
    /*
     0: occlusion
     1: not occlusion
     2: unknown type
     */
    int occflag_;
    
    // default is -1
    float feature_quality_score_;

    // 3
    std::vector<float> euler_angles_;

    // 3x3
    std::vector<float> camera_matrix_;

    // 3x3
    std::vector<float> rotation_matrix_;

    // 3
    std::vector<float> rotation_vector_;

    // 3
    std::vector<float> translation_vector_;

    // 3x4
    std::vector<float> projection_matrix_;

    // 4x4
    std::vector<float> modelview_matrix_;

    // original 3x4 projection doesn't consider z-order culling that an OpenGL system does.
    // so we need to transfer the original coordinate(image coordinate) to NDC coordinate
    // original coordinate transform:
    // [x y z].t() = R * [X Y Z].t() + t
    // x' = x / z
    // y' = y / z
    // u = fx * x' + cx
    // v = fy * y' + cy
    // u / image_width * 2 - 1 --> [-1 1]
    // v / image_height * 2 - 1 --> [-1 1]
    // float far = 100000, near = 0.01;
    // so opengl projection matrix equal:
    // [2 * camera_matrix[0, 0] / image_width       0                                           -1 + (2 * camera_matrix[0, 2] / image_width)    0                               ]
    // [0                                           2 * camera_matrix[1, 1] / image_height      -1 + (2 * camera_matrix[1, 2] / image_height)   0                               ]
    // [0                                           0                                           -(far + near) / (far - near)                    -2 * far * near / (far - near)  ]
    // [0                                           0                                           -1                                              0                               ]
    // 4x4
    std::vector<float> projection_matrix_opengl_;
};

class MMCV_EXPORT FacesInfo
{
public:
    FacesInfo();
    virtual ~FacesInfo();

#ifdef BUILD_JNI
    virtual void to_java(JNIEnv *jenv, jobject ret, std::string cname = "com/momocv/FacesInfo");
#endif

    std::vector<SingleFaceInfo> facesinfo_;
};

enum PoseEstimationType
{
    POSE_ESTIMATION_NORMAL = 0,
    POSE_ESTIMATION_MORE_PRECISE = 1,
    POSE_ESTIMATION_NORMAL_BY87POINTS = 2, // online 2
    POSE_ESTIMATION_WITH_EULERS = 3,
};

class MMCV_EXPORT FaceParams : public BaseParams
{
public:
    FaceParams();
    virtual ~FaceParams();

#ifdef BUILD_JNI
    virtual void from_java(JNIEnv *jenv, jobject params_obj, std::string cname = "com/momocv/FaceParams");
#endif

    //Face detection interval, How many frames between two face detection?
    int frame_interval_;
    
    // [0, 1, 2]
    // version 0 : 96 stable keypoints
    // version 1 : 96points add new eye points
    // version 2 : 137 points
    // default is 0
    int face_alignment_version_;
    
    // [0, INF)
    // max tracking faces.
    // default is 3
    int max_faces_;

    // stable keypoints coefs. [0, INF)
    // default is 2.0
    float keypoints_stable_coef_;

    // [POSE_ESTIMATION_NORMAL, POSE_ESTIMATION_MORE_PRECISE, POSE_ESTIMATION_WITH_EULERS]
    // default is POSE_ESTIMATION_NORMAL
    int pose_estimation_type_;

    // stable pose coefs. [0, INF)
    // default is 2.0
    float pose_stable_coef_;

    // [false, true]
    // detect video or picture.
    // default is false
    bool detect_single_frame_;

    // [false, true]
    // detect quality. default is false, and ret info is true.
    // default is false
    bool image_quality_controller_;
    
    // [false, true]
    // use npd and faster-rcnn mixed  algorithm
    // default is false,if it is set to true, use_npd_ must be false
    bool use_mix_;

    // [false, true]
    // use npd or faster-rcnn facedetect algorithm
    // default is true
    bool use_npd_;
    
    // [false, true]
    // use accelerate npd algorithm for Live broadcast
    // default is false
    bool npd_accelerate_;
    
    // [false, true]
    // ture is asynchronous face detect.
    // default is true
    bool asynchronous_face_detect_;

    // When the face area occupies a very small proportion of the picture
    // if you want to capture faces, please open this switch
    // !!!If you want the param do_facedect_corp_center_ work, the ohther param use_npd_ must be set to false
    // default is false
    bool do_facedect_corp_center_;

    // [false, true]
    // true will make keypoints to be more stable, but will cost more time.
    // default is true
    bool supper_stable_mode_;

    // carefule if you change it
    // default is 45.0
    double fov_;

    // carefule if you change it
    // default is 5000.0
    double zFar_;

    // carefule if you change it
    // default is 0.05
    double zNear_;

    // carefule if you change it
    // default is 1.0
    float focal_length_multiply_;

    // [false, true]
    // ture will make face features.
    // default is false
    bool save_features_;
    
    //specified id will save_features_when more than one person in a frame
    //default is 0, will save all person features
    int extract_feature_id_;
    
    //重置指定id的特征，对于新的客户端提特征逻辑，如果某个ID算法停止提特征了，可以通过此参数对该ID重置，重新提特征
    //默认是: 0 
    //如果被设置为-1，新的客户端提特征逻辑将会失效，采用旧的提特征逻辑
    int reset_feature_id_;
    
    // euler_angles constraint for save features,must be three elements
    // default is[40,45,50] {pitch=40,yaw=45,roll=50}
    std::vector<float> constraint_euler_angles_;

    //[FaceFeaturesParams::V0, FaceFeaturesParams::V1, FaceFeaturesParams::V2]
    //FaceResgister should use FaceFeaturesParams::V2
    //FaceScanner should use FaceFeaturesParams::V1
    // default is FaceFeaturesParams::V0
    int save_features_version_;

    // [false, true]
    // compute feature asynchronous if true, but when save_features_ is false or detect_single_frame_ is true, it'll no work.
    // default is false
    bool asynchronous_save_features_;

    // [false, true]
    // feature quality strict level
    // default is false
    bool feature_strict_;

    // [false, true]
    // default is false
    bool debug_on_;

    // debug file destination path.
    // default is "momocv_debug.log"
    std::string debug_output_;
};

class MMCV_EXPORT FaceProcessor
{
public:
    FaceProcessor();
    virtual ~FaceProcessor();

    bool load_model(const std::string& fd_path);
    
    bool load_model(const std::string& fd_path, const int _mobile_level);

    bool load_model(const std::vector<uint8_t>& fd_buf);

    bool load_model(const std::vector<uint8_t>& fd_buf, const int _mobile_level);

    bool process_frame(const MMFrame& _frame, const FaceParams& params, FacesInfo& _ret);

    bool reset();

private:
    void* face_processor_impl_;
};

}
