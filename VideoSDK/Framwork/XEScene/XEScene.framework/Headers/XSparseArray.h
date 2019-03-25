/******************************************************************************

@File         XSparseArray.h

@Version       1.0

@Created      2017, 4, 14

@Description  

@HISTORY:

******************************************************************************/
#ifndef _X_SPARSE_ARRAY_H_
#define _X_SPARSE_ARRAY_H_

#include "XTypes.h"
#include "XBitArray.h"
#include "XArray.h"

template<typename T>
class XSparseArray
{
public:
	explicit			XSparseArray(xint32 nInitialSize = 32, xint32 nNewGranularity = 16);
						XSparseArray(const XSparseArray<T>& other);
						~XSparseArray();
	XSparseArray<T>&	operator=(const XSparseArray<T>& other);

	T&					Get(xint32 nIndex);
	const T&			Get(xint32 nIndex) const;
	xint32				Add(const T& value);
	void				Remove(xint32 nIndex);
	void				Clear(xbool bReleaseMem = xtrue);
	void				DeleteContents(xbool bClear = xtrue);
	void				ReleaseContents(xbool bClear = xtrue);
	void				FreeContents(xbool bClear = xtrue);
	xint32				Num() const;
	void				Resize(xint32 nNum);
	xint32				GetGranularity() const;
	void				SetGranularity(xint32 nNewGranularity);
	xint32				Size() const;
	xbool				IsUsed(xint32 nIndex) const;

private:
	struct XSparseNode
	{
		xint32 nNext;
		T value;
	};

	XBitArray				m_BitArray;
	XArray<XSparseNode>	m_Elements;
	xint32					m_nFirstFreeIndex;
	xint32					m_nInitialSize;
	xint32					m_nGranularity;
};

//	Implementations
template<typename T>
XSparseArray<T>::XSparseArray(xint32 nInitialSize, xint32 nNewGranularity):
	m_Elements(nNewGranularity),
	m_BitArray(nInitialSize, nNewGranularity)
{
	ASSERT(nInitialSize > 0 && nNewGranularity > 0);

	m_nInitialSize = nInitialSize;
	m_nGranularity = nNewGranularity;
	Clear();
}

template<typename T>
XSparseArray<T>::XSparseArray(const XSparseArray<T>& other)
{
	*this = other;
}

template<typename T>
XSparseArray<T>::~XSparseArray()
{
	m_nFirstFreeIndex = X_INDEX_NONE;
	m_nGranularity = 0;
}

template<typename T>
XSparseArray<T>& XSparseArray<T>::operator=(const XSparseArray<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	m_BitArray = other.m_BitArray;
	m_Elements = other.m_Elements;
	m_nFirstFreeIndex = other.m_nFirstFreeIndex;
	m_nGranularity = other.m_nGranularity;

	return *this;
}

template<typename T>
T& XSparseArray<T>::Get(xint32 nIndex)
{
	ASSERT(nIndex >= 0 && nIndex < m_Elements.Num() && m_BitArray.Get(nIndex));

	return m_Elements[nIndex].value;
}

template<typename T>
const T& XSparseArray<T>::Get(xint32 nIndex) const
{
	ASSERT(nIndex >= 0 && nIndex < m_Elements.Num() && m_BitArray.Get(nIndex));

	return m_Elements[nIndex].value;
}

template<typename T>
xint32  XSparseArray<T>::Add(const T& value)
{
	if (m_nFirstFreeIndex == X_INDEX_NONE || m_Elements[m_nFirstFreeIndex].nNext == X_INDEX_NONE)
	{
		xint32 nNum = m_Elements.Num();
		if (!nNum)
		{
			Resize(m_nInitialSize);
		}
		else
		{
			Resize(nNum + m_nGranularity);
		}
	}


	m_BitArray.Set(m_nFirstFreeIndex, xtrue);
	xint32 nNextIndex = m_Elements[m_nFirstFreeIndex].nNext;	
	m_Elements[m_nFirstFreeIndex].value = value;

	xint32 nCurrentIndex = m_nFirstFreeIndex;
	m_nFirstFreeIndex = nNextIndex;

	return nCurrentIndex;
}

template<typename T>
void XSparseArray<T>::Remove(xint32 nIndex)
{
	if (m_nFirstFreeIndex < 0 || nIndex < 0 ||
		nIndex >= m_Elements.Num() || !m_BitArray.Get(nIndex))
	{
		return;
	}
	m_BitArray.Set(nIndex, xfalse);

	m_Elements[nIndex].nNext = m_nFirstFreeIndex;
	m_nFirstFreeIndex = nIndex;
}

