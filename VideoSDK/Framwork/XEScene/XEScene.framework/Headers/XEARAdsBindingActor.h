/******************************************************************************

@File         XEARAdsBindingActor.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef XE_ARADS_BINDING_ACTOR_H
#define XE_ARADS_BINDING_ACTOR_H

#include "XEARAdsBindingTransform.h"

class XEARAdsBindingActor
	:public XEARAdsBindingTransform
{
	friend class XEARAdsBindingActorInstance;
public:
	XEARAdsBindingActor();
	virtual ~XEARAdsBindingActor();
public:
	virtual void                 Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*          Serialize(XMLElement* pEleParent) override;
	virtual XETrackBase*         SetupComponentTrack(XETreeNode::Manager* pNodeMgr);
	X_FORCEINLINE const XString& GetBindActorName()const{ return m_strBindActorName; }
	X_FORCEINLINE void           SetBindActorName(const XString& strName){ m_strBindActorName = strName; }
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	XString              m_strBindActorName;
};

#endif // XE_ARADS_BINDING_ACTOR_H
