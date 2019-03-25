#ifndef XAUDIO_LISTENER_H_
#define XAUDIO_LISTENER_H_

#include "XBase3DTypes.h"
#include "XBaseCamera.h"
#include "XRefCount.h"

namespace XAudio
{
	class XAudioListener : public XRefCount
	{
		friend class XAudioController;		

	public:
		static XAudioListener* getInstance();
		
		const XVECTOR3& getPosition() const;

		void setPosition(const XVECTOR3& position);

		void setPosition(float x, float y, float z);

		float getGain() const;

		void setGain(float gain);

		const XVECTOR3& getVelocity() const;

		void setVelocity(const XVECTOR3& velocity);

		void setVelocity(float x, float y, float z);

		const float* getOrientation() const;

		const XVECTOR3& getOrientationForward() const;

		const XVECTOR3& getOrientationUp() const;

		void setOrientation(const XVECTOR3& forward, const XVECTOR3& up);

		void setOrientation(float forwardX, float forwardY, float forwardZ, float upX, float upY, float upZ);

		XBaseCamera* getCamera() const;

		void setCamera(XBaseCamera* camera);

	private:
		XAudioListener();

		~XAudioListener();

		void cameraChanged(XBaseCamera* camera);

		float        m_gain;
		XVECTOR3     m_position;
		XVECTOR3     m_velocity;
		XVECTOR3     m_orientation[2];
		XBaseCamera* m_camera;
	};

}

#endif
