/******************************************************************************

 @File         XViewport.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description

 @HISTORY:

******************************************************************************/

#ifndef _XVIEWPORT_H_
#define _XVIEWPORT_H_

#include "XBase3DTypes.h"
#include "XMemBase.h"

class XBaseCamera;

class XViewport
{
public:
								XViewport();
								~XViewport();
	xbool						Init(XVIEWPORTPARAMETER * pViewPortParam);
	xbool						Release();
	xbool						SetParam(XVIEWPORTPARAMETER * pViewPortParam);
	xbool						TransformWorldToScreen(const XVECTOR3& vWorldPoint, XVECTOR3& vScreenPoint);
	xbool						InvTransformScreenToWorld(const XVECTOR3& vScreePoint, XVECTOR3& vWorldPoint);
	xbool						SetCamera(XBaseCamera* pCamera);
	XVIEWPORTPARAMETER *		GetViewportParam();
	XBaseCamera*				GetCamera();
	const XMATRIX4				GetViewScale();
	XCOLOR						GetClearColor();
	void						SetClearColor(XCOLOR clearColor);
	void						EnableClearColor(xbool bClearColor);
	xbool						IsClearColor() { return m_bClearColor; }

private:
	XVIEWPORTPARAMETER			m_ViewportParam;
	XBaseCamera*				m_pXCamera;
	XMATRIX4					m_matViewScale;
	XMATRIX4					m_matInvViewScale;
	XCOLOR						m_ClearColor;
	xbool						m_bClearColor;
};
#endif // _XVIEWPORT_H_
