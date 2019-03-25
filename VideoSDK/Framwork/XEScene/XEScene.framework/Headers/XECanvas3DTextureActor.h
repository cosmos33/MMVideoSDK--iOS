/******************************************************************************

@File         XECanvas3DTextureActor.h

@Version       1.0

@Created      2017, 11, 9

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XECANVAS3DTEXTUREACTOR_H
#define XECANVAS3DTEXTUREACTOR_H
#include "XEActor.h"
class XECanvas3DTextureActor :public XEActor
{
public:
	XECanvas3DTextureActor();
	~XECanvas3DTextureActor(){};
public:
	virtual void Initialize(XEWorld* pWorld) override;
	XE_ACTOR_CAST(XECanvas3DTextureActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XECanvas3DTextureActor)
	static const XString	ACTOR_TYPENAME;
};

#endif // XECANVAS3DTEXTUREACTOR_H
