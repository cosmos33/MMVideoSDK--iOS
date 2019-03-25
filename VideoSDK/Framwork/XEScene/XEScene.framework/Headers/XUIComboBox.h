#ifndef _XUICOMBOBOX_H_
#define _XUICOMBOBOX_H_

#include "XUIWidget.h"
#include "XUIEditBox.h"
#include "XUIButton.h"
#include "XUIListView.h"

class XUIComboBox : public XUIWidget
{
public:
	X_CLASS_DEF(XUIComboBox)

protected:

//Protected Class
class XUIComboItem : public XUIWidget
{
public:
	friend class XUIComboBox;

	XUIComboItem();
	~XUIComboItem();

	static XUIComboItem*								Create();
	static XUIComboItem*								Create(const XString& strBackgroundTexture, const XString& strBackgroundSelectedTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);


	void												SetString(const XString& strString);
	XString												GetString() const;

	void												LoadBackgroundTexture(const XString& strBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void												LoadBackgroundSelectedTexture(const XString& strBackgroundSelectedTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);

	virtual void										SetContentSize(const XVECTOR2& vContentSize);

protected:
	virtual xbool										Init() override;
	virtual xbool										Init(const XString& strBackgroundTexture, const XString& strBackgroundSelectedTexture = "", TextureResType eTextureType = TextureResType::XUI_LOCAL);

	void												InitProtectedChild();

protected:
	XUILabel*											m_pLabel;
	XUIImage*											m_pBackgroundImage;

};

class XUIComboListView : public XUIListView
{
public:
	static XUIComboListView*							Create();

protected:
	virtual void										OnFocusGot() override;
	virtual void										OnFocusLost() override;

};

class XUIComboEditBoxDelegate : public XUIEditBoxDelegate
{
public:
	XUIComboEditBoxDelegate(XUIComboBox* pComboBox);
	virtual ~XUIComboEditBoxDelegate() {};
	virtual void										EditBoxEditingDidBegin(XUIEditBox* pEditBox) {};
	virtual void										EditBoxTextChanged(XUIEditBox* editBox, const XString& strText);;
	virtual void										EditBoxReturn(XUIEditBox* pEditBox){};
	virtual void										EditBoxEditingDidEndWithAction(XUIEditBox* pEditBox, EditBoxEndAction eAction);

private:
	XUIComboBox*										m_pComboBox;
};
 
//Protected Class End

public:
	enum class EventType
	{
		SELECTED_CHANGED
	};

	typedef std::function<void(XUINode*, XUIComboBox::EventType)> XUIComboBoxCallback;

	XUIComboBox();
	~XUIComboBox();


	static XUIComboBox*									Create();

	static XUIComboBox*									Create(const XString& strEditBoxBackgroundTexture, const XString& strButtonTexture, 
																const XString& strButtonSelectedTexture, const XString& strListViewBackgroundTexture,
																const XString& strItemBackgroundTexture, const XString& strItemBackgroundSerlectedTexture,
														TextureResType eTextureType = TextureResType::XUI_LOCAL);

	static XUIComboBox*									Create(const XString& strEditBoxBackgroundTexture, const XString& strButtonTexture,
																const XString& strItemBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);


	void												LoadEditBoxBackgroundTexture(const XString& strEditBoxBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void												LoadButtonNormalTexture(const XString& strButtonNormalTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void												LoadButtonSelectedTexture(const XString& strButtonSelectedTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void												LoadListViewBackgroundTexture(const XString& strListViewBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void												LoadItemBackgroundTexture(const XString& strItemBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	void												LoadItemBackgroundSelectedTexture(const XString& strItemBackgroundSelectedTExture, TextureResType eTextureType = TextureResType::XUI_LOCAL);

	XString												GetEditBoxBackgroundTexture() const;
	XString												GetButtonNormalTexture() const;
	XString												GetButtonSelectedTexture() const;
	XString												GetListViewBackgroundTexture() const;
	XString												GetItemBackgroundTexture() const;
	XString												GetItemBackgroundSelectedTexture() const;

	void												SetAllowEdit(const xbool& bAllowEdit);
	xbool												IsAllowEdit() const;

	void												SetItemHeight(const xint32& nHeight);
	xint32												GetItemHeight() const;

	void												SetFontColor(const XCOLORBASE& color);
	XCOLORBASE											GetFontColor() const;

	void												SetListViewHeight(const xint32 ItemNum);
	xint32												GetListViewHeight() const;

	void												SetListData(const XArray<XString>& vList);
	XArray<XString>&									GetListData();

	void												SetCurrentData(const XString& strData, const xbool& bSafeCheck = xtrue);
	XString												GetCurrentData() const;

	void												AddComboBoxEventListener(const XUIComboBoxCallback& callback);
protected:
	virtual xbool										Init() override;

	virtual xbool										Init(const XString& strEditBoxBackgroundTexture, const XString& strButtonTexture,
															const XString& strButtonSelectedTexture, const XString& strListViewBackgroundTexture,
															const XString& strItemBackgroundTexture, const XString& strItemBackgroundSerlectedTexture,
														TextureResType eTextureType = TextureResType::XUI_LOCAL);

	virtual xbool										Init(const XString& strEditBoxBackgroundTexture, const XString& strButtonTexture, 
															const XString& strItemBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);

	void												InitProtectedChild();

	void												ShowListView();
	void												ShowListViewByKeyWord(const XString& strKeyWord);
	void												HideListView();

														//m_vListData won't be modified.
	void												SetListDataOnlyForShow(const XArray<XString>& vList);

	virtual void										OnFocusGot() override;
	virtual void										OnFocusLost() override;

	virtual xbool										OnTouchBegan(XUITouch* pTouch, XUIEvent* pUnusedEvent);
	void												TouchListViewEvent(XUINode* pNode, XUIListView::EventType eType);
	void												TouchButtonEvent(XUINode* pNode, XUIWidget::TouchEventType eType);

	virtual xbool										SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
	virtual xbool										SerilizeEnd() override;

	void												BindProtectedEvent();


	virtual XUINode*									CreateClonedInstance() override;
	virtual void										CopyProperties(XUINode* pNode)override;

protected:

	
	XUIImage*											m_pBackgroundImage;
	XUIEditBox*											m_pEditBox;
	XUIImage*											m_pButton;
	XUIListView*										m_pListView;


	xbool												m_bAllowEdit;
	xint32												m_nItemHeight;
	xint32												m_nItemNumberPerPage;

	XString												m_strItemBackgroundTexture;
	XString												m_strItemBackgroundSelectedTexture;
	TextureResType										m_eItemBackgroundTextureType;
	TextureResType										m_eItemBackgroundSelectedTextureType;

	XCOLORBASE											m_FontColor;

	XUIComboBoxCallback									m_ComboBoxEventCallback;

	XArray<XString>										m_vListData;
	xint32												m_nDefaultDataIndex;

	XArray<XString>										m_vSerilizeListData;
};






#endif
