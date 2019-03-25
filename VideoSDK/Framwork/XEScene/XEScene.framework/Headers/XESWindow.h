//
//  XESWindow.h
//  XEScene
//
//  Created by momo783 on 02/02/2018.
//

#ifndef XESWINDOW_H_
#define XESWINDOW_H_

#include "xcommon/XPlatformWindow.h"
#include "core/XESDefine.h"
#include "core/XESGeometry.h"
#include "core/events/XESTouchEvent.h"
#include "XECore/XEEngine/XEViewport.h"
#include <vector>

XESCENE_NAMESPACE_BEGIN

class Touch;
class TouchEvent;

class Window : public IXPlatformWindow
{
public:
    
    Window();
    Window(int nwidht, int height);
    
    virtual ~Window(){};
    
    virtual void*               GetWinHandle() {return _winHandler;}
    virtual unsigned int        GetWidth() {return m_nWidth;}
    virtual unsigned int        GetHeight() { return m_nHeight;}
    virtual bool                IsFullScreen() {return true;}
    virtual int                 GetMouseX() {return  0;}
    virtual int                 GetMouseY(){ return 0;}
    
    void SetWidthHeight(int width, int height);
    
    virtual xbool   HandleToucheHitTest(xfloat32 xs, xfloat32 ys);
    virtual void    HandleTouchesBegin(xint32 num, intptr_t ids[], xfloat32 xs[], xfloat32 ys[]);
    virtual void    HandleTouchesMove (xint32 num, intptr_t ids[], xfloat32 xs[], xfloat32 ys[]);
    virtual void    HandleTouchesMove (xint32 num, intptr_t ids[], xfloat32 xs[], xfloat32 ys[], xfloat32 fs[], xfloat32 ms[]);
    virtual void    HandleTouchesEnd  (xint32 num, intptr_t ids[], xfloat32 xs[], xfloat32 ys[]);
    virtual void    HandleTouchesCancel(xint32 num, intptr_t ids[], xfloat32 xs[], xfloat32 ys[]);
    
    
    const Rect&  GetViewPortRect() const;
    
    std::vector<Touch*> GetAllTouches() const;
    
    xfloat32 GetScaleX() const;
    xfloat32 GetScaleY() const;
    
    X_FORCEINLINE XEViewport* GetViewport() { return m_pViewport; }
    
    void  SetViewport(XEViewport* mViewport) { m_pViewport = mViewport; }
    
protected:
    
    int m_nWidth;
    int m_nHeight;
    
    void HandleTouchesOfEndOrCancel(TouchEvent::EventCode nEventCode, int num, intptr_t ids[], float xs[], float ys[]);
    
protected:
    
    xfloat32    m_ScaleX;
    xfloat32    m_ScaleY;
    
    Size    m_ScreenSize;
    Rect    m_rViewPortRect;
    
    XEViewport*  m_pViewport;

private:
    void *_winHandler;
public:
    void SetWinHandler(void *_winHandler);
    
    void SetScreenScale(xfloat32 scale);

};

XESCENE_NAMESPACE_END

XESS_IGNORE extern IXPlatformWindow *g_pXWindow;

#endif /* XESWINDOW_H_ */
