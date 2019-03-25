/******************************************************************************

 @File         XPlatformWindow.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XWindow.

 @HISTORY:

******************************************************************************/
#ifndef _X_WINDOW_H_
#define _X_WINDOW_H_

#include "XMemBase.h"

class IXPlatformWindow : public XMemBase
{
public:
	virtual					~IXPlatformWindow(){}

	virtual void*			GetWinHandle() = 0;

	virtual unsigned int	GetWidth() = 0;
	virtual unsigned int	GetHeight() = 0;
	virtual bool			IsFullScreen() = 0;

	virtual int				GetMouseX() = 0;
	virtual int				GetMouseY() = 0;
    virtual void			SetWidthHeight(int width, int height) = 0;
};

extern IXPlatformWindow* g_pXWindow;

#endif //_X_WINDOW_H_