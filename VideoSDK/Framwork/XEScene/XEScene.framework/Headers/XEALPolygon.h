/******************************************************************************

@File         XEALPolygon.h

@Version       1.0

@Created      2018, 11, 22

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/


#ifndef _XE_ALPOLYGON_H_
#define _XE_ALPOLYGON_H_

//AL is short for algorithm.

#include "XMath3D.h"
#include "XArray.h"
#include "XClass.h"

namespace XEALPolygon
{
	template<typename T, typename EqualFn>
	X_INLINE xuint32 FilterRepeat(T* data, xuint32 count, EqualFn equalFn)
	{
		//return the account of repeated points which placed in the tail memory to the original data.
		T* src = data + 1;
		T* dst = data;
		T* end = data + count;
		while (src < end)
		{
			if (equalFn(*(T*)src, *(T*)dst))
			{
				++src;
			}
			else
			{
				dst[1] = src[0];
				++src;
				++dst;
			}
		}
		return (dst - data) + 1;
	}

X_EEB_BEGIN
#ifdef _DEBUG
	void __REPEATE_TEST();
#endif // _DEBUG
	//judge an area whether is a convex or concave one.must be an area.
	struct linkList
	{
		xint32 nIndex;
		linkList* pNext;
		linkList();
		static xbool DestroyLinkList(linkList* pHead);
	};
X_EEB_END
	xbool IsConvex(XVECTOR2* pPoints, xint32 nCount);
	xbool IsPointInRing(const XVECTOR2& p, const XArray<XVECTOR2>& ring);
	X_EES_LINE xbool IsPointInPolygon(const XVECTOR2& p, const XVECTOR2* polygon, xint32 numPoints);
	xbool IsPointInPolygon(const XVECTOR2& p, const XArray<XVECTOR2>& polygon);
}


#endif//_XE_ALPOLYGON_H_