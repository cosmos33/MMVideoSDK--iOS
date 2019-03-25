/******************************************************************************

@File         UILabel.h

@Version       1.0

@Created      2018, 6, 13

@Description  

@HISTORY:

******************************************************************************/

#ifndef _XUI_LABEL_H_
#define _XUI_LABEL_H_

#include "XUIWidget.h"
#include <string>

class IXUIFontTexture;
class XUIFontSprite;
class IXUIFontSysTexture;
struct XUISysFontDef;

#ifdef DEBUG
	#define _X_FontDebug 0
#endif // DEBUG

enum XUITextVAlignment
{
	XUI_TV_TOP,
	XUI_TV_CENTER,
	XUI_TV_BOTTOM
};

enum XUITextHAlignment
{
	XUI_TH_LEFT,
	XUI_TH_CENTER,
	XUI_TH_RIGHT
};

enum XUIGlyphCollection {
	XUI_GC_DYNAMIC,
	XUI_GC_CUSTOM
};

struct XUITTFConfig
{
	explicit XUITTFConfig(const XString& _strFilePath = "", xfloat32 _fontPointSize = 12, xint32 _nOutline = 0,
		const XUIGlyphCollection& _eGlyphCollection = XUIGlyphCollection::XUI_GC_DYNAMIC, const xchar *_pCustomGlyphCollection = NULL)
		: strFontFilePath(_strFilePath)
		, fontPointSize(_fontPointSize)
		, eGlyphs(_eGlyphCollection)
		, pCustomGlyphs(_pCustomGlyphCollection)
		, nOutlineSize(_nOutline)
	{}

	XString				strFontFilePath;		// 字体文件路径
	xfloat32			fontPointSize;			// 字体点数大小   

	XUIGlyphCollection	eGlyphs;				// 更新类型
	const xchar			*pCustomGlyphs;			// 自定义类型时，预生成的字符
	xint32				nOutlineSize;			// 字体边界线宽 

	// 	xbool				bItalics;				// 斜体
	//  xbool				bUnderline;				// 下划线
	// 	xbool				bStrikethrough;			// 删除线
};



class XUILabel : public XUIWidget
{
public:
	X_CLASS_DEF(XUILabel)

	enum XUIELabelEffect {
		XUI_NORMAL,
		XUI_OUTLINE
	};

public:

	static XUILabel*				CreateWithTTF();

	static XUILabel*				CreateWithTTF(const XUITTFConfig& ttfConfig, const XString& strUtf8Text, xint32 nLineWidth = 0,
										XUITextHAlignment hAlignment = XUI_TH_LEFT, XUITextVAlignment vAlignment = XUI_TV_TOP);

	static XUILabel*				CreateWithTTF(const XString& strUtf8Text, const XString& strFontFilePath, xfloat32 fontPointSize, xint32 nLineWidth = 0,
										XUITextHAlignment hAlignment = XUI_TH_LEFT, XUITextVAlignment vAlignment = XUI_TV_TOP);

	static XUILabel*				CreateWithSystemFont();
	static XUILabel*				CreateWithSystemFont(const XString& strUtf8Text, const XString& fontName, xfloat32 fontPointSize,
										XUITextHAlignment hAlignment = XUI_TH_LEFT, XUITextVAlignment vAlignment = XUI_TV_TOP);

public:
									XUILabel(XUITextHAlignment hAlignment = XUI_TH_LEFT,	XUITextVAlignment vAlignment = XUI_TV_TOP);
	virtual							~XUILabel();		
	virtual	const XVECTOR2&			GetContentSize() const override;
	virtual void					Visit(IXWorld* pWorld, const XMATRIX4& matParentTransform, xuint32 unParentFlags) override;
	virtual void					Draw(IXWorld* pWorld, xuint32 unParentFlags) override;

	/*
		应用设置
	*/	
	void							UpdateImmediately();

