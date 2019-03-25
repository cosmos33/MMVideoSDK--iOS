/******************************************************************************

 @File         XApplication.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XApplication.

 @HISTORY:

******************************************************************************/

#ifndef _X_APPLICATION_H_
#define _X_APPLICATION_H_

#include "XMemBase.h"
#include "XString.h"

class XViewport;

struct XApplicationInitParameter
{
	const char*		pszBaseDir;
};

class IXApplication : public XMemBase
{
public:
	virtual					~IXApplication() {}
	virtual xbool			Init(const XApplicationInitParameter* pParam) = 0;
	virtual void			Release() = 0;
	virtual void			FrameStep() = 0;
	virtual XViewport*		GetAppViewPort() = 0;
};

extern IXApplication* g_pXApp;


#endif //_X_APPLICATION_H_