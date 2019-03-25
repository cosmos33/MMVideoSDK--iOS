/******************************************************************************

@File         XESeqBindingActorInstance.h

@Version       1.0

@Created      2018,5, 3

@HISTORY:

******************************************************************************/
#ifndef _XE_SEQ_BINDING_ACTOR_INSTANCE_H
#define _XE_SEQ_BINDING_ACTOR_INSTANCE_H
#include "XESeqBase.h"
#include "XETransform.h"

class XEActor;
class XESeqBindingActor;
class XESeqBindingActorInstance 
	:public XESeqBaseInstance
{
public:
	XESeqBindingActorInstance(XESeqBindingActor* pNodeTl);
	virtual ~XESeqBindingActorInstance();
public:
	virtual void         SetTime(xint32 nMicrosecond) override;//in microsecond.
	virtual void         Apply() override;
	virtual xbool        AcceptActor(XEActor* pActor);
	XEActor*			 GetAcceptActor(){ return m_pActor; }
	XESeqBindingActor*   GetSeqBindingActorTemplate();
protected:
	virtual void		 SetActorTemplateAssetPath(XESeqBindingActor* pBindingActorTemplate, XEActor* pActor);
protected:
	XEActor*             m_pActor;
public:
	XE_USER_NODE_CAST(XESeqBindingActorInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_SEQ_BINDING_ACTOR_INSTANCE_H
