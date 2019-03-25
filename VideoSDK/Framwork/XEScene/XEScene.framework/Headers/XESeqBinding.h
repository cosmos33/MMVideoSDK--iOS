/******************************************************************************

@File         XESeqBinding.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_BINDING_H
#define XE_SEQ_BINDING_H
#include "XESeqBase.h"
class XETrackBase;
class XESequencer;
class XESeqBinding :public XESeqBase
{
public:
	XESeqBinding();
	virtual ~XESeqBinding();
public:
	virtual void         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent) override;
public:
	XETrackBase*         CreateTrack(const XString& szTrackType, XETreeNode::Manager* pNodeMgr);
public:
	XE_USER_NODE_CAST(XESeqBinding)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_SEQ_BINDING_H
