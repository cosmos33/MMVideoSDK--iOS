/******************************************************************************

@File         XESceneARAdsVideoActor.h

@Version       1.0

@Created      2018/5/30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XESCENEARADSVIDEOACTOR_H
#define XESCENEARADSVIDEOACTOR_H

#include "XEActor.h"
#include "XESceneARAdsVideoComponent.h"
#include "XECanvas3DTextureComponent.h"

class XESceneARAdsVideoActor :public XEActor
{
public:
	XESceneARAdsVideoActor();
	~XESceneARAdsVideoActor(){};
public:
	virtual void                 Initialize(XEWorld* pWorld) override;
	virtual void                 RenderDummyShape(XEViewport* pViewport) override;
	virtual void                 Release() override;
public:
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	XE_ACTOR_CAST(XESceneARAdsVideoActor)
	X_CLASS_DEF(XESceneARAdsVideoActor)
	static const XString	ACTOR_TYPENAME;
protected:
	XECanvas3DTextureComponent   m_Canvas3DTexture;
};

#endif // XESCENEARADSVIDEOACTOR_H
