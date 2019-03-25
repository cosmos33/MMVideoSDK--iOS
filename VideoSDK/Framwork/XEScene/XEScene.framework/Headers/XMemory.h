/******************************************************************************

 @File         XMemory.h

 @Version      1.0

 @Created      2017, 3, 6

 @Description  内存管理类
			   如果使用标准的内存管理，#define _X_DISABLE_MALLOC
 @HISTORY:

******************************************************************************/

#ifndef _XMEMORY_H_
#define _XMEMORY_H_

#include "XTypes.h"

class XMemory
{
public:
	static void*	Malloc(size_t size);
	static void*	Realloc(void* pMem, size_t size);
	static void 	Free(void *p);
	static void*	MallocTemp(size_t size);
	static void 	FreeTemp(void* p);
	static void* 	Memcpy(void* pDest, const void* pSrc, size_t size);
	static void 	ExportMemLog(const xchar* szPath);

	template <class T>
	static T* MallocArray(xuint32 uCount)
	{
		void* p = Malloc(sizeof(T) * uCount + sizeof(xuint32));
		if (p)
		{
			xuint32* pCnt = (xuint32*)p;
			*pCnt++ = uCount;
			p = (void*)pCnt;

			T* pCurItem = (T*)p;
			for (xuint32 i = 0; i < uCount; i++)
			{
				new ((void*)&*pCurItem++) T;
			}
		}

		return (T*)p;
	}

	template <class T>
	static void FreeArray(T* p)
	{
		if (p)
		{
			xuint32* pCnt = (xuint32*)p - 1;
			xuint32 uCount = *pCnt;

			T* pCurItem = (T*)p;
			for (xuint32 i = 0; i < uCount; i++)
				pCurItem++->~T();

			p = (T*)pCnt;
		}
		Free(p);
	}
};

#endif
