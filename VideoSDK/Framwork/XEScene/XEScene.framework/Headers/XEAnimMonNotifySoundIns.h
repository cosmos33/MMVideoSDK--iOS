#ifndef XE_ANIM_MON_NOTIFY_SOUND_INS_H
#define XE_ANIM_MON_NOTIFY_SOUND_INS_H

#include "XEAnimMonNotifyInstance.h"
#include "XETransform.h"
#include "XEUtility.h"
#include "XEEventReceiver.h"


class XESkeleton;
class XEBindSocketInstance;
class XESocketListenerUserNodeIns;
class XEAnimMonNotifySound;
class XEAudioComponent;
class XEActorComponent;
class XEAnimMonNotifySoundIns
	: public XEAnimMonNotifyInstance
	, public XEEventReceiver
{
public:
	XEAnimMonNotifySoundIns(XEAnimMonNotifySound* pNodeTl);
	virtual ~XEAnimMonNotifySoundIns();

	struct SpawnAudio
	{
		SpawnAudio() :pAudio(NULL), nLifeTime(10000), nFadeOutTime(-1), nSpawnAccumulateTime(0){}
		xbool operator == (const SpawnAudio& sp) const
		{
			return sp.pAudio == pAudio;
		}
		xint32                       nLifeTime;
		xint32                       nFadeOutTime;
		XEAudioComponent*            pAudio;
		xint32                       nSpawnAccumulateTime;
	};
	typedef XArray<SpawnAudio>  AudioPawnList;

protected:
	class InsDelayDestroyer :public XEUtility::XEDelayDestroyer
	{
		friend class XEAnimMonNotifySoundIns;
	public:
		InsDelayDestroyer() :m_nAccumulateFadeOutTime(0), m_pAudioComponent(NULL), m_bShouldBeDeleted(xfalse), m_bSpawnMode(xfalse){}
		virtual ~InsDelayDestroyer(){}
	public:
		virtual xbool ShouldBeDeleted() override;
		virtual void  Release() override;
		virtual void  Tick(xfloat32 fDel) override;
		virtual void  Render(XEViewport* pViewport) override;
	protected:
		xint32                                m_nAccumulateFadeOutTime;
		XEAudioComponent*                     m_pAudioComponent;
		AudioPawnList                         m_aAudioPawnList;
		xbool                                 m_bSpawnMode;
		xbool                                 m_bShouldBeDeleted;
	};

public:
	virtual void                              Release() override;
	virtual void                              Tick(xfloat32 fInterval) override;
	virtual void                              Render(XEViewport* pViewport) override;
	virtual void                              Apply() override;
	xbool                                     AcceptSound();
	XEAnimMonNotifySound*                     GetAnimMonNotifySound();
	xbool                                     SpawnSound(xint32 nLifeTime = 1.e4f);
	xbool                                     BindXESocketInstance();
	void                                      UnbindXESocketInstance();
	xbool                                     GetDefaultPawnTransform(XETransform& tf);
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet               GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
	void                                      OnSocketUpdate(const XMATRIX4& matWorld);
	void                                      ClearAllSpawnSound();
	void                                      ExplainLiveNotify(void* pParam = NULL);
	void                                      ExplainSilentNotify();
	void                                      ApplySpawnMode();
	XEBindSocketInstance*                     GetBindSocketInstance();
	X_FORCEINLINE XEAudioComponent*           GetSound(){ return m_pAudioComponent; }
protected:
	virtual XEWorld*                          GetReceiverWorld();
public:
	XE_USER_NODE_CAST(XEAnimMonNotifySoundIns)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME);
	XE_EVENT_CHANNEL_TYPE_DEF(RC_CHANNEL);
	static const XString                      NODE_TYPENAME;
	static const XString                      RC_CHANNEL;
protected:
	XEAudioComponent*                         m_pAudioComponent;
	XESocketListenerUserNodeIns*              m_pSocketListenerSoundNode;
	AudioPawnList                             m_aAudioPawnList;

};



#endif