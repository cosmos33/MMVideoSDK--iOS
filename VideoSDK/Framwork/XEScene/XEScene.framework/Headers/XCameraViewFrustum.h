/******************************************************************************

 @File         XCameraViewFrustum.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description

 @HISTORY:

******************************************************************************/

#ifndef _XCAMERAVIEWFRUSTUM_H_
#define _XCAMERAVIEWFRUSTUM_H_

#include "XBase3DTypes.h"
#include "XCustomGeometry.h"
#include "XArray.h"
#include "XMemBase.h"

class XBaseCamera;
class XViewport;

class XCameraViewFrustum
{
public:
	enum
	{
		XVF_LEFT = 0,
		XVF_RIGHT,
		XVF_TOP,
		XVF_BOTTOM,
		XVF_NEAR,
		XVF_FAR,
	};
	
public:

								XCameraViewFrustum();
								XCameraViewFrustum(const XCameraViewFrustum& frustum);
	virtual						~XCameraViewFrustum() {}
	xbool						Init(xint32 iNumPlane);
	xbool						Init(XBaseCamera* pCamera, xfloat32 fVLeft, xfloat32 fVTop, xfloat32 fVRight, xfloat32 fVBottom, xbool bZClip);
	xbool						Init(XViewport* pView, xint32 iSLeft, xint32 iSTop, xint32 iSRight, xint32 iSBottom, xbool bZClip);
	void						Release();
	xbool						AddClipPlane(const XCusSPlane& ClipCusPlane);
	xbool						AddClipPlane(const XVECTOR3& vPanelNormal, xfloat32 fDistance);
	xint32						IsAABBInViewFrustum(const XVECTOR3& vMins, const XVECTOR3& vMaxs);
	xint32						IsAABBInViewFrustum(const XCusAABB& cusAABB);
	xint32						IsSphereInViewFrustum(const XVECTOR3& vSphereCenter, xfloat32 fSphereRadius);
	xbool						IsPointInViewFrustum(const XVECTOR3& vPoint);
	XCusSPlane*					GetTemporaryPlanePointer(xint32 iPanelIndex);
	xint32						GetClipPlaneNum();
	void						EnableClipPlane(xint32 iPanelIndex, xbool bEnable);
	xbool						IsClipPlaneEnable(xint32 iPanelIndex);
	const XCameraViewFrustum&	operator = (const XCameraViewFrustum& frustum);
protected:
	void						CreateClipViewFrustumPlane(const XVECTOR3& vPoint0, const XVECTOR3& vPoint1, const XVECTOR3& vPoint2, XCusSPlane* pCusPlane);
protected:
	struct ViewFrustumPlane
	{
		XCusSPlane	Plane;
		xbool		bEnable;
	};
	XArray<ViewFrustumPlane> m_aVFPlanes;

};


#endif	//	_XCAMERAVIEWFRUSTUM_H_
