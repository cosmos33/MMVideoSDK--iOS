/******************************************************************************

@File         XEActorVisibleEvent.h

@Version       1.0

@Created      2018,6,12

@HISTORY:

******************************************************************************/
#ifndef _XE_EVENT_ACTOR_VISIBLE_H
#define _XE_EVENT_ACTOR_VISIBLE_H
#include "XEEventBase.h"
class XEActorVisibleEvent 
	: public XEEventBase
{
public:
	XEActorVisibleEvent(){}
	virtual ~XEActorVisibleEvent(){}
public:
	virtual void                 Release() override;
	virtual void                 Execute(XEWorld* pWorld = NULL) override;
	virtual xbool                IsReceiverInChannel(const XString& szChannelName) const override;//to determine the channel here.
protected:
	virtual void                 ProcessFromReceiver(XEEventReceiver* rc);
public:
	XE_EVENT_TYPE_DEF(EVENT_TYPENAME)
	X_CLASS_DEF(XEActorVisibleEvent)
    static const XString         EVENT_TYPENAME;
	
};
#endif // _XE_EVENT_ACTOR_VISIBLE_H
