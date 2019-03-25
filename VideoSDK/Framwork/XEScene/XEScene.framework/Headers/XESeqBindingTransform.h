/******************************************************************************

@File         XESeqBindingTransform.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_BINDING_TRANSFORM_H
#define XE_SEQ_BINDING_TRANSFORM_H
#include "XESeqBinding.h"
class XETrackTransform;
class XESeqBindingTransform :public XESeqBinding
{
public:
	XESeqBindingTransform();
	virtual ~XESeqBindingTransform();
public:
	virtual void         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent) override;
public:
	XETrackTransform*    AddTransformTrack(XETreeNode::Manager* pNodeMgr);
	XETrackTransform*    GetTransformTrack();
	void                 RemoveTransformTrack(XETreeNode::Manager* pNodeMgr);
public:
	XE_USER_NODE_CAST(XESeqBindingTransform)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_SEQ_BINDING_TRANSFORM_H
