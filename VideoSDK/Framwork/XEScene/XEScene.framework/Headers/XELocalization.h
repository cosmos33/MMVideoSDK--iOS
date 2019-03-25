/******************************************************************************

@File         XELocalization.h

@Version       1.0

@Created      2018, 04, 17

@Description  The Localization class 

@HISTORY:

******************************************************************************/

#ifndef _XE_LOCALIZATION_H_
#define _XE_LOCALIZATION_H_

#include <string>

#if X_PLATFORM_WIN_DESKTOP
#define xetr(STR) XELocalization::getLocaleString(STR).c_str()
#else
#define xetr(STR) STR
#endif

class UResourceBundle;
namespace XELocalization{
	bool          GetLocalizatingContext();
	bool          ResInited();
	bool          getLocaleRes(const char* packagename, const char* localeid);
	std::string   getLocaleString(const char* stringid);
	extern std::string gTranslateFile;
	extern UResourceBundle *gResourceBundle;
}

#endif


