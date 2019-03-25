/******************************************************************************

@File         XESeqBindingActorParticle.h

@Version       1.0

@Created      2018,3, 28

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_BINDING_ACTOR_PARTICLE_H
#define XE_SEQ_BINDING_ACTOR_PARTICLE_H
#include "XESeqBindingActor.h"
class XETrackInt32;
class XESeqBindingActorParticle :public XESeqBindingActor
{
public:
	XESeqBindingActorParticle();
	virtual ~XESeqBindingActorParticle();
public:
	virtual void         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent) override;
	XETrackInt32*        AddToggleTrack(XETreeNode::Manager* pNodeMgr);
public:
	XE_USER_NODE_CAST(XESeqBindingActorParticle)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

};

#endif // XE_SEQ_BINDING_ACTOR_PARTICLE_H
