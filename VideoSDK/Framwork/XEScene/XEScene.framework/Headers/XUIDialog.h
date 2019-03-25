#ifndef _XUIDIALOG_H_
#define _XUIDIALOG_H_

// 当前废弃不用

#include "XUIWidget.h"

class XUISprite;
class IXTexture2D;
class XUIDialog : public XUIWidget
{
public:
	X_CLASS_DEF(XUIDialog)

	static XUIDialog*		Create();
	static XUIDialog*		Create(const XString& strBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	XUIDialog();
	virtual ~XUIDialog();
	virtual void			Draw(IXWorld* pWorld, xuint32 unParentFlags)override;
	virtual void			SetContentSize(const XVECTOR2& vContentSize)override;
	virtual void			LoadTexture(const XString& strBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);

	xbool					IsModal()const{ return m_bModal; }
	virtual void			Show(xbool bModal = xfalse);
	virtual void			Hide();
	virtual xbool			IsShow()const{ return m_bVisible; }
	xbool					IsTouchMovable()const{ return m_bTouchMovable; }
	virtual void			SetTouchMovable(xbool bTouchMovable){ m_bTouchMovable = bTouchMovable; }

	virtual void			SetTouchEnabled(xbool enabled)override;
	virtual xbool			HitTest(const XVECTOR2& vPoint, XVECTOR2* pHitPos) override;
	virtual xbool			OnTouchBegan(XUITouch* pTouch, XUIEvent* pUnusedEvent)override;
	virtual void			OnTouchMoved(XUITouch *pTouch, XUIEvent* pUnusedEvent)override;
	virtual void			OnTouchEnded(XUITouch *pTouch, XUIEvent* pUnusedEvent)override;
protected:
	virtual xbool			Init() override;
	virtual xbool			Init(const XString& strBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
protected:
	XUISprite*				m_pImageSprite;
	IXTexture2D*			m_pTexture;
	TextureResType			m_eTextureType;
	xbool					m_bModal;
	xbool					m_bTouchMovable;
	mutable xbool			m_bHitOnWidget;	// when modal
};

#endif
