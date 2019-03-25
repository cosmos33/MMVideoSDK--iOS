#ifndef XE_TRACK_COLOR_H
#define XE_TRACK_COLOR_H
#include "XETrackBase.h"

class XETrackColor
	:public XETrackBase
{
public:
	XETrackColor();
	virtual ~XETrackColor();
public:
	virtual void            Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*     Serialize(XMLElement* pEleParent)override;
public:
	XE_USER_NODE_CAST(XETrackColor)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};
#endif