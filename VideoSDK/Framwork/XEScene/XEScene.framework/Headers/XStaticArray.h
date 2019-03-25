/******************************************************************************

@File         XStaticArray.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/
#ifndef _X_STATIC_LIST_H_
#define _X_STATIC_LIST_H_

#include "XTypes.h"
template<typename T, xint32 nSize>
class XStaticArray
{
public:
	typedef xint32	(*CmpFunctionPtr)(const T*, const T*);

					XStaticArray();
					~XStaticArray();
	const T&		operator[](xint32 nIndex) const;
	T&				operator[](xint32 nIndex);
	void			Add(const T& value);
	void			Add(const XStaticArray<T, nSize>& other);
	xint32			AddUnique(const T& value);
	xint32			Find(const T& value, xint32 nBeginIndex = 0) const;
	xint32			IndexOf(const T* pValue) const;
	void			Insert(xint32 nIndex, const T& value);
	void			RemoveByIndex(xint32 nIndex);
	void			RemoveFastByIndex(xint32 nIndex);
	xbool			Remove(const T& value);
	xbool			RemoveFast(const T& value);
	xint32			Num() const;
	void			SetNum(xint32 nNewNum);
	void			SetNum(xint32 nNewNum, const T& initValue);
	xint32			Size() const;
	T*				GetData();
	const T*		GetData() const;
	void			Clear();
	void			DeleteContents(xbool bReleaseMem = xtrue);
	void			ReleaseContents(xbool bReleaseMem = xtrue);
	void			FreeContents(xbool bReleaseMem = xtrue);
	void			QSort(CmpFunctionPtr pCMP = SortCompare);

private:
	static xint32	SortCompare(const T* pT0, const T* pT1);

private:
	xint32			m_nNum;
	T				m_Data[nSize];
};

////////////////////////////////////////////////////////////////////
//	Implementations
template<typename T, xint32 nSize>
X_INLINE XStaticArray<T, nSize>::XStaticArray():
	m_nNum(0)
{
}

template<typename T, xint32 nSize>
X_INLINE XStaticArray<T, nSize>::~XStaticArray()
{
	m_nNum = 0;
}

template<typename T, xint32 nSize>
X_INLINE const T& XStaticArray<T, nSize>::operator[](xint32 nIndex) const
{
	ASSERT(nIndex >= 0 && nIndex < m_nNum);
	return m_Data[nIndex];
}

template<typename T, xint32 nSize>
X_INLINE T& XStaticArray<T, nSize>::operator[](xint32 nIndex)
{
	ASSERT(nIndex >= 0 && nIndex < m_nNum);
	return m_Data[nIndex];
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::Add(const T& value)
{
	if (m_nNum >= nSize)
	{
		return;
	}
	m_Data[m_nNum++] = value;
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::Add(const XStaticArray<T, nSize>& other)
{
	xint32 nNum = other.Num();
	if (m_nNum + nNum > nSize)
	{
		return;
	}

	for (xint32 i = 0; i < nNum; i++)
	{
		m_Data[m_nNum++] = other[i];
	}
}

template<typename T, xint32 nSize>
xint32 XStaticArray<T, nSize>::AddUnique(const T& value)
{
	xint32 nIndex = Find(value);

	if (nIndex == X_INDEX_NONE)
	{
		nIndex = m_nNum;
		Add(value);
	}

	return nIndex;
}

template<typename T, xint32 nSize>
xint32 XStaticArray<T, nSize>::Find(const T& value, xint32 nBeginIndex) const
{
	if (nBeginIndex < 0 || nBeginIndex >= m_nNum)
	{
		return X_INDEX_NONE;
	}

	for (xint32 i = nBeginIndex; i < m_nNum; i++)
	{
		if (m_Data[i] == value)
		{
			return i;
		}
	}

	return X_INDEX_NONE;
}

template<typename T, xint32 nSize>
xint32 XStaticArray<T, nSize>::IndexOf(const T* pValue) const
{
	if (pValue == NULL)
	{
		return X_INDEX_NONE;
	}

	xint32 nIndex = pValue - m_Data;

	if (nIndex < 0 || nIndex >= m_nNum)
	{
		return X_INDEX_NONE;
	}

	return nIndex;
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::Insert(xint32 nIndex, const T& value)
{
	if (nIndex < 0 || nIndex > m_nNum || m_nNum >= nSize)
	{
		return;
	}

	for (xint32 i = m_nNum - 1; i >= nIndex; i--)
	{
		m_Data[i+1] = m_Data[i];
	}

	m_Data[nIndex] = value;
	m_nNum++;
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::RemoveByIndex(xint32 nIndex)
{
	if (nIndex < 0 || nIndex >= m_nNum)
	{
		return;
	}

	m_nNum--;
	for (xint32 i = nIndex; i < m_nNum; i++)
	{
		m_Data[i] = m_Data[i+1];
	}
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::RemoveFastByIndex(xint32 nIndex)
{
	if (nIndex < 0 || nIndex >= m_nNum)
	{
		return;
	}

	m_nNum--;
	if (nIndex != m_nNum)
	{
		m_Data[nIndex] = m_Data[m_nNum];
	}
}

template<typename T, xint32 nSize>
xbool XStaticArray<T, nSize>::Remove(const T& value)
{
	xint32 nIndex = Find(value);
	if (nIndex < 0)
	{
		return xfalse;
	}

	RemoveByIndex(nIndex);
	return xtrue;
}

template<typename T, xint32 nSize>
xbool XStaticArray<T, nSize>::RemoveFast(const T& value)
{
	xint32 nIndex = Find(value);
	if (nIndex < 0)
	{
		return xfalse;
	}

	RemoveFastByIndex(nIndex);
	return xtrue;
}

template<typename T, xint32 nSize>
X_INLINE xint32 XStaticArray<T, nSize>::Num() const
{
	return m_nNum;
}

template<typename T, xint32 nSize>
X_INLINE void XStaticArray<T, nSize>::SetNum(xint32 nNewNum)
{
	if (nNewNum < 0 || nNewNum > nSize)
	{
		return;
	}
	m_nNum = nNewNum;
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::SetNum(xint32 nNewNum, const T& initValue)
{
	if (nNewNum < 0 || nNewNum > nSize)
	{
		return;
	}

	for (xint32 i = m_nNum; i < nNewNum; i++)
	{
		m_Data[i] = initValue;
	}

	m_nNum = nNewNum;
}

template<typename T, xint32 nSize>
X_INLINE xint32 XStaticArray<T, nSize>::Size() const
{
	return nSize;
}

template<typename T, xint32 nSize>
X_INLINE T* XStaticArray<T, nSize>::GetData()
{
	return m_Data;
}

template<typename T, xint32 nSize>
X_INLINE const T* XStaticArray<T, nSize>::GetData() const
{
	return m_Data;
}

template<typename T, xint32 nSize>
X_INLINE void XStaticArray<T, nSize>::Clear()
{
	m_nNum = 0;
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::DeleteContents(xbool bReleaseMem)
{
	for (xint32 i = 0; i < m_nNum; i++)
	{
		X_SAFEDELETE(m_Data[i]);
	}

	Clear(bReleaseMem);
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::ReleaseContents(xbool bReleaseMem)
{
	for (xint32 i = 0; i < m_nNum; i++)
	{
		X_SAFERELEASE_INTERFACE(m_Data[i]);
	}

	Clear(bReleaseMem);
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::FreeContents(xbool bReleaseMem)
{
	for (xint32 i = 0; i < m_nNum; i++)
	{
		X_SAFEFREE(m_Data[i]);
	}

	Clear(bReleaseMem);
}

template<typename T, xint32 nSize>
void XStaticArray<T, nSize>::QSort(CmpFunctionPtr pCMP)
{
	if (pCMP == NULL)
	{
		return;
	}
	typedef xint32 (*CmpVoid)(const void *, const void *);
	CmpVoid pFuncVoidCom = (CmpVoid)pCMP;
	qsort(m_Data, m_nNum, sizeof(T), pFuncVoidCom);
}

template<typename T, xint32 nSize>
xint32 XStaticArray<T, nSize>::SortCompare(const T* pT0, const T* pT1)
{
	return *pT0 - *pT1;
}

#endif
