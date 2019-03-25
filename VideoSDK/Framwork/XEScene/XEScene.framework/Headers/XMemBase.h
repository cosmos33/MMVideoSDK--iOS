/******************************************************************************

 @File         XMemBase.h

 @Version      1.0

 @Created      2017, 3, 6

 @Description  XMemBase class.

 @HISTORY:

******************************************************************************/
#ifndef _X_MEMBASE_H_
#define _X_MEMBASE_H_

#include "XMemory.h"

typedef void(*StructureMemObjFunc)(void *pObj);
typedef void (*DeStructureMemObjFunc)(void *pObj);

extern StructureMemObjFunc g_pStructureMemObjFunc;
extern DeStructureMemObjFunc g_pDeStructureMemObjFunc;

class XMemBase
{
public:
							XMemBase() 	{	if (NULL != g_pStructureMemObjFunc)  g_pStructureMemObjFunc(this); }
							~XMemBase(){ if (NULL != g_pDeStructureMemObjFunc) g_pDeStructureMemObjFunc(this); }

#ifndef _X_DISABLE_MALLOC
	void*					operator new(size_t nSize) throw();
	void*					operator new[](size_t nSize) throw();
	void*					operator new(size_t nSize, void* p) throw();

	void					operator delete(void* p);
	void					operator delete[](void* p);
	void					operator delete(void *, void *) throw(){}
#endif
};



#endif
