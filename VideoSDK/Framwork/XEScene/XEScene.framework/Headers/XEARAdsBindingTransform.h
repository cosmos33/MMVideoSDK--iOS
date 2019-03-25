/******************************************************************************

@File         XEARAdsBindingTransform.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef XE_ARADS_BINDING_TRANSFORM_H
#define XE_ARADS_BINDING_TRANSFORM_H

#include "XEARAdsBinding.h"

class XETrackTransform;
class XEARAdsBindingTransform :public XEARAdsBinding
{
public:
	XEARAdsBindingTransform();
	virtual ~XEARAdsBindingTransform();
public:
	virtual void         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent) override;
public:
	XETrackTransform*    AddTransformTrack(XETreeNode::Manager* pNodeMgr);
	XETrackTransform*    GetTransformTrack();
	void                 RemoveTransformTrack(XETreeNode::Manager* pNodeMgr);
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_ARADS_BINDING_TRANSFORM_H
