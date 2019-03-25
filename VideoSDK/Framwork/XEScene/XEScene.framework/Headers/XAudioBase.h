#ifndef XAUDIO_BASE_H_
#define XAUDIO_BASE_H_

#include "XPlatform.h"
#include "XTypes.h"


#ifdef X_PLATFORM_ANDROID
#include <AL/al.h>
#include <AL/alc.h>
#define AL_ALEXT_PROTOTYPES
#include <AL/alext.h>
#elif X_PLATFORM_WIN_DESKTOP
#define AL_LIBTYPE_STATIC
#include <AL/al.h>
#include <AL/alc.h>
#elif X_PLATFORM_LINUX
#include <AL/al.h>
#include <AL/alc.h>
#elif X_PLATFORM_XOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#define EngineFileSystem  1

namespace XAudio
{
	enum class XAudioFormat
	{
		PCM, 
		VORBIS 
	};
	
	enum class XAudioReadMode
	{		
		LoadDecompressed,		
		LoadCompressed,		
		Stream
	};

	struct XAudioDataInfo
	{
		xuint32 numSamples; 
		xuint32 sampleRate; 
		xuint32 numChannels; 
		xuint32 bitDepth; 
	};

	struct XAudioClipDesc
	{	
		XAudioReadMode readMode;		
		XAudioFormat format;
		xuint32 frequency;		
		xuint32 bitDepth;		
		xuint32 numChannels;		
		bool is3D;		
		bool keepSourceData;

		XAudioClipDesc()
			: readMode(XAudioReadMode::LoadDecompressed)
			, format(XAudioFormat::PCM)
			, frequency(44100)
			, bitDepth(16)
			, numChannels(2)
			, is3D(true)
			, keepSourceData(true)
		{

		}
	};


	class XAudioImportOptions
	{
	public:
		XAudioImportOptions()
			:mFormat(XAudioFormat::PCM), mReadMode(XAudioReadMode::LoadDecompressed), mIs3D(true), mBitDepth(16)
		{

		}

		XAudioFormat getFormat() const { return mFormat; }
		void setFormat(XAudioFormat format) { mFormat = format; }

		XAudioReadMode getReadMode() const { return mReadMode; }
		void setReadMode(XAudioReadMode readMode) { mReadMode = readMode; }

		bool getIs3D() const { return mIs3D; }
		void setIs3D(bool is3d) { mIs3D = is3d; }

		xuint32 getBitDepth() const { return mBitDepth; }
		void setBitDepth(xuint32 bitDepth) { mBitDepth = bitDepth; }

		//static XAudioImportOptions* create();

	private:
		XAudioFormat mFormat;
		XAudioReadMode mReadMode;
		bool mIs3D;
		xuint32 mBitDepth;
	};

	extern ALenum __al_error_code;


#define AL_LAST_ERROR() __al_error_code

#define AL_CHECK( al_code ) do \
		    { \
					        while (alGetError() != AL_NO_ERROR) ; \
        al_code; \
        __al_error_code = alGetError(); \
        if (__al_error_code != AL_NO_ERROR) \
				        { \
            assert(0); \
				        } \
		    } while(0)


}


#endif
