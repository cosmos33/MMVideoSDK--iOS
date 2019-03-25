/******************************************************************************

 @File         XEngineRoot.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XEngineRoot.

 @HISTORY:

******************************************************************************/
#ifndef _X_ENGINEROOT_H_
#define _X_ENGINEROOT_H_

#include "XSys.h"
#include "XTypes.h"
#include "XMemBase.h"
#include "XBase3DTypes.h"

class IXPlatformWindow;
class XViewport;
class XEnvironment;

struct XEngineRootParameter
{
	XEngineRootParameter()
		:pszEngineResDirectory(NULL),
		 pszAPPProjectResDirectory(NULL),
         pszDocumentDirectory(NULL),
		 pFOutputInfoFuncition(NULL),
		 pXWindow(NULL)
	{
	}
    const xchar*         pszEngineResDirectory;
    const xchar*         pszAPPProjectResDirectory;
    const xchar*         pszDocumentDirectory;
    pOutputInfoFunction	 pFOutputInfoFuncition;
	IXPlatformWindow*	 pXWindow;
};

class IXEngineRoot 
{
public:	
	virtual					~IXEngineRoot(){}
	virtual xbool			Init(const XEngineRootParameter* pParam) = 0;
	virtual void			Release() = 0;
	virtual void			FrameStep() =0;
	virtual void			EachFrame() = 0;
	virtual xint32			GetRTTID() = 0;
	virtual void			ResizeRenderWindow(IXPlatformWindow* pWin) = 0;
	virtual void			ShowPerfInfos(xbool bShow, const xchar *pszGroupNames = NULL) = 0;
	virtual void			WriteLog(const xchar *szInfo, ...) = 0;
	virtual void			WriteLogAndOutputDebug(const xchar* szInfo, ...) = 0;
	
	virtual void			ReloadResource(const XString &strFilePath) = 0;	
	virtual xbool			IsResourceLoaded(const XString &strFilePath) = 0;
};

extern IXEngineRoot* g_pXEngineRoot;


#endif //_X_ENGINEROOT_H_

