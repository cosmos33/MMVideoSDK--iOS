/******************************************************************************

@File         XESpawnParticleSystemEvent.h

@Version       1.0

@Created      2018,6,12

@HISTORY:

******************************************************************************/
#ifndef _XE_EVENT_SPAWN_PARTICLE_SYSTEM_H
#define _XE_EVENT_SPAWN_PARTICLE_SYSTEM_H
#include "XEEventBase.h"
#include "XEUtility.h"

class XEParticleSystemComponent;
class XESpawnParticleSystemEvent 
	: public XEEventBase
{
public:
	XESpawnParticleSystemEvent(){}
	virtual ~XESpawnParticleSystemEvent(){}
protected:
	class InsDelayDestroyer :public XEUtility::XEDelayDestroyer
	{
		friend class XESpawnParticleSystemEvent;
	public:
		InsDelayDestroyer() :m_nAccumulateFadeOutTime(0), m_pParticleSystemComponent(NULL), m_bShouldBeDeleted(xfalse){}
		virtual ~InsDelayDestroyer(){}
	public:
		virtual xbool              ShouldBeDeleted() override;
		virtual void               Release() override;
		virtual void               Tick(xfloat32 fDel) override;
		virtual void               Render(XEViewport* pViewport) override;
	protected:
		xint32                     m_nAccumulateFadeOutTime;//delay time for deleting...
		XEParticleSystemComponent* m_pParticleSystemComponent;//the transmission particle systems.
		xbool                      m_bShouldBeDeleted;
	};
public:
	virtual void                   Release() override;
	virtual void                   Execute(XEWorld* pWorld = NULL) override;
	virtual xbool                  IsReceiverInChannel(const XString& szChannelName) const override;//to determine the channel here.
protected:
	virtual void                   ProcessFromReceiver(XEEventReceiver* rc);
public:
	XE_EVENT_TYPE_DEF(EVENT_TYPENAME)
	X_CLASS_DEF(XESpawnParticleSystemEvent)
    static const XString           EVENT_TYPENAME;
	
};
#endif // _XE_EVENT_SPAWN_PARTICLE_SYSTEM_H
