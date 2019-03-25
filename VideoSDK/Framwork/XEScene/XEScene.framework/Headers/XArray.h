/******************************************************************************

@File         XArray.h

@Version      1.0

@Created      2017, 4, 14

@Description  基本的动态数组

@HISTORY:	

******************************************************************************/
#ifndef _XARRAY_H_
#define _XARRAY_H_

#include "XTypes.h"
#include "XString.h"

template<typename T>
class XArray
{
public:
	explicit		XArray(xint32 nInitalSize = 16, xint32 nGranularity = 16);
					XArray(const XArray<T>& other);
					~XArray();

	XArray<T>&		operator=(const XArray<T>& other);
	T&				operator[](xint32 nIndex);
	const T&		operator[](xint32 nIndex) const;
	
	/*
	 * 在数组尾端添加一个元素，可能引起内存重新分配
	 * 
	 * @param	value 待添加的元素
	 * @returns 当前元素数量
	 */ 
	xint32			Add(const T& value);
	
	/*
	* 如果数组中不存在该元素，则添加，如果存在该元素，则不添加
	*
	* @param	value 待添加的元素
	* @return	添加或已存在的位置索引，如果已存在返回X_INDEX_NONE
	*/
	xint32			AddUnique(const T& value);

	/*
	* 在指定索引处插入一个元素，若索引越界则无动作
	*
	* @param	nIndex 指定索引
	* @param	value 待添加的元素
	*/
	void			Insert(xint32 nIndex, const T& value);

	/*
	* 在指定索引处删除一个元素，若索引越界则无动作
	*
	* @param	nIndex 指定索引
	*/
	void			RemoveAt(xint32 nIndex);
	
	/*
	* 在指定索引处快速删除一个元素，不保证元素顺序，若索引越界则无动作
	*
	* @param	nIndex 指定索引
	*/
	void			RemoveAtFast(xint32 nIndex);

	/*
	* 根据元素值查找并删除一个元素，若索引越界则无动作
	*
	* @param	value 元素值
	* @returns  找到返回xtrue，未找到返回xfalse
	*/
	xbool			Remove(const T& value);

	/*
	* 根据元素值查找并快速删除一个元素，不保证元素顺序，若索引越界则无动作
	*
	* @param	value 元素值
	* @returns  找到返回xtrue，未找到返回xfalse
	*/
	xbool			RemoveFast(const T& value);

	/*
	* 清空数组
	*
	* @param	bReleaseMem 是否清空为该数组分配的内存
	*/
	void			Clear(xbool bRelease = xtrue);

	/*
	* 依次Delete数组中的元素，之后调用Clear
	*
	* @notice	元素须为指针类型
	*
	* @param	bReleaseMem Clear的参数
	*/
	void			DeleteContents(xbool bRelease = xtrue);
	
	/*
	* 依次调用数组中元素的Release接口，之后调用Clear
	*
	* @notice	元素须为指针类型且具有Release接口
	*
	* @param	bReleaseMem Clear的参数
	*/
	void			ReleaseContents(xbool bRelease = xtrue);

	/*
	* 返回元素数量
	*/
	xint32			Num() const;

	/*
	* 设置数组中的元素数量
	*
	* @notice	若元素类型是指针(需要Delete)，同时nNum小于实际数量时，直接DeleteContent会造成内存泄露
	*
	* @param	nNum 新的数量
	*/
	void			SetNum(xint32 nNum);

	/*
	* 设置数组中的元素数量，并赋初值
	*
	* @notice	见上
	*
	* @param	nNum 新的数量
	* @param	initValue 元素初值
	*/
	void			SetNum(xint32 nNum, const T& initValue);

	/*
	* 设置数组的容量
	*
	* @notice	见上
	*
	* @param	nNum 新的数量
	*/
	void			Resize(xint32 nSize);

	/*
	* 返回数组的容量
	*/
	xint32			Size() const;

