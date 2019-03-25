/******************************************************************************

@File         XRefCount.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/
#ifndef _X_REFCOUNT_H_
#define _X_REFCOUNT_H_

#include "XTypes.h"

class XRefCount 
{
public:
	XRefCount();
	virtual ~XRefCount();

	xuint32 AddRef() const;
	xuint32 SubRef() const;
	xuint32 GetRefCount() const;
protected:
	mutable xint32 m_nRefCounts;
};
#endif //_X_REF_COUNT_H_
