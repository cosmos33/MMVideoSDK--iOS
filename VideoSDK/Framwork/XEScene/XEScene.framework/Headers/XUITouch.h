#ifndef _UITOUCH_H_H
#define _UITOUCH_H_H

#include "XMemBase.h"
#include "XMath3D.h"
#include "XUIManager.h"
class XUITouch : public XMemBase
{
public:
	XUITouch()
		: m_nID(0)
		, m_bStartPointCaptured(xfalse)
		, m_vStartPoint(0.0f)
		, m_vPoint(0.0f)
		, m_fCurForce(0.0f)
		, m_fMaxForce(0.0f)
	{}
	void SetTouchInfo(xint32 id, xfloat32 x, xfloat32 y)
	{
		m_nID = id;         
		m_vPrePoint = m_vPoint;
		XUIRect rect = g_pIXUIManager->GetRect();
		//m_vPoint.Set(x + rect.origin.x, y + rect.origin.y);
		m_vPoint.Set(x, y);
		m_fCurForce = 0.0f;
		m_fMaxForce = 0.0f;
		if (!m_bStartPointCaptured)
		{
			m_vStartPoint = m_vPoint;
			m_bStartPointCaptured = xtrue;
			m_vPrePoint = m_vPoint;
		}
	}
	xint32		m_nID;
	xbool		m_bStartPointCaptured;
	XVECTOR2	m_vStartPoint;
	XVECTOR2	m_vPoint;
	XVECTOR2	m_vPrePoint;
	xfloat32	m_fCurForce;
	xfloat32	m_fMaxForce;
};
#endif
