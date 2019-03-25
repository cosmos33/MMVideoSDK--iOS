/******************************************************************************

 @File         XOrthoCamera.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description

 @HISTORY:

******************************************************************************/

#ifndef _XORTHOCAMERA_H_
#define _XORTHOCAMERA_H_

#include "XBaseCamera.h"

class XOrthoCamera : public XBaseCamera
{
public:

							XOrthoCamera();
	virtual					~XOrthoCamera() {}
	xbool					Init(xfloat32 fLeft, xfloat32 fRight, xfloat32 fBottom, xfloat32 fTop, xfloat32 fZNear, xfloat32 fZFar);
	virtual void			Release();
	virtual xbool			IsPerspective();
	virtual xbool			IsOrthogonal();
	xbool					SetProjectionParam(xfloat32 fLeft, xfloat32 fRight, xfloat32 fBottom, xfloat32 fTop, xfloat32 fZNear, xfloat32 fZFar);
	xfloat32				GetLeft();
	xfloat32				GetRight();
	xfloat32				GetTop();
	xfloat32				GetBottom();
protected:
	virtual xbool			UpdateProjectTM();
	virtual xbool			CreateViewFrustum();
	virtual xbool			UpdateWorldFrustum();
protected:
	xfloat32				m_fLeft;
	xfloat32				m_fRight;
	xfloat32				m_fTop;
	xfloat32				m_fBottom;
};

#endif	//	_XORTHOCAMERA_H_
