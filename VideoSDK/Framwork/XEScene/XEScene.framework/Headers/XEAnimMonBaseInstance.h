/******************************************************************************

@File         XEAnimMonBaseInstance.h

@Version       1.0

@Created      2018,4, 28

@HISTORY:

******************************************************************************/
#ifndef _XE_ANIM_MON_BASE_INSTANCE_H
#define _XE_ANIM_MON_BASE_INSTANCE_H

#include "XEUserNode.h"

class XEAnimMonController;
class XEAnimMontageInstance;
class XEAnimMonBase;

class XEAnimMonBaseInstance 
	: public XEUserNodeInstance
{
public:
	XEAnimMonBaseInstance(XEAnimMonBase* pNodeTl);
	virtual ~XEAnimMonBaseInstance(){}
public:
	XEAnimMontageInstance*          GetAnimMontageInstance();
public:
	XE_USER_NODE_CAST(XEAnimMonBaseInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_ANIM_MON_BASE_INSTANCE_H
