/******************************************************************************

@File         XELog.h

@Version       1.0

@Created      2017, 6, 12

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_LOG_H_
#define _XE_LOG_H_

#include <string>
#include <fstream>
#include "XESingleton.h"

using std::ofstream;
using std::string;

class XELogImpl
{
public:
						XELogImpl();
	virtual				~XELogImpl();
	bool				Init(const string& strLogPath);
	void				Release();
	bool				Log(const char* pszFmt, ...);

protected:
	ofstream			m_File;
	string				m_strLogPath;
};

class XELog	: public XESingleton<XELog>
{
	friend XESingleton<XELog>;
public:	
	virtual				~XELog();
	bool				Init(const string& strLogPath);
	void				Release();
	bool				Log(const char* pszFmt, ...);

protected:
						XELog();

	XELogImpl			m_Impl;
};



#endif


