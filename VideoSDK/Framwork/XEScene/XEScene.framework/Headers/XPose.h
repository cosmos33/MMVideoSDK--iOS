#ifndef _XPOSE_H_
#define _XPOSE_H_

#include "XBaseTM.h"
#include "XBoneMap.h"
#include "XAnimation.h"

class XSkeleton;
class XSkeletonMask;
class XFileBase;

/*
Pose represent a snapshot of bone transforms in a Skeleton.
Pose is a partial pose, which means transforms in it only mapped to part of a Skeleton.
Pose is mostly used in animation sampling and blending process.
For full representation of a Skeleton snapshot, see FullPose below.
*/
class XPose
	: public XMemBase
{
public:
										// construct an empty Pose.
										XPose() = default;
										// construct an empty Pose.
	explicit							XPose(PoseType type);
										// PoseType::POSE_TYPE_NORMAL
	explicit							XPose(xint32 nBoneCount);
										// when type is PoseType::Additive
										XPose(PoseType type, xint32 nBoneCount);

	void								SetBoneCount(xint32 nBoneCount);

	void								SetPoseType(PoseType type) { m_PoseType = type; }

	PoseType							GetPoseType() const { return m_PoseType; }

	void								Clear();

	const XBoneMap&						GetBoneMap() const { return m_BoneMap; }

	XBoneMap&							GetBoneMap() { return m_BoneMap; }

	xint32								GetBoneCount() const { return m_aBoneTransforms.Num(); }

	bool								Exist(xint32 iBoneIndex) const { return m_BoneMap.Exist(iBoneIndex); }

	const XBaseTM&						GetBoneByStorageIndex(xint32 iStorageIndex) const { return m_aBoneTransforms[iStorageIndex]; }
    XBaseTM&					        GetBoneByStorageIndex(xint32 iStorageIndex) { return m_aBoneTransforms[iStorageIndex]; }
    // need to keep bone index in ascending order by caller
	void								SetBone(xint32 iStorageIndex, xint32 iBoneIndex, const XBaseTM& trTransform);

	void								RemoveBoneByStorageIndex(xint32 iStorageIndex);

	XPose								MaskPose(const XSkeletonMask& mask) const;

	// this = this * (1 - Factor) + other * Factor
	void								MageOtherPose(const XPose &Other, xfloat32 fFactor);

	const XArray<XBaseTM>&				GetTransforms() const { return m_aBoneTransforms; }

	XArray<XBaseTM>&					GetTransforms() { return m_aBoneTransforms; }

	bool								Serialize(XXMLExtendTool& ar);
	bool								Save(XFileBase* file) const;
	bool								Load(XFileBase* file);

private:

	void						        AddNewBoneTM(const XBaseTM &tm, xint32 iBoneIndex);

	PoseType							m_PoseType = PoseType::POSE_TYPE_NORMAL;

	XBoneMap							m_BoneMap;
	XArray<XBaseTM>						m_aBoneTransforms;
};


/*
FullPose represent a snapshot of bone transforms in a Skeleton.
FullPose stores all the transforms of a Skeleton.

*/
class XFullPose
	: public XMemBase
{
public:

										// empty constructor
										XFullPose() = default;


										// construct a FullPose, allocate storages.
	explicit							XFullPose(const XSkeleton* pSkeleton);

										XFullPose(const XFullPose& other) = default;
	XFullPose&							operator=(const XFullPose& other) = default;

	// bind to a skeleton and initialize storage
	void								BindSkeleton(const XSkeleton* pSkeleton);

	const XSkeleton*					GetSkeleton() const { return m_pSkeleton; }

	xint32								GetBoneCount() const { return m_aBoneTransforms.Num(); }

	const XBaseTM&					GetBone(xint32 iBoneIndex) const { return m_aBoneTransforms[iBoneIndex]; }

	XBaseTM&							GetBone(xint32 iBoneIndex) { return m_aBoneTransforms[iBoneIndex]; }

	void								SetBone(xint32 iBoneIndex, const XBaseTM& trTransform) { m_aBoneTransforms[iBoneIndex] = trTransform; }

	XPose								GeneratePose(const XSkeletonMask& mask) const;

	void								OverrideFromPose(const XPose& pose, const XSkeletonMask& bonemask);
	void								AdditiveBlendFromPose(const XPose& pose, xfloat32 fT, const XSkeletonMask& bonemask);
    void								RightAdditiveBlendFromPose(const XPose& pose, xfloat32 fT, const XSkeletonMask& bonemask);
    void								LerpBlendFromPose(const XPose& pose, xfloat32 fT, const XSkeletonMask& bonemask);

	const XArray<XBaseTM>&		GetTransforms() const { return m_aBoneTransforms; }

	XArray<XBaseTM>&				GetTransforms() { return m_aBoneTransforms; }

	bool								Serialize(XXMLExtendTool& ar);
	bool								Save(XFileBase* file) const;
	bool								Load(XFileBase* file);

private:
//	PoseType							m_PoseType;
	const XSkeleton*					m_pSkeleton = nullptr;

	XArray<XBaseTM>			m_aBoneTransforms;

};

void ApplyFullPoseToSkeleton(const XFullPose& pose, XSkeleton* pSkeleton);
void ApplyPoseToSkeleton(const XPose& pose, XSkeleton* pSkeleton);

XFullPose ConstructDefaultFullPoseFromSkeleton(const XSkeleton* pSkeleton);
XFullPose ConstructCurrentFullPoseFromSkeleton(const XSkeleton* pSkeleton);
void ConstructDefaultFullPoseFromSkeleton(const XSkeleton* pSkeleton, XFullPose& pose); // will be faster if pose has already initialized using same skeleton
void ConstructCurrentFullPoseFromSkeleton(const XSkeleton* pSkeleton, XFullPose& pose); // will be faster if pose has already initialized using same skeleton

// replace ASkeleton::GetDefaultPose temporarily
inline XFullPose ConstructDefaultFullPoseFromSkeleton_TEMP(const XSkeleton* pSkeleton) { return ConstructDefaultFullPoseFromSkeleton(pSkeleton); }

XPose ConstructDefaultPoseFromSkeleton(const XSkeleton* pSkeleton);
XPose ConstructCurrentPoseFromSkeleton(const XSkeleton* pSkeleton);

XPose ConstructMaskedDefaultPoseFromSkeleton(const XSkeleton* pSkeleton, XSkeletonMask const& mask);
XPose ConstructMaskedCurrentPoseFromSkeleton(const XSkeleton* pSkeleton, XSkeletonMask const& mask);

// note, the result will be wrong if non-uniform scaling exist in the bone path.
XBaseTM CalculateGlobalTransform(const XFullPose& pose, xint32 iBoneIndex);
XMATRIX4 CalculateGlobalBoneMatrix(const XFullPose& pose, xint32 iBoneIndex, xint32 iStopBone = -1);

#endif // _XPose_H_
