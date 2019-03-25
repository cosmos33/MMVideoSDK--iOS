#ifndef _XUIGUIDEPAGE_H_
#define _XUIGUIDEPAGE_H_


#include "XUIImage.h"

class XUIGuidePage;
class XUIGuidePageGroup : public XUIWidget
{
public:
	X_CLASS_DEF(XUIGuidePageGroup)
		XUIGuidePageGroup();

	static XUIGuidePageGroup*								Create(const XArray<XUIGuidePage*>& vGuidePage);
	static XUIGuidePageGroup*								Create();

	virtual xbool											Init() override;

	void										 			SetAutoTouchEventEnabled();
	void													SetRemoveSelfWhenEnd(const xbool& bRemove);
	xbool													GetRemoveSelfWhenEnd();

	void													PrevPage();
	void													NextPage();

	void													AppendGuidePage(XUIGuidePage* pPage);

	void													InsertGuidePage(XUIGuidePage* pPage, const xint32& nIndex);
	void													RemoveGuidePage(const xint32& nIndex);

	virtual xbool											SerilizeXML(XXMLExtendTool& outXmlArchive) override;
	virtual xbool											SerilizeChildrenXML(XXMLExtendTool& outXmlArchive) override;
	virtual xbool											SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:

	XUIGuidePageGroup(const XArray<XUIGuidePage*>& vGuidePage);
	virtual ~XUIGuidePageGroup();
	 
private:

	xint32													m_nCurrentIndex;
	XArray<XUIGuidePage*>									m_vGuidePage;

	xbool													m_bAutoTouchEnabled;
	xbool													m_bRemoveSelfWhenEnd;

	XUIWidget::XUIWidgetTouchCallback						m_AutoTouchCallBack;

};

class XUIGuidePage : public XUIWidget
{
public:
	X_CLASS_DEF(XUIGuidePage)
		XUIGuidePage();

	static XUIGuidePage*									Create(const XVECTOR2& v2ScreenSize);
	static XUIGuidePage*									Create();


	void													SetMaskSceneSize(const XVECTOR2& v2ScreenSize);
	XVECTOR2												GetMaskSceneSize();

	void													SetTargetWidget(XUIWidget* pWidget, const xbool& bTouchAllow = xfalse);
	XUIWidget*												GetHighLightWidget();

	xfloat32												GetAlpha();
	void													SetAlpha(const xfloat32& fAlpha);

	XUIWidget*												GetTouchMaskWidget();
	XUIWidget*												GetVisibleMaskWidget();

	virtual xbool											SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;

protected:
	
	XUIGuidePage(const XVECTOR2& v2ScreenSize);
	virtual ~XUIGuidePage() {};


	virtual xbool											Init() override;
	virtual void											InitProtectedChild();


	virtual XUINode*										CreateClonedInstance() override;
	virtual void											CopyProperties(XUINode* pNode)override;

private:

	XVECTOR2												m_v2ScreenSize;

	XUIWidget*												m_pTargetCloneWidget;

	XUIWidget*												m_pTouchMaskWidget;

	XUIImage*												m_pVisibleMaskWidget;

};

#endif
