/******************************************************************************

 @File         XCSWrapper.h

 @Version      1.0

 @Created      2017, 3, 6

 @Description  

 @HISTORY:

******************************************************************************/


#ifndef _X_XCriticalSection_H_
#define _X_XCriticalSection_H_

#include "XTypes.h"
#include "XMemBase.h"

class XThreadMutex;
class XCriticalSection : public XMemBase
{
public:
	XCriticalSection(XThreadMutex* mutex);
	~XCriticalSection();
	void Enter();
	void Leave();
	void Attach(XThreadMutex* mutex);
	void Detach();
protected:
	XThreadMutex*	m_pMutex;
	xint32				m_nCnt;
};

#endif


