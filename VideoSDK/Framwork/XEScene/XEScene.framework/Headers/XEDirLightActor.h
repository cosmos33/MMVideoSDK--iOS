/******************************************************************************

@File         XEDirLightActor.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEDIRECTIONLIGHTACTOR_H
#define XEDIRECTIONLIGHTACTOR_H
#include "XEActor.h"
#include "XELightComponent.h"
#include "XECanvas3DTextureComponent.h"

class XEDirLightActor
	:public XEActor
{
public:
	XEDirLightActor();
	~XEDirLightActor();
public:
	XE_ACTOR_CAST(XEDirLightActor)
    XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEDirLightActor)
	virtual void Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void Render(XEViewport* pViewport) override;
	virtual void Initialize(XEWorld* pWorld) override;
	virtual void Release() override;
	static const XString ACTOR_TYPENAME;
private:
	void RenderDummyShape(XEViewport* pViewport) override;
protected:
	XECanvas3DTextureComponent m_Canvas3DTexture;
	xfloat32                   m_fLastDummyRenderScale;
};

#endif // XEDIRECTIONLIGHTACTOR_H
