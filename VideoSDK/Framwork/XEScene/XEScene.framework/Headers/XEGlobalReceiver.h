/******************************************************************************

@File         XEGlobalReceiver.h

@Version       1.0

@Created      2018,6,12

@HISTORY:

******************************************************************************/
#ifndef _XE_RECEIVER_GLOBAL_H
#define _XE_RECEIVER_GLOBAL_H
#include "XEEventReceiver.h"
class XEGlobalReceiver 
	: public XEEventReceiver
{
public:
	XEGlobalReceiver(){}
	virtual ~XEGlobalReceiver(){}
public:
	virtual XEWorld*           GetReceiverWorld(){ return NULL; }//the receiver channel world.
public:
	XE_EVENT_CHANNEL_TYPE_DEF(RC_CHANNEL)
	X_CLASS_DEF(XEGlobalReceiver)
	static const  XString      RC_CHANNEL;
};
#endif // _XE_RECEIVER_GLOBAL_H
