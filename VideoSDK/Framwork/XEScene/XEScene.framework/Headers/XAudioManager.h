#ifndef XAUDIO_MANAGER_H_
#define XAUDIO_MANAGER_H_

#include "XTypes.h"


namespace XAudio
{
	class XAudioSource;
	class XAudioImportOptions;
}
namespace XAudio
{
	class IXAudioManager
	{
	public:
		~IXAudioManager() {}

		virtual bool            Init() = 0;
		virtual void            Release() = 0;

		virtual void            AddAudioSource(const xchar* szAudioFileName, XAudioSource* s, bool paused) = 0;
		virtual void            RemoveAudioSource(XAudioSource* s) = 0;
		virtual void            RemoveAudioSource(const xchar* szAudioFileName) = 0;
		virtual void            StopSources() = 0;
		virtual XAudioSource*   CreateAudio(const xchar* szAudioFileName, XAudioImportOptions* importOptions) = 0;
		virtual XAudioSource*   GetAudio(const xchar* szAudioFileName) = 0;
	};

	extern IXAudioManager* g_pIXAudioManager;
}

#endif