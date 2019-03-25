/******************************************************************************

@File         XEParticleSystemActor.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEAPARTICLESYSTEMACTOR_H
#define XEAPARTICLESYSTEMACTOR_H
#include "XEActor.h"
#include "XEParticleSystemComponent.h"
#include "XECanvas3DTextureComponent.h"

class XEParticleSystemActor:public XEActor
{
public:
	XEParticleSystemActor();
	~XEParticleSystemActor(){};
public:
	virtual void Initialize(XEWorld* pWorld) override;
	XE_ACTOR_CAST(XEParticleSystemActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEParticleSystemActor)
	static const XString	ACTOR_TYPENAME;
private:
	virtual void RenderDummyShape(XEViewport* pViewport) override;
	virtual void FocusActor(xbool bFocus) override;
	virtual void Release() override;
protected:
	XECanvas3DTextureComponent m_Canvas3DTexture;
};

#endif // XEAPARTICLESYSTEMACTOR_H
