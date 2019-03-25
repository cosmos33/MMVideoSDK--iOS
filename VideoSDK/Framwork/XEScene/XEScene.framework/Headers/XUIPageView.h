#ifndef _XUIPAGEVIEW_H_
#define _XUIPAGEVIEW_H_

#include "XUIListView.h"

class XUIPageViewIndicator;
class XUIPageView : public XUIListView
{
public:
	X_CLASS_DEF(XUIPageView)

	enum class EventType
	{
		TURNING
	};
	enum class TouchDirection
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	typedef std::function<void(XUINode*, EventType)> XUIPageViewCallback;
	static XUIPageView* Create();
	XUIPageView();
	virtual ~XUIPageView();
	virtual void		SetContentSize(const XVECTOR2& vContentSize)override;
	virtual void		SetDirection(Direction direction) override;
	void				AddPage(XUIWidget* pPage);
	void				InsertPage(XUIWidget* pPage, xint32 nIndex);
	void				RemovePage(XUIWidget* pPage);
	void				RemovePageAtIndex(xint32 nIndex);
	void				RemoveAllPages();
	void				ScrollToPage(xint32 nIndex);
	void				ScrollToPage(xint32 nIndex, xfloat32 fTime);
	void				ScrollToItem(xint32 nIndex);
	void				ScrollToItem(xint32 nIndex, xfloat32 fTime);
	xint32				GetCurrentPageIndex();
	void				SetCurrentPageIndex(xint32 nIndex);
	void				AddEventListener(const XUIPageViewCallback& callback);
	void				SetIndicatorEnabled(xbool bEnabled);
	xbool				GetIndicatorEnabled() const;
	void				SetIndicatorPositionAsAnchorPoint(const XVECTOR2& vPositionAsAnchorPoint);
	const XVECTOR2&		GetIndicatorPositionAsAnchorPoint() const{ return m_vIndicatorPositionAsAnchorPoint; }
	void				SetIndicatorPosition(const XVECTOR2& vPosition);
	const XVECTOR2&		GetIndicatorPosition() const;
	void				SetIndicatorSpaceBetweenIndexNodes(xfloat32 fSpaceBetweenIndexNodes);
	xfloat32			GetIndicatorSpaceBetweenIndexNodes() const;
	void				SetIndicatorSelectedIndexColor(const XCOLORBASE& color);
	const XCOLORBASE&	GetIndicatorSelectedIndexColor() const;
	void				SetIndicatorIndexNodesColor(const XCOLORBASE& color);
	const XCOLORBASE&	GetIndicatorIndexNodesColor() const;
	void				SetIndicatorIndexNodesScale(xfloat32 fIndexNodesScale);
	xfloat32			GetIndicatorIndexNodesScale() const;
	void				SetIndicatorIndexNodesTexture(const XString& strTexName, XUIWidget::TextureResType eTexType = XUIWidget::TextureResType::XUI_LOCAL);
	virtual xbool		SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	virtual xbool		Init() override;
	virtual XUINode*	CreateClonedInstance() override;
	virtual void		CopyProperties(XUINode* pNode)override;
	virtual void		DoLayout() override;
	void				PageTurningEvent();
	virtual void		RemedyLayoutParameter(XUIWidget* pItem)override;
	virtual void		MoveInnerContainer(const XVECTOR2& vDeltaMove, xbool bStartBounceBack) override;
	virtual void		OnItemListChanged() override;
	virtual void		HandleReleaseLogic(XUITouch* pTouch) override;
	virtual void		HandlePressLogic(XUITouch *pTouch) override;
	void				RefreshIndicatorPosition();

protected:
	XUIPageViewIndicator* m_pIndicator;
	xbool				m_bIndicatorEnabled;
	XVECTOR2			m_vIndicatorPositionAsAnchorPoint;
	xint32				m_nCurrentPageIndex;
	XUIPageViewCallback m_pEventCallback;
	xbool				m_bTouchBegin;
};

#endif
