/******************************************************************************

@File         XESkeletonInstance.h

@Version       1.0

@Created      2018,4, 26

@HISTORY:

******************************************************************************/
#ifndef XE_SKELONTON_INSTANCE_H
#define XE_SKELONTON_INSTANCE_H
#include "XEUserNode.h"
#include "XEBindSocketInstance.h"

class XESkeleton;
class XSkeleton;
class XEBoneInstance;
class XEPhysicsSkeletalBodyInstance;
class XEPhysicsConstraintInstance;
class XEPhysicsSkeletalRootInstance;
class XEModelComponent;

class XESkeletonInstance 
	:public XEUserNodeInstance
{
public:
	             XESkeletonInstance(XESkeleton* pNodeTl);
	virtual     ~XESkeletonInstance();
public:
	virtual void                   Apply() override;
	virtual Manager*               GetNodeManager() override{ return m_pNodeManager; }
	void                           UpdateSocket();
	XESkeleton*                    GetSkeletonTemplate();
	XEBindSocketInstance*          GetBindSocketInstance(const XString& sokcetName);
	xint32                         GetBindSocketInstances(XEBindSocketInstance::BindSocketInstanceList& socketInstances);
	XEBoneInstance*                GetXEBoneInstance(xint32 nBoneIndex);
	X_FORCEINLINE void             EnableRenderBone(xbool bEnable){ m_bEnableRenderBone = bEnable; }
	X_FORCEINLINE xbool            IsEnableRenderBone(){ return m_bEnableRenderBone; }
	X_FORCEINLINE void             SelectBone(xint32 nIndex){ m_nSelectedBoneIndex = nIndex; }
	X_FORCEINLINE xint32           GetSelectBone()const{ return m_nSelectedBoneIndex; }
	X_FORCEINLINE XSkeleton*       GetXSkeleton(){ return m_pSkelentonIns; }
	X_EES_LINE X_FORCEINLINE const XSkeleton* GetXSkeleton() const{ return m_pSkelentonIns; }
	X_FORCEINLINE  void            SetXSkeleton(XSkeleton* pSkeletonIns){ m_pSkelentonIns = pSkeletonIns; }
	X_EES_LINE X_FORCEINLINE const Manager* GetNodeManager()const{ return m_pNodeManager; }
	X_FORCEINLINE XEModelComponent*	GetAttachComponent(){ return m_pAttachComponent; }
	void						   SetBoneSize(xfloat32 fSize){ m_fBoneSize = fSize; }
	xfloat32					   GetBoneSize(){ return m_fBoneSize; }
	void						   EnableRenderCone(xbool bRender){ m_bIsRenderSkeletalCone = bRender; }
	xbool						   IsEnableRenderCone(){ return m_bIsRenderSkeletalCone; }
	void						   SetAttachComponent(XEModelComponent* pComponent);
	xbool						   ReCreatePhysicsInstance();
	void						   AddSelectedIns(XEUserNode* pIns){ m_aSelectInsNode.AddUnique(pIns); }
	void						   ClearSelectedInsList();

public:
	virtual void                   Release() override;
	virtual void	               Render(XEViewport *pViewport) override;
public:
	XE_USER_NODE_CAST(XESkeletonInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	xbool                          m_bEnableRenderBone;
	xint32                         m_nSelectedBoneIndex;//one only
	XSkeleton*                     m_pSkelentonIns;
	Manager*                       m_pNodeManager;
	xfloat32					   m_fBoneSize;
	xbool						   m_bIsRenderSkeletalCone;
	XEModelComponent*			   m_pAttachComponent;//Create   SkeletalPhysicsInstance
	XArray<XEUserNode*>			   m_aSelectInsNode;
};
#endif // XE_SKELONTON_INSTANCE_H
