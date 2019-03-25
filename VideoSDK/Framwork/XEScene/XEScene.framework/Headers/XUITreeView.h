#ifndef _XUITREEVIEW_H_
#define _XUITREEVIEW_H_

#include "XUIScrollView.h"
#include "XUIImage.h"

class XUIImage;
class XUILabel;
class XUITreeView;
class XUIWidgetAlignment;
class XUITreeViewItem : public XUIImage
{
public:
	static XUITreeViewItem* Create(const XString& strText);
	static XUITreeViewItem* Create(XUITreeView* pTree, const XString& strText);
	static XUITreeViewItem* Create(XUITreeViewItem* pTreeItem, const XString& strText);
	
	virtual void			ReleaseUpEvent()override;
	XUITreeViewItem*		GetChildItem(xint32 nIndex);
	xint32					GetChildItemNum();
	void					AddChildItem(XUITreeViewItem* pItem);
	void					RemoveChildItem(XUITreeViewItem* pItem);
	void					SetText(const XString& strText);
	const XString&			GetText()const;
	void					SetExpand(xbool bExpand);
	xbool					IsExpand()const{ return m_bExpand; }
	XUIWidgetAlignment*		GetLabelAlignment();
protected:
	XUITreeViewItem();
	~XUITreeViewItem(){}
	xbool					Init(XUITreeView* pTree, const XString& strText);
	xbool					Init(XUITreeViewItem* pTree, const XString& strText);
	xbool					Init(const XString& strText);
	void					TouchImageEvent(XUINode* pNode, XUIWidget::TouchEventType eType);
	void					OnChildAdded();
	void					OnChildRemoved();
	void					OnAttachedToTreeView();
	void					SetTreeViewRecrusive(XUITreeView* pTree);
	void					SetHeight(xfloat32 fHeight);
	void					SetFontSize(xfloat32 fSize);
	void					UpdateWidget();
protected:
	XUITreeView*			m_pTreeView;
	XUIImage*				m_pImage;
	XUILabel*				m_pLabel;
	xbool					m_bExpand;
	friend class XUITreeView;
};

class XUITreeView : public XUIScrollView
{
public:
	X_CLASS_DEF(XUITreeView)
	enum class EventType
	{
		ON_SELECTED_ITEM_START,
		ON_SELECTED_ITEM_END
	};
	typedef std::function<void(XUINode*, EventType)> XUITreeViewCallback;
	static XUITreeView*	Create();
	XUITreeView();
	virtual ~XUITreeView();

	void						AddItem(XUITreeViewItem* pItem);
	void						AddEventListener(const XUITreeViewCallback& callback){ m_pEventCallback = callback; }
	XUITreeViewItem*			GetSelectedItem(){ return m_pSelectedItem; }
	void						SetLineIndent(xfloat32 fLineIndent);
	xfloat32					GetLineIndent()const{ return m_fLineIndent; }
	void						SetRowHeight(xfloat32 fHeight);
	xfloat32					GetRowHeight()const{ return m_fRowHeight; }
	void						SetDefaultFontSize(xfloat32 fFontSize);
	xfloat32					GetDefaultFontSize()const{ return m_fFontSize; }
	void						SetExpandFlagVisible(xbool bShow);
	xbool						IsExpandFlagVisible(){ return m_bExpandFlagVisible; }
	virtual void				DoLayout() override;
	virtual xbool				SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	void						UpdateInnerContainerSize();
	virtual void				InterceptTouchEvent(XUIWidget::TouchEventType event, XUIWidget* sender, XUITouch* touch) override;
	void						SelectedItemEvent(TouchEventType event);
	xbool						Init()override;
	virtual XUINode*			CreateClonedInstance() override;
	virtual void				CopyProperties(XUINode* pNode)override;
protected:
	XArray<XUITreeViewItem*>	m_aItems;
	XUITreeViewItem*			m_pSelectedItem;
	XUITreeViewCallback			m_pEventCallback;
	xfloat32					m_fLineIndent;
	xfloat32					m_fRowHeight;
	xfloat32					m_fFontSize;
	xbool						m_bExpandFlagVisible;
	xbool						m_bInnerContainerDoLayoutDirty;
	friend class XUITreeViewItem;
};

#endif
