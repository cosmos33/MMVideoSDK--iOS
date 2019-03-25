//
//  MomoAP_SoundTrack.hpp
//  test_speexdsp_ver1
//
//  Created by MOMO on 2017/8/17.
//  Copyright © 2017年 ksel. All rights reserved.
//

#ifndef MomoAP_SoundTrack_hpp
#define MomoAP_SoundTrack_hpp

//#include <stdio.h>
#include <string>
#include <vector>


//using namespace std;

// sound track params
typedef struct
{
    int rate;
    int nChannels;
    int nReserved[4];
}Ctrl_Params_SoundTrc;


// interface
class SoundTrack {
    const int    RESULT_LIST_MAX_LENGT;
    const float  NORM;
    const int    SPECTRUM_SIZE;
    const int    ORI_SPEC_SIZE;
    const int    ORI_SPEC_WIDTH;
    const int    ORI_SPEC_HEIGHT;
    const int    TRAIN_SPEC_WIDTH;
    const int    TRAIN_SPEC_HEIGHT;
    const int    WINDOW_SIZE;
    const int    FRAME_SIZE;
    const float  THR_DB;
    const float  THR_SPEECH_ENERGY;
    const float  INFINITY_SMALL ;
    const float  WAV_DECISION_RATIO;
    
public:
    SoundTrack();
    ~SoundTrack();
    
    bool LoadModel(const std::string& prototxt_path, const std::string& model_path);
    bool LoadModel(const std::string& protobin_path);
    bool LoadModel(const std::vector<uint8_t>& model_buf);
    
    bool Reset();
    bool ProcessSound(const std::string& rawReadPath, Ctrl_Params_SoundTrc &params);
    bool ProcessSound(const int16_t* input_buf, int input_len, int segment_index, Ctrl_Params_SoundTrc &params);
    bool GetResult(int& label_return, int& energy_rank);
    bool DeleteSegment(int delete_segment_index);
    
private:
    
    void  *classifier_ptr_;
    void  *spectrum_img_ptr_;
    
    int   segments_num_;
    int   result_;
    int   segments_index_last_;
    
    int   queue_head_;
    int   queue_rear_;
    int   queue_size_;
    int   energy_rank_;
    
    std::vector<std::vector<float> > segments_energies_;
    std::vector<int16_t>buffer_queue_;
    std::vector<std::vector<int> > segments_lables_;
    std::vector<int> empty_vector_int_;
    std::vector<float> empty_vector_float_;

    
    
    bool   gen_spectrum(std::vector<int16_t> &frame, int rate);
    bool   ComputeSpectrumOfHalfSecond(std::vector<int16_t> &data, int rate, std::vector<float> &output);
    int    add_hanning_window(std::vector<float> &frame);
    int    power_spectrum(std::vector<float> &in, std::vector<float> &out);
    
    int    audio_classifier();
    int    cv_resize(std::vector<float> &in);
    int    load_caffe();
    int    classify();
    int    post_process();
    int    energy_post_process();
    
    float  max(std::vector<float>& vector_name);
    float  min(std::vector<float>& vector_name);
    int    normalize(std::vector<float> &arr, int length);
    
    
    bool   check_silence_with_energy(float energy);
    std::vector<float>  calc_block_energy(std::vector<int16_t> &frame, int rate);

};


#endif 
