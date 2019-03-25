/******************************************************************************

@File         XRenderSystemBase.h

@Version       1.0

@Created      2017, 3, 6

@Description  The interface of RendererSystemBase.

@HISTORY:

******************************************************************************/
#ifndef _X_RENDERER_SYSTEM_H_
#define _X_RENDERER_SYSTEM_H_

#include "XSys.h"
#include "XBase3DTypes.h"
#include "XMemBase.h"


class IXPlatformWindow;
class IXWorld;
class XViewport;
class XBaseCamera;

struct XRenderSystemParameter
{
	IXWorld*		pXRenderScene;
	XViewport*		pXViewport;
	XCOLOR			ClrClearColor;
};

struct XRenderSystemInitializeParameter
{
	IXPlatformWindow*		pXRenderWindow;
};

enum XRenderSystemTexFormatSupport
{
	XRTFS_PVR1 = XBit(0),
	XRTFS_PVR2 = XBit(1),
	XRTFS_ETC1 = XBit(2),
	XRTFS_ETC2 = XBit(3)

};

enum XRendererSystemType
{
	XRT_OPENGLES2,
	XRT_OPENGLES3,
	XRT_METAL,
	XRT_VULKAN,
};

class IXRenderSystemBase : public XMemBase
{
public:
	virtual						~IXRenderSystemBase() {};
	virtual	xbool				Init(const XRenderSystemInitializeParameter* pParam) = 0;
	virtual void				Release() = 0;	
	virtual void				RenderSystemRender(const XRenderSystemParameter& renderParam) = 0;
	virtual xbool				CanSupportTexFormat(xint32 nFmtFlag) = 0;
	virtual xuint32				GetCurTexFormat() = 0;
	virtual xint32				GetRendererType() = 0;
	virtual xint32				GetRTTID() = 0;
	
	virtual void				ResizeWindow(IXPlatformWindow* pWin) = 0;
	virtual xbool				CreateRenderWindow(IXPlatformWindow* pWin) = 0;

	/* 销毁渲染窗口
	*
	* @notice	如果窗口是当前渲染的窗口，将会销毁失败.
	* @param	pWin 将被销毁的窗口
	* @returns  xtrue 成功销毁
	*/
	virtual xbool				DestroyRenderWindow(IXPlatformWindow* pWin) = 0;

	/* 切换pWin为当前渲染的窗口
	*
	* @notice	当前未实现多窗口同时渲染的支持，所以只支持当前渲染窗口切换。（不可在每帧频繁切换，切换本身有开销）
	* @param	pWin 将被切换的窗口
	* @returns  xtrue 切换成功
	*/
	virtual xbool				SwitchCurRenderWindow(IXPlatformWindow* pWin) = 0;

	/* 获取当前渲染窗口
	*/
	virtual IXPlatformWindow*	GetCurRenderWindow() = 0;
};

extern IXRenderSystemBase*	g_pXCurrentRenderer;

#endif //_X_RENDERER_SYSTEM_H_