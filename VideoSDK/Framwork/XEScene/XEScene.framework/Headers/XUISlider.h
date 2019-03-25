#ifndef _XUISLIDER_H_
#define _XUISLIDER_H_

#include "XUIWidget.h"

class XUISprite;
class IXTexture2D;
class XUIImage;
class XUISlider : public XUIWidget
{
public:
	X_CLASS_DEF(XUISlider)
	enum class EventType
	{
		XUI_ON_PERCENTAGE_CHANGED,
		XUI_ON_SLIDEBALL_DOWN,
		XUI_ON_SLIDEBALL_UP,
		XUI_ON_SLIDEBALL_CANCEL
	};
	typedef std::function<void(XUINode*, EventType)> XUISliderCallback;
	static XUISlider*	Create();
	static XUISlider*	Create(const XString& strBarTexture, const XString& strBallNormalTexture, TextureResType eTexType = TextureResType::XUI_LOCAL);
	XUISlider();
	virtual ~XUISlider();
	XUIImage*			GetBarImage();
	XUIImage*			GetProgressBarImage();
	XUIImage*			GetBallImage();
	void				LoadBarTexture(const XString& strBarTexture, TextureResType eTexType = TextureResType::XUI_LOCAL);
	void				LoadProgressBarTexture(const XString& strProgressBarTexture, TextureResType eTexType = TextureResType::XUI_LOCAL);
	void				LoadBallNormalTexture(const XString& strBarNormalTexture, TextureResType eTexType = TextureResType::XUI_LOCAL);
	void				LoadBallPressedTexture(const XString& strBarPressedTexture, TextureResType eTexType = TextureResType::XUI_LOCAL);
	void				LoadBallDisabledTexture(const XString& strBarDisabledTexture, TextureResType eTexType = TextureResType::XUI_LOCAL);
	XString				GetBarTexture()const;
	XString				GetProgressBarTexture()const;
	XString				GetBallNormalTexture()const;
	XString				GetBallPressedTexture()const;
	XString				GetBallDisabledTexture()const;
	void				SetPercent(xint32 nPercent);
	xint32				GetPercent()const{ return m_nPercent; }
	void				SetMaxPercent(xint32 nMaxPercent){ m_nMaxPercent = nMaxPercent; }
	xint32				GetMaxPercent()const{ return m_nMaxPercent; }
	void				AddEventListener(const XUISliderCallback& callback){ m_SliderCallback = callback; }
	virtual xbool		OnTouchBegan(XUITouch* pTouch, XUIEvent* pUnusedEvent) override;
	virtual void		OnTouchMoved(XUITouch* pTouch, XUIEvent* pUnusedEvent) override;
	virtual void		OnTouchEnded(XUITouch* pTouch, XUIEvent* pUnusedEvent) override;
	virtual void		OnTouchCancelled(XUITouch* pTouch, XUIEvent* pUnusedEvent) override;
	virtual xbool		HitTest(const XVECTOR2& vPoint, XVECTOR2* pHitPos) override;
	virtual void		SetContentSize(const XVECTOR2& vContentSize)override;
	void				SetBallSize(const XVECTOR2& vSize);
	XVECTOR2			GetBallSize() const;
	void				PercentChangedEvent(EventType event);
	virtual xbool		SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	virtual xbool		Init() override;
	virtual xbool		Init(const XString& strBarTexture, const XString& strBallNormalTexture, TextureResType eTexType = TextureResType::XUI_LOCAL);
	virtual XUINode*	CreateClonedInstance() override;
	virtual void		CopyProperties(XUINode* pNode)override;
	xfloat32			GetPercentWithBallPos(const XVECTOR2 &vPoint);
protected:
	XUIImage*			m_pBarImage;
	XUIImage*			m_pProgressBarImage;
	XUIImage*			m_pBallImage;
	XUISliderCallback	m_SliderCallback;
	xint32				m_nPercent;
	xint32				m_nMaxPercent;
};
#endif
