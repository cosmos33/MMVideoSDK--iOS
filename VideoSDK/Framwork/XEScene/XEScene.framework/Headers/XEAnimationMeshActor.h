/******************************************************************************

@File         XEAnimationMeshActor.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEANIMATIONMESHACTOR_H
#define XEANIMATIONMESHACTOR_H
#include "XEActor.h"
#include "XEAnimatableModelComponent.h"

class XEAnimationMeshActor :public XEActor
{
public:
	XEAnimationMeshActor();
	~XEAnimationMeshActor(){};
public:
	virtual void                 Initialize(XEWorld* pWorld) override;
public:
	XE_ACTOR_CAST(XEAnimationMeshActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEAnimationMeshActor)
	static const XString	ACTOR_TYPENAME;
};

#endif // XEANIMATIONMESHACTOR_H
