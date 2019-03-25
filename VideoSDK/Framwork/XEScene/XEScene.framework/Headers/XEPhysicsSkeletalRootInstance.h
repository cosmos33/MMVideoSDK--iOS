/******************************************************************************

@File         XEPhysicsSkeletalRootInstance.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_PHYSICS_SKELETAL_ROOT_INSTANCE_H
#define XE_PHYSICS_SKELETAL_ROOT_INSTANCE_H

#include "XEUserNode.h"
#include "IXConstraint.h"

class XEActorComponent;
class XEModelComponent;
class XEPhysicsConstraint;
class IXSkeletalPhysicsInstance;
class XEPhysicsSkeletalRoot;

//Create   SkeletalPhysicsInstance 
class XEPhysicsSkeletalRootInstance
	: public XEUserNodeInstance
{
public:
										XEPhysicsSkeletalRootInstance(XEPhysicsSkeletalRoot*pRoot);
	virtual                             ~XEPhysicsSkeletalRootInstance();
	XEPhysicsSkeletalRoot*				GetRootTemplate();
	virtual Manager*                    GetNodeManager()override{ return m_pNodeManager; }
	void								RemovePhysicsNodeInstance(XEUserNodeInstance* pNode, xbool bIncludeChild = xfalse, xbool bReleaseMemory = xtrue, xbool bReleaseNodes = xtrue);
	virtual	void						Release() override;
	void								SetAttachComponnet(XEModelComponent* pComponent){ m_pAttachComponnet = pComponent; }
	XEModelComponent*					GetAttachComponnet(){ return m_pAttachComponnet; }
	xbool								ReCreatePhysicsInstance(xbool bIsModify = xfalse);
	virtual void                        Apply()override;
public:
	XE_USER_NODE_CAST(XEPhysicsSkeletalRootInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	XEModelComponent*					m_pAttachComponnet;
	Manager*							m_pNodeManager;
};

#endif // XE_PHYSICS_SKELETAL_ROOT_INSTANCE_H