	/*
	* 查找元素的索引位置
	*
	* @param	value 元素值
	* @param	nBeginIndex 起始索引
	* @returns  找到返回索引，未找到返回X_INDEX_NONE
	*/
	xint32			Find(const T& value, xint32 nBeginIndex = 0) const;
	
	/*
	* 倒序查找元素的索引位置
	*
	* @param	value
	* @returns  找到返回索引，未找到返回X_INDEX_NONE
	*/
	xint32			ReverseFind(const T& value) const;

	/*
	* 返回指向数组首元素的指针
	*/
	T*				GetData();
	const T*		GetData() const;

	/*
	* 交换两个数组的元素
	*/
	void			Swap(XArray<T>& other);

	typedef			xint32(*CmpFunctionPtr)(const T*, const T*);
	void			QSort(CmpFunctionPtr pCMP = SortCompare);

	// 行为可能有误，尽量不要使用
	xint32			GetGranularity() const;
	void			SetGranularity(xint32 nNewGranularity);

private:
	static xint32	SortCompare(const T* pT0, const T* pT1);
	static void*	Allocate(xint32 nNum);
	static void		DeAllocate(void* ptr, xint32 nNum);

private:
	xint32			m_nInitialSize;
	xint32			m_nGranularity;
	xint32			m_nSize;
	xint32			m_nNum;
	T*				m_pElements;
};


template<typename T>
XArray<T>::XArray(xint32 nInitalSize, xint32 nGranularity):
	m_nInitialSize(nInitalSize),
	m_nGranularity(nGranularity),
	m_nSize(0),
	m_nNum(0),
	m_pElements(NULL)
{
	ASSERT(nInitalSize > 0 && nGranularity > 0);
}

template<typename T>
XArray<T>::XArray(const XArray<T>& other) :
m_nSize(0),
m_nNum(0),
m_pElements(NULL)
{
	*this = other;
}

template<typename T>
XArray<T>::~XArray()
{
	DeAllocate(m_pElements, m_nSize);
	m_pElements = NULL;
	m_nInitialSize = 0;
	m_nGranularity = 0;
	m_nSize = 0;
	m_nNum = 0;
}

template<typename T>
XArray<T>& XArray<T>::operator=(const XArray<T>& other)
{
	if (&other == this)
	{
		return *this;
	}

	Clear(xtrue);

	m_nInitialSize = other.m_nInitialSize;
	m_nGranularity = other.m_nGranularity;
	m_nSize = other.m_nSize;
	m_nNum = other.m_nNum;

	m_pElements = (T*)Allocate(m_nSize);
	for (xint32 i = 0; i < m_nNum; i++)
	{
		m_pElements[i] = other.m_pElements[i];
	}

	return *this;
}


template<typename T>
xint32 XArray<T>::Add(const T& value)
{
	if (m_nNum == m_nSize)
	{
		xint32 nNewSize = m_nSize ? m_nSize + m_nGranularity : m_nInitialSize;
		Resize(nNewSize);
	}
	m_pElements[m_nNum] = value;
	return m_nNum ++;
}


template<typename T>
xint32 XArray<T>::AddUnique(const T& value)
{
	xint32 nIndex = Find(value);
	if (nIndex == X_INDEX_NONE)
	{
		nIndex = m_nNum;
		Add(value);
	}

	return nIndex;
}

template<typename T>
void XArray<T>::Insert(xint32 nIndex, const T& value)
{
	if (nIndex < 0 || nIndex > m_nNum)
	{
		return;
	}

	if (m_nNum == m_nSize)
	{
		xint32 nNewSize = m_nSize ? m_nSize + m_nGranularity : m_nInitialSize;
		Resize(nNewSize);
	}
	for (xint32 i = m_nNum - 1; i >= nIndex; i--)
	{
		m_pElements[i+1] = m_pElements[i];
	}
	m_pElements[nIndex] = value;
	m_nNum++;
}

