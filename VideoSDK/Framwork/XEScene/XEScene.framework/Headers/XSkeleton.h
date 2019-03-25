/******************************************************************************

@File         XSkeleton.h

@Version       1.0

@Created      2017, 4, 14

@Description  skeleton class.

@HISTORY:

******************************************************************************/
#ifndef _X_SKELETON_H_
#define _X_SKELETON_H_

#include "XBase3DTypes.h"
#include "XBaseCoordSpace.h"
#include "XString.h"
#include "XMemBase.h"
#include "XArray.h"
#include "XHashTable.h"
#include "XCustomGeometry.h"
#include "XBone.h"

class XJoint;
class XSkeleton;
class XMATRIX4;
class XFileBase;

class XSkeleton : public XBaseCoordSpace
{
public:
	struct XSkeletonRenderData
	{
		XArray<XBone::XBoneRenderData> bones;
	};

	struct XSkeletonMuscleData
	{
		struct Muscle
		{
			XString             strName{""};
			xint32              iStart{-1};
			xint32              iEnd{-1};
			XArray<xint32>		aBones;
			bool                bEnableScale{xfalse};
			xfloat32            fRelaxedLength{0};
			xfloat32            fMultiplier{0};
		};
		XArray<Muscle>  muscles;

		xbool                   Save(XFileBase* pFile) const;
		xbool                   Load(XFileBase* pFile);
	};

public:

										XSkeleton();
										XSkeleton(const XSkeleton& s);
	XSkeleton&                          operator=(XSkeleton const& other);
	virtual								~XSkeleton();

public:
	 bool								Init();
	 void								Release();
	 XSkeleton*							Clone() const;
	 xbool								Load(XFileBase* pFile);
	 xbool								Load(const xchar* szFile);
	 xbool								UpdateBoneTree(XBone* pRootBone, xint32 nDeltaTime);
	 xbool								FindRefBone();
	 void								GetOriginBoneState_r(xint32 nBoneIdx, xint32 nParent, xbool bUseScale, XMATRIX4* aMats, XMATRIX4* aUpToRootMats);
	 void								GetFrameBoneState_r(xint32 nBoneIdx, xint32 nParent, xbool bUseScale, XMATRIX4* aRelMats, XMATRIX4* aOutMats, XMATRIX4* aUpToRootMats);

public:
	xbool								Save(XFileBase* pFile);
	xbool								Save(const xchar* szFile);
	xbool								SaveToXml(XFileBase * pFile);
	xbool								SaveToXml(const xchar * szFile);
	xbool								LoadFromXml(const xchar * szFile);

	xbool								SaveHierachy(XFileBase* pFile) const;
	xbool								LoadHierachy(XFileBase* pFile);
	xbool								Update(xint32 iDeltaTime);
	void								FillRenderData(XSkeletonRenderData& renderData, xfloat32 fSkeletonSize);
	xbool								RayCastBone(const XVECTOR3& vStart, const XVECTOR3& vEnd,
													xfloat32* pOutFraction = NULL, xint32* pOutSkeletedBoneId = NULL);
	xint32								AddBone(XBone* pBone);
	XBone*								GetBone(const xchar* szName, xint32* pnIndex) const;
	XBone*								GetBone(xint32 nIndex) const { return (nIndex >= 0 && nIndex < m_aBones.Num()) ? m_aBones[nIndex] : NULL; }
	xint32								GetBoneNum() const { return m_aBones.Num(); }
	xint32								GetRootBoneNum() const{ return m_aRootBones.Num(); }
	xint32								GetRootBone(xint32 n) const { return (n >= 0 && n < m_aRootBones.Num()) ? m_aRootBones[n] : NULL; }
	void								ResetBoneRelativeTM();
	xint32								GetRefBone() const { return m_nRefBone; }
	void								OnBoneLocalScaleChanges(XBone* pBone);
	void								OnBoneWholeScaleChanges();
	void								GetOriginBoneState(XArray<XMATRIX4>& aMats, xbool bUseScale = false);
	void								GetFrameBoneState(XArray<XMATRIX4>& aRelMats, XArray<XMATRIX4>& aOutMats, xbool bUseScale = false);
	xint32								AddJoint(XJoint* pJoint);
	XJoint*								GetJoint(const xchar* szName, xint32* pnIndex);
	XJoint*								GetJoint(xint32 nIndex) { return (nIndex >= 0 && nIndex < m_aJoints.Num()) ? m_aJoints[nIndex] : NULL; }
	xint32								GetJointIndex(XJoint* pJoint);
	xint32								GetJointNum() const { return m_aJoints.Num(); }
	xint32								GetAnimDataSize();
	const xchar*						GetFileName() const { return m_strFileName; }
	xuint32								GetSkeletonID() const { return m_uSkeletonID; }
	xuint32								GetUpdateCounter() const { return m_uUpdateCnt; }
	xint32								GetAnimFPS() const { return m_nAnimFPS; }
	void								SetAnimFPS(xint32 nFPS) { m_nAnimFPS = nFPS; }
	xuint32								GetVersion() { return m_uVersion; }
	xfloat32							GetInheritScale() { return m_fInheritScale; }
	void								SetInheritScale(xfloat32 fScale);
	void								CalcFootOffset(const xchar* szFootBone=NULL);
	void								SetFootOffset(xfloat32 fOffset) { m_fFootOffset = fOffset; }
	xfloat32							GetFootOffset() { return m_fFootOffset; }
	xint32								GetFootBone() { return m_nFootBone; }
	void								SetSkinManFlag(xint32 nFlag) { m_nSkinManFlag = nFlag; }
	xint32								GetSkinManFlag() const { return m_nSkinManFlag; }
	void								BoneNameChanged(const xchar * szBefore, const xchar * szAfter);
	XSkeletonMuscleData&                GetMuscleData() { return m_muscleData; }
	XSkeletonMuscleData const&          GetMuscleData() const { return m_muscleData; }

protected:
	XString								m_strFileName;			
	xuint32								m_uSkeletonID;			
	xuint32								m_uUpdateCnt;			
	xint32								m_nRefBone;				
	xint32								m_nSkinManFlag;			
	xuint32								m_uVersion;				
	xint32								m_nAnimFPS;				
	xfloat32							m_fFootOffset;			
	xbool								m_bTrackSetOK;			
	xint32								m_nFootBone;			
	xfloat32							m_fInheritScale;		
	XArray<XBone*>						m_aBones;				
	XArray<XJoint*>						m_aJoints;
	XHashTable<XString, xint32>			m_BoneNameToBoneIndex;	
	XArray<xint32>						m_aRootBones;			
	xfloat32							m_fBoneRadius;			
	xint32								m_nCurrentSelected;		
	XSkeletonRenderData					m_renderData;
	XSkeletonMuscleData                 m_muscleData;
};
#endif