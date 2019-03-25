/******************************************************************************

@File         XECmdHelper.h

@Version       1.0

@Created      2017, 6, 12

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef XECMDHELPER_H
#define XECMDHELPER_H
#include "XESingleton.h"

class XECmdHelper :
	public XESingleton<XECmdHelper>
{
public:
	XECmdHelper();
	~XECmdHelper();
public:
	void DebugStaticMesh();
};

#endif // XECMDHELPER_H
