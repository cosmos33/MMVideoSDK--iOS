#ifndef _UILAYOUT_H_
#define _UILAYOUT_H_

#include "XUIWidget.h"

class XUILayoutManager;
class XUIImage;
class XUILayout : public XUIWidget
{
public:
	enum class Type
	{
		XUI_ABSOLUTE,
		XUI_VERTICAL,
		XUI_HORIZONTAL,
		XUI_GRID,
		XUI_TREE
	};
	enum class Order
	{
		XUI_NORMAL,
		XUI_INVERSE
	};
	enum class ClippingType
	{
		XUI_STENCIL,
		XUI_SCISSOR
	};
	XUILayout();
	virtual ~XUILayout();
	static XUILayout*	Create();
	XUIImage*			GetImage();
	virtual void		LoadBackGroundTexture(const XString& strTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	XString				GetBackGroundTexture();
	virtual void		SetContentSize(const XVECTOR2& vContentSize)override;
	virtual void		SetAnchorPoint(const XVECTOR2& vAnchorPoint)override;

	virtual void		SetPadding(xfloat32 fLeft, xfloat32 fRight, xfloat32 fTop, xfloat32 fBottom);
	virtual void		SetLeftPadding(xfloat32 fLeft){ m_fLeftPadding = fLeft; }
	virtual void		SetRightPadding(xfloat32 fRight){ m_fRightPadding = fRight; }
	virtual void		SetTopPadding(xfloat32 fTop){ m_fTopPadding = fTop; }
	virtual void		SetBottomPadding(xfloat32 fBottom){ m_fBottomPadding = fBottom; }
	void				GetPadding(xfloat32& fLeft, xfloat32& fRight, xfloat32& fTop, xfloat32& fBottom)const;
	xfloat32			GetLeftPadding()const{ return m_fLeftPadding; }
	xfloat32			GetRightPadding()const{ return m_fRightPadding; }
	xfloat32			GetTopPadding()const{ return m_fTopPadding; }
	xfloat32			GetBottomPadding()const{ return m_fRightPadding; }
	void				SetSpaceX(xfloat32 fSpaceX){ m_fSpaceX = fSpaceX; }
	xfloat32			GetSpaceX()const{ return m_fSpaceX; }
	void				SetSpaceY(xfloat32 fSpaceY){ m_fSpaceY = fSpaceY; }
	xfloat32			GetSpaceY()const{ return m_fSpaceY; }
	virtual void		SetOrder(Order eOrder){ m_eOrder = eOrder; }
	virtual Order		GetOrder()const{ return m_eOrder; }

	void				SetLineIndent(xfloat32 fIndent){ m_fLineIndent = fIndent; }
	xfloat32			GetLineIndent()const{ return m_fLineIndent; }

	virtual void		EnableClipping(xbool bEnabled);
	virtual xbool		IsClippingEnabled()const{ return m_bClippingEnabled; }
	void				SetClippingType(ClippingType eType);
	ClippingType		GetClippingType()const{ return m_eClippingType; }
	virtual void		SetLayoutType(Type eType);
	virtual Type		GetLayoutType() const{ return m_eLayoutType; }
	virtual void		SetGlobalZOrder(xfloat32 fGlobalZOrder) override;
	virtual void		AddChild(XUINode* pChild)override;
	virtual void		Visit(IXWorld* pWorld, const XMATRIX4& matParentTransform, xuint32 unParentFlags)override;
	virtual void		RemoveChild(XUINode* pChild, xbool bCleanup = xtrue) override;
	virtual void		RemoveAllChildren(xbool bClean = xtrue) override;
	virtual void		OnEnter() override;
	virtual void		OnExit() override;
	virtual void		ForceDoLayout();
	virtual void		RequestDoLayout();
	virtual void		Adapt()override;
	std::function<xint32(FocusDirection, XUIWidget*)> onPassFocusToChild;

	virtual void					DoLayout();
	virtual XUILayoutManager*		CreateLayoutManager();
	virtual XVECTOR2				GetLayoutContentSize()const;
	virtual const XArray<XUINode*>& GetLayoutElements()const;

	virtual xbool		SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;

	// deprecated
	void				SetLoopFocus(xbool bLoop){}
	xbool				IsLoopFocus()const{ return xfalse; }
	void				SetPassFocusToChild(xbool bPass){}
	xbool				IsPassFocusToChild()const{ return xtrue; }
protected:
	virtual xbool		Init();
	virtual XUINode*	CreateClonedInstance() override;
	virtual void		CopyProperties(XUINode* pNode)override;
	virtual void		CopyClonedChildren(XUINode* pNode)override{} // do not clone children
	void				SupplyTheLayoutParameterLackToChild(XUIWidget* pChild);
	xint32				FindNearestChildWidgetIndex(FocusDirection direction, XUIWidget* pWidget);
	XUIImage*			m_pImage;
	xbool				m_bClippingEnabled;
	ClippingType		m_eClippingType;
	Type				m_eLayoutType;
	xbool				m_bLayoutDirty;
	xbool				m_bClippingRectDirty;
	XUILayoutManager*	m_pLayoutManager;
	xfloat32			m_fLeftPadding;
	xfloat32			m_fRightPadding;
	xfloat32			m_fTopPadding;
	xfloat32			m_fBottomPadding;
	xfloat32			m_fSpaceX;
	xfloat32			m_fSpaceY;
	xfloat32			m_fLineIndent;
	Order				m_eOrder;
};

#endif