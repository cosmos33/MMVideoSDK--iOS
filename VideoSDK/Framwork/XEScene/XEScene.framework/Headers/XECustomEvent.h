/******************************************************************************

@File         XECustomEvent.h

@Version       1.0

@Created      2019,1,7

@HISTORY:

******************************************************************************/
#ifndef _XE_EVENT_CUSTOM_H
#define _XE_EVENT_CUSTOM_H
#include "XEEventBase.h"

class XECustomEventReceiver;
class XECustomEvent 
	: public XEEventBase
{
public:
	XECustomEvent();
	virtual ~XECustomEvent(){}
public:
	virtual void                         Release() override;
	virtual void                         Tick(xfloat32 fInterval);//in milliseconds, will not be removed.
	virtual void                         Execute(XEWorld* pWorld = NULL) override;
	virtual XEEventList*                 GetEventList(XEWorld* pWorld = NULL, xbool* pHasTheEvent = NULL) override;//override this if you want to change the event list. World of NULL as default
	virtual xbool                        IsReceiverInChannel(const XString& szChannelName) const override;//to determine the channel here.
	X_FORCEINLINE XECustomEventReceiver* GetDedicatedReceiver() const{ return m_pDedicatedReceiver; }
protected:
	virtual void                         ProcessFromReceiver(XEEventReceiver* rc);
public:
	XE_EVENT_TYPE_DEF(EVENT_TYPENAME)
	X_CLASS_DEF(XECustomEvent)
	static const XString                 EVENT_TYPENAME;
protected:						         
	XECustomEventReceiver*               m_pDedicatedReceiver;//dedicated receiver, inner used.
};
#endif // _XE_EVENT_CUSTOM_H
