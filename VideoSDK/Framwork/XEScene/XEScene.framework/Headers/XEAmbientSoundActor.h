#ifndef XE_AMBIENTSOUNDACTOR_H
#define XE_AMBIENTSOUNDACTOR_H
#include "XEActor.h"


class XEAmbientSoundActor : public XEActor
{
public:
	XEAmbientSoundActor();
	~XEAmbientSoundActor(){};

private:

public:
	virtual void Initialize(XEWorld* pWorld) override;	
	virtual void RenderDummyShape(XEViewport* pViewport) override;
	virtual void Release() override;
	virtual void RenderDrawDebug(XEViewport* pViewport)override;
	virtual void Tick(xfloat32 fDel, xbool bForceTick = xtrue)override;
	virtual void Render(XEViewport* pViewport) override;

public:
	XE_ACTOR_CAST(XEAmbientSoundActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEAmbientSoundActor)
	static const XString	   ACTOR_TYPENAME;

};




#endif