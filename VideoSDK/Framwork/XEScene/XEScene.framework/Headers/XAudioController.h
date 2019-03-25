#ifndef XAUDIO_CONTROLLER_H_
#define XAUDIO_CONTROLLER_H_

#include <set>
#include <memory>
#include <mutex>
#include <thread>

#include "XRefCount.h"
#include "XAudioBase.h"

namespace XAudio
{
	class XAudioListener;
	class XAudioSource;
	
	class XAudioController : public XRefCount
	{		
		friend class XAudioSource;

	public:
		static XAudioController*		Create();
		
		XAudioController();
		
		virtual ~XAudioController();

	private:			
		bool initialize();	

		void finalize();

		void pause();

		void resume();	

		void update(float elapsedTime);

		void addPlayingSource(XAudioSource* source);

		void removePlayingSource(XAudioSource* source);

		static void streamingThreadProc(void* arg);


		bool                         m_streamingThreadActive;
		ALCdevice*                   m_alcDevice;
		ALCcontext*                  m_alcContext;
		XAudioSource*                m_pausingSource;
		std::set<XAudioSource*>      m_playingSources;
		std::set<XAudioSource*>      m_streamingSources;

		std::unique_ptr<std::thread> m_streamingThread;
		std::unique_ptr<std::mutex>  m_streamingMutex;
	};

}

#endif
