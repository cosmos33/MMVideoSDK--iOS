#ifndef X_AUDIOSOURCE_H_
#define X_AUDIOSOURCE_H_

#include "XAudioProperties.h"
#include "XBase3DTypes.h"
#include "XRefCount.h"

namespace XAudio
{
	class XAudioBuffer;

	class XAudioSource : public XRefCount
	{
	public:		
		friend class XAudioController;

		enum State
		{
			INITIAL,
			PLAYING,
			PAUSED,
			STOPPED
		};
		
		static XAudioSource* create(const char* url, XAudioImportOptions* importOptions, bool streamed = false);

		static XAudioSource* create(XAudioProperties* properties, XAudioImportOptions* importOptions);

		void play();
		
		void pause();

		void resume();

		void stop();

		void rewind();
		
		XAudioSource::State getState() const;
		
		bool isStreamed() const;

		bool isStoped() const;

		xbool isLooped() const;
		void setLooped(xbool looped);
		
		float getGain() const;		
		void setGain(float gain);

		float getPitch() const;
		void setPitch(float pitch);

		const XVECTOR3& getVelocity() const;
		void setVelocity(const XVECTOR3& velocity);
		void setVelocity(float x, float y, float z);

		void setTransform(const XMATRIX4& transform);
		xbool is3D() const;

		void setMinDistance(float distance);
		void setAttenuation(float attenuation);
		float getTime() const;

	private:
		XAudioSource(XAudioBuffer* buffer, ALuint source);

		virtual ~XAudioSource();

		XAudioSource& operator=(const XAudioSource&);

		bool streamDataIfNeeded();

		ALuint        m_alSource;
		XAudioBuffer* m_buffer;
		xbool         m_looped;
		float         m_gain;
		float         m_pitch;
		XVECTOR3      m_velocity;		
	};

}

#endif
