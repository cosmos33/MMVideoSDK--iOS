#ifndef _XUIRICHTEXT_H_
#define _XUIRICHTEXT_H_

#include "XUIWidget.h"
#include "XUIGeometry.h"

class XUILabel;

class XUIRichElement : public XMemBase
{
public:
	enum class Type
	{
		XUI_TEXT,  
		XUI_IMAGE, 
		XUI_CUSTOM,
		XUI_NEWLINE
	};
	XUIRichElement();
	virtual ~XUIRichElement(){};
	virtual const XString& GetType()const{ return m_strType; }
	xbool	Init(xint32 tag, const XCOLORBASE& color);
	xbool	EqualType(Type type);
	void	SetColor(const XCOLORBASE& color);
	virtual xbool	SerilizeXML(XXMLExtendTool& outXmlArchive);
	virtual XUIRichElement* Clone();
protected:
	virtual void			CopyProperties(XUIRichElement* pParameter);
	virtual XUIRichElement*	CreateClonedInstance();
	XString		m_strType;
	Type		m_eType;
	xint32		m_nTag;
	XCOLORBASE	m_color;
	friend class XUIRichText;
};

class XUIRichElementText : public XUIRichElement
{
public:
	enum {
		ITALICS_FLAG = 1 << 0,          /*!< italic text */
		BOLD_FLAG = 1 << 1,             /*!< bold text */
		UNDERLINE_FLAG = 1 << 2,        /*!< underline */
		STRIKETHROUGH_FLAG = 1 << 3,    /*!< strikethrough */
		URL_FLAG = 1 << 4,              /*!< url of anchor */
		OUTLINE_FLAG = 1 << 5,          /*!< outline effect */
		SHADOW_FLAG = 1 << 6,           /*!< shadow effect */
		GLOW_FLAG = 1 << 7              /*!< glow effect */
	};
	XUIRichElementText();
	virtual ~XUIRichElementText(){};
	xbool Init(xint32 tag, const XCOLORBASE& color, const XString& strText,
		const XString& strfontName, xfloat32 fFontSize, xint32 nflags,
		const XCOLORBASE& outlineColor = XCOLORBASE(1.0f), xint32 nOutlineSize = -1,
		const XCOLORBASE& shadowColor = XCOLORBASE(0.0f), const XVECTOR2& vShadowOffset = XVECTOR2(2.0, -2.0), xint32 nShadowBlurRadius = 0,
		const XCOLORBASE& glowColor = XCOLORBASE(1.0f));
	static XUIRichElementText* Create(xint32 tag, const XCOLORBASE& color, const XString& strText,
		const XString& strfontName, xfloat32 fFontSize, xint32 nflags,
		const XCOLORBASE& outlineColor = XCOLORBASE(1.0f), xint32 nOutlineSize = -1,
		const XCOLORBASE& shadowColor = XCOLORBASE(0.0f), const XVECTOR2& vShadowOffset = XVECTOR2(2.0, -2.0), xint32 nShadowBlurRadius = 0,
		const XCOLORBASE& glowColor = XCOLORBASE(1.0f));
	virtual xbool	SerilizeXML(XXMLExtendTool& outXmlArchive)override;
protected:
	virtual void			CopyProperties(XUIRichElement* pParameter);
	virtual XUIRichElement*	CreateClonedInstance();
	XString		m_strText;
	XString		m_strFontName;
	xfloat32	m_fFontSize;
	xint32		m_unFlags;
	XCOLORBASE	m_clrOutline;              
	xint32		m_nOutlineSize;            
	XCOLORBASE	m_clrShadow;               
	XVECTOR2	m_vShadowOffset;           
	xint32		m_nShadowBlurRadius;       
	XCOLORBASE	m_clrGlow;                 
	friend class XUIRichText;
};
class XUIImage;
class XUIRichElementImage : public XUIRichElement
{
public:
	XUIRichElementImage();
	virtual ~XUIRichElementImage(){}
	xbool Init(xint32 tag, const XCOLORBASE& color, const XString& filePath, XUIWidget::TextureResType eTexType = XUIWidget::TextureResType::XUI_LOCAL);
	xbool Init(xint32 tag, const XCOLORBASE& color, XUIImage* pImage);
	static XUIRichElementImage* Create(xint32 tag, const XCOLORBASE& color, const XString& filePath, XUIWidget::TextureResType eTexType = XUIWidget::TextureResType::XUI_LOCAL);
	static XUIRichElementImage* Create(xint32 tag, const XCOLORBASE& color, XUIImage* pImage);
	void SetWidth(xint32 nWidth){ m_nWidth = nWidth; }
	void SetHeight(xint32 nHeight){ m_nHeight = nHeight; }
	virtual xbool	SerilizeXML(XXMLExtendTool& outXmlArchive)override;
protected:
	virtual void			CopyProperties(XUIRichElement* pRichElement);
	virtual XUIRichElementImage*	CreateClonedInstance();
	XString m_strFilePath;
	XUIWidget::TextureResType m_eTextureType;
	xint32 m_nWidth;
	xint32 m_nHeight;
	XUIImage* m_pImage;
	friend class XUIRichText;
};

