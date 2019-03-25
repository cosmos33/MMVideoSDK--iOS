#ifndef _XUITABVIEW_H_
#define _XUITABVIEW_H_

#include "XUIWidget.h"
#include "XUIAbstractCheckButton.h"

class XUILabel;
class XUILayout;
class XUITabControl;
class XUITabHeader : public XUIAbstractCheckButton
{
	friend class XUITabControl;

public:
	X_CLASS_DEF(XUITabHeader)
	enum class EventType
	{
		SELECTED,
		UNSELECTED
	};


	static XUITabHeader*								Create();
	static XUITabHeader*								Create(	const XString& strTitle,
																const XString& strBackgroundTexture,
																const XString& strCrossTexture,
																TextureResType texType = TextureResType::XUI_LOCAL);
	static XUITabHeader*								Create(	const XString& strTitle,
																const XString& strBackgroundTexture,
																const XString& strBackgroundSelectedTexture,
																const XString& strCrossTexture,
																const XString& strBackgroundDisabledTexture,
																const XString& strFrontCrossDisabledTexture,
																TextureResType texType = XUIWidget::TextureResType::XUI_LOCAL);

	XUILabel*											GetTitleRenderer() const;

	void												SetTitleText(const XString& strText);
	XString												GetTitleText() const;

	void												SetTitleColor(const XCOLORBASE& color);
	XCOLORBASE											GetTitleColor() const;

	void												SetTitleFontSize(const xfloat32& fSize);
	xfloat32											GetTitleFontSize() const { return m_fTabLabelFontSize; }

	void												SetTitleFontName(const XString& strFontName);
	XString												GetTitleFontName() const;

	xint32												GetIndexInTabControl() const;

	virtual XUINode*									CreateClonedInstance() override;
	virtual void										CopyProperties(XUINode* pNode)override;

protected:

	XUITabHeader();
	virtual ~XUITabHeader();

	void												UpdateContentSize();
	void												UpdateTabLabelRenderPosition();

	virtual void										InitProtectedChild() override;
	virtual void										ReleaseUpEvent() override;
	virtual void										DispatchSelectChangedEvent(xbool bSelected) override;

private:

	XUILabel*											m_pTabLabelRender;
	xfloat32											m_fTabLabelFontSize;
	XUITabControl*										m_pTabView;

	typedef std::function<void(xint32 nTabIndex, XUITabHeader::EventType)> XUITabCallback;

	XUITabCallback										m_TabSelectedEvent;

};

class XUITabControl : public XUIWidget
{
public:
	X_CLASS_DEF(XUITabControl)
	enum class Dock
	{
		TOP,
		LEFT,
		BOTTOM,
		RIGHT
	};

	enum class EventType
	{
		SELECT_CHANGED,
	};

	typedef std::function<void(XUINode* pNode, xint32 nTabIndex, EventType)> XUITabControlCallBack;

	XUITabControl();
	virtual ~XUITabControl();

public:
	static XUITabControl*								Create();

	void												RemoveTab(const xint32& nIndex);

	void												SetSelectTab(const xint32& nIndex);
	void												SetSelectTab(XUITabHeader* pTabHeader);

	XUITabHeader*										GetTabHeader(const xint32& nIndex) const;

	XUILayout*											GetTabContainer(const xint32& nIndex) const;

	void												InsertTab(const xint32& nIndex, XUITabHeader* pHeader, XUILayout* pContainer);

	xint64												GetTabCount() const;

	xint32												GetSelectedTabIndex() const;

	xint32												IndexOfTabHeader(const XUITabHeader* pTabCell) const;

	void												AddTabChangedEventListener(const XUITabControlCallBack& callback);

	void												SetHeaderWidth(const xfloat32& fHeaderWidth);
	xfloat32											GetHeaderWidth() const { return m_fHeaderWidth; }

	void												SetHeaderHeight(const xfloat32& fHeaderHeight);
	xfloat32											GetHeaderHeight() const { return m_fHeaderHeight; }

// 	void												IgnoreHeadersTextureSize(const xbool& bIgnore);
// 	xbool												IsIgnoreHeadersTextureSize() const;

	void												SetHeaderSelectedZoom(const xfloat32& fZoom);
	xfloat32											GetHeaderSelectedZoom() const { return m_fCurrentHeaderZoom; }

	void												SetHeaderDockPlace(const XUITabControl::Dock& eDockPlace);
	XUITabControl::Dock									GetHeaderDockPlace() const { return m_eHeaderDockPlace; };

	virtual xbool										SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;

protected:

	void												InitTabHeadersPos(const xint32& nStartIndex);
	void												InitContainers();

	XUITabControlCallBack								m_TabChangedCallback;

	void												DispatchSelectedTabChanged(const xint32& nTabIndex, const XUITabHeader::EventType& eEventType);


	virtual XUINode*									CreateClonedInstance() override;
	virtual void										CopyProperties(XUINode* pNode)override;

private:

	typedef	struct XUICellContainer 
	{
		XUITabHeader*	m_pHeader;
		XUILayout*			m_pContainer;

		XUICellContainer(XUITabHeader* pHeaderCell, XUILayout* pLayout)
			: m_pHeader(pHeaderCell)
			, m_pContainer(pLayout)
		{
		}
	} XUITabItem;



	void												InitAfterInsert(const xint32& nIndex);

	void												ActiveTabItem(XUITabItem* pItem);
	
	void												DeactiveTabItem(XUITabItem* pItem);

	XVECTOR2											GetHeaderAnchorWithDock() const;

	XUITabItem*											m_pSelectedItem;

	xfloat32											m_fHeaderHeight;
	xfloat32											m_fHeaderWidth;

	Dock												m_eHeaderDockPlace;
	XVECTOR2											m_vContainerPosition;
	XVECTOR2											m_vContainerSize;

	xfloat32											m_fCurrentHeaderZoom;
	xbool												m_bIgnoreHeaderTextureSize;

	XArray<XUITabItem*>									m_vTabItems;
};





#endif
