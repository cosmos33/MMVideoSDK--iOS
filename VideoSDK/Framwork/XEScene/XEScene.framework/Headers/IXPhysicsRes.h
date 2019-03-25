#ifndef _IXPHYSICSRES_H_
#define _IXPHYSICSRES_H_

#include "XArray.h"
#include "XMath3D.h"
#include "XRefCount.h"
#include "XArray.h"
#include "IXConstraint.h"

// 物理资源
enum PhysicsResourceType
{
	// 静态物理资源，在模型转换时生成，包括碰撞Mesh，碰撞凸包等
	PRT_STATIC = 0,
	// 骨骼模型物理资源，在模型转换时生成，包括碰撞体和约束关节
	PRT_SKELETAL,
	PRT_NUM
};

class XFileBase;
class IXPhysicsRes : public XMemBase, public XRefCount
{
public:
	virtual ~IXPhysicsRes(){}

	virtual PhysicsResourceType		GetType() const = 0;

	/**
	* 获取资源路径
	* @return 资源路径
	*/
	virtual const xchar*			GetName() = 0;

	/**
	* 释放资源
	* @notice 引用计数减1
	*/
	virtual void					Release() = 0;
	
	/*
	* 内部调用
	*/
	virtual xbool					Save(XFileBase* pFile) = 0;
	virtual	xbool					Load(XFileBase* pFile) = 0;
};

namespace physx
{
	class PxDefaultMemoryOutputStream;
}

class IXStaticPhysicsRes : public IXPhysicsRes
{
public:
	virtual xbool AddStaticGeometry(physx::PxDefaultMemoryOutputStream* pGeometryBuffer) = 0;
	virtual xbool AddConvexGeomerty(physx::PxDefaultMemoryOutputStream* pGeometryBuffer) = 0;
};

class XModel;
class XSkinData;
class XSkeleton;
class IXSkeletalBody;
class IXConstraint;
class IXSkeletalPhysicsRes : public IXPhysicsRes
{
public:
	enum EPhysResFitVertWeight
	{
		EVW_ANY_WEIGHT,
		EVW_DOMINANT_WEIGHT
	};

	struct XPhysResCreateParams
	{
		XPhysResCreateParams()
			: fMinBoneSize(0.2f)
			, fMinWeldSize(1.e-4f)
			, eVertWeight(EVW_DOMINANT_WEIGHT)
			, eAngularConstraintMode(CM_LIMITED)
			, bAutoOrientToBone(xtrue)
			, bCreateConstraints(xtrue)
			, bWalkPastSmall(xtrue)
			, bBodyForAll(xfalse) {}

		xfloat32				fMinBoneSize;
		xfloat32				fMinWeldSize;
		EPhysResFitVertWeight	eVertWeight;
		EConstraintMotion		eAngularConstraintMode;
		xbool					bAutoOrientToBone;
		xbool					bCreateConstraints;
		xbool					bWalkPastSmall;
		xbool					bBodyForAll;
		XArray<XString>			aPhysicsBones;
	};

	struct XPhyConstraintBoneNames
	{
		XString					strBone1Name;
		XString					strBone2Name;
		

		xbool operator== (const XPhyConstraintBoneNames& rhs)
		{
			return strBone1Name == rhs.strBone1Name && strBone2Name == rhs.strBone2Name;
		}
	};

	virtual const xchar*		GetModelFile() const = 0;

	// 从Model初始化骨骼物理资源
	virtual xbool				InitFromSkinModel(const xchar* szSkinModelFile, const XPhysResCreateParams& Params) = 0;

	virtual xbool				CreateSkeletalBody(const xchar* szBoneName) = 0;
	virtual void				RemoveSkeletalBody(const xchar* szBoneName) = 0;
	virtual xbool				CreateConstraint(const xchar* szBone1Name, const xchar* szBone2Name) = 0;
	virtual void				RemoveConstraint(const xchar* szBone1Name, const xchar* szBone2Name) = 0;

	virtual IXSkeletalBody*		GetSkeletalBody(const xchar* szBoneName) = 0;
	virtual IXConstraint*		GetConstraint(const xchar* szBone1Name, const xchar* szBone2Name) = 0;

	virtual void				DebugDraw(IXModelInstance* pModelIns, const XCOLORBASE& Color = XCOLORBASE(1.0f, 0.0f, 0.0f, 1.0)) const = 0;
	//获取资源中所有绑定了刚体的骨骼名称
	virtual void				GetAllBoneName(XArray<XString>& aBoneNames) = 0;
	//获取资源中所有关节绑定的骨骼名称对
	virtual void				GetAllConstraintBoneNames(XArray<XPhyConstraintBoneNames>& aConstraintBoneNames) = 0;

};
#endif
