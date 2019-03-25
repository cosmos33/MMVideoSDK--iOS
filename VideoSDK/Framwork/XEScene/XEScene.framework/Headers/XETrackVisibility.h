/******************************************************************************

@File         XETrackVisibility.h

@Version       1.0

@Created      2018,3, 2

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_VISIBILITY_H
#define XE_TRACK_VISIBILITY_H
#include "XETrackBool.h"

class XETrackVisibility 
	:public XETrackBool
{
public:
	XETrackVisibility();
	virtual ~XETrackVisibility();
public:
	virtual void            Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*     Serialize(XMLElement* pEleParent)override;
public:
	XE_USER_NODE_CAST(XETrackVisibility)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_TRACK_VISIBILITY_H
