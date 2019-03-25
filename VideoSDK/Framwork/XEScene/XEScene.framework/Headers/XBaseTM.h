/******************************************************************************

@File         XBaseTM.h

@Version       1.0

@Created      2017, 3, 27

@Description  Class representing a XBaseTM.

@HISTORY:

******************************************************************************/
#ifndef _XBASETM_H_
#define _XBASETM_H_
#include "XMath3D.h"

class XFileBase;
class XXMLExtendTool;

class XBaseTM
{
public:
								XBaseTM();
								XBaseTM(const XQUATERNION& qRot,
										const XVECTOR3& vTrans,
										const XVECTOR3& vScale,
										const XVECTOR3& vLocalScale = XVECTOR3(1.0f, 1.0f, 1.0f));
	explicit					XBaseTM(const XMATRIX4& mTM);
	xbool						Save(XFileBase* pFile) const;
	xbool						Load(XFileBase* pFile);
	xbool						Serialize(XXMLExtendTool& xmlArchive);
	void						SetTrans(const XVECTOR3& vTrans);
	const XVECTOR3&				GetTrans() const;
	void						SetScale(const XVECTOR3& vScale);
	const XVECTOR3&				GetScale() const;
	void						SetLocalScale(const XVECTOR3& vScale);
	const XVECTOR3&				GetLocalScale() const;
	const XQUATERNION&			GetRotation() const;
	void						SetRotation(const XQUATERNION& qRot);
	XMATRIX4					CalculateTM() const;
	XMATRIX4					CalculateTM(const XVECTOR3& vParentLocalScale) const;
	XMATRIX4					CalculateInheritTM() const;
	XMATRIX4					CalculateInheritTM(const XVECTOR3& vParentLocalScale) const;
	void						DecomposeTM(const XMATRIX4& tmTransformMatrix);
	void						Inverse();
	XBaseTM						GetInverse() const;
	static const XBaseTM&		GetIdentity();
	static const XBaseTM&		GetZero();
	friend xbool				operator==(XBaseTM const& lrhs, XBaseTM const& rrhs);
	friend xbool				operator!=(XBaseTM const& lrhs, XBaseTM const& rrhs);
	XVECTOR3					m_vTrans;
	XQUATERNION					m_qRotation;
	XVECTOR3					m_vLocalScale;
	XVECTOR3					m_vScale;
};
XBaseTM Additive(const XBaseTM& mTarget, const XBaseTM& mDiffer, xfloat32 fFactor);
XBaseTM RightAdditive(const XBaseTM& mTarget, const XBaseTM& mDifference, xfloat32 fFactor);
XBaseTM Divide(const XBaseTM& mWorld, const XBaseTM& mParent, xbool bInheritScale = xtrue);
XBaseTM Multiply(const XBaseTM& mLocal, const XBaseTM& mParent, xbool bInheritScale = xtrue);
XBaseTM Differ(const XBaseTM& mSrc, const XBaseTM& mRefer);
XBaseTM RightDiffer(const XBaseTM& mSrc, const XBaseTM& mRefer);

template <typename T>
T Lerp(const T& lvalue, const T& rvalue, xfloat32 fFactor);
template <>
XBaseTM Lerp<XBaseTM>(const XBaseTM& ml, const XBaseTM& mr, xfloat32 fFactor);

#endif // _XBASETM_H_
