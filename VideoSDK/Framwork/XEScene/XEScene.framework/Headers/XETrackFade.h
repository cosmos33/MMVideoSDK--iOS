/******************************************************************************

@File         XETrackFade.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_FADE_H
#define XE_TRACK_FADE_H
#include "XETrackFloat.h"

class XETrackFade 
	:public XETrackFloat
{
public:
	XETrackFade();
	virtual ~XETrackFade();
public:
	virtual void            Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*     Serialize(XMLElement* pEleParent)override;
public:
	XE_USER_NODE_CAST(XETrackFade)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_TRACK_FADE_H
