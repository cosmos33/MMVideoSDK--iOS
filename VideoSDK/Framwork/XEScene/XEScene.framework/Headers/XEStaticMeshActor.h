/******************************************************************************

@File         XEStaticMeshActor.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEASTATICMESHACTOR_H
#define XEASTATICMESHACTOR_H
#include "XEActor.h"
#include "XEModelComponent.h"

class XEStaticMeshActor
	:public XEActor
{
public:
	XEStaticMeshActor();
	~XEStaticMeshActor();
public:
	XE_ACTOR_CAST(XEStaticMeshActor)
    XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEStaticMeshActor)
	virtual void          Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void          Render(XEViewport* pViewport) override;
	virtual void          Initialize(XEWorld* pWorld) override;
	static const XString ACTOR_TYPENAME;
public:

};
#endif // XEASTATICMESHACTOR_H
