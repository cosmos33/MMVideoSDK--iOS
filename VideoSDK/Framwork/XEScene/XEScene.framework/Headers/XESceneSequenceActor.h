/******************************************************************************

@File         XESceneSequence.h

@Version       1.0

@Created      2018, 3, 8

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XESCENESEQUENCEACTOR_H
#define XESCENESEQUENCEACTOR_H
#include "XEActor.h"
#include "XESceneSequenceComponent.h"
#include "XECanvas3DTextureComponent.h"

class XESceneSequenceActor :public XEActor
{
public:
	XESceneSequenceActor();
	~XESceneSequenceActor(){};
public:
	virtual void                 Initialize(XEWorld* pWorld) override;
	virtual void                 RenderDummyShape(XEViewport* pViewport) override;
	virtual void                 Release() override;
public:
	XE_ACTOR_CAST(XESceneSequenceActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XESceneSequenceActor)
	static const XString	ACTOR_TYPENAME;
protected:
	XECanvas3DTextureComponent   m_Canvas3DTexture;
};

#endif // XESCENESEQUENCEACTOR_H
