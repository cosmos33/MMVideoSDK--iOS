/******************************************************************************

@File         XEVariantDataReceiver.h

@Version       1.0

@Created      2018,6,12

@HISTORY:

******************************************************************************/
#ifndef _XE_RECEIVER_VARIANT_DATA_H
#define _XE_RECEIVER_VARIANT_DATA_H
#include "XEEventReceiver.h"
#include "XEVariant.h"
class XEWorld;
class XEViewport;
class XEVariantDataReceiver 
	: public XEEventReceiver
{
public:
	XEVariantDataReceiver() :m_pReceiverWorld(NULL){}
	virtual ~XEVariantDataReceiver(){}
	class Listener
	{
		friend class XEVariantDataReceiver;
	protected:
		virtual void           Ls_OnEventData(XEVariantDataReceiver* pReceiver, XEEventBase* pEvent){}
		virtual void           Ls_OnEventTick(XEVariantDataReceiver* pReceiver, XEEventBase* pEvent, xfloat32 fInterval){}
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
	X_CLASS_DEF(XEVariantDataReceiver)
	static const  XString      RC_CHANNEL;
private:
	XEWorld*                   m_pReceiverWorld;
	ListenerArray              m_aListeners;
	
};
#endif // _XE_RECEIVER_VARIANT_DATA_H
