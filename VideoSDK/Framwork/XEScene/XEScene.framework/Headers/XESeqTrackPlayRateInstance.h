/******************************************************************************

@File         XESeqTrackPlayRateInstance.h

@Version       1.0 

@Created      2018,5, 3

@HISTORY:

******************************************************************************/
#ifndef _XE_SEQ_TRACK_PLAY_RATE_INSTANCE_H
#define _XE_SEQ_TRACK_PLAY_RATE_INSTANCE_H

#include "XESeqBase.h"

class XESeqTrackPlayRate;
class XESeqTrackPlayRateInstance 
	: public XESeqBaseInstance
{
public:
	XESeqTrackPlayRateInstance(XESeqTrackPlayRate* pNodeTl);
	virtual ~XESeqTrackPlayRateInstance();
public:
	virtual void            SetTime(xint32 nMicrosecond) override;//in microsecond.
	XESeqTrackPlayRate*     GetSeqTrackPlayRateTemplate();
public:
	XE_USER_NODE_CAST(XESeqTrackPlayRateInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

};

#endif // _XE_SEQ_TRACK_PLAY_RATE_INSTANCE_H
