/******************************************************************************

@File         XEARAdsBinding.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef XE_ARADS_BINDING_H
#define XE_ARADS_BINDING_H

#include "XEARAdsBase.h"

class XETrackBase;
class XEARAds;
class XEARAdsBinding :public XEARAdsBase
{
public:
	XEARAdsBinding();
	virtual ~XEARAdsBinding();
public:
	virtual void         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent) override;
public:
	XETrackBase*         CreateTrack(const XString& szTrackType, XETreeNode::Manager* pNodeMgr);
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_ARADS_BINDING_H
