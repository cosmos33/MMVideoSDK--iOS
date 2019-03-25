/******************************************************************************

@File         XEARAdsTrackPlayRateInstance.h

@Version       1.0 

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef _XE_ARADS_TRACK_PLAY_RATE_INSTANCE_H
#define _XE_ARADS_TRACK_PLAY_RATE_INSTANCE_H

#include "XEARAdsBase.h"

class XEARAdsTrackPlayRate;
class XEARAdsTrackPlayRateInstance
	: public XEARAdsBaseInstance
{
public:
	XEARAdsTrackPlayRateInstance(XEARAdsTrackPlayRate* pNodeTl);
	virtual ~XEARAdsTrackPlayRateInstance();
public:
	virtual void            SetTime(xint32 nMicrosecond) override;//in microsecond.
	XEARAdsTrackPlayRate*   GetARAdsTrackPlayRateTemplate();
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

};

#endif // _XE_ARADS_TRACK_PLAY_RATE_INSTANCE_H
