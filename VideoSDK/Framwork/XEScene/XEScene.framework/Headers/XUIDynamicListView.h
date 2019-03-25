#ifndef _UIDYNAMICLISTVIEW_H_
#define _UIDYNAMICLISTVIEW_H_


#include "XUIListView.h"
#include "XHashTable.h"

class XUIDynamicListDelegate
{
public:
	virtual XUIWidget* GetDynamicItem(const xint32& nIndex) = 0;
	virtual xint32 GetDynamicItemNumber() = 0;
};

class XUIDynamicListView : public XUIListView
{
public:
	X_CLASS_DEF(XUIDynamicListView)
	static XUIDynamicListView* Create();
	XUIDynamicListView();


	virtual xbool Init() override;

	void SetDynamicListDelegate(XUIDynamicListDelegate* pDelegate);
	XUIDynamicListDelegate* GetDynamicListDelegate();


	virtual void											Update(xfloat32 fDelta) override;

	virtual xbool											SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
	virtual xbool											SerilizeXML(XXMLExtendTool& outXmlArchive) override;


	void UpdateView();
protected:



	void RemoveDynamicItem(const xint32& nIndex);
	xint32 RemoveRowByIndex(const xint32& nIndex);
	xint32 PushFrontRow();
	void InsertDynamicItem(XUIWidget* pWidget, const xint32& nIndex);
	void PushBackDynamicItem(XUIWidget* pWidget);

	//获得最左、上、右、下个可见的Item的Index
	xint32 GetVisibleBottomItem();
	xint32 GetVisibleTopItem();
	xint32 GetVisibleLeftItem();
	xint32 GetVisibleRightItem();

	XVECTOR4 GetVisibleRect(XUIWidget* pChildNode);
	XVECTOR4 GetVisibleRect(const xint32& nIndex);

	//获取最后一个点



	virtual void OnTouchMoved(XUITouch *pTouch, XUIEvent* pUnusedEvent) override;
protected:

	virtual XUINode*		CreateClonedInstance() override;

private:
	XUIDynamicListDelegate*							m_pDelegate;
	
	xint32											m_nFrontIndex;
	xint32											m_nBackIndex;

};




#endif
