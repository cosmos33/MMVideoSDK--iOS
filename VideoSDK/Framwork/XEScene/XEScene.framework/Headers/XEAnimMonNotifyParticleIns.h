/******************************************************************************

@File         XEAnimMonNotifyParticleIns.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_MON_NOTIFY_PARTICLE_INS_H
#define XE_ANIM_MON_NOTIFY_PARTICLE_INS_H
#include "XEAnimMonNotifyInstance.h"
#include "XETransform.h"
#include "XEUtility.h"
#include "XEEventReceiver.h"

class XESkeleton;
class XEBindSocketInstance;
class XESocketListenerUserNodeIns;
class XEAnimMonNotifyParticle;
class XEParticleSystemComponent;
class XEActorComponent;

class XEAnimMonNotifyParticleIns
	: public XEAnimMonNotifyInstance
	, public XEEventReceiver
{
public:
	XEAnimMonNotifyParticleIns(XEAnimMonNotifyParticle* pNodeTl);
	virtual ~XEAnimMonNotifyParticleIns();

	struct SpawnParticle
	{
		SpawnParticle() :pParticle(NULL), nLifeTime(10000), nFadeOutTime(-1), nSpawnAccumulateTime(0){}
		xbool operator == (const SpawnParticle& sp) const
		{
			return sp.pParticle == pParticle;
		}
		xint32                                nLifeTime;//set to -1 means will never dead, in millisecond.
		xint32                                nFadeOutTime;//when life is over, should be fade out and then remove it.
		XEParticleSystemComponent*            pParticle;
		xint32                                nSpawnAccumulateTime;//in millisecond.
	};
	typedef XArray<SpawnParticle>  ParticleSystemPawnList;

protected:
	class InsDelayDestroyer :public XEUtility::XEDelayDestroyer
	{
		friend class XEAnimMonNotifyParticleIns;
	public:
		InsDelayDestroyer() :m_nAccumulateFadeOutTime(0), m_pParticleSystemComponent(NULL), m_bShouldBeDeleted(xfalse), m_bSpawnMode(xfalse){}
		virtual ~InsDelayDestroyer(){}
	public:
		virtual xbool ShouldBeDeleted() override;
		virtual void  Release() override;
		virtual void  Tick(xfloat32 fDel) override;
		virtual void  Render(XEViewport* pViewport) override;
	protected:
		xint32                                m_nAccumulateFadeOutTime;//delay time for deleting...
		XEParticleSystemComponent*            m_pParticleSystemComponent;//the transmission particle systems.
		ParticleSystemPawnList                m_aParticleSystemPawnList;//the transmission particle systems.
		xbool                                 m_bSpawnMode;
		xbool                                 m_bShouldBeDeleted;
	};

public:
	virtual void                              Release() override;
	virtual void                              Tick(xfloat32 fInterval) override;
	virtual void                              Render(XEViewport* pViewport) override;
	virtual void                              Apply() override;
	xbool                                     AcceptParticleSystem();
	XEAnimMonNotifyParticle*                  GetAnimMonNotifyParticle();
	xbool                                     SpawnParticleSystem(xint32 nLifeTime = 1.e4f);
	xbool                                     BindXESocketInstance();//will generate from its template.
	void                                      UnbindXESocketInstance();
	xbool                                     GetDefaultPawnTransform(XETransform& tf);
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet               GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
	void                                      OnSocketUpdate(const XMATRIX4& matWorld);//come from the socket-listeners.
	void                                      ClearAllSpawnParticleSystem();
	void                                      ExplainLiveNotify(void* pParam = NULL);
	void                                      ExplainSilentNotify();
	void                                      ApplySpawnMode();
	XEBindSocketInstance*                     GetBindSocketInstance();
	X_FORCEINLINE XEParticleSystemComponent*  GetParticleSystem(){ return m_pParticleSystemComponent; }
protected:
	virtual XEWorld*                          GetReceiverWorld();//the receiver channel world.
public:
	XE_USER_NODE_CAST(XEAnimMonNotifyParticleIns)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME);
	XE_EVENT_CHANNEL_TYPE_DEF(RC_CHANNEL);
	static const XString                      NODE_TYPENAME;
	static const XString                      RC_CHANNEL;
protected:								      
	XEParticleSystemComponent*                m_pParticleSystemComponent;//master particle system for an instance.
	XESocketListenerUserNodeIns*              m_pSocketListenerParticleNode;
	ParticleSystemPawnList                    m_aParticleSystemPawnList;
};

#endif // XE_ANIM_MON_NOTIFY_PARTICLE_INS_H
