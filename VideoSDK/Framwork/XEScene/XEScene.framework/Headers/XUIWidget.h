#ifndef _XUIWIDGET_H_
#define _XUIWIDGET_H_

#include "XUINode.h"
#include "XUILayoutParameter.h"
#include "XHashTable.h"
#include "XBase3DTypes.h"

class XUIEventListenerTouchOne;
class XUITouch;
class XUIEvent;
class XUIWidgetAlignment;
class XUILayoutParameter;
class XUIWidget : public XUINode
{
public:
	X_CLASS_DEF(XUIWidget )
	enum class FocusDirection
	{
		XUI_LEFT,
		XUI_RIGHT,
		XUI_UP,
		XUI_DOWN
	};
	enum class PositionType
	{
		XUI_ABSOLUTE,
		XUI_PERCENT
	};
	enum class SizeType
	{
		XUI_ABSOLUTE,
		XUI_PERCENT
	};
	enum class TouchEventType
	{
		XUI_BEGAN,
		XUI_MOVED,
		XUI_ENDED,
		XUI_CANCELED
	};
	enum class BrightStyle
	{
		XUI_NONE = -1,
		XUI_NORMAL,
		XUI_HIGHLIGHT
	};
	enum class TextureResType
	{
		XUI_LOCAL = 0,
		XUI_PLIST = 1
	};
	typedef std::function<void(XUINode*, XUIWidget::TouchEventType)> XUIWidgetTouchCallback;
	typedef std::function<void(XUINode*)> XUIWidgetClickCallback;
	typedef std::function<void(XUINode*, xint32)> XUIWidgetEventCallback;
	typedef std::function<void(XUIWidget*, XUIWidget*)> XUIWidgetFocusChangedCallback;

public:
	XUIWidget();
	virtual						~XUIWidget();
	static XUIWidget*			Create();

	virtual void				SetEnabled(xbool enabled);
	xbool						IsEnabled() const{ return m_bEnabled; }
	virtual void				SetColor(const XCOLORBASE& color);
	const XCOLORBASE&			GetColor() const{ return m_Color; }
	void						SetBright(xbool bBright);
	xbool						IsBright() const{ return m_bBright; }
	void						SetBrightStyle(BrightStyle style);
	virtual void				SetTouchEnabled(xbool enabled);
	xbool						IsTouchEnabled() const{ return m_bTouchEnabled; }
	void						SetHighlighted(xbool bHighlight);
	xbool						IsHighlighted() const{ return m_bHighlight; }

	virtual void				SetPosition(const XVECTOR2& vPos) override;

	void						AddTouchEventListener(const XUIWidgetTouchCallback& callback);
	void						AddClickEventListener(const XUIWidgetClickCallback& callback);
	void						AddWidgetEventListener(const XUIWidgetEventCallback& callback);
	virtual xbool				HitTest(const XVECTOR2& vPoint, XVECTOR2* pHitPos);
	virtual xbool				OnTouchBegan(XUITouch* pTouch, XUIEvent* pUnusedEvent);
	virtual void				OnTouchMoved(XUITouch *pTouch, XUIEvent* pUnusedEvent);
	virtual void				OnTouchEnded(XUITouch *pTouch, XUIEvent* pUnusedEvent);
	virtual void				OnTouchCancelled(XUITouch *pTouch, XUIEvent* pUnusedEvent);
	XUIWidgetAlignment*			GetAlignment(){ return m_pAlignment; }
	virtual void				RefreshLayout() override;
	void						SetListenerFixedPriority(xint32 nPriority);
	void						SetSwallowTouches(xbool bSwallow);
	xbool						IsSwallowTouches()const;
	xbool						IsFocused()const{ return m_bFocused; }
	void						SetFocused(xbool bFocus);
	xbool						IsFocusEnabled()const{ return m_bFocusEnabled; }
	void						SetFocusEnabled(xbool bEnable){ m_bFocusEnabled = bEnable; }
	void						SetPropagateTouchEvents(xbool bPropagate){ m_bPropagateTouchEvents = bPropagate; }
	xbool						IsPropagateTouchEvents()const{ return m_bPropagateTouchEvents; }

	const XVECTOR2&				GetTouchBeganPosition()const{ return m_vTouchBeganPosition; }
	const XVECTOR2&				GetTouchMovePosition()const{ return m_vTouchMovePosition; }
	const XVECTOR2&				GetTouchEndPosition()const{ return m_vTouchEndPosition; }
	//virtual void				IgnoreContentAdaptWithSize(xbool bIgnore);
	//bool						IsIgnoreContentAdaptWithSize() const{ return m_bIgnoreSize; }
	//XVECTOR2					GetVirtualSize();

	// layout
	void						SetLayoutParameter(XUILayoutParameter* parameter);
	XUILayoutParameter*			GetLayoutParameter()const;

	virtual void				FirstTick() override;
	virtual void				Visit(IXWorld* pWorld, const XMATRIX4& matParentTransform, xuint32 unParentFlags);
	virtual XUIWidget*			GetSelectedWidget(const XVECTOR2& vHitPos);
	virtual xbool				SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	virtual xbool				Init() override;
	virtual XUINode*			CreateClonedInstance() override;
	virtual void				CopyProperties(XUINode* pNode)override;
	virtual void				InterceptTouchEvent(TouchEventType event, XUIWidget* pSender, XUITouch* pTouch);
	void						PropagateTouchEvent(TouchEventType event, XUIWidget* pSender, XUITouch *pTouch);
	virtual void				Adapt(){}
	virtual void				OnPressStateChangedToNormal();
	virtual void				OnPressStateChangedToPressed();
	virtual void				OnPressStateChangedToDisabled();
	void						PushDownEvent();
	void						MoveEvent();
	virtual void				ReleaseUpEvent();
	virtual void				CancelUpEvent();
	xbool						IsParentEnabled();
	XUIWidget*					GetParentWidget(XUINode* pNode);
	xbool						IsParentVisible();
	virtual void				UpdateColor(){}
	XUIWidgetAlignment*			GetLayoutComponent();
	void						DispatchFocusEvent(XUIWidget* pLoseFocus, XUIWidget* pGetFocus);
	void						OnFocusChange(XUIWidget* pLoseFocus, XUIWidget* pGetFocus);
	void						RequestFocus();
	virtual void				OnFocusGot(){}
	virtual void				OnFocusLost(){}
protected:
	xbool						m_bEnabled;
	XCOLORBASE					m_Color;
	xbool						m_bBright;
	BrightStyle					m_BrightStyle;
	xbool						m_bTouchEnabled;
	xbool						m_bHighlight;
	xbool						m_bHitted;
	XUIEventListenerTouchOne*	m_pTouchListener;
	XVECTOR2					m_vTouchBeganPosition;
	XVECTOR2					m_vTouchMovePosition;
	XVECTOR2					m_vTouchEndPosition;
	XUIWidgetTouchCallback		m_TouchEventCallback;
	XUIWidgetClickCallback		m_ClickEventCallback;
	XUIWidgetEventCallback		m_WidgetEventCallback;

	XUIWidgetFocusChangedCallback m_FocusChangedCallback;
	XUIWidgetAlignment*			m_pAlignment;
	xbool						m_bAlignmentNeedUpdate;
	xbool						m_bFocused;
	xbool						m_bFocusEnabled;

	XHashTable<xint32, XUILayoutParameter*> m_tbLayoutParameter;
	XUILayoutParameter::Type				m_eLayoutParameterType;

	static XUIWidget*			g_pFocusedWidget;
	xbool						m_bPropagateTouchEvents;
};
#endif
