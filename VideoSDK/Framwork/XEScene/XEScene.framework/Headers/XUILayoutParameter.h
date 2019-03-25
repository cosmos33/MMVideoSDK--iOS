#ifndef _UILAYOUTPARAMETER_H_
#define _UILAYOUTPARAMETER_H_

#include "XMemBase.h"
#include "XString.h"

class XUIMargin
{
public:
	XUIMargin()
		: fLeft(0.0f)
		, fRight(0.0f)
		, fTop(0.0f)
		, fBottom(0.0f){}	
	xfloat32 fLeft;
	xfloat32 fRight;
	xfloat32 fTop;
	xfloat32 fBottom;
};

class XUILayoutParameter : public XMemBase
{
public:
	enum class Type
	{
		XUI_NONE = 0,
		XUI_LINEAR,
		XUI_RELATIVE
	};
	XUILayoutParameter();
	virtual ~XUILayoutParameter();
	static XUILayoutParameter*	Create();
	void						SetMargin(const XUIMargin& margin){ m_Margin = margin; }
	const XUIMargin&			GetMargin()const{ return m_Margin; }
	Type						GetLayoutType() const{ return m_eLayoutType; }
	virtual XUILayoutParameter*	Clone();
protected:
	virtual void				CopyProperties(XUILayoutParameter* pParameter);
	virtual XUILayoutParameter*	CreateClonedInstance();
	Type		m_eLayoutType;
	XUIMargin	m_Margin;
};

class XUILinearLayoutParameter : public XUILayoutParameter
{
public:
	enum class LinearGravity
	{
		XUI_NONE,
		XUI_LEFT,
		XUI_TOP,
		XUI_RIGHT,
		XUI_BOTTOM,
		XUI_CENTER_VERTICAL,
		XUI_CENTER_HORIZONTAL
	};
	XUILinearLayoutParameter();
	virtual ~XUILinearLayoutParameter(){};
	static XUILinearLayoutParameter* Create();
	void SetGravity(LinearGravity eGravity){ m_eLinearGravity = eGravity; }
	LinearGravity GetGravity() const{ return m_eLinearGravity; }
	virtual void				CopyProperties(XUILayoutParameter* pParameter);
	virtual XUILayoutParameter*	CreateClonedInstance();
protected:
	LinearGravity m_eLinearGravity;
};

class XUIRelativeLayoutParameter : public XUILayoutParameter
{
public:
	enum class RelativeAlign
	{
		XUI_NONE,
		XUI_PARENT_TOP_LEFT,
		XUI_PARENT_TOP_CENTER_HORIZONTAL,
		XUI_PARENT_TOP_RIGHT,
		XUI_PARENT_LEFT_CENTER_VERTICAL,
		XUI_CENTER_IN_PARENT,
		XUI_PARENT_RIGHT_CENTER_VERTICAL,
		XUI_PARENT_LEFT_BOTTOM,
		XUI_PARENT_BOTTOM_CENTER_HORIZONTAL,
		XUI_PARENT_RIGHT_BOTTOM,
		XUI_LOCATION_ABOVE_LEFTALIGN,
		XUI_LOCATION_ABOVE_CENTER,
		XUI_LOCATION_ABOVE_RIGHTALIGN,
		XUI_LOCATION_LEFT_OF_TOPALIGN,
		XUI_LOCATION_LEFT_OF_CENTER,
		XUI_LOCATION_LEFT_OF_BOTTOMALIGN,
		XUI_LOCATION_RIGHT_OF_TOPALIGN,
		XUI_LOCATION_RIGHT_OF_CENTER,
		XUI_LOCATION_RIGHT_OF_BOTTOMALIGN,
		XUI_LOCATION_BELOW_LEFTALIGN,
		XUI_LOCATION_BELOW_CENTER,
		XUI_LOCATION_BELOW_RIGHTALIGN
	};
	XUIRelativeLayoutParameter();
	virtual ~XUIRelativeLayoutParameter(){};
	static XUIRelativeLayoutParameter* Create();
	void			SetAlign(RelativeAlign eAlign){ m_eRelativeAlign = eAlign; }
	RelativeAlign	GetAlign() const{ return m_eRelativeAlign; }
	void			SetRelativeToWidgetName(const XString& strName){ m_strRelativeWidgetName = strName; }
	const XString&	GetRelativeToWidgetName() const{ return m_strRelativeWidgetName; }
	void			SetRelativeName(const XString& strName){ m_strRelativeLayoutName = strName; }
	const XString&	GetRelativeName() const{ return m_strRelativeLayoutName; }
protected:
	virtual void				CopyProperties(XUILayoutParameter* pParameter);
	virtual XUILayoutParameter*	CreateClonedInstance();
	RelativeAlign	m_eRelativeAlign;
	XString			m_strRelativeWidgetName;
	XString			m_strRelativeLayoutName;
	xbool			m_bPut;
	friend class XUIRelativeLayoutManager;
};


#endif