class XUIRichElementCustomNode : public XUIRichElement
{
public:
	XUIRichElementCustomNode();
	virtual ~XUIRichElementCustomNode(){}
	xbool Init(xint32 nTag, const XCOLORBASE& color, XUINode* pNode);
	static XUIRichElementCustomNode* Create(xint32 nTag, const XCOLORBASE& color, XUINode* pNode);
	virtual xbool	SerilizeXML(XXMLExtendTool& outXmlArchive)override;
protected:
	virtual void	CopyProperties(XUIRichElement* pRichElement);
	virtual XUIRichElementCustomNode*	CreateClonedInstance();

	XUINode* m_pNode;
	friend class XUIRichText;
};

class XUIRichElementNewLine : public XUIRichElement
{
public:
	XUIRichElementNewLine();
	virtual ~XUIRichElementNewLine(){};
	static XUIRichElementNewLine* Create(xint32 nTag, const XCOLORBASE& color);
protected:
	virtual void					CopyProperties(XUIRichElement* pRichElement);
	virtual XUIRichElementNewLine*	CreateClonedInstance();

	friend class XUIRichText;
};

class XUIRichText : public XUIWidget
{
public:
	X_CLASS_DEF(XUIRichText)

	enum class WrapMode
	{
		XUI_WRAP_PER_WORD,
		XUI_WRAP_PER_CHAR
	};

	enum class HorizontalAlignment 
	{
		XUI_LEFT,
		XUI_CENTER,
		XUI_RIGHT,
	};
	enum class TextLine
	{
		XUI_NONE,
		XUI_DEL,
		XUI_UNDER
	};

	enum class TextStyle
	{
		XUI_NONE,
		XUI_OUTLINE,
		XUI_SHADOW,
		XUI_GLOW
	};
	XUIRichText();
	virtual ~XUIRichText();
	static XUIRichText* Create();
	void				InsertElement(XUIRichElement* pElement, xint32 nIndex);
	void				AddElement(XUIRichElement* pElement);
	void				RemoveElement(xint32 nIndex);
	void				RemoveElement(XUIRichElement* pElement);
	void				NewLine();
	xint32				GetElementsNum() const;
	
	void				SetVerticalSpace(xfloat32 fSpace);
	void				SetWrapMode(WrapMode eWrapMode);
	WrapMode			GetWrapMode()const{ return m_eKeyWrapMode; }
	/*void				SetHorizontalAlignment(HorizontalAlignment eAlignment);
	HorizontalAlignment GetHorizontalAlignment() const;
	/*void				SetFontColor(const XCOLORBASE& clr);
	XCOLORBASE			GetFontColor()const;
	void				SetFontSize(xfloat32 fSize);
	void				SetAnchorFontColor(const XCOLORBASE& clor);
	XCOLORBASE			GetAnchorFontColor()const;
	void				SetAnchorTextBold(xbool bEnable);
	xbool				IsAnchorTextBoldEnabled()const;
	void				SetAnchorTextItalic(xbool bEnable);
	xbool				IsAnchorTextItalicEnabled()const;
	void				SetTextLine(TextLine eTextLine);
	TextLine			GetTextline()const;
	void				SetTextStyle(TextStyle eTextStyle);
	TextStyle			GetTextStyle()const;*/
	void				FormatText();
	const XVECTOR2&		GetActualSize()const{ return m_vActualSize; }
	virtual xbool		SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	virtual xbool		Init() override;
	virtual XUINode*	CreateClonedInstance() override;
	virtual void		CopyProperties(XUINode* pNode)override;
	virtual void		Adapt();
	void				AddNewLineElement();
	void				HandleText(const XString& strText, const XString& strFontName, xfloat32 fFontSize, const XCOLORBASE& color, xint32 nFlags, 
						const XCOLORBASE& clrOutline = XCOLORBASE(1.0f), xint32 nOutlineSize = -1,
						const XCOLORBASE& clrShadow = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f), const XVECTOR2& vShadowOffset = XVECTOR2(2.0f, -2.0f), xint32 nShadowBlurRadius = 0,
						const XCOLORBASE& clrGlow = XCOLORBASE(1.0f));
	void				HandleImage(const XString& strText, const XCOLORBASE& color, xint32 nWidth, xint32 nHeight);
	void				HandleImage(XUIImage* pImage);
	void				HandleCustom(XUINode* pNode);
	void				PushToContainer(XUINode* pNode);
	void				FormatNodes();
	xint32				FindSplitPositionForWord(XUILabel* pLabel, const XString& strText);
	xint32				FindSplitPositionForChar(XUILabel* pLabel, const XString& strText);
	void				DoHorizontalAlignment(const XArray<XUINode*>& aRow, xfloat32 fRowWidth);
	xfloat32			StripTrailingWhitespace(const XArray<XUINode*>& aRow);
protected:
	xbool				m_bFormatTextDirty;
	xfloat32			m_fLeftSpaceWidth;
	xfloat32			m_fVerticalSpace;
	WrapMode			m_eKeyWrapMode;
	HorizontalAlignment	m_nKeyHAlignment;
	XCOLORBASE			m_clrAnchorFont;
	XArray<XUIRichElement*>		m_aRichElements;
	XArray<XArray<XUINode*>>	m_aElementRenders;
	XVECTOR2			m_vActualSize;
};

#endif
