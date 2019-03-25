/******************************************************************************

@File         XETriggerSphereActor.h

@Version       1.0

@Created      2018, 12, 19 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_TRIGGER_SPHERE_ACTOR_H
#define XE_TRIGGER_SPHERE_ACTOR_H

#include "XETriggerBaseActor.h"

class XETriggerSphereActor : public XETriggerBaseActor
{
public:
	XETriggerSphereActor();
	virtual ~XETriggerSphereActor();

	//XEActor Interface Begin.
	virtual void				Initialize(XEWorld* pWorld) override;
	//XEActor Interface End.

protected:
	//XEActor Interface Begin.

	//XEActor Interface End.

public:
	XE_ACTOR_CAST(XETriggerSphereActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XETriggerSphereActor)
	static const XString ACTOR_TYPENAME;
};
#endif //XE_TRIGGER_SPHERE_ACTOR_H