/******************************************************************************

@File         XEARAdsTrackPlayRate.h

@Version       1.0 

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef XE_ARADS_TRACK_PLAY_RATE_H
#define XE_ARADS_TRACK_PLAY_RATE_H

#include "XETrackVirtual.h"
#include "XETrackFloat.h"

class XEARAdsTrackPlayRate
	: public XETrackVirtual<XETrackFloat>
{
public:
	XEARAdsTrackPlayRate();
	virtual ~XEARAdsTrackPlayRate();
public:
	virtual void            Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*     Serialize(XMLElement* pEleParent)override;
	virtual xbool           GetOutValueForInVal(xint32 nMicrosecond, void* pOutVal) override;
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

};

#endif // XE_ARADS_TRACK_PLAY_RATE_H
