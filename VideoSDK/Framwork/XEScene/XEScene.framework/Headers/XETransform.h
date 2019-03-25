/******************************************************************************

@File         XETransform.h

@Version       1.0

@Created      2017, 9, 20

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XETRANSFORM_H
#define XETRANSFORM_H
#include "XMemBase.h"
#include "XEMath.h"
#include "XClass.h"

class XETransform:public XMemBase
{
	friend class XEActorComponent;
public:

	XETransform();
	virtual ~XETransform(){};
public:
	void                           SetRotateEuler(const xfloat32 fRoll, const xfloat32 fYaw, const xfloat32 fPitch);//normally, "Pitch" is rotate around x, however, here "Roll" is rotate around x, as the "Forward" direction is "Z", thus, "Pitch" is the right definition for the "Forward".  
	void                           GetRotateEuler(xfloat32& fRoll, xfloat32& fYaw, xfloat32& fPitch);
	X_EES_LINE void                GetRotateEuler(xfloat32& fRoll, xfloat32& fYaw, xfloat32& fPitch) const;
	void                           SetQuaternion(const XQUATERNION& quat);
	XQUATERNION&                   GetQuaternion();
	X_EES_LINE const XQUATERNION&  GetQuaternion() const;
	void                           SetDirAndUp(const XVECTOR3& vDir, const XVECTOR3& vUp);
	void                           GetDirAndUp(XVECTOR3& vDir, XVECTOR3& vUp);
	void                           SetLocation(const xfloat32 fX, const xfloat32 fY, const xfloat32 fZ);
	void                           SetLocation(const XVECTOR3& vLocation);
	XVECTOR3&                      GetLocation();
	X_EES_LINE const XVECTOR3&     GetLocation() const;
	void                           SetScale(const xfloat32 fX, const xfloat32 fY, const xfloat32 fZ);
	void                           SetScale(const XVECTOR3& vScale);
	XVECTOR3&                      GetScale();
	X_EES_LINE const XVECTOR3&     GetScale() const;
	XMATRIX4                       GetTransform() const;
	void                           SetFromMatrix4(const XMATRIX4& mt4);

private:
	//local			          
	XVECTOR3                       m_vLocation;//relative to its parent
	XQUATERNION                    m_qRotation;//relative to its parent
	XVECTOR3                       m_vScale;//relative to its parent
	//world
	//Self.local * Parent.world = Self.world.
	mutable XMATRIX4               m_matWorldTransform;
public:						       
	static const XVECTOR3          TF_FORWARD;
	static const XVECTOR3          TF_RIGHT;
	static const XVECTOR3          TF_UP;
	static const XVECTOR3          TF_NORMAL;
};

#endif // XETRANSFORM_H
