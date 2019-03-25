#ifndef _XUIBUTTON_H_
#define _XUIBUTTON_H_

#include "XUIWidget.h"

class XUIImage;
class XUIButton : public XUIWidget
{
public:
	X_CLASS_DEF(XUIButton)

	static XUIButton*		Create();
	static XUIButton*		Create(const XString& strNormalTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	XUIButton();
	virtual ~XUIButton();
	virtual void			Draw(IXWorld* pWorld, xuint32 unParentFlags)override;
	virtual void			SetContentSize(const XVECTOR2& vContentSize)override;
	virtual void			SetAnchorPoint(const XVECTOR2& vAnchorPoint)override;

	XUIImage*				GetImage();
	void					LoadNormalTexture(const XString& strTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void					LoadPressedTexture(const XString& strTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	// FIXME Hover仅在PC平台上有效，暂时不开发
	void					LoadHoverTexture(const XString& strTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void					LoadDisabledTexture(const XString& strTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	XString					GetNormalTexture()const;
	XString					GetPressedTexture()const;
	XString					GetDisabledTexture()const;

	virtual xbool			SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	virtual xbool			Init() override;
	virtual xbool			Init(const XString& strNormalTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	virtual void			OnPressStateChangedToNormal() override;
	virtual void			OnPressStateChangedToPressed() override;
	virtual void			OnPressStateChangedToDisabled() override;
	virtual XUINode*		CreateClonedInstance() override;
	virtual void			CopyProperties(XUINode* pNode)override;
	virtual void			UpdateColor();
protected:
	XUIImage*				m_pImage;
	xbool					m_bPressedLoaded;
	xbool					m_bDisabledLoaded;
};
#endif
