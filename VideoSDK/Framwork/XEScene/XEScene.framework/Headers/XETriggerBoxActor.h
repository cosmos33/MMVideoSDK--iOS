/******************************************************************************

@File         XETriggerBoxActor.h

@Version       1.0

@Created      2018, 12, 17 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_TRIGGER_BOX_ACTOR_H
#define XE_TRIGGER_BOX_ACTOR_H
#include "XETriggerBaseActor.h"

class XETriggerBoxActor : public XETriggerBaseActor
{
public:
	XETriggerBoxActor();
	virtual ~XETriggerBoxActor();

	//XEActor Interface Begin.
	virtual void				  Initialize(XEWorld* pWorld) override;
	//XEActor Interface End.
protected:
	//XEActor Interface Begin.
	//virtual void                RenderDummyShape(XEViewport* pViewport);
	
	//XEActor Interface End.

public:
	XE_ACTOR_CAST(XETriggerBoxActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XETriggerBoxActor)
	static const XString ACTOR_TYPENAME;
protected:
	
};
#endif //XE_TRIGGER_BOX_ACTOR_H