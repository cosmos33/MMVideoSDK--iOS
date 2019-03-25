/******************************************************************************

@File         XBone.h

@Version      1.0

@Created      2017, 4, 14

@Description  

@HISTORY:

******************************************************************************/

#ifndef _X_BONE_H_
#define _X_BONE_H_

#include "XBase3DTypes.h"
#include "XArray.h"
#include "XMemBase.h"
#include "XCustomGeometry.h"

class XSkeleton;
class XJoint;
class XAnimJoint;
class XBoneControllerBase;
class XFileBase;

class XBone : public XMemBase
{
	friend class XSkeleton;
public:	

	struct XBoneRenderData
	{
		XCusSphere sphere;
		XArray<XCusCone> cones;
		XCOLORBASE color;
	};


	enum
	{
		FLAG_FAKEBONE	= 0x01,
		FLAG_FLIPPED	= 0x02,
	};
	
	enum
	{
		BM_NORMAL = 0,
		BM_COMBINE,
		BM_EXCLUSIVE,
		BM_ABSTRACK,
	};
	enum
	{
		TRANS_POS_X = 0x01,		
		TRANS_POS_Y = 0x02,		
		TRANS_POS_Z = 0x04,		
		TRANS_POS = 0x07,		
		TRANS_ORI = 0x08,		
		TRANS_ALL = 0x0f,		
	};
	
	struct BoneState
	{
		XQUATERNION					quOrientation;	
		XVECTOR3					vPos;			
		xfloat32					fWeight;		
		xint32						iBlendMode;		
	};

public:
									XBone(); 
									~XBone();
		
	xbool							Init(XSkeleton* pSkeleton);
	void							Release();
	XBone*							Duplicate(XSkeleton* pDstSkeleton);
	xbool							Load(XFileBase* pFile);
	xbool							Save(XFileBase* pFile);

	virtual void					SetName(const xchar* szName);
	const xchar*					GetName() const { return m_strName; }
	XSkeleton*						GetSkeleton() { return m_pSkeleton; }
	void							SetSkeleton(XSkeleton* pSkeleton) { m_pSkeleton = pSkeleton; }

	xbool							IsAnimDriven() { return m_bAnimDriven; }
	void							SetAnimDriven(xbool bAnimDriven);
	void							FillBoneRenderData(XBoneRenderData& renderData, xfloat32 fBoneSize, const XMATRIX4& rootMat);

	/*
	* 骨头更新
	*
	* @notice	更新骨头的各矩阵信息， 绝对矩阵，父骨头空间矩阵等都会更新
	*
	* @param	nDeltaTime 步进时间
	* @returns  
	*/
	xbool						Update(xint32 nDeltaTime);

	/*
	* 骨头的父子关系
	*
	* @notice	
	*
	* @param	
	* @returns 
	*/
	xint32						GetParent()	{ return m_iParent; }
	void						SetParent(xint32 iParent) { m_iParent = iParent; }
	XBone*						GetParentPtr();
	XBone*						GetRootBonePtr();

	xbool						AddChild(xint32 iChild);
	xint32						GetChild(xint32 iIndex) { return m_aChildren[iIndex]; }
	xint32						GetChildNum() { return m_aChildren.Num(); }
	XBone*						GetChildPtr(xint32 iIndex);

	xint32						GetFirstJoint() { return m_iFirstJoint; }
	void						SetFirstJoint(xint32 iJoint) { m_iFirstJoint = iJoint; }
	XJoint*						GetFirstJointPtr();
	xbool						AddJoint(xint32 iJoint);
	XAnimJoint*					GetAnimJointPtr();

	/*
	* 骨头标志类型编辑
	*
	* @notice	
	*/
	void						SetFlippedFlag(xbool bFlip) { bFlip ? m_byBoneFlags |= FLAG_FLIPPED : m_byBoneFlags &= ~FLAG_FLIPPED; }
	xbool						IsFlipped() { return (m_byBoneFlags & FLAG_FLIPPED) ? xtrue : xfalse; }
	void						SetBoneFlags(xint8 byFlags) { m_byBoneFlags = byFlags; }
	xint8						GetBoneFlags() { return m_byBoneFlags; }

