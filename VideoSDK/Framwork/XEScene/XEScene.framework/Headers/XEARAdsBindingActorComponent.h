/******************************************************************************

@File         XEARAdsBindingActorComponent.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef XE_ARADS_BINDING_COMPONENT_H
#define XE_ARADS_BINDING_COMPONENT_H

#include "XEARAdsBindingTransform.h"

class XEActorComponent;
class XEARAdsBindingActorComponent :public XEARAdsBindingTransform
{
public:
	XEARAdsBindingActorComponent();
	virtual ~XEARAdsBindingActorComponent();
public:
	virtual void         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent) override;
public:
	void                 AcceptComponent(XEActorComponent* pComponent);
private:
	XEActorComponent*    m_pComponent;//in runtime mode to fill.
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_ARADS_BINDING_COMPONENT_H
