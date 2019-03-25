/******************************************************************************

 @File         XBaseCamera.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XBaseCamera.

 @HISTORY:

******************************************************************************/

#ifndef _X_BASECAMERAE_H_
#define _X_BASECAMERAE_H_

#include "XBase3DTypes.h"
#include "XCameraViewFrustum.h"
#include "XMembase.h"

class XBaseCamera : public XMemBase
{
public:

								XBaseCamera();
	virtual						~XBaseCamera();
	xbool						Init(xfloat32 fZNear, xfloat32 fZFar);
	virtual void				Release() {}
	virtual xbool				IsPerspective();
	virtual xbool				IsOrthogonal();
	void						SetDirAndUp(const XVECTOR3& vecDir, const XVECTOR3& vecUp);
	xbool						MoveForward(xfloat32 fDistance);
	xbool						MoveBack(xfloat32 fDistance);
	xbool						MoveLeft(xfloat32 fDistance);
	xbool						MoveRight(xfloat32 fDistance);
	xbool						MoveDelta(const XVECTOR3& vecDelta);
	xbool						RotateCameraAroundAxisInWorld(const XVECTOR3& vecPos, const XVECTOR3& vecAxis, xfloat32 fDeltaRad);
	xbool						DegDelta(xfloat32 vDelta);//yaw
	xbool						PitchDelta(xfloat32 vDelta);
	xbool						SetDeg(xfloat32 vDeg);
	xbool						SetPitch(xfloat32 vPitch); // pitch
	xbool						SetMirrorCamera(XBaseCamera* pCamera, const XVECTOR3& vOrgin, const XVECTOR3& vNormal);
	xbool						SetViewMatrix(const XMATRIX4& matView);
	xbool						SetProjectionMatrix(const XMATRIX4& matProjection);
	xbool						SetZNearFar(xfloat32 fFront, xfloat32 fBack, xbool bUpdateProjMat = xtrue);
	xfloat32					GetZNear() const;
	xfloat32					GetZFar() const;
	void						SetPos(const XVECTOR3& vPos);
	const XMATRIX4&				GetViewMatrix() const;
	const XMATRIX4&				GetProjectionMatrix() const;
	const XMATRIX4&				GetViewProjMatrix() const;
	const XVECTOR3&				GetDir() const;
	const XVECTOR3&				GetHorizontalDir() const;
	const XVECTOR3&				GetUp() const;
	const XVECTOR3&				GetRight() const;
	const XVECTOR3&				GetLeft() const;
	const XVECTOR3&				GetHorizontalLeft() const;
	XVECTOR3					GetHorizontalRight() const;
	virtual xbool				IsAABBInViewFrustum(const XCusAABB& aabb);
	virtual xbool				IsAABBInViewFrustum(const XVECTOR3& vMins, const XVECTOR3& vMaxs);
	virtual xbool				IsSphereInViewFrustum(const XVECTOR3& vCenter, xfloat32 fRadius);
	virtual xbool				IsPointInViewFrustum(const XVECTOR3& vPos);
	virtual xbool				TransformWorldToProj(const XVECTOR3& vWorld, XVECTOR3& vProj);
	virtual xbool				InvTransformProjToWorld(const XVECTOR3& vProj, XVECTOR3& vWorld);
	const XVECTOR3&				GetCameraPos() const;
	xfloat32					GetDeg() const;
	xfloat32					GetPitch() const;
	const XMATRIX4&				GetPostProjectMatrix() const;
	void						SetPostProjectMatrix(const XMATRIX4& matPostProjectTM);
	XCameraViewFrustum*			GetWorldFrustum();
	XCameraViewFrustum*			GetViewFrustum();
	xbool						IsMirrored();
	XBaseCamera*				GetMirrorCamera();
	const XMATRIX4&				GetMirrorMatrix();
protected:
	xbool						UpdateViewTM();
	xbool						UpdateDirAndUp();
	xbool						UpdateForMirroredCamera();
	virtual xbool				UpdateProjectTM() = 0;
	virtual xbool				CreateViewFrustum() = 0;
	virtual xbool				UpdateWorldFrustum() = 0;
protected:
	XVECTOR3					m_vPosition;
	XVECTOR3					m_vDir;
	XVECTOR3					m_vUp;
	XVECTOR3					m_vLeft;
	XVECTOR3					m_vRight;
	XVECTOR3					m_vHorizontalDir;
	XVECTOR3					m_vHorizontalLeft;
	XMATRIX4					m_matView;
	XMATRIX4					m_matProject;
	XMATRIX4					m_matViewProject;
	XMATRIX4					m_matPostProject;
	XMATRIX4					m_matInvProject;
	XMATRIX4					m_matInvViewProject;
	XMATRIX4					m_matMirror;
	xbool						m_bMirrored;
	xfloat32					m_fDeg;
	xfloat32					m_fPitch;
	xfloat32					m_fZNear;
	xfloat32					m_fZFar;
	XCameraViewFrustum			m_ViewFrustum;
	XCameraViewFrustum			m_WorldFrustum;
	XBaseCamera*				m_pMirrorCamera;
};

#endif	//	_X_BASECAMERAE_H_
