/******************************************************************************

@File         XEARAdsBase.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef _XE_ARADS_BASE_H
#define _XE_ARADS_BASE_H

#include "XEFactoryUserNodeUtil.h"

class XEARAds;
class XEARAdsBase
	: public XEUserNode
{
public:
	XEARAdsBase(){}
	virtual ~XEARAdsBase(){}
	typedef XArray<XEARAdsBase*>      ARAdsBaseList;
public:
	XEARAds* GetARAds();
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

class XEWorld;
class XEARAdsInstance;

class XEARAdsBaseInstance
	:public XEUserNodeInstance
{
public:
	XEARAdsBaseInstance(XEUserNode* pNodeTl) :XEUserNodeInstance(pNodeTl){}
	virtual ~XEARAdsBaseInstance(){}
	typedef XArray<XEARAdsBaseInstance*> ARAdsBaseInstanceList;
public:
	virtual void         SetTime(xint32 nMicrosecond) override;//in microsecond.
	XEWorld*             GetWorld();
	XEARAdsInstance*     GetARAdsInstance();
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_ARADS_BASE_H
