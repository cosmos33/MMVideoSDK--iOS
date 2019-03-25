/******************************************************************************

@File         XBitArray.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/
#ifndef _X_BIT_ARRAY_H_
#define _X_BIT_ARRAY_H_

#include "XTypes.h"

class XBitArray
{
public:
	explicit	XBitArray(xint32 nInitialSize = 256, xint32 nGranularity = 16);
				XBitArray(const XBitArray& other);
				~XBitArray();
	XBitArray&	operator=(const XBitArray& other);

	xbool		Get(xint32 nIndex) const;
	void		Set(xint32 nIndex, xbool bValue);
	//	将所有值设置为false
	void		Clear(xbool bReleaseMem = xtrue);
	xint32		Num() const;
	void		Resize(xint32 nNumBits);

private:
	xint32		m_nNumSetBits;
	xint32		m_nNumBits;
	xint32*		m_pBits;
	xint32		m_nInitialSize;
	xint32		m_nGranularity;
};

#endif