	/*
		设置字体大小
	*/
	void							SetTextPointSize(xfloat32 fPointSize);
	X_FORCEINLINE xfloat32			GetTextPointSize() const { return m_fOriginalFontSize; }

	/*
		更改字体
	*/
	void							SetTTFFontPath(const XString &strPath);
	X_FORCEINLINE const XString&	GetTTFFontPath() const { return m_strFontPath; }


	/*
		设置文本内容
	*/
	void							SetString(const XString &strUtf8Text);
	const XString&					GetString() const { return m_utf8Text; }
	xint32							GetStringCount() const { return (xint32)(m_utf32Text.length()); }

	/*
		设置文本对齐方式， hAlign ： 水平对齐， vAlign 竖直对齐
	*/

	void							SetAlignment(XUITextHAlignment hAlign, XUITextVAlignment vAlign);
	void							SetHAlignMent(XUITextHAlignment hAlign);
	void							SetVAlignMent(XUITextVAlignment vAlign);
	X_FORCEINLINE XUITextHAlignment	GetHAlignment() { return m_eHAlignment; }
	X_FORCEINLINE XUITextVAlignment	GetVAlignment() { return m_eVAlignment; }

	/*
		设置文本区域, 
		@ fWidth或fHeight为 小于等于 0.0，则表示大小自动适应。 即Label的宽度和高度，按文字行最大宽度和高度自动调整
		  当fWidth > 0.0，且文字行宽度超出fWidth，如果此时自动换行为true，则自动换行; 为false，则截断本行
		  当fHeight >0.0，且文字总高度超出fHeight，则截断文字。
	*/
	void							SetDimensions(xfloat32 fWidth, xfloat32 fHeight);
	XVECTOR2						GetDimensions() const { return XVECTOR2(m_fTextAreaWidth, m_fTextAreaHeight); }

	/* 
		设置文本颜色
	*/
	void							SetTextColor(const XCOLORBASE &clr);
	X_FORCEINLINE const XCOLORBASE&	GetTextColor() const { return m_TexColor; }

	/*
		设置文本的字间距, 仅TTF文字支持
	*/
	void							SetAdditionalKerning(xfloat32 fAdditionalKerning);
	X_FORCEINLINE xfloat32			GetAdditionalKerning() const { return m_fAdditionalKerning; }

	/*
		设置文本的行间距, 仅TTF文字支持
	*/
	void							SetLineSpacing(xfloat32 fLineSpacing);
	X_FORCEINLINE xfloat32			GetLineSpacing() const { return m_fLineSpacing; }

	/*
		设置是否自动换行	
		@ 默认true，为false时，要求m_fLabelWidth > 0.0f，才会进行自动换行处理。
	*/
	void							SetEnableWrap(xbool bEnableWrap);
	X_FORCEINLINE xbool				GetEnableWrap() const { return m_bEnableWrap; }
	
	/*
		设置是否允许在西文单词中换行, 仅TTF文字支持
	*/
	void							SetBreakOfWesternWord(xbool bBreakOfWesternWord);
	X_FORCEINLINE xbool				GetBreakOfWesternWord() const { return m_bBreakOfWesternWord; }
	
	/*
		设置系统字体名称
	*/
	void							SetSystemFontName(const XString &strFontName);
	X_FORCEINLINE const XString&	GetSystemFontName() const {	return m_strSystemFontName; }

	/*
		切换到系统字体
	*/
	void							ChangeToSystemFont();

	virtual xbool					SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;

	static const XString&			GetDefaultTTFPath() { return s_strDefaultTTFPath; }
	static void						SetDefaultTTFPath(const XString &strTemp) { s_strDefaultTTFPath = strTemp; }

protected:

	virtual XUINode*				CreateClonedInstance() override;
	virtual void					CopyProperties(XUINode* pNode) override;

	void							Reset();
	void							ClearData();
	void							ReleaseTTF();
	void							ReleaseSystemFInfo();

