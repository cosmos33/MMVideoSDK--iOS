/******************************************************************************

 @File         XCRC.h

 @Version      1.0

 @Created      2017, 3, 6

 @Description  CRC

 @HISTORY:

******************************************************************************/

#ifndef _XCRC_H_
#define _XCRC_H_

#include "XTypes.h"

class XCRC
{
public:
	static xuint32	StringCrc(const xchar* szStr);
	static xuint32	LowStringCrc(const xchar* szStr);
	static xuint32	FileNameCrc(const xchar* szFile);

	static void		InitChecksum(xuint32& uCrcvalue);
	static void		Update(xuint32& uCrcvalue, const xuint8 data);
	static void 	UpdateChecksum(xuint32 &uCrcvalue, const void* pData, xint32 uLength);
	static void 	FinishChecksum(xuint32& uCrcvalue);
	static xuint32 	BlockChecksum(const void* pData, xint32 length);
};

#endif