template<typename T>
void XSparseArray<T>::Clear(xbool bReleaseMem)
{
	m_BitArray.Clear(bReleaseMem);
	m_Elements.Clear(bReleaseMem);
	m_nFirstFreeIndex = X_INDEX_NONE;
}

template<typename T>
void XSparseArray<T>::Resize(xint32 nNum)
{
	if (nNum == m_Elements.Num())
	{
		return;
	}
	m_Elements.SetNum(nNum);

	m_nFirstFreeIndex = X_INDEX_NONE;	
	for (xint32 i = 0; i < nNum; i++)
	{
		if (m_BitArray.Get(i))
		{
			continue;
		}

		m_Elements[i].nNext = m_nFirstFreeIndex;
		m_nFirstFreeIndex = i;
	}

	xint32 nBitsNum = m_BitArray.Num();
	for (xint32 i = nNum; i < nBitsNum; i++)
	{
		m_BitArray.Set(i, xfalse);
	}
}

template<typename T>
void XSparseArray<T>::DeleteContents(xbool bClear)
{

	xint32 nNum = m_Elements.Num();
	for (xint32 i = 0; i < nNum; i++)
	{
		if (!m_BitArray.Get(i))
		{
			continue;
		}
		XSparseNode& node = m_Elements[i];
		X_SAFEDELETE(node.value.value);
	}
	m_BitArray.Clear(bClear);

	if (!bClear)
	{
		xint32 nNum = m_Elements.Num();
		for (xint32 i = 0; i < nNum; i++)
		{
			m_Elements[i].nNext = i + 1;
		}

		if (nNum)
		{
			m_Elements[nNum - 1].nNext = X_INDEX_NONE;
		}

		m_nFirstFreeIndex = 0;
	}
	else
	{
		m_Elements.Clear();
		m_nFirstFreeIndex = X_INDEX_NONE;
	}
}

template<typename T>
void XSparseArray<T>::ReleaseContents(xbool bClear)
{
	xint32 nNum = m_Elements.Num();
	for (xint32 i = 0; i < nNum; i++)
	{
		if (!m_BitArray.Get(i))
		{
			continue;
		}
		XSparseNode& node = m_Elements[i];
		X_SAFERELEASE_INTERFACE(node.value.value);
	}
	m_BitArray.Clear(bClear);

	if (!bClear)
	{
		xint32 nNum = m_Elements.Num();
		for (xint32 i = 0; i < nNum; i++)
		{
			m_Elements[i].nNext = i + 1;
		}

		if (nNum)
		{
			m_Elements[nNum - 1].nNext = X_INDEX_NONE;
		}

		m_nFirstFreeIndex = 0;
	}
	else
	{
		m_Elements.Clear();
		m_nFirstFreeIndex = X_INDEX_NONE;
	}
}

template<typename T>
void XSparseArray<T>::FreeContents(xbool bClear)
{
	xint32 nNum = m_Elements.Num();
	for (xint32 i = 0; i < nNum; i++)
	{
		if (!m_BitArray.Get(i))
		{
			continue;
		}
		XSparseNode& node = m_Elements[i];
		X_SAFEFREE(node.value.value);
	}
	m_BitArray.Clear(bClear);

	if (!bClear)
	{
		xint32 nNum = m_Elements.Num();
		for (xint32 i = 0; i < nNum; i++)
		{
			m_Elements[i].nNext = i + 1;
		}

		if (nNum)
		{
			m_Elements[nNum - 1].nNext = X_INDEX_NONE;
		}

		m_nFirstFreeIndex = 0;
	}
	else
	{
		m_Elements.Clear();
		m_nFirstFreeIndex = X_INDEX_NONE;
	}
}


template<typename T>
X_INLINE xint32 XSparseArray<T>::Num() const
{
	return m_BitArray.Num();
}

template<typename T>
X_INLINE xint32 XSparseArray<T>::GetGranularity() const
{
	return m_nGranularity;
}

template<typename T>
void XSparseArray<T>::SetGranularity(xint32 nNewGranularity)
{
	if (nNewGranularity <= 0)
	{
		nNewGranularity = 16;
	}

	m_nGranularity = nNewGranularity;
	m_Elements.SetGranularity(m_nGranularity);

	if (m_nFirstFreeIndex >= m_Elements.Num())
	{
		m_nFirstFreeIndex = X_INDEX_NONE;
	}
}

template<typename T>
X_INLINE xint32 XSparseArray<T>::Size() const
{
	return m_Elements.Num();
}

template<typename T>
X_INLINE xbool XSparseArray<T>::IsUsed(xint32 nIndex) const
{
	ASSERT(nIndex >= 0 && nIndex < m_Elements.Num());
	return m_BitArray.Get(nIndex);
}

#endif