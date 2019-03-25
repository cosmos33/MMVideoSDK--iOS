/******************************************************************************

@File         XETrackInt32.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_TRACK_INT32_H
#define XE_SEQ_TRACK_INT32_H
#include "XETrackBase.h"

class XETrackInt32 :public XETrackBase
{
public:
	XETrackInt32();
	virtual ~XETrackInt32();
public:
	virtual void          Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*   Serialize(XMLElement* pEleParent)override;
	virtual xbool         GetOutValueForInVal(xint32 nMicrosecond, void* pOutVal) override;
public:
	XE_USER_NODE_CAST(XETrackInt32)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_SEQ_TRACK_INT32_H
