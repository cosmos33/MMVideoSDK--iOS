#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

#include "XMemBase.h"
#include "XUIAssist.h"
#include "XMath3D.h"
#include "XUIGeometry.h"

class XUIEvent;
class XUIScene;
class IXWorld;
class IXUIActionManager;
class IXUIManager : public XMemBase
{
public:
	virtual					~IXUIManager() {};
	/**
	* 初始化及释放
	*/
	virtual xbool			Init() = 0;
	virtual void			Release() = 0;
	
	/*
	* UIScene相关
	*/
	virtual XUIScene*		CreateUIScene() = 0;
	virtual void			RemoveUIScene(XUIScene* pScene) = 0;
	virtual XUIScene*		LoadUIScene(const xchar* szFile) = 0;
	virtual xbool			SaveUIScene(const xchar* szFile, XUIScene* pScene, xbool bBinary) = 0;
	// 分辨率相关
	virtual void			SetScreenResolution(const XVECTOR2& vResolution) = 0;
	virtual const XVECTOR2&	GetScreenResolution() const = 0;
    // 设置屏幕比例，在ios上使用[[UIScreen mainScreen] scale]作为参数输入，win32固定为1;
    virtual void            SetScaleFactor(xfloat32 fScale) = 0;
    virtual xfloat32        GetScaleFactor()const = 0;
    // 设置屏幕区域，在ios上使用applicationFrame作为输入，win32暂时不使用
    virtual void            SetRect(const XUIRect& rect) = 0;
    virtual const XUIRect&  GetRect()const = 0;

	virtual void			Tick(xfloat32 fDelta) = 0;
	virtual void			Render(IXWorld* pWrold) = 0;
	virtual void			AdoptScene(XUIScene* pScene) = 0;
	
	// 事件处理
	virtual xbool			HandleTouchesBegin(xint32 nNumber, intptr_t ids[], xfloat32 fPosX[], xfloat32 fPosY[]) = 0;
	virtual xbool			HandleTouchesMove(xint32 nNumber, intptr_t ids[], xfloat32 fPosX[], xfloat32 fPosY[]) = 0;
	virtual xbool			HandleTouchesEnd(xint32 nNumber, intptr_t ids[], xfloat32 fPosX[], xfloat32 fPosY[]) = 0;

	//动画系统
	virtual IXUIActionManager*		GetActionManager() = 0;
};

extern IXUIManager* g_pIXUIManager;
#endif
