/******************************************************************************

@File         XESceneARAds.h

@Version       1.0

@Created      2018/5/30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XESCENEARADSACTOR_H
#define XESCENEARADSACTOR_H

#include "XEActor.h"
#include "XESceneARAdsComponent.h"
#include "XECanvas3DTextureComponent.h"

class XESceneARAdsActor :public XEActor
{
public:
	XESceneARAdsActor();
	~XESceneARAdsActor(){};
public:
	virtual void                 Initialize(XEWorld* pWorld) override;
	virtual void                 RenderDummyShape(XEViewport* pViewport) override;
	virtual void                 Release() override;
public:
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	XE_ACTOR_CAST(XESceneARAdsActor)
	X_CLASS_DEF(XESceneARAdsActor)
	static const XString	ACTOR_TYPENAME;
protected:
	XECanvas3DTextureComponent   m_Canvas3DTexture;
};

#endif // XESCENEARADSACTOR_H
