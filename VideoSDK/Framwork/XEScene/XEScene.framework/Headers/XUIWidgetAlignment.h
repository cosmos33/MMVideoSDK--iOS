#ifndef _UIWIDGETALIGNMENT_H_
#define _UIWIDGETALIGNMENT_H_

#include "XMemBase.h"
#include "XMath3D.h"

class XUINode;
class XUIWidgetAlignment : public XMemBase
{
public:
	enum class HorizontalEdge
	{
		XUI_NONE,
		XUI_LEFT,
		XUI_RIGHT,
		XUI_LEFT_RIGHT,
		XUI_CENTER
	};
	enum class VerticalEdge
	{
		XUI_NONE,
		XUI_TOP,
		XUI_BOTTOM,
		XUI_TOP_BOTTOM,
		XUI_CENTER
	};
	static XUIWidgetAlignment* Create(XUINode* pNode);

	XUIWidgetAlignment();
	virtual ~XUIWidgetAlignment();
	
	xbool			Init(XUINode* pNode);
	virtual XUIWidgetAlignment* Clone();
	xbool			IsEnabled() const { return m_bEnabled; }
	void			SetEnabled(xbool bEnabled){ m_bEnabled = bEnabled; }

	XUINode*		GetOwner() const { return m_pOwner; }
	void			SetOwner(XUINode *pNode){ m_pOwner = pNode; }
	XUINode*		GetTarget()const { return m_pTarget; }
	void			SetTarget(XUINode* pNode){ m_pTarget = pNode; }
	// 
	HorizontalEdge	GetHorizontalEdge()const{ return m_eHorizontalEdge; }
	void			SetHorizontalEdge(HorizontalEdge eEdge);
	VerticalEdge	GetVerticalEdge()const{ return m_eVerticalEdge; }
	void			SetVerticalEdge(VerticalEdge eEdge);
	xfloat32		GetLeftMargin()const{ return m_fLeftMargin; }
	void			SetLeftMargin(xfloat32 fMargin){ m_fLeftMargin = fMargin; m_bLeftMarginPercent = xfalse; }
	xfloat32		GetRightMargin()const{ return m_fRightMargin; }
	void			SetRightMargin(xfloat32 fMargin){ m_fRightMargin = fMargin; m_bRightMarginPercent = xfalse; }
	xfloat32		GetTopMargin()const{ return m_fTopMargin; }
	void			SetTopMargin(xfloat32 fMargin){ m_fTopMargin = fMargin; m_bTopMarginPercent = xfalse; }
	xfloat32		GetBottomMargin()const{ return m_fBottomMargin; }
	void			SetBottomMargin(xfloat32 fMargin){ m_fBottomMargin = fMargin; m_bRightMarginPercent = xfalse; }

	xfloat32		GetLeftMarginPercent()const{ return m_fLeftMarginPercent; }
	void			SetLeftMarginPercent(xfloat32 fMarginPercent){ m_fLeftMarginPercent = fMarginPercent; m_bLeftMarginPercent = xtrue; }
	xfloat32		GetRightMarginPercent()const{ return m_fRightMarginPercent; }
	void			SetRightMarginPercent(xfloat32 fMarginPercent){ m_fRightMarginPercent = fMarginPercent; m_bLeftMarginPercent = xtrue; }
	xfloat32		GetTopMarginPercent()const{ return m_fTopMarginPercent; }
	void			SetTopMarginPercent(xfloat32 fMarginPercent){ m_fTopMargin = fMarginPercent; m_bLeftMarginPercent = xtrue; }
	xfloat32		GetBottomMarginPercent()const{ return m_fBottomMarginPercent; }
	void			SetBottomMarginPercent(xfloat32 fMarginPercent){ m_fBottomMarginPercent = fMarginPercent; m_bLeftMarginPercent = xtrue; }	
	void			RefreshLayout();
	void			RefreshHorizontalMargin();
	void			RefreshVerticalMargin();

	void			SetPercentOnlyEnabled(xbool bEnable){} // deprecated
protected:
	xbool			m_bEnabled;
	XUINode*		m_pOwner;
	XUINode*		m_pTarget;
	HorizontalEdge	m_eHorizontalEdge;
	VerticalEdge	m_eVerticalEdge;
	xfloat32		m_fLeftMargin;
	xfloat32		m_fRightMargin;
	xfloat32		m_fTopMargin;
	xfloat32		m_fBottomMargin;
	xfloat32		m_fLeftMarginPercent;
	xfloat32		m_fRightMarginPercent;
	xfloat32		m_fTopMarginPercent;
	xfloat32		m_fBottomMarginPercent;
	xbool			m_bLeftMarginPercent;
	xbool			m_bRightMarginPercent;
	xbool			m_bTopMarginPercent;
	xbool			m_bBottomMarginPercent;
	friend class XUIWidget;
};

#endif
