/******************************************************************************

@File         XECANVAS2DRECTANGLEACTOR_H.h

@Version       1.0

@Created      2017, 11, 9

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XECANVAS2DRECTANGLEACTOR_H
#define XECANVAS2DRECTANGLEACTOR_H
#include "XEActor.h"
class XECanvas2DRectangleActor :public XEActor
{
public:
	XECanvas2DRectangleActor();
	~XECanvas2DRectangleActor(){};
public:
	virtual void Initialize(XEWorld* pWorld) override;
	XE_ACTOR_CAST(XECanvas2DRectangleActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XECanvas2DRectangleActor)
	static const XString	ACTOR_TYPENAME;
};

#endif // XECANVAS2DRECTANGLEACTOR_H
