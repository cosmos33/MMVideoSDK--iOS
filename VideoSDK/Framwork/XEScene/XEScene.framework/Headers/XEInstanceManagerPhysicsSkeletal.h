/******************************************************************************

@File         XEInstanceManagerPhysicsSkeletal.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_INSTANCE_MANAGER_PHYSICS_SKELTAL_H
#define XE_INSTANCE_MANAGER_PHYSICS_SKELTAL_H

#include "XESingleton.h"
#include "XTypes.h"
#include "XString.h"
#include "XEUserNode.h"
#include "XEInstanceManagerBase.h"
#include "XEPhysicsSkeletalRoot.h"

class XEPhysicsSkeletalRootInstance;
class XESkeleton;
//一个XEPhysicsSkeletalRoot 对应一个phy资源
class XEInstanceManagerPhysicsSkeletal
	: public XEInstanceManagerBase
	, public XESingleton<XEInstanceManagerPhysicsSkeletal>
{
public:
	XEInstanceManagerPhysicsSkeletal();
	~XEInstanceManagerPhysicsSkeletal(){}

public:
	virtual XEUserNode*						CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld) override;
	virtual XEUserNode*						GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload = xfalse) override;
	virtual void							Reload(const xchar* szAssetFile = NULL);
	virtual void							SaveImpl() const override;
	virtual xbool							IsNodesModifiedImpl()const override;
	void									Release() override;
 public:	
	virtual XEUserNodeInstance*				CreateInstance(const xchar* szPhyResPath, const xchar* szSkePath, xbool bIsReload = xfalse);
	xbool									RemoveSkeletalPhysicsRoot(const xchar* szPhyAssetPath);
public:
	//更新骨架模板
	void									UpdateSkeletalPhyNodeForSkeletonTemplate(XESkeleton* pSkeletonTemplate);
private:
	XEPhysicsSkeletalRoot*					FindSkeletalPhysicsRootTemplate(const xchar* szPhyAssetPath);
	XEPhysicsSkeletalRoot*					LoadPhyAsset(const xchar* szPhyResPath, const xchar* szSkePath, xbool bIsReload = xfalse);
	void									AttachPhysicsBodyTempateToSkeletonTemp(XEPhysicsSkeletalBody* pBodyTemplate,XESkeleton* pSkeletonTp);
	void									AttachPhysicsConstraintTempateToSkeletonTemp(XEPhysicsConstraint* pConstraintTemplate, XESkeleton* pSkeletonTp);
public:
	//for lua side
	static XEInstanceManagerPhysicsSkeletal*GetInstanceManagerPhysicsSkeletal();
private:
	XArray<XEPhysicsSkeletalRoot*>			m_aSkeletalPhysicsRoot;
};

#endif // XE_INSTANCE_MANAGER_PHYSICS_SKELTAL_H
