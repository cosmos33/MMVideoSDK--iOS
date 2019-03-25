/******************************************************************************

@File         XEARAdsBindingActorParticleInstance.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef _XE_ARADS_BINDING_ACTOR_PARTICLE_INSTANCE_H
#define _XE_ARADS_BINDING_ACTOR_PARTICLE_INSTANCE_H

#include "XEARAdsBindingActorInstance.h"

class XEActor;
class XEARAdsBindingActorParticle;
class XEARAdsBindingActorParticleInstance 
	:public XEARAdsBindingActorInstance
{
public:
	XEARAdsBindingActorParticleInstance(XEARAdsBindingActorParticle* pNodeTl);
	virtual ~XEARAdsBindingActorParticleInstance();
	enum{ PST_ACTIVE = 0, PST_DEACTIVE, PST_TRIGGER};
public:
	virtual void         SetTime(xint32 nMicrosecond) override;//in microsecond.
	virtual xbool        AcceptActor(XEActor* pActor) override;
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

};

#endif // _XE_ARADS_BINDING_ACTOR_PARTICLE_INSTANCE_H
