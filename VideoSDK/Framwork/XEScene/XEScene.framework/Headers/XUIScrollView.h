#ifndef _XUISCROLLVIEW_H_
#define _XUISCROLLVIEW_H_

#include "XUILayout.h"
#include <list>
class XUILayout;
class XUIScrollViewBar;
class XUIScrollView : public XUILayout
{
public:
	X_CLASS_DEF(XUIScrollView)
	typedef enum
	{
		SCROLLVIEW_EVENT_SCROLL_TO_TOP,
		SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM,
		SCROLLVIEW_EVENT_SCROLL_TO_LEFT,
		SCROLLVIEW_EVENT_SCROLL_TO_RIGHT,
		SCROLLVIEW_EVENT_SCROLLING,
		SCROLLVIEW_EVENT_BOUNCE_TOP,
		SCROLLVIEW_EVENT_BOUNCE_BOTTOM,
		SCROLLVIEW_EVENT_BOUNCE_LEFT,
		SCROLLVIEW_EVENT_BOUNCE_RIGHT,
		SCROLLVIEW_EVENT_SCROLLING_BEGAN,
		SCROLLVIEW_EVENT_SCROLLING_ENDED,
		SCROLLVIEW_EVENT_AUTOSCROLL_ENDED
	}ScrollviewEventType;
	enum class Direction
	{
		XUI_NONE,
		XUI_VERTICAL,
		XUI_HORIZONTAL,
		XUI_BOTH
	};
	enum class EventType
	{
		XUI_SCROLL_TO_TOP,
		XUI_SCROLL_TO_BOTTOM,
		XUI_SCROLL_TO_LEFT,
		XUI_SCROLL_TO_RIGHT,
		XUI_SCROLLING,
		XUI_BOUNCE_TOP,
		XUI_BOUNCE_BOTTOM,
		XUI_BOUNCE_LEFT,
		XUI_BOUNCE_RIGHT,
		XUI_CONTAINER_MOVED,
		XUI_SCROLLING_BEGAN,
		XUI_SCROLLING_ENDED,
		XUI_AUTOSCROLL_ENDED,
		XUI_TOP_ON_RELEASE,
		XUI_BOTTOM_ON_RELEASE,
	};
	static XUIScrollView*	Create();
	XUIScrollView();
	virtual ~XUIScrollView();
	typedef std::function<void(XUINode*, EventType)> XUIScrollViewCallback;
	virtual void			SetContentSize(const XVECTOR2& vContentSize)override;
	virtual void			SetDirection(Direction eDir);
	Direction				GetDirection()const{ return m_eDirection; }
	XUILayout*				GetInnerContainer()const;
	virtual void			StopAutoScroll();
	virtual void			ScrollToBottom(xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToTop(xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToLeft(xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToRight(xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToTopLeft(xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToTopRight(xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToBottomLeft(xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToBottomRight(xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToPercentVertical(xfloat32 fPercent, xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToPercentHorizontal(xfloat32 fPercent, xfloat32 fTimeInSec, xbool bAttenuated);
	virtual void			ScrollToPercentBothDirection(const XVECTOR2& vPercent, xfloat32 fTimeInSec, xbool bAttenuated);
	xfloat32				GetScrolledPercentVertical() const;
	xfloat32				GetScrolledPercentHorizontal() const;
	XVECTOR2				GetScrolledPercentBothDirection() const;
	virtual void			JumpToBottom();
	virtual void			JumpToTop();
	virtual void			JumpToLeft();
	virtual void			JumpToRight();
	virtual void			JumpToTopLeft();
	virtual void			JumpToTopRight();
	virtual void			JumpToBottomLeft();
	virtual void			JumpToBottomRight();
	virtual void			JumpToPercentVertical(xfloat32 fPercent);
	virtual void			JumpToPercentHorizontal(xfloat32 fPercent);
	virtual void			JumpToPercentBothDirection(const XVECTOR2& vPercent);
	void					SetInnerContainerSize(const XVECTOR2& vSize);
	const XVECTOR2&			GetInnerContainerSize() const;
	void					SetInnerContainerPosition(const XVECTOR2& vPos);
	const XVECTOR2&			GetInnerContainerPosition() const;
	virtual void			AddScrollViewEventListener(const XUIScrollViewCallback& callback);
	
	virtual void			AddChild(XUINode* pChild)override;
	virtual xint32			GetChildrenNum()const override;
	virtual XArray<XUINode*>&		GetChildren()override;
	virtual const XArray<XUINode*>& GetChildren() const override;
	virtual XUINode*		GetChildByName(const XString& strChild)const override;
	virtual XUINode*		GetChildByNameRecrusive(const XString& strChild)const override;
	virtual void			RemoveChild(XUINode* pChild, xbool bClean = xtrue)override;
	virtual void			RemoveAllChildren(xbool bClean = xtrue)override;
	
	virtual xbool			OnTouchBegan(XUITouch* pTouch, XUIEvent* pUnusedEvent)override;
	virtual void			OnTouchMoved(XUITouch *pTouch, XUIEvent* pUnusedEvent)override;
	virtual void			OnTouchEnded(XUITouch *pTouch, XUIEvent* pUnusedEvent)override;
	virtual void			OnTouchCancelled(XUITouch *pTouch, XUIEvent* pUnusedEvent)override;
	virtual void			Update(xfloat32 fDelta) override;
	void					SetBounceEnabled(xbool bEnabled){ m_bBounceEnabled = bEnabled; }
	xbool					IsBounceEnabled() const{ return m_bBounceEnabled; }
	void					SetInertiaScrollEnabled(xbool bEnabled){ m_bInertiaScrollEnabled = bEnabled; }
	xbool					IsInertiaScrollEnabled() const{ return m_bInertiaScrollEnabled; }
	void					SetScrollBarEnabled(xbool enabled);
	xbool					IsScrollBarEnabled() const{ return m_bScrollBarEnabled; }
	void					SetScrollBarWidth(xfloat32 fWidth);
	xfloat32				GetScrollBarWidth() const;
	void					SetScrollBarColor(const XCOLORBASE& color);
	XCOLORBASE				GetScrollBarColor() const;
	void					LoadScrollBarTexture(const XString& strTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	XString					GetScrollBarTexture();

	xfloat32				GetVerticalScrollBarPosPercent();
	xfloat32				GetHorizontalScrollBarPosPercent();
	/*void					SetScrollBarAutoHideEnabled(xbool autoHideEnabled);
	xbool					IsScrollBarAutoHideEnabled() const;
	void					SetScrollBarAutoHideTime(xfloat32 fAutoHideTime);
	xfloat32				GetScrollBarAutoHideTime() const;*/
	
	virtual void			SetLayoutType(Type type) override;
	virtual Type			GetLayoutType() const override;
	virtual void			SetOrder(XUILayout::Order eOrder)override;
	virtual XUILayout::Order GetOrder()const override;
	virtual void			OnEnter() override;
	xbool					IsScrolling() const{ return m_bScrolling; }
	xbool					IsAutoScrolling() const{ return m_bAutoScrolling; }
	virtual xbool			SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	enum class MoveDirection
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
	};

	virtual xbool			Init() override;
	virtual void			StartAttenuatingAutoScroll(const XVECTOR2& vDeltaMove, const XVECTOR2& vInitialVelocity);
	void					StartAutoScroll(const XVECTOR2& fDeltaMove, xfloat32 fTime, xbool bAttenuated);
	void					StartAutoScrollToDestination(const XVECTOR2& vDes, xfloat32 fTime, xbool bAttenuated);
	
	virtual void			InitScrollBar();
	virtual void			RemoveScrollBar();

	XVECTOR2				FlattenVectorByDirection(const XVECTOR2& vec);
	virtual XVECTOR2		GetHowMuchOutOfBoundary(const XVECTOR2& vAddition = XVECTOR2(0.0f));
	xbool					IsOutOfBoundary(MoveDirection dir);
	xbool					IsOutOfBoundary();
	void					JumpToDestination(const XVECTOR2& vDes);
	virtual void			ScrollChildren(const XVECTOR2& vDeltaMove);
	virtual void			MoveInnerContainer(const XVECTOR2& vDeltaMove, xbool bCanStartBounceBack);
	xbool					CalculateCurrAndPrevTouchPoints(XUITouch* touch, XVECTOR2* currPt, XVECTOR2* prevPt);
	void					GatherTouchMove(const XVECTOR2& vDelta);	
	XVECTOR2				CalculateTouchMoveVelocity() const;
	
	xbool					IsNecessaryAutoScrollBrake();
	void					ProcessAutoScrolling(xfloat32 fDeltaTime);
	
	void					StartInertiaScroll(const XVECTOR2& vTouchMoveVelocity);
	xbool					StartBounceBackIfNeeded();
	void					UpdateScrollBar(const XVECTOR2& vOutOfBoundary);

	virtual void			HandlePressLogic(XUITouch* pTouch);
	virtual void			HandleMoveLogic(XUITouch* pTouch);
	virtual void			HandleReleaseLogic(XUITouch* pTouch);
	virtual void			InterceptTouchEvent(XUIWidget::TouchEventType event, XUIWidget* pSender, XUITouch* pTouch) override;

	void					ProcessScrollEvent(MoveDirection eDir, xbool bounce);
	void					ProcessScrollingEvent();
	void					ProcessScrollingEndedEvent();
	void					DispatchEvent(ScrollviewEventType eScrollEventType, EventType eEventType);
	// deprecated
	virtual xfloat32		GetAutoScrollStopEpsilon() const{ return X_EPSILON_FLT32; }
protected:
	XUILayout*				m_pInnerContainer;
	Direction				m_eDirection;
	xfloat32				m_fLeftBoundary;
	xfloat32				m_fRightBoundary;
	xfloat32				m_fTopBoundary;
	xfloat32				m_fBottomBoundary;

	std::list<XVECTOR2>		m_aTouchMoveDisplacements;
	std::list<xfloat32>		m_aTouchMoveTimeDeltas;
	xuint32					m_unTouchMovePreviousTimestamp;

	xbool					m_bScrolling;
	xbool					m_bAutoScrolling;
	xbool					m_bAutoScrollAttenuate;
	xfloat32				m_fAutoScrollTotalTime;
	xfloat32				m_fAutoScrollAccumulatedTime;
	XVECTOR2				m_vAutoScrollStartPosition;
	XVECTOR2				m_vAutoScrollTargetDelta;
	xbool					m_bAutoScrollCurrentlyOutOfBoundary;
	xbool					m_bAutoScrollBraking;
	XVECTOR2				m_vAutoScrollBrakingStartPosition;
	
	xbool					m_bInertiaScrollEnabled;
	xbool					m_bBounceEnabled;
	XVECTOR2				m_vOutOfBoundaryAmount;
	xbool					m_bOutOfBoundaryAmountDirty;

	xbool					m_bInterceptTouch;

	xbool					m_bScrollBarEnabled;
	XUIScrollViewBar*		m_pVerticalScrollBar;
	XUIScrollViewBar*		m_pHorizontalScrollBar;
	xfloat32				m_fScrollBarWidth;
	XCOLORBASE				m_clrScrollBar;
	XUIScrollViewCallback	m_pEventCallback;
	xbool					m_bTopOnRelease;
	xbool					m_bBottomOnRelease;
protected:
	virtual XUINode*		CreateClonedInstance() override;
	virtual void			CopyProperties(XUINode* pNode)override;
};
#endif
