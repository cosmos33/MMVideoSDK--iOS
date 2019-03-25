#ifndef _XUIABSTRACTCHECKBUTTON_H_
#define _XUIABSTRACTCHECKBUTTON_H_

#include "XUIWidget.h"

class XUIImage;
class XUIAbstractCheckButton : public XUIWidget
{

public:

	void										LoadTextures(const XString& strBackGroundNormalTexture,
															const XString& strBackGroundSelectedTexture,
															const XString& strCrossNormalTexture,
															const XString& strBackGroundDisabledTexture,
															const XString& strFrontCrossDisabledTexture,
															TextureResType eTextureType = TextureResType::XUI_LOCAL);

	void										LoadBackGroundTexture(const XString& strBackGroundNormalTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void										LoadBackGroundSelectedTexture(const XString& strBackGroundSelectedTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void										LoadFrontCrossTexture(const XString& strCrossNormalTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void										LoadBackGroundDisabledTexture(const XString& strBackGroundDisabledTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void										LoadFrontCrossDisabledTexture(const XString& strFrontCrossDisabledTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);

	XString										GetBackgroundTexture()const;
	XString										GetBackgroundSelectedTexture()const;
	XString										GetBackgroundDisabledTexture()const;
	XString										GetFrontCrossTexture()const;
	XString										GetFrontCrossDisabledTexture()const;


	void										SetSelected(const xbool& selected);
	xbool										IsSelected() const;
	
	void										SetZoomScale(const xfloat32& scale);
	xfloat32									GetZoomScale() const;


	virtual	void								SetContentSize(const XVECTOR2& vContentSize) override;
	virtual	void								SetAnchorPoint(const XVECTOR2& vAnchorPoint) override;

	virtual xbool								Init() override;
	virtual xbool								Init(const XString& strBackGroundNormalTexture,
													const XString& strBackGroundSelectedTexture,
													const XString& strCrossNormalTexture,
													const XString& strBackGroundDisabledTexture,
													const XString& strFrontCrossDisabledTexture,
													TextureResType eTextureType = TextureResType::XUI_LOCAL);


	

	virtual xbool								SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;

protected:

	XUIAbstractCheckButton();
	virtual ~XUIAbstractCheckButton();

	virtual void								InitProtectedChild();
	virtual void								OnPressStateChangedToNormal() override;
	virtual void								OnPressStateChangedToPressed() override;
	virtual void								OnPressStateChangedToDisabled() override;

	virtual void								DispatchSelectChangedEvent(xbool bSelected) = 0;

	virtual void								CopyProperties(XUINode* pNode);

protected:
	XUIImage*									m_pBackGroundBoxImage;
 	XUIImage*									m_pFrontCrossImage;

	xbool										m_bSelected;

	xfloat32									m_fZoomScale;
	xfloat32									m_fBackgroundTextureScaleX;
	xfloat32									m_fBackgroundTextureScaleY;

	xbool										m_bBackgroundSelectedTextureLoaded;
	xbool										m_bBackgroundDisabledTextureLoaded;
	xbool										m_bFrontCrossDisabeldTextureLoaded;
};
















#endif