	/*
	* 骨头的原始矩阵编辑
	*
	* @notice 由文件中加载的矩阵信息
	*/
	const XMATRIX4&				GetBoneInitTM() { return m_matBoneInit; }
	void						SetBoneInitTM(const XMATRIX4& mat) { m_matBoneInit = mat; }
	const XMATRIX4&				GetOriginalMatrix() { return m_matOriginRel; }
	void						SetOriginalMatrix(const XMATRIX4& mat);
	const XVECTOR3&				GetOriginalPos() const { return m_vOriginRel; }
	const XQUATERNION&			GetOriginalDir() const { return m_quOriginRel; }


	void						AddBlendState(const XQUATERNION& quOrientation, const XVECTOR3& vPos, xfloat32 fWeight, xint32 iMode);
	xint32						GetBlendStateNum() { return m_aBlendStates.Num(); }
	BoneState&					GetBlendState(xint32 n) { return m_aBlendStates[n]; }
	void						PrepareTransition(xint32 iTransTime);

	/*
	* 骨头控制器
	*
	* @notice 骨头更新时，会调用控制器，参与骨头各矩阵的计算
	*/
	XBoneControllerBase*		GetFirstController() { return m_pFirstController; }
	void						SetFirstController(XBoneControllerBase* pController) { m_pFirstController = pController; }

	/*
	* 重置骨头的相对矩阵
	*
	* @notice 使用m_matOriginRel来重置相对矩阵
	*/
	void						ResetRelativeTM();

	/*
	* 设置骨头的相对矩阵
	*
	* @notice 
	*/
	void						SetRelativeTM(const XMATRIX4& mat);
	void						SetRelativeTM(const XQUATERNION& quRot, const XVECTOR3& vTrans);
	const XMATRIX4&				GetRelativeTM() { return m_matRelativeTM; }
	const XQUATERNION&			GetRelativeQuat() { return m_quRelativeTM; }	

	/*
	* 骨头到父骨头空间的转换矩阵
	*
	* @notice 设置到父骨头空间的矩阵，但是不影响相对矩阵
	*/
	void						SetUpToParentTM(const XMATRIX4& matUpToParent);	
	const XMATRIX4&				GetUpToParentTM() const { return m_matUpToParentNoScale; }
	const XMATRIX4&				GetUpToRootTM() { return m_matUpToRootNoScale; }

	/*
	* 骨头的模型空间矩阵
	*
	* @notice
	*/
	const XMATRIX4&				GetLocalAbsTM() const { return m_matLocalAbsTM; }
	const XMATRIX4&				GetAbsoluteTM() { return m_matAbsoluteTM; }
	const XMATRIX4&				GetNoScaleAbsTM();	

	/*
	* 设置模型空间矩阵
	*
	* @notice 特殊情况下使用，通常此矩阵由内部计算得出
	*/
	void						SetLocalAbsTM(const XMATRIX4 &mat) { m_matLocalAbsTM = mat; }
	void						SetAbsoluteTM(const XMATRIX4 &mat) { m_matAbsoluteTM = mat; }


	xbool						IsInheritScale() const { return m_bInheritScale; }
	void						SetInheritScale(bool InheritScale) { m_bInheritScale = InheritScale; }
	void						SetLocalSF(const XVECTOR3& vScale);
	const XVECTOR3&				GetLocalSF() const { return m_vLocalSF; }
	void						SetGlobalSF(const XVECTOR3& vScale);
	XVECTOR3					GetGlobalSF() const { return m_vGlobalSF; }
	XVECTOR3					GetLocalScale() const { return m_vGlobalSF*m_vLocalSF; }

	xuint32						GetTransMask() { return m_TransData.dwTransMask; }
	void						SetTransMask(xuint32 dwMask) { m_TransData.dwTransMask = dwMask; }

#ifdef DQ_ONLY_LOCAL_SCALE
	const XMATRIX4&				GetUpToRootNoRotTM() { return m_matUpToRootNoRot; }
	const XMATRIX4&				GetLocalAbsTMNoRot() const { return m_matLocalAbsTMNoRot; }
	const XMATRIX4&				GetLocalAbsTMNoRotInv() const { return m_matLocalAbsTMNoRotInv; }
#endif

protected:

