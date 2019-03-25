/******************************************************************************

@File         XEPhysicsSkeletalRoot.h

@Version       1.0

@Created      2018,8, 29

@HISTORY:

******************************************************************************/

#ifndef XE_PHYSICS_SKELETAL_ROOT_H
#define XE_PHYSICS_SKELETAL_ROOT_H

#include "XEUserNode.h"
#include "IXSkeletalBody.h"
/*
* XEPhysicsSkeletalRoot:代表一个phy 资源
* 一个模型可能加载了多个phy资源，但同时起作用的有且仅有一个phy（也就是XEPhysicsSkeletalRoot指针）
*/
class XEPhysicsConstraint;
class XEPhysicsSkeletalBody;
class IXSkeletalPhysicsRes;

class XEPhysicsSkeletalRoot : public XEUserNode
{
public:
											XEPhysicsSkeletalRoot();
	virtual								    ~XEPhysicsSkeletalRoot();
	virtual void                            Release() override;
	virtual Manager*						GetNodeManager() override{ return m_pNodeManager; }
	XString&								GetSkeAssetPath(){ return m_strSkeAssetPath; }
	XString									GetPhyAssetPath();//phy asset

	//phy asset
	xbool									LoadSkeletalPhyAsset(const xchar* szPhyResPath, const xchar* szSkePath, xbool bReload = xfalse);
	IXSkeletalPhysicsRes*					GetXSkeletalPhysicsRes(){ return m_pSkeletalPhyRes; }
	xbool									GetIsModify(){ return m_bIsModify; }
	void									SetIsModify(xbool bIsModify){ m_bIsModify = bIsModify; }
	xbool									Save();
public:
	//create or remove body in physics world
	xbool									CreateSkeletalBodyInPhysicsWorld(const xchar* szBoneName);
	xbool									CreateConstraintInPhysicsWorld(const xchar* szBone1Name, const xchar* szBone2Name);
	void									RemovePhysicsSkeletalBodyFromPhysicsWorld(XEPhysicsSkeletalBody* pBodyTemp);
	void									RemoveConstraintFromPhysicsWorld(const xchar* szBone1Name,const xchar* szBone2Name);
	//create or remove node
	XEPhysicsSkeletalBody*					CreatePhysicsSkeletalBodyNode(const xchar* szBoneName);
	XEPhysicsConstraint*					CreateConstraintNode(const xchar* szBone1Name, const xchar* szBone2Name);
	//remove body node or constraint node
	void									RemoveNodeTempate(XEUserNode* pNode, xbool bIncludeChild = xfalse, xbool bReleaseMemory = xtrue, xbool bReleaseNodes = xtrue);

private:
	XEPhysicsSkeletalBody*					IsExistPhysicsSkeletalBodyNode(const xchar* szNodeName);
	XEPhysicsConstraint*					IsExistXEPhysicsConstraint(XString strConstraintNodeName);
	void									RemoveAllSkeletalNode();
	XEPhysicsSkeletalBody*					GetSkeletalBodyNode(const xchar* szNodeName);
public:
	XE_USER_NODE_CAST(XEPhysicsSkeletalRoot)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	static const XString  SUFFIX;
private:
	XString									m_strSkeAssetPath;//ske asset path
	Manager*								m_pNodeManager;
	IXSkeletalPhysicsRes*					m_pSkeletalPhyRes;
	xbool									m_bIsModify;
};

#endif