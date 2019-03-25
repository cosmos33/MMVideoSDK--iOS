//
// Created by HongjieFu on 2018/6/8.
// AudioEngine Macros
//

#define AUDIO_ENGINE_NAMESPACE_START    namespace audio{
#define AUDIO_ENGINE_NAMESPACE_END      };
#define USING_AUDIO                     using namespace audio;


#define AUDIO_DEBUG

#ifdef AUDIO_DEBUG
#define AUDIO_LOG_D(...) NSLog(__VA_ARGS__)
#define AUDIO_LOG_I(...) NSLog(__VA_ARGS__)
#else
#define AUDIO_LOG_D(...) do {} while (0)
#define AUDIO_LOG_I(...) do {} while (0)
#endif


/**
 * for iOS
 * The total number of sounds/buffers that can be loaded assuming memory is sufficient
 */
//Number of buffers slots that will be initially created
#define XE_BUFFERS_START 64
//Number of buffers that will be added
#define XE_BUFFERS_INCREMENT 16