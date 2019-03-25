#ifndef _XUIMESSAGETIP_H_
#define _XUIMESSAGETIP_H_

#include "XUIWidget.h"
#include "XUIAssist.h"

struct XUIShowMessageData
{
	xfloat32 fShowDelta;
	xfloat32 fOnShowDelta;
	xfloat32 fOnHideDelta;

	xbool bShowInCenter;

	xfloat32 fFontSize;
	XCOLORBASE cFontColor;


	XString strMessage;
	XString strBackgroundFile;
};

class XUIMessageTip : public XUIWidget
{
	enum XUIMessageTipState
	{
		XUI_SHOW,
		XUI_HIDE,
		XUI_ONSHOW,
		XUI_ONHIDE,
	};
public:
	static void ShowMessage(const XString& strMessage, const xbool& bShowInCenter = false, const XString& strBackGroundFile = "", const xbool bShowImmediately = xfalse, const xfloat32& fFontSize = 32, const XCOLORBASE& cFontColor = XCOLORBASE(1.0, 1.0, 1.0, 1.0), const xfloat32& fShowDelta = 0.0f, const xfloat32& fOnShowDelta = 0.35f, const xfloat32 fOnHideDelta = 0.3f);

	virtual xbool Init() override;
	void InitByScene();
	virtual void Update(xfloat32 fDelta) override;

	void SetOpacity(xfloat32 fOpacity);
	xfloat32 GetOpacity();
protected:
	static XUIMessageTip* GetInstance();
	XUIMessageTip();
	virtual ~XUIMessageTip();

	static XUIMessageTip* g_pMessageBox;

private:

	XArray<XUIShowMessageData> m_vMessageQueue;
	XUIShowMessageData m_cCurrentMessage;

	XUIMessageTipState m_eTipState;

	XUIScene* m_pMessageTipScene;
};

#endif
