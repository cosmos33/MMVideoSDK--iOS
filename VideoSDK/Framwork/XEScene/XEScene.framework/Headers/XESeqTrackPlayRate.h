/******************************************************************************

@File         XESeqTrackPlayRate.h

@Version       1.0 

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_TRACK_PLAY_RATE_H
#define XE_SEQ_TRACK_PLAY_RATE_H
#include "XETrackVirtual.h"
#include "XETrackFloat.h"

class XESeqTrackPlayRate 
	: public XETrackVirtual<XETrackFloat>
{
public:
	XESeqTrackPlayRate();
	virtual ~XESeqTrackPlayRate();
public:
	virtual void            Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*     Serialize(XMLElement* pEleParent)override;
	virtual xbool           GetOutValueForInVal(xint32 nMicrosecond, void* pOutVal) override;
public:
	XE_USER_NODE_CAST(XESeqTrackPlayRate)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

};

#endif // XE_SEQ_TRACK_PLAY_RATE_H