	xbool							UpdateContent();
	xbool							GenerateSpriteBuff(xint32 nSpriteNum);

// TTF
	xbool							InitWithTTF(const XUITTFConfig& ttfConfig, const XString& strText, xint32 nLabelWidth = 0);
	xbool							SetTTFConfiImpl(const XUITTFConfig& ttfConfig);
	xbool							ChangeFontTexture(IXUIFontTexture *pTexture, xbool bDistanceFieldEnabled);
	xbool							UpdateContentWithFontTexture();

	xbool							ComputeHorizontalKernings(const std::u32string& stringToRender);
	void							UpdateAlignmentOffet();
	void							UpdateFontSprite();
#if _X_FontDebug
	void							ShowTextureTest();
#endif

	xbool							ComputeMultilineTextWrap();
	void							ComputeAlignmentOffset();

	void							AddPlaceholderInfo(xint32 letterIndex, char32_t utf32Char);
	void							AddLetterInfo(const XVECTOR2& vPoint, char32_t utf32Char, xint32 nletterIndex, xint32 nlineIndex);

	xint32							GetFirstWordLen(const std::u32string& utf32Text, xint32 nStartIndex, xint32 nTextLen);
// ----

// System Font
	void							GetSysFontDef(XUISysFontDef *pDef) const;
	xbool							UpdateContentWithSystemFont();

// ----

	
	enum ELabelType 
	{
		XUIL_TTF = 0,
		XUIL_SYSTEMF,
	};

	struct LetterInfo
	{
		char32_t	utf32Char;
		xbool		valid;
		xfloat32	positionX;
		xfloat32	positionY;
		xint32		lineIndex;
	};

	ELabelType					m_eCurLabelType;
	xbool						m_bContentDirty;
	std::u32string				m_utf32Text;
	XString						m_utf8Text;
	
	xfloat32					m_fOutlineSize;
	//xbool						m_bUseDistanceField;
	xfloat32					m_fOriginalFontSize;

	XUIELabelEffect				m_eCurrLabelEffect;

	// align
	xfloat32					m_fTextAreaWidth;					
	xfloat32					m_fTextAreaHeight;
	XUITextHAlignment			m_eHAlignment;
	XUITextVAlignment			m_eVAlignment;	
	xfloat32					m_fAdditionalKerning;			// 附加的字间隔
	xfloat32					m_fLineSpacing;					// 附加的行间隔
	xfloat32					m_fLineHeight;					// 行高
	xbool						m_bEnableWrap;					// 是否自动换行，默认true。为false时，要求m_fLabelWidth > 0.0f，才会进行自动换行处理。
	xbool						m_bBreakOfWesternWord;			// 是否允许在西文单词中换行	

	// ---------------------------------TTF Draw buffer--------------------------------------------
	XString						m_strFontPath;
	XUITTFConfig				m_FontConfig;

	// align buf
	XArray<xint32>				m_vhorizontalKernings;

	//xint32						m_nLengthOfString;
	xfloat32					m_fTextDesiredHeight;
	XArray<xfloat32>			m_vLineWidth;
	XArray<xfloat32>			m_vlinesOffsetX;				// 各行开始偏移 由对齐关系产生
	xfloat32					m_fLetterOffsetY;				// 首行距离顶的偏移
	xint32						m_nNumberOfLines;

	// draw
	XCOLORBASE					m_TexColor;
	IXUIFontTexture*			m_pFontTexture;
	XArray<LetterInfo>			m_vLettersInfo;
	
	XArray<XUIFontSprite*>		m_vFontSpriteBuf;
	XArray<XUIFontSprite*>		m_vDrawFontSprite;
	// -----------------------------------------end------------------------------------------------


	// -------------------------------------System font draw buffer---------------------------------
	IXUIFontSysTexture*			m_pSystempFontTexture;
	XString						m_strSystemFontName;


	// -----------------------------------------end-------------------------------------------------


	static XString				s_strDefaultTTFPath;
	
};



#endif
