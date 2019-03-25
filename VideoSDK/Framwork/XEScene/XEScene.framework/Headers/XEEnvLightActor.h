/******************************************************************************

@File         XEEnvLightActor.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEENVLIGHTACTOR_H
#define XEENVLIGHTACTOR_H
#include "XEActor.h"
#include "XELightComponent.h"

class XEEnvLightActor
	:public XEActor
{
public:
	XEEnvLightActor();
	~XEEnvLightActor();
public:
	XE_ACTOR_CAST(XEEnvLightActor)
    XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEEnvLightActor)
	virtual void Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void Render(XEViewport* pViewport) override;
	virtual void Initialize(XEWorld* pWorld) override;
	static const XString ACTOR_TYPENAME;
};

#endif // XEENVLIGHTACTOR_H
