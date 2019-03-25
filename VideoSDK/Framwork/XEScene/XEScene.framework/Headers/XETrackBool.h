/******************************************************************************

@File         XETrackBool.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_TRACK_BOOL_H
#define XE_SEQ_TRACK_BOOL_H
#include "XETrackBase.h"

class XETrackBool :public XETrackBase
{
public:
	XETrackBool();
	virtual ~XETrackBool();
public:
	virtual void          Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*   Serialize(XMLElement* pEleParent)override;
	virtual xbool         GetOutValueForInVal(xint32 nMicrosecond, void* pOutVal) override;
public:
	XE_USER_NODE_CAST(XETrackBool)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_SEQ_TRACK_BOOL_H
