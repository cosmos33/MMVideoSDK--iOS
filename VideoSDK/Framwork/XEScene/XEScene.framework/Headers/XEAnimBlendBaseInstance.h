/******************************************************************************

@File         XEAnimBlendBaseInstance.h

@Version       1.0

@Created      2018,9, 27

@HISTORY:

******************************************************************************/
#ifndef _XE_ANIM_BLEND_ELE_BASE_INSTANCE_H
#define _XE_ANIM_BLEND_ELE_BASE_INSTANCE_H

#include "XEUserNode.h"

class XEAnimMonController;
class XEAnimBlendInstance;
class XEAnimBlendBase;

class XEAnimBlendBaseInstance
	: public XEUserNodeInstance
{
public:
	XEAnimBlendBaseInstance(XEAnimBlendBase* pNodeTl);
	virtual ~XEAnimBlendBaseInstance(){}
public:
	XEAnimBlendInstance*          GetAnimBlendInstance();
public:
	XE_USER_NODE_CAST(XEAnimBlendBaseInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_ANIM_BLEND_ELE_BASE_INSTANCE_H
