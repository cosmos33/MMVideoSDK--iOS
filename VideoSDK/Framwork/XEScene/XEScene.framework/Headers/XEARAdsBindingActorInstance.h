/******************************************************************************

@File         XEARAdsBindingActorInstance.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef _XE_ARADS_BINDING_ACTOR_INSTANCE_H
#define _XE_ARADS_BINDING_ACTOR_INSTANCE_H

#include "XEARAdsBase.h"
#include "XETransform.h"

class XEActor;
class XEARAdsBindingActor;
class XEARAdsBindingActorInstance 
	:public XEARAdsBaseInstance
{
public:
	XEARAdsBindingActorInstance(XEARAdsBindingActor* pNodeTl);
	virtual ~XEARAdsBindingActorInstance();
public:
	virtual void         SetTime(xint32 nMicrosecond) override;//in microsecond.
	virtual void         Apply() override;
	virtual xbool        AcceptActor(XEActor* pActor);
	XEActor*			 GetAcceptActor(){ return m_pActor; }
	XEARAdsBindingActor* GetARAdsBindingActorTemplate();
protected:
	XEActor*             m_pActor;
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_ARADS_BINDING_ACTOR_INSTANCE_H
