/******************************************************************************

@File         XEPointLightActor.h

@Version       1.0

@Created      2018.10.9

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEPOINTLIGHTACTOR_H
#define XEPOINTLIGHTACTOR_H
#include "XEActor.h"
#include "XELightComponent.h"
#include "XECanvas3DTextureComponent.h"

class XEPointLightActor
	:public XEActor
{
public:
	XEPointLightActor();
	~XEPointLightActor();
public:
	XE_ACTOR_CAST(XEPointLightActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEPointLightActor)
	virtual void Tick(xfloat32 fDels, xbool bForceTick = xtrue) override;
	virtual void Render(XEViewport* pViewport) override;
	virtual void Initialize(XEWorld* pWorld) override;
	virtual void Release() override;
	static const XString ACTOR_TYPENAME;

private:
	virtual void RenderDrawDebug(XEViewport* pViewport)override;
	virtual void RenderDummyShape(XEViewport* pViewport)override;
protected:
	XECanvas3DTextureComponent m_Canvas3DTexture;
	xfloat32                   m_fLastDummyRenderScale;

};

#endif // XEDIRECTIONLIGHTACTOR_H
