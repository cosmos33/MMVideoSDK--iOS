#ifndef _XUIPROGRESSBAR_H_
#define _XUIPROGRESSBAR_H_

#include "XUIWidget.h"

class XUIImage;
class XUIProgressBar : public XUIWidget
{
public:
	X_CLASS_DEF(XUIProgressBar)

	enum class Direction
	{
		XUI_LEFT,
		XUI_RIGHT
	};
	static XUIProgressBar*		Create();
	static XUIProgressBar*		Create(const XString& strTexture, xfloat32 fPercentage = 0.0f, TextureResType eTextureType = XUIWidget::TextureResType::XUI_LOCAL);
	XUIProgressBar();
	virtual ~XUIProgressBar();
	virtual void				Draw(IXWorld* pWorld, xuint32 unParentFlags) override;
	virtual void				SetContentSize(const XVECTOR2& vContentSize)override;
	XUIImage*					GetImage();
	void						LoadTexture(const XString& strTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	XString						GetTexture()const;
	void						SetDirection(Direction eDirection);
	Direction					GetDirection()const{ return m_eDirection; }
	void						SetPercent(xfloat32 fPercent);
	xfloat32					GetPercent() const{ return m_fPercent; }
	virtual xbool				SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	xbool						Init() override;
	xbool						Init(const XString& strTexture, xfloat32 fPercentage = 0.0f, TextureResType eTextureType = XUIWidget::TextureResType::XUI_LOCAL);
	virtual XUINode*			CreateClonedInstance() override;
	virtual void				CopyProperties(XUINode* pNode)override;
	void						UpdateProgressBar();
	void						SpriteFlipX();
	
protected:
	XUIImage*					m_pImage;
	Direction					m_eDirection;
	xfloat32					m_fPercent;
};

#endif
