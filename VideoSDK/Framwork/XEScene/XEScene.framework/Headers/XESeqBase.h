/******************************************************************************

@File         XESeqBase.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef _XE_SEQ_BASE_H
#define _XE_SEQ_BASE_H

#include "XEFactoryUserNodeUtil.h"

class XESequencer;
class XESeqBase 
	: public XEUserNode
{
public:
	XESeqBase(){}
	virtual ~XESeqBase(){}
	typedef XArray<XESeqBase*>      SeqBaseList;
public:
	XESequencer* GetSequencer();
public:
	XE_USER_NODE_CAST(XESeqBase)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	
};

class XEWorld;
class XESequencerInstance;

class XESeqBaseInstance
	:public XEUserNodeInstance
{
public:
	XESeqBaseInstance(XEUserNode* pNodeTl):XEUserNodeInstance(pNodeTl){}
	virtual ~XESeqBaseInstance(){}
	typedef XArray<XESeqBaseInstance*> SeqBaseInstanceList;
public:
	virtual void         SetTime(xint32 nMicrosecond) override;//in microsecond.
	XEWorld*             GetWorld();
	XESequencerInstance* GetSequencerInstance();
public:
	XE_USER_NODE_CAST(XESeqBaseInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_SEQ_BASE_H
