/******************************************************************************

 @File         XPerspectiveCamera.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description	XPerspectiveCamera.

 @HISTORY:

******************************************************************************/

#ifndef _XPERSPECTIVECAMERA_H_
#define _XPERSPECTIVECAMERA_H_

#include "XBaseCamera.h"

const xfloat32 DEFAULTFOVDEGREE = 60.0f;
const xfloat32 DEFAULTZNEAR = 0.01f;
const xfloat32 DEFAULTZFAR = 1000.0f;
const xfloat32 DEFAULTRADIO = 1.3333f;

class XPerspectiveCamera	: public XBaseCamera
{
public:
								XPerspectiveCamera();
	virtual						~XPerspectiveCamera() {}
	xbool						Init(xfloat32 fFov = XENGINE_DEGREETORADIAN(DEFAULTFOVDEGREE), xfloat32 fZNear = DEFAULTZNEAR, xfloat32 fZFar = DEFAULTZFAR, xfloat32 fRatio = DEFAULTRADIO);
	virtual void				Release();
	virtual xbool				IsPerspective();
	virtual xbool				IsOrthogonal();
	void						SetFOV(xfloat32 fFOV);
	xfloat32					GetFOV() const;
	xfloat32					GetRatio() const;
	xbool						SetProjectionParam(xfloat32 fFOV, xfloat32 fZNear, xfloat32 fZFar, xfloat32 fRatio);
	void						GetProjectionParam(xfloat32* pvFOV, xfloat32* pfZNear, xfloat32* pfZFar, xfloat32* pfRatio);
protected:
	virtual xbool				UpdateProjectTM();
	virtual xbool				CreateViewFrustum();
	virtual xbool				UpdateWorldFrustum();
protected:
	xfloat32					m_fFOV;
	xfloat32					m_fRatio;
};


#endif//_XPERSPECTIVECAMERA_H_

