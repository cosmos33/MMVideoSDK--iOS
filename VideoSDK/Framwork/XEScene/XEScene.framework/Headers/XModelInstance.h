/******************************************************************************

@File         XModelInstance.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/

#ifndef _X_MODEL_INSTANCE_H_
#define _X_MODEL_INSTANCE_H_

#include "XArray.h"
#include "XCustomGeometry.h"
#include "XGlobalFuncs.h"
#include "XModel.h"
#include "XPrimitiveBase.h"
#include "XBaseCoordSpace.h"
#include "XObject.h"
#include "XBlendShapeTarget.h"


class XSkeleton;
class IXVertexDesc;
class XPerspectiveCamera;
class IXMaterialInstance;
class XBlendShapeInstance;

struct XHitMeshInfo
{
	XString	strHitBoneName;
	XString strHitSkinName;
	XString strHitMeshName;
	IXMaterialInstance* pMeshMtlIns;

	XHitMeshInfo() : pMeshMtlIns(NULL) {}
};

struct XRAYTRACERT
{
	XRAYTRACERT() :pCustomData(NULL){}
	XVECTOR3			vPoint;
	XVECTOR3			vHitPos;
	XVECTOR3			vNormal;
	XVECTOR3			vTangent;
	XVECTOR3			vBinormal;
	xfloat32			fFraction;
	XHitMeshInfo		hitMesh;
	void*				pCustomData;
};

struct XOutputVertexTransform
{
	XOutputVertexTransform() : Position(0.0f), TangentZ(0.0f), TangentX(0.0f) {}
	XOutputVertexTransform(const XVECTOR3& otherPosition, const XVECTOR3& otherTangentZ, const XVECTOR3& otherTangentX) 
		: Position(otherPosition), TangentZ(otherTangentZ), TangentX(otherTangentX){}
	XVECTOR3		Position;
	XVECTOR3		TangentZ;
	XVECTOR3		TangentX;
};

class IXModelInstance : public XBaseCoordSpace, public IXPrimitiveBase, public IXObject
{
public:
	 virtual							~IXModelInstance() {}
	virtual void						Release() = 0;
	virtual xbool						RayTraceToAABB(const XVECTOR3& vStart, const XVECTOR3& vDelta, xfloat32 &fFraction) = 0;
	virtual xbool						RayTraceToMesh(const XVECTOR3& vStart, const XVECTOR3& vDelta, XRAYTRACERT* pOutTraceRt, xbool bForceTwoSided = xfalse) = 0;
	virtual void						Hide(xbool bHide) = 0;
	virtual xbool						IsHidden() const = 0;
	virtual const XModel*				GetSkinModel() const = 0;
	virtual XModel*						GetSkinModel() = 0;
	virtual XSkeleton*					GetSkeleton() = 0;
	virtual const XSkeleton*			GetSkeleton() const = 0;
	virtual void						GetBoneOBB(XArray<XCusOBB>& aOutObb) const = 0;
	virtual IXVertexDesc*				GetMeshVertexDef(xint32 nSkinIndex, xint32 nLODIndex, xint32 nMeshIndex, xbool bUseInstancedRender = xfalse) = 0;
	virtual XModelType					GetSkinModelType() const = 0;
	virtual xbool						GetBoneAABB(const xchar* szBoneName, XCusAABB& aabb) = 0;
	virtual void						UpdateSkinInfoAndMeshInfo() = 0;
	virtual void						ChangeSkeleton() = 0;

	virtual void						UpdateBlendMatrix(xbool bClearPreMatrix = xfalse) = 0;	
	virtual XArray<XVECTOR4>*			GetBlendMatrix(xint32 nSkinIndex, xint32 nLODIndex, xint32 nMeshIndex) = 0;
	virtual void						UpdateBlendMatrixAndAABB() = 0;

	virtual void						SetSkinCurrentLOD(const xchar* szSkinName = NULL, xint32 nLODIndex = -1) = 0;
	virtual void						Tick(xint32 nDeltaTime, xbool bClearPreMatrix = xfalse) = 0;

	virtual void						SetBlendShapeTargetWeights(XSkinModelBlendShapeWeight const& weightBuffer) = 0;
	virtual XSkinModelBlendShapeWeight&	GetBlendShapeTargetWeights() = 0;
	virtual const XSkinModelBlendShapeWeight&	GetBlendShapeTargetWeights() const = 0;
	virtual void						UpdateBlendShape() = 0;
	virtual void						WaitAsyncBlendShapeDone() const = 0;
	virtual void						SetMeshAsCloth(const xchar* szMeshName, xbool bIsCloth) = 0;
	virtual const XBlendShapeInstance*	GetBlendShapeInstance() const = 0;
	virtual void						TickAABB() = 0;

	/*
	   return vertex current position、normal、Tangent in model space by vertexindex
	   notice : shoud be call after Tick function;
	   @param szSkinName : skin name (Incomplete path, only name)
	   @param pOriginVertex : Reference memory in the model;
	*/
	virtual xbool						GetCurVertexsTransformInfo(const xchar* szSkinName, xint32 nLODIndex, const xchar* strRawMeshName,
											const XArray<xint32> &vVertexIndex, XArray<XOutputVertexTransform> &outCurVertex,
											xbool bUpdateMorph = xfalse, xbool bUpdateBone = xfalse, XArray<XBaseVertex*> *pOriginVertex = NULL) = 0;
	virtual xbool						GetCurVertexsTransformInfo(xint32 nSkinIndex, xint32 nLODIndex, xint32 nRawMeshIndex,
											const XArray<xint32> &vVertexIndex,	XArray<XOutputVertexTransform> &outCurVertex, 
											xbool bUpdateMorph = xfalse, xbool bUpdateBone = xfalse, XArray<XBaseVertex*> *pOriginVertex = NULL) = 0;
	

}; 

#endif
