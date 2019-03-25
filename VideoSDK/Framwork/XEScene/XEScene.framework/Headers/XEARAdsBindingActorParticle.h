/******************************************************************************

@File         XEARAdsBindingActorParticle.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef XE_ARADS_BINDING_ACTOR_PARTICLE_H
#define XE_ARADS_BINDING_ACTOR_PARTICLE_H

#include "XEARAdsBindingActor.h"

class XETrackInt32;
class XEARAdsBindingActorParticle :public XEARAdsBindingActor
{
public:
	XEARAdsBindingActorParticle();
	virtual ~XEARAdsBindingActorParticle();
	enum{ PST_ACTIVE = 0, PST_DEACTIVE, PST_TRIGGER};
public:
	virtual void         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent) override;
	XETrackInt32*        AddToggleTrack(XETreeNode::Manager* pNodeMgr);

public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

};

#endif // XE_ARADS_BINDING_ACTOR_PARTICLE_H
