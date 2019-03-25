/******************************************************************************

@File         XESeqBindingActorParticleInstance.h

@Version       1.0

@Created      2018,5, 3

@HISTORY:

******************************************************************************/
#ifndef _XE_SEQ_BINDING_ACTOR_PARTICLE_INSTANCE_H
#define _XE_SEQ_BINDING_ACTOR_PARTICLE_INSTANCE_H
#include "XESeqBindingActorInstance.h"
class XEActor;
class XESeqBindingActorParticle;
class XESeqBindingActorParticleInstance 
	:public XESeqBindingActorInstance
{
public:
	XESeqBindingActorParticleInstance(XESeqBindingActorParticle* pNodeTl);
	virtual ~XESeqBindingActorParticleInstance();
	enum{ PST_ACTIVE = 0, PST_DEACTIVE, PST_TRIGGER};
public:
	virtual void         SetTime(xint32 nMicrosecond) override;//in microsecond.
	virtual xbool        AcceptActor(XEActor* pActor) override;
protected:
	virtual void		 SetActorTemplateAssetPath(XESeqBindingActor* pBindingActorTemplate, XEActor* pActor)override;
public:
	XE_USER_NODE_CAST(XESeqBindingActorParticleInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
private:
	xint32               m_nActiveState;

};

#endif // _XE_SEQ_BINDING_ACTOR_PARTICLE_INSTANCE_H