	/*
	* 骨头数据，用于文件读写的骨头信息
	*
	* @param
	*/
	struct BoneReadData
	{
		xint8						byFlags;
		xint32						iParent;
		xint32						iFirstJoint;
		xint32						iNumChild;
		XMATRIX4					matRelative;
		XMATRIX4					matBoneInit;
	};

	struct BoneTrans
	{
		xbool						bDoTrans;
		xuint32						dwTransMask;
		XVECTOR3					vStartPos;
		XQUATERNION					quStartRot;
		xint32						iAllTime;
		xint32						iCurTime;
	};

	void						UpdateBoneStatesAndTransition(xint32 nDeltaTime);
	void						PassAccuWholeScale();

	/*
	* 由骨头的原始状态， 计算转到根空间矩阵
	*
	* @notice	
	* @param	bUseScale  true: 考虑骨头缩放
	* @param	matParent  父骨头转到根空间的矩阵
	* @param	matOut	 计算输出矩阵	
	*/
	void						BuildOriginUpToRootMatrix(xbool bUseScale, const XMATRIX4& matParentUpToRoot, XMATRIX4& matOut, XMATRIX4& matOutUpToRoot);

	/*
	* 由指定的骨头信息， 计算转到根空间矩阵
	*
	* @notice
	* @param	bUseScale   true: 考虑骨头缩放
	* @param	matParent   父骨头转到根空间的矩阵
	* @param	matFrameRel 骨头的相对矩阵
	* @param	matOut	  计算输出矩阵
	*/
	void						BuildFrameUpToRootMatrix(xbool bUseScale, const XMATRIX4& matParentUpToRoot, const XMATRIX4& matFrameRel, XMATRIX4& matOut, XMATRIX4& matOutUpToRoot);

	xbool						IsPosXTransSet() { return (m_TransData.dwTransMask & TRANS_POS_X) ? xtrue : xfalse; }
	xbool						IsPosYTransSet() { return (m_TransData.dwTransMask & TRANS_POS_Y) ? xtrue : xfalse; }
	xbool						IsPosZTransSet() { return (m_TransData.dwTransMask & TRANS_POS_Z) ? xtrue : xfalse; }
	xbool						IsOriTransSet() { return (m_TransData.dwTransMask & TRANS_ORI) ? xtrue : xfalse; }
	
	XString						m_strName;
	XSkeleton*					m_pSkeleton;			
	xint32						m_iParent;				
	xint32						m_iFirstJoint;	
	XArray<xint16>				m_aChildren;			
	xint8						m_byBoneFlags;			
	xbool						m_bAnimDriven;			
	xbool						m_bInheritScale;
	XMATRIX4					m_matBoneInit;			
														
	XMATRIX4					m_matOriginRel;			

	XMATRIX4					m_matRelativeTM;		
	XQUATERNION					m_quRelativeTM;			
	XMATRIX4					m_matUpToParentNoScale;
	XMATRIX4					m_matUpToRootNoScale;
	XMATRIX4					m_matToParent;	        
	XMATRIX4					m_matToRoot;	        
	XMATRIX4					m_matLocalAbsTM;		
	XMATRIX4					m_matAbsoluteTM;		
	XMATRIX4					m_matNoScaleAbs;		

	XMATRIX4					m_matPassToChild;       
	BoneTrans					m_TransData;			

	XArray<BoneState>			m_aBlendStates;			
	XArray<BoneState>			m_aCombineStates;

	XVECTOR3					m_vOriginRel;
	XQUATERNION					m_quOriginRel;
	XMATRIX4					m_matOriginRelNoScale;	
	XVECTOR3					m_vLocalSF;
	XVECTOR3					m_vGlobalSF;

	XBoneControllerBase*		m_pFirstController;		

#ifdef DQ_ONLY_LOCAL_SCALE
	//for dual quaternion blending
	XMATRIX4						m_matUpToRootNoRot;			
	XMATRIX4						m_matLocalAbsTMNoRot;
	XMATRIX4						m_matLocalAbsTMNoRotInv;
#endif   
};

#endif
