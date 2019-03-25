/******************************************************************************

@File         XEPhysicsSkeletalActorNodeInstance.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_PHYSICIS_SKELETAL_ACTOR_H
#define XE_PHYSICIS_SKELETAL_ACTOR_H

#include "XEUserNode.h"
#include "XArray.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class XEAnimatableModelComponent;
class XEActorComponent;
class IXCloth;
class XEWorld;

typedef void (*CallBackMessageBox)(const xchar* szInfo);

//as a usernode instance.
class XEPhysicsSkeletalActorNodeInstance
	:public XEUserNodeInstance
{
public:
	XEPhysicsSkeletalActorNodeInstance();
	virtual ~XEPhysicsSkeletalActorNodeInstance();
public:
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif

	virtual void		Release() override;
	void				SetAttachComponent(XEActorComponent* pComponent){ m_pActorComponent = pComponent; }
	XEActorComponent*	GetAttachComponent(){ return m_pActorComponent; }
public:
	XE_USER_NODE_CAST(XEPhysicsSkeletalActorNodeInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
private:
	XEActorComponent*			m_pActorComponent;
};

#endif // XE_PHYSICIS_SKELETAL_ACTOR_H