template<typename T>
void XArray<T>::RemoveAt(xint32 nIndex)
{
	if (nIndex < 0 || nIndex >= m_nNum)
	{
		return;
	}

	m_nNum--;
	for (xint32 i = nIndex; i < m_nNum; i++)
	{
		m_pElements[i] = m_pElements[i+1];
	}
}

template<typename T>
void XArray<T>::RemoveAtFast(xint32 nIndex)
{
	if (nIndex < 0 || nIndex >= m_nNum)
	{
		return;
	}

	m_nNum--;
	if (nIndex != m_nNum)
	{
		m_pElements[nIndex] = m_pElements[m_nNum];
	}
}

template<typename T>
xbool XArray<T>::Remove(const T& value)
{
	xint32 nIndex = Find(value);
	if (nIndex < 0)
	{
		return xfalse;
	}

	RemoveAt(nIndex);
	return xtrue;
}

template<typename T>
xbool XArray<T>::RemoveFast(const T& value)
{
	xint32 nIndex = Find(value);
	if (nIndex < 0)
	{
		return xfalse;
	}

	RemoveAtFast(nIndex);
	return xtrue;
}

template<typename T>
X_INLINE void XArray<T>::Clear(xbool bReleaseMem)
{
	m_nNum = 0;
	if (bReleaseMem)
	{
		DeAllocate(m_pElements, m_nSize);
		m_pElements = NULL;
		m_nSize = 0;
	}
}

template<typename T>
void XArray<T>::DeleteContents(xbool bReleaseMem)
{
	for (xint32 i = 0; i < m_nNum; i++)
	{
		X_SAFEDELETE(m_pElements[i]);
	}

	Clear(bReleaseMem);
}

template<typename T>
void XArray<T>::ReleaseContents(xbool bReleaseMem)
{
	for (xint32 i = 0; i < m_nNum; i++)
	{
		X_SAFERELEASE_INTERFACE(m_pElements[i]);
	}

	Clear(bReleaseMem);
}

template<typename T>
X_INLINE xint32 XArray<T>::Num() const
{
	return m_nNum;
}

template<typename T>
void XArray<T>::SetNum(xint32 nNum)
{
	if (nNum < 0)
	{
		return;
	}
	if (nNum > m_nSize)
	{
		xint32 nNewSize = nNum + m_nGranularity;
		nNewSize -= nNewSize % m_nGranularity;
		Resize(nNewSize);
	}
	m_nNum = nNum;
}

template<typename T>
void XArray<T>::SetNum(xint32 nNum, const T& initValue)
{
	if (nNum < 0)
	{
		return;
	}
	if (nNum > m_nSize)
	{
		xint32 nNewSize = nNum + m_nGranularity;
		nNewSize -= nNewSize % m_nGranularity;
		Resize(nNewSize);
	}

	for (xint32 i = m_nNum; i < nNum; i++)
	{
		m_pElements[i] = initValue;
	}

	m_nNum = nNum;
}

template<typename T>
X_INLINE xint32 XArray<T>::GetGranularity() const
{
	return m_nGranularity;
}

template<typename T>
void XArray<T>::SetGranularity(xint32 nNewGranularity)
{
	if (nNewGranularity <= 0)
	{
		nNewGranularity = 16;
	}
	m_nGranularity = nNewGranularity;

	if (m_nSize)
	{
		xint32 nNewSize = m_nNum + m_nGranularity;
		nNewSize -= nNewSize % m_nGranularity;
		Resize(nNewSize);
	}
}

template<typename T>
void XArray<T>::Resize(xint32 nNewSize)
{
	if (nNewSize < 0)
	{
		return;
	}
	if (m_nSize == nNewSize)
	{
		return;
	}

	T* pOldElements = m_pElements;
	m_pElements = (T*)Allocate(nNewSize);

	xint32 nMinNum = m_nNum < nNewSize ? m_nNum : nNewSize;
	for (xint32 i = 0; i < nMinNum; i++)
	{
		m_pElements[i] = pOldElements[i];
	}

	DeAllocate(pOldElements, m_nSize);
	pOldElements = NULL;

	m_nSize = nNewSize;
	if (nNewSize < m_nNum)
	{
		m_nNum = nNewSize;
	}
}

