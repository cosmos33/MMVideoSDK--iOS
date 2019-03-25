#ifndef _UIGlobalAssist_H_
#define _UIGlobalAssist_H_

#include "XUIMessageTip.h"
#include "XUIMessageBox.h"

class XUIGlobalAssist
{
public:

	static void Tip(const XString& strMessage,const xbool& bShowCenter = xfalse, const XString& strBackGroundFile = "", const xbool bShowImmediately = xfalse, const xfloat32& fFontSize = 32, const XCOLORBASE& cFontColor = XCOLORBASE(1.0, 1.0, 1.0, 1.0), const xfloat32& fShowDelta = 0.0f, const xfloat32& fOnShowDelta = 0.35f, const xfloat32 fOnHideDelta = 0.3f);


	static void Warning(const XString& strWarning, const XUIMessageBoxFlagCallBack& callback = XUIMessageBoxFlagCallBack());
	static void Information(const XString& strInformation, const XUIMessageBoxFlagCallBack& callback = XUIMessageBoxFlagCallBack());

	static void MessageBox_YesNo(const XString& strMessage, const XString& strTitle, const XUIMessageBoxFlagCallBack& callback);
	static void MessageBox_OKCancel(const XString& strMessage, const XString& strTitle, const XUIMessageBoxFlagCallBack& callback);
	static void MessageBox_OKCancelClose(const XString& strMessage, const XString& strTitle, const XUIMessageBoxFlagCallBack& callback);

	static void MessageBox(const XString& strMessage, const XString& strTitle, const xint32& nMessageFlags, const XUIMessageBoxFlagCallBack& callback);
	static void MessageBox(const XString& strMessage, const XString& strTitle, XArray<XString> Buttons, const XUIMessageBoxStringCallBack& callback);

	static void MessageBox(const XString& strMessage, const XString& strTitle, const xint32& nRemoveSelfCountdown);


	static void MessageBox(const XString& strMessage, const XString& strTitle, const int& nMessageBoxFlags, const xint32& nRemoveSelfCountdown, const XUIMessageBoxFlagCallBack& MessageBoxCallBack = XUIMessageBoxFlagCallBack(),
		const XCOLORBASE& cMessageColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f), const XCOLORBASE& cTitleColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f),
		const XString& strBackGroundImageFile = "", const XString& strTitleBackGroundImageFile = "", const XString& strButtonNormalImageFile = "", const XString& strButtonPressedImageFile = "");

	static void MessageBox(const XString& strMessage, const XString& strTitle, XArray<XString> vButtonLabels, const xint32& nRemoveSelfCountdown, const XUIMessageBoxStringCallBack& MessageBoxCallBack = XUIMessageBoxStringCallBack(),
		const XCOLORBASE& cMessageColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f), const XCOLORBASE& cTitleColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f),
		const XString& strBackGroundImageFile = "", const XString& strTitleBackGroundImageFile = "", const XString& strButtonNormalImageFile = "", const XString& strButtonPressedImageFile = "");

	static void MessageBox(XUIWidget* pMessageWidget, const XString& strTitle, const int& nMessageBoxFlags, const xint32& nRemoveSelfCountdown, const XUIMessageBoxFlagCallBack& MessageBoxCallBack = XUIMessageBoxFlagCallBack(),
		const XCOLORBASE& cTitleColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f),
		const XString& strBackGroundImageFile = "", const XString& strTitleBackGroundImageFile = "", const XString& strButtonNormalImageFile = "", const XString& strButtonPressedImageFile = "");

	static void MessageBox(XUIWidget* pMessageWidget, const XString& strTitle, XArray<XString> vButtonLabels, const xint32& nRemoveSelfCountdown, const XUIMessageBoxStringCallBack& MessageBoxCallBack = XUIMessageBoxStringCallBack(),
		const XCOLORBASE& cTitleColor = XCOLORBASE(0.0f, 0.0f, 0.0f, 1.0f),
		const XString& strBackGroundImageFile = "", const XString& strTitleBackGroundImageFile = "", const XString& strButtonNormalImageFile = "", const XString& strButtonPressedImageFile = "");
};


















#endif