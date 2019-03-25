#ifndef XE_MODEL_MESH_SKELETON_NODE_INCLUDE_H
#define XE_MODEL_MESH_SKELETON_NODE_INCLUDE_H
#include "XEUserNode.h"

class XEAnimatableModelComponent;
class XEActorComponent;

class XEModelMeshSkeletonNodeInstance
	:public XEUserNodeInstance
{
public:
	XEModelMeshSkeletonNodeInstance();
	virtual ~XEModelMeshSkeletonNodeInstance();

public:
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif

	virtual void		Release() override;
	void				SetAttachComponent(XEActorComponent* pComponent){ m_pActorComponent = pComponent; }
	XEActorComponent*	GetAttachComponent(){ return m_pActorComponent; }
public:
	XE_USER_NODE_CAST(XEModelMeshSkeletonNodeInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
private:
	XEActorComponent*			m_pActorComponent;
};

#endif //XE_MODEL_MESH_SKELETON_NODE_INCLUDE_H