template<typename T>
X_INLINE xint32 XArray<T>::Size() const
{
	return m_nSize;
}

template<typename T>
X_INLINE T& XArray<T>::operator[](xint32 nIndex)
{
	ASSERT(nIndex >= 0 && nIndex < m_nNum);
	return m_pElements[nIndex];
}

template<typename T>
X_INLINE const T& XArray<T>::operator[](xint32 nIndex) const
{
	ASSERT(nIndex >= 0 && nIndex < m_nNum);
	return m_pElements[nIndex];
}


template<typename T>
X_INLINE xint32 XArray<T>::Find(const T& value, xint32 nBeginIndex) const
{
	if (nBeginIndex < 0 || nBeginIndex >= m_nNum)
	{
		return X_INDEX_NONE;
	}

	for (xint32 i = nBeginIndex; i < m_nNum; i++)
	{
		if (m_pElements[i] == value)
		{
			return i;
		}
	}

	return X_INDEX_NONE;
}

template<typename T>
X_INLINE xint32 XArray<T>::ReverseFind(const T& value) const
{
	for (xint32 i = m_nNum - 1; i >= 0;  i--)
	{
		if (m_pElements[i] == value)
		{
			return i;
		}
	}
	return X_INDEX_NONE;
}

template<typename T>
X_INLINE T* XArray<T>::GetData()
{
	return m_pElements;
}

template<typename T>
X_INLINE const T* XArray<T>::GetData() const
{
	return m_pElements;	
}

template<typename T>
X_INLINE void XArray<T>::Swap(XArray<T>& other)
{
	xint32 nInitialSize = other.m_nInitialSize;
	xint32 nGranularity = other.m_nGranularity;
	xint32 nSize = other.m_nSize;
	xint32 nNum = other.m_nNum;
	T* pArrElements = other.m_pElements;

	other.m_nInitialSize = m_nInitialSize;
	other.m_nGranularity = m_nGranularity;
	other.m_nSize = m_nSize;
	other.m_nNum = m_nNum;
	other.m_pElements = m_pElements;

	m_nInitialSize = nInitialSize;
	m_nGranularity = nGranularity;
	m_nSize = nSize;
	m_nNum = nNum;
	m_pElements = pArrElements;
}

template<typename T>
void XArray<T>::QSort(CmpFunctionPtr pCMP)
{
	if (pCMP == NULL)
	{
		return;
	}
	typedef xint32 (*CmpVoid)(const void *, const void *);
	CmpVoid pFuncVoidCom = (CmpVoid)pCMP;
	qsort(m_pElements, m_nNum, sizeof(T), pFuncVoidCom);
}


template<typename T>
void* XArray<T>::Allocate(xint32 nNum)
{
	void* ptr = XMemory::Malloc(nNum * sizeof(T));
	for (xint32 i = 0; i < nNum; i++)
	{
		new (&((T*)ptr)[i]) T;
	}
	return ptr;
}

template<typename T>
void XArray<T>::DeAllocate(void* ptr, xint32 nNum)
{
	for (xint32 i = 0; i < nNum; i++)
	{
		((T*)ptr)[i].~T();
	}
	X_SAFEFREE(ptr);
}

template<typename T>
X_INLINE xint32 XArray<T>::SortCompare(const T* pT0, const T* pT1)
{
	return *pT0 - *pT1;
}

template<>
X_INLINE xint32 XArray<XString>::SortCompare(const XString* pT0, const XString* pT1)
{
	if (*pT0 < *pT1)
	{
		return -1;
	}
	else if (*pT0 == *pT1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


template<>
X_INLINE xint32 XArray<XString*>::SortCompare(XString* const* pT0, XString* const* pT1)
{
	if (**pT0 < **pT1)
	{
		return -1;
	}
	else if (**pT0 == **pT1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

#endif