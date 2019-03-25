#ifndef _XUIMESSAGEBOX_H_
#define _XUIMESSAGEBOX_H_

#include "XUIWidget.h"
#include "XUIAssist.h"

class XUIImage;
class XUILabel;
class XUIButton;

enum XUIMessageBoxFlag
{
	XUI_YES = 1 << 0,
	XUI_NO = 1 << 1,
	XUI_OK = 1 << 2,
	XUI_CANCEL = 1 << 3,
	XUI_CLOSE = 1 << 4
};

class XUIMessageBoxFlagCallBack
{
public:

	typedef std::function<void(XUIMessageBoxFlag eResult)> XUIMessageFlagCallBack;

	XUIMessageBoxFlagCallBack();
	XUIMessageBoxFlagCallBack(const XUIMessageFlagCallBack& callback);

	void SetMessageBoxFloagCallBack(const XUIMessageFlagCallBack& callback);
	XUIMessageFlagCallBack GetMessageBoxFloagCallBack() const { return m_MessageFlagCallBack; };
private:

	XUIMessageFlagCallBack m_MessageFlagCallBack;
};

class XUIMessageBoxStringCallBack
{
public:

	typedef std::function<void(XString strResult)> XUIMessageStringCallBack;

	XUIMessageBoxStringCallBack();
	XUIMessageBoxStringCallBack(const XUIMessageStringCallBack& callback);

	void SetMessageBoxFloagCallBack(const XUIMessageStringCallBack& callback);
	XUIMessageStringCallBack GetMessageBoxFloagCallBack() const { return m_MessageStringCallBack; };
private:

	XUIMessageStringCallBack m_MessageStringCallBack;
};

class XUIMessageBox : public XUIWidget
{
public:
	

	XUIMessageBox();

	

	static XString GetLabelFromFlag(const XUIMessageBoxFlag& flag);


	static void ShowMessage(const XString& strMessage, const XString& strTitle, const int& nMessageBoxFlags, const xint32& nRemoveSelfCountdown = 0, const XUIMessageBoxFlagCallBack& MessageBoxCallBack = XUIMessageBoxFlagCallBack(),
		const XCOLORBASE& cMessageColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f), const XCOLORBASE& cTitleColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f),
		const XString& strBackGroundImageFile = "", const XString& strTitleBackGroundImageFile = "", const XString& strButtonNormalImageFile = "", const XString& strButtonPressedImageFile = "");

	static void ShowMessage(const XString& strMessage, const XString& strTitle, XArray<XString> vButtonLabels, const xint32& nRemoveSelfCountdown = 0, const XUIMessageBoxStringCallBack& MessageBoxCallBack = XUIMessageBoxStringCallBack(),
		const XCOLORBASE& cMessageColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f), const XCOLORBASE& cTitleColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f),
		const XString& strBackGroundImageFile = "", const XString& strTitleBackGroundImageFile = "", const XString& strButtonNormalImageFile = "", const XString& strButtonPressedImageFile = "");

	static void ShowMessage(XUIWidget* pMessageWidget, const XString& strTitle, const int& nMessageBoxFlags, const xint32& nRemoveSelfCountdown = 0, const XUIMessageBoxFlagCallBack& MessageBoxCallBack = XUIMessageBoxFlagCallBack(),
		const XCOLORBASE& cTitleColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f),
		const XString& strBackGroundImageFile = "", const XString& strTitleBackGroundImageFile = "", const XString& strButtonNormalImageFile = "", const XString& strButtonPressedImageFile = "");

	static void ShowMessage(XUIWidget* pMessageWidget, const XString& strTitle, XArray<XString> vButtonLabels, const xint32& nRemoveSelfCountdown = 0, const XUIMessageBoxStringCallBack& MessageBoxCallBack = XUIMessageBoxStringCallBack(),
		const XCOLORBASE& cTitleColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f),
		const XString& strBackGroundImageFile = "", const XString& strTitleBackGroundImageFile = "", const XString& strButtonNormalImageFile = "", const XString& strButtonPressedImageFile = "");

	static XUILabel* CreateMessageWithString(const XString& strMessage);
public:
	static XUIMessageBox* Create(XUIWidget* pMainMessageWidget, const XString& strTitle, const int& nMessageBoxFlags, const XUIMessageBoxFlagCallBack& MessageBoxCallBack = XUIMessageBoxFlagCallBack());
	virtual xbool Init(XUIWidget* pMainMessageWidget, const XString& strTitle, const int& nMessageBoxFlags, const XUIMessageBoxFlagCallBack& MessageBoxCallBack = XUIMessageBoxFlagCallBack());

	static XUIMessageBox* Create(XUIWidget* pMainMessageWidget, const XString& strTitle, XArray<XString> vButtonLabels, const XUIMessageBoxStringCallBack& MessageBoxCallBack = XUIMessageBoxStringCallBack());
	virtual xbool Init(XUIWidget* pMainMessageWidget, const XString& strTitle, XArray<XString> vButtonLabels, const XUIMessageBoxStringCallBack& MessageBoxCallBack = XUIMessageBoxStringCallBack());

	virtual void Update(xfloat32 fDelta) override;

protected:

	void InitChildren(XUIWidget* pMainMessageWidget, const XString& strTitle);
	void InitButtons(const int& nMessageBoxFlags, const XUIMessageBoxFlagCallBack& callback);
	void InitButtons(const XArray<XString> vButtonLabels, const XUIMessageBoxStringCallBack& callback);

	static XUIButton* CreateButtonWithString(const XString& strLabel);

	void SetTitleTextColor(const XCOLORBASE& color);

	void SetTitleBackGround(const XString& strImageFile);
	void SetBackGround(const XString& strImageFile);

	void SetButtonNormalImage(const XString& strImageFile);
	void SetButtonPressedImage(const XString& strImageFile);

	//在fTime秒后移除自己
	void StartCountdownForRemoveSelf(const xfloat32& fTime);

private:

	XUIImage* m_pTitleBackGroundImage;
	XUIImage* m_pBackGroundImage;
	XUILabel* m_pTitleLabel;
	XUIWidget* m_pMessageWidget;
	
	XString m_strTitle;
	xfloat32 m_fRemoveSelfCountdown;
	xbool m_bRemoveSelfCountdownEnabled;

	XArray<XUIButton*> m_vButtons;


};

#endif
