/******************************************************************************

@File         XEAnimMonTrack.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_MON_TRACK_H
#define XE_ANIM_MON_TRACK_H
#include "XEAnimMonBase.h"
class XEAnimMonTrack :public XEAnimMonBase
{
public:
	XEAnimMonTrack();
	virtual ~XEAnimMonTrack();
public:
	virtual void         Deserialize(const XMLElement* pEleMontage, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent)override;
	virtual xbool        Verify(AnimMonBaseList* pUnsuggestedList = NULL) override;
public:
	XE_USER_NODE_CAST(XEAnimMonTrack)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_ANIM_MON_TRACK_H
