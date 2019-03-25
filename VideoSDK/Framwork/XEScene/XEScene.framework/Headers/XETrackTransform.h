/******************************************************************************

@File         XETrackTransform.h

@Version       1.0

@Created      2018,3, 2

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_TRANSFORM_H
#define XE_TRACK_TRANSFORM_H
#include "XETrackBase.h"

class XETrackTransform 
	:public XETrackBase
{
public:
	XETrackTransform();
	virtual ~XETrackTransform();
public:
	virtual void            Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*     Serialize(XMLElement* pEleParent)override;
public:
	XE_USER_NODE_CAST(XETrackTransform)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_TRACK_TRANSFORM_H
