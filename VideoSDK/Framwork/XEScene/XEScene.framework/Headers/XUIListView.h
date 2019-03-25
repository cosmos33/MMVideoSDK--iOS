#ifndef _XUILISTVIEW_H_
#define _XUILISTVIEW_H_

#include "XUIScrollView.h"

class XUIListView : public XUIScrollView
{
public:
	X_CLASS_DEF(XUIListView)

	enum class Gravity
	{
		LEFT,
		RIGHT,
		CENTER_HORIZONTAL,
		TOP,
		BOTTOM,
		CENTER_VERTICAL
	};
	enum class EventType
	{
		ON_SELECTED_ITEM_START,
		ON_SELECTED_ITEM_END
	};
	enum class MagneticType
	{
		NONE,
		CENTER,
		BOTH_END,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
	};
	typedef std::function<void(XUINode*, EventType)> XUIListViewCallback;
	static XUIListView*	Create();
	XUIListView();
	virtual ~XUIListView();
	void					PushBackCustomItem(XUIWidget* pItem);
	void					InsertCustomItem(XUIWidget* pItem, xint32 nIndex);
	void					RemoveLastItem();
	void					RemoveItem(xint32 nIndex);
	void					RemoveAllItems();
	void					MoveItem(xint32 nCurrentIndex, xint32 nNewIndex);
	XUIWidget*				GetItem(xint32 nIndex)const;
	XArray<XUIWidget*>&		GetItems();
	xint32					GetIndex(XUIWidget* pItem) const;
	void					SetGravity(Gravity eGravity);
	void					SetMagneticType(MagneticType eMagneticType);
	MagneticType			GetMagneticType() const{ return m_eMagneticType; }
	void					SetMagneticAllowedOutOfBoundary(xbool bMagneticAllowedOutOfBoundary){ m_bMagneticAllowedOutOfBoundary = bMagneticAllowedOutOfBoundary; }
	xbool					GetMagneticAllowedOutOfBoundary() const{ return m_bMagneticAllowedOutOfBoundary; }
	void					SetItemsMargin(xfloat32 fMargin);
	xfloat32				GetItemsMargin()const{ return m_fItemsMargin; }
	virtual void			SetPadding(xfloat32 l, xfloat32 t, xfloat32 r, xfloat32 b)override;
	virtual void			SetLeftPadding(xfloat32 l)override;
	virtual void			SetRightPadding(xfloat32 r)override;
	virtual void			SetTopPadding(xfloat32 t)override;
	virtual void			SetBottomPadding(xfloat32 b)override;
	void					SetScrollDuration(xfloat32 fTime);
	xfloat32				GetScrollDuration() const{ return m_fScrollTime; }
	virtual void			DoLayout() override;
	virtual void			RequestDoLayout() override;
	virtual void			AddChild(XUINode* pChild)override;
	virtual void			RemoveAllChildren(xbool bClean = xtrue) override;
	virtual void			RemoveChild(XUINode* pChild, xbool bClean = xtrue) override;
	XUIWidget*				GetClosestItemToPosition(const XVECTOR2& vTargetPosition, const XVECTOR2& vItemAnchorPoint) const;
	XUIWidget*				GetClosestItemToPositionInCurrentView(const XVECTOR2& vPositionRatioInView, const XVECTOR2& vItemAnchorPoint) const;
	XUIWidget*				GetCenterItemInCurrentView() const;
	XUIWidget*				GetLeftmostItemInCurrentView() const;
	XUIWidget*				GetRightmostItemInCurrentView() const;
	XUIWidget*				GetTopmostItemInCurrentView() const;
	XUIWidget*				GetBottommostItemInCurrentView() const;
	virtual void			SetContentSize(const XVECTOR2& vContentSize)override;
	virtual void			JumpToTop() override;
	virtual void			JumpToBottom() override;
	virtual void			JumpToLeft() override;
	virtual void			JumpToRight() override;
	virtual void			JumpToTopLeft() override;
	virtual void			JumpToTopRight() override;
	virtual void			JumpToBottomLeft() override;
	virtual void			JumpToBottomRight() override;
	void					JumpToItem(xint32 nItemIndex, const XVECTOR2& vPositionRatioInView, const XVECTOR2& vItemAnchorPoint);
	void					ScrollToItem(xint32 nItemIndex, const XVECTOR2& vPositionRatioInView, const XVECTOR2& vItemAnchorPoint);
	void					ScrollToItem(xint32 nItemIndex, const XVECTOR2& vPositionRatioInView, const XVECTOR2& vItemAnchorPoint, xfloat32 fTimeInSec);
	xint32					GetCurSelectedIndex() const{ return m_nCurSelectedIndex; }
	void					SetCurSelectedIndex(xint32 nItemIndex);
	// @ AddEventListener deprecated
	void					AddEventListener(const XUIListViewCallback& callback){ m_pEventCallback = callback; }
	void					AddListViewEventListener(const XUIListViewCallback& callback){ m_pEventCallback = callback; }
	virtual void			SetDirection(Direction dir) override;
	virtual xbool			SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	xbool					Init()override;
	virtual XUINode*		CreateClonedInstance() override;
	virtual void			CopyProperties(XUINode* pNode)override;
	virtual void			HandleReleaseLogic(XUITouch* pTouch) override;
	virtual void			OnItemListChanged();
	void					UpdateInnerContainerSize();
	virtual void			RemedyLayoutParameter(XUIWidget* pItem);
	void					RemedyVerticalLayoutParameter(XUILinearLayoutParameter* pLayoutParameter, xint32 nItemIndex);
	void					RemedyHorizontalLayoutParameter(XUILinearLayoutParameter* pLayoutParameter, xint32 nItemIndex);
	void					SelectedItemEvent(TouchEventType event);
	virtual void			InterceptTouchEvent(XUIWidget::TouchEventType event, XUIWidget* sender, XUITouch* touch) override;
	virtual XVECTOR2		GetHowMuchOutOfBoundary(const XVECTOR2& vAddition = XVECTOR2(0.0f)) override;
	virtual void			StartAttenuatingAutoScroll(const XVECTOR2& vDeltaMove, const XVECTOR2& vInitialVelocity) override;
	void					StartMagneticScroll();
	XVECTOR2				CalculateItemDestination(const XVECTOR2& vPositionRatioInView, XUIWidget* pItem, const XVECTOR2& vItemAnchorPoint);
protected:
	XArray<XUIWidget*>		m_aItems; 
	Gravity					m_eGravity;
	MagneticType			m_eMagneticType;
	xbool					m_bMagneticAllowedOutOfBoundary;
	xfloat32				m_fItemsMargin;
	xfloat32				m_fLeftPadding;
	xfloat32				m_fRightPadding;
	xfloat32				m_fTopPadding;	
	xfloat32				m_fBottomPadding;
	xfloat32				m_fScrollTime;
	xint32					m_nCurSelectedIndex;
	xbool					m_bInnerContainerDoLayoutDirty;
	XUIListViewCallback		m_pEventCallback;
};
#endif
