/******************************************************************************

 @File         XTempMemBuffer.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  Temporary memory buffer wrapper.

 @HISTORY:

******************************************************************************/

#ifndef _XTEMPMEMBUFFER_H_
#define _XTEMPMEMBUFFER_H_

#include "XTypes.h"
#include "XMemBase.h"

class XScopedBufferPtr : public XMemBase
{
public:
	
			XScopedBufferPtr(xuint32 uSize);
			~XScopedBufferPtr();
	void	Free();
	void	Resize(xuint32 uNewSize);
	void* 	GetBuffer() const { return m_pBuffer; }
	xuint32 GetSize() const { return m_uSize; }

private:
	xuint32	m_uSize;
	void*	m_pBuffer;
};

#endif	//	_XTEMPMEMBUFFER_H_


