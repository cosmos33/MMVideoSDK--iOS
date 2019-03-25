/******************************************************************************

@File         XEWin32Window.h

@Version       1.0

@Created      2017, 6, 2

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_WIN32WINDOW_H_
#define _XE_WIN32WINDOW_H_
#include "XPlatform.h"

#if X_PLATFORM_WIN_DESKTOP


#include <Windows.h>
#include <qwidget.h>
#include "XPlatformWindow.h"

class XEWin32Window : public IXPlatformWindow
{
public:
							XEWin32Window();
	virtual					~XEWin32Window();

	xbool					Create(QWidget* pQWidget);
	QWidget*                GetWidget(){ return m_pQWidget; }
	virtual void*			GetWinHandle();

	virtual unsigned int	GetWidth();
	virtual unsigned int	GetHeight();
	virtual float           GetWindowScale();
	virtual bool			IsFullScreen();

	virtual int				GetMouseX();
	virtual int				GetMouseY();
	virtual void			SetWidthHeight(int width, int height);

	xbool					IsVisible();
	void					SetWindowTitle(const char* szText);

protected:
	HWND					m_hWnd;
	QWidget*				m_pQWidget;
};

#endif

#endif


