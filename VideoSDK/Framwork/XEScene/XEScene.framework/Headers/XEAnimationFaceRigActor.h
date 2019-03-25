/******************************************************************************

@File         XEAnimationFaceRigActor.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_ANIMATION_FACE_RIG_ACTOR_H
#define _XE_ANIMATION_FACE_RIG_ACTOR_H
#include "XEActor.h"
#include "XEAnimatableFaceRigComponent.h"

class XEAnimationFaceRigActor :public XEActor
{
public:
	XEAnimationFaceRigActor();
	~XEAnimationFaceRigActor(){};
public:
	virtual void  Initialize(XEWorld* pWorld) override;
public:
	XE_ACTOR_CAST(XEAnimationFaceRigActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEAnimationFaceRigActor)
	static const XString	ACTOR_TYPENAME;
};

#endif // _XE_ANIMATION_FACE_RIG_ACTOR_H
