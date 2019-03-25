#ifndef XEAUDIOCOMPONENT_H
#define XEAUDIOCOMPONENT_H

#include "XEActorComponent.h"
#include "XBase3DTypes.h"
#include "XAudioBase.h"
#include "XAudioSource.h"
#include <map>


class XEAudioComponent :public XEActorComponent
{
public:
	XEAudioComponent();
	~XEAudioComponent();

public:
	virtual void                                     Empty() override;
	virtual void                                     Release() override;
	virtual void                                     Render(XEViewport* pViewport) override;
	virtual void                                     Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void                                     Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*                              Serialize(XMLElement* pEleParent) override;
#if X_PLATFORM_WIN_DESKTOP			                 
	virtual void                                     GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif	
public:
	virtual xbool                                    LoadAsset(const xchar* pPath);
	X_FORCEINLINE const XString&                     GetAssetPath() const { return m_szAssetPath; }

	X_FORCEINLINE XAudio::XAudioSource*			     GetAudioSource(){ return m_pAudioSource; }
	X_FORCEINLINE const XAudio::XAudioSource*	     GetAudioSource() const { return m_pAudioSource; }

	void                                             SetVolume(float volume);
	float                                            GetVolume() const;
	void                                             SetPitch(float pitch);
	void                                             SetMinDistance(float distance);
	void                                             SetAttenuation(float attenuation);
	void                                             SetTime(float time);
	float                                            GetTime() const;
	XAudio::XAudioSource::State                      GetState() const;
	xbool                                            Is3D() const;
	xbool                                            IsLooped() const;
	void                                             SetLooped(xbool looped);
	//void                                             SetVelocity(const XVECTOR3 velocity);

protected:
	virtual xbool              MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual xbool              ApplyWorldTransformImpl(const XMATRIX4& mat) override;
	void                       PlayInternal(const xfloat32 StartTime = 0.f, const xfloat32 FadeInDuration = 0.f, const xfloat32 FadeVolumeLevel = 1.f);

public:
	virtual void FadeIn(xfloat32 FadeInDuration, xfloat32 FadeVolumeLevel = 1.f, xfloat32 StartTime = 0.f);
	virtual	void FadeOut(xfloat32 FadeOutDuration, xfloat32 FadeVolumeLevel);
	virtual void Play(xfloat32 StartTime = 0.f);
	xbool        IsPlaying(void);
	void         Pause();
	void         Stop();
	void         Rewind();
	void         Resume();

public:
	XE_COMPONENT_CAST(XEAudioComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEAudioComponent)
	static const XString COMPONENT_TYPENAME;

protected:
	XAudio::XAudioSource*                            m_pAudioSource;
	XAudio::XAudioImportOptions*                     m_pImportOptions;
	XString                                          m_szAssetPath;
	float                                            m_Volume;
	xfloat32							             m_fPlaybackTime;
	xuint8								             m_bFinished;
	xuint8								             m_bWasPlaying;
	xuint8								             m_bAutoPlay;
	xuint8								             m_bLooped;
	//bool                                             m_bLooped;
	XVECTOR3                                         m_Velocity;
	XVECTOR3                                         m_LastPosition;
	float                                            m_fPitch;	
	xint32                                           m_nPriority;
	float                                            m_fMinDistance;
	float                                            m_fAttenuation;

};

#endif
