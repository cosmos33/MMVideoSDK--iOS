/******************************************************************************

@File         XECustomEventReceiver.h

@Version       1.0

@Created      2019,1,7

@HISTORY:

******************************************************************************/
#ifndef _XE_RECEIVER_CUSTOM_EVENT_H
#define _XE_RECEIVER_CUSTOM_EVENT_H
#include "XEEventReceiver.h"
#include "XEVariant.h"
class XEWorld;
class XEViewport;
class XECustomEventReceiver 
	: public XEEventReceiver
{
public:
	XECustomEventReceiver() :m_pReceiverWorld(NULL){}
	virtual ~XECustomEventReceiver(){}
	class Listener
	{
		friend class XECustomEventReceiver;
	protected:
		virtual void           Ls_OnEventData(XECustomEventReceiver* pReceiver, XEEventBase* pEvent);
		virtual void           Ls_OnEventTick(XECustomEventReceiver* pReceiver, XEEventBase* pEvent, xfloat32 fInterval){}
		virtual void           Ls_OnEventStatusReady(XECustomEventReceiver* pReceiver, XEEventBase* pEvent){}
		virtual void           Ls_OnEventStatusExplain(XECustomEventReceiver* pReceiver, XEEventBase* pEvent){}
		virtual void           Ls_OnEventStatusEntrance(XECustomEventReceiver* pReceiver, XEEventBase* pEvent){}
		virtual void           Ls_OnEventStatusTrigger(XECustomEventReceiver* pReceiver, XEEventBase* pEvent){}
		virtual void           Ls_OnEventStatusRestore(XECustomEventReceiver* pReceiver, XEEventBase* pEvent){}
		virtual void           Ls_OnEventStatusCustom(XECustomEventReceiver* pReceiver, XEEventBase* pEvent){}
		virtual void           Ls_OnEventStatusRelease(XECustomEventReceiver* pReceiver, XEEventBase* pEvent){}
	};
	typedef XArray<Listener*>  ListenerArray;
public:
	virtual XEWorld*           GetReceiverWorld(){ return m_pReceiverWorld; }//the receiver channel world.
	virtual void               RespondOnEvent(XEEventBase* pEvent) override;
	virtual void               RespondOnEventTick(XEEventBase* pEvent, xfloat32 fInterval) override;//in milliseconds.
	virtual void               SetReceiverWorld(XEWorld* pWorld)override{ m_pReceiverWorld = pWorld; }
	X_FORCEINLINE void         AddListener(Listener* pListener){ m_aListeners.AddUnique(pListener); }
	X_FORCEINLINE xbool        RemoveListener(Listener* pListener){ return m_aListeners.Remove(pListener); }
public:
	XE_EVENT_CHANNEL_TYPE_DEF(RC_CHANNEL)
	X_CLASS_DEF(XECustomEventReceiver)
	static const  XString      RC_CHANNEL;
private:
	XEWorld*                   m_pReceiverWorld;
	ListenerArray              m_aListeners;
	
};
#endif // _XE_RECEIVER_CUSTOM_EVENT_H
