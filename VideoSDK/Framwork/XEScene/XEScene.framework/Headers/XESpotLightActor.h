
#ifndef XESPOTLIGHTACTOR_H
#define XESPOTLIGHTACTOR_H
#include "XEActor.h"
#include "XELightComponent.h"
#include "XECanvas3DTextureComponent.h"

class XESpotLightActor
	:public XEActor
{
public:
	XESpotLightActor();
	~XESpotLightActor();
public:
	XE_ACTOR_CAST(XESpotLightActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XESpotLightActor)
	virtual void Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
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

#endif
