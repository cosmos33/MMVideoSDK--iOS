/******************************************************************************

@File         XHashTable.h

@Version       1.0

@Created      2017, 4, 14

@Description  HashTable

@HISTORY:

******************************************************************************/
#ifndef _X_HASHTABLE_H_
#define _X_HASHTABLE_H_

#include "XTypes.h"
#include "XSparseArray.h"

template<typename K, typename T>
struct XHashNode
{
	K key;
	T value;
	static xbool KeyEqual(const K& key0, const K& key1){ return key0 == key1; }
	static xint32 GetHash(const K& key, xint32 nTableMask){ return key & (nTableMask - 1); }
};

template<typename K, typename T>
class XHashTable
{
public:
	explicit				XHashTable(xint32 nInitialSize = 1024, xint32 nNewGranularity = 1024, xint32 nTableSize = 1024);// nTableSize = pow(2, n);
							XHashTable(const XHashTable<K, T>& other);
							~XHashTable();

	XHashTable<K, T>&		operator=(const XHashTable<K, T>& other);
	
	/*
	* 添加一对键-值
	* 
	* @notice	如果键值已存在，则修改值
	*
	* @param	key	键
	* @value	value 值
	*/
	void					Set(const K& key, const T& value);

	/*
	* 根据键查找值
	*
	* @param	key	键
	* @return	指向内部元素的指针，未找到则返回空
	*/
	T*						Find(const K& key);

	/*
	* 查找的const版本
	*/
	const T*				Find(const K& key) const;

	/*
	* 查找，当值是指针类型
	* 
	* @notice	值是指针类型时调用，否则效率低
	*
	* @param	key	键
	* @return	查找的值（指针）
	*/
	T						FindRef(const K& key) const; 

	/*
	* 根据键值查找并删除一个元素
	*
	* @param	value 键值
	* @returns  找到返回xtrue，未找到返回xfalse
	*/
	xbool					Remove(const K& key);

	/*
	* 清空HashTable
	*
	* @param	bReleaseMem 是否清空为该HashTable分配的内存
	*/
	void					Clear(xbool bReleaseMem = xtrue);

	/*
	* 依次Delete HashTable中的元素，之后调用Clear
	*
	* @notice	元素须为指针类型
	*
	* @param	bReleaseMem Clear的参数
	*/
	void					DeleteContents(xbool bReleaseMem = xtrue);

	/*
	* 依次调用HashTable中元素的Release接口，之后调用Clear
	*
	* @notice	元素须为指针类型且具有Release接口
	*
	* @param	bReleaseMem Clear的参数
	*/
	void					ReleaseContents(xbool bReleaseMem = xtrue);

	/*
	* 返回元素数量
	*/
	xint32					Num() const;
	
	/*
	* 遍历HashTable时使用
	*
	* @notice	效率低，禁止在效率敏感处调用
	*
	* @param	nIndex 既是传入，又是传出参数。
	*
	* @example
	*			xint32 nIndex = 0;
	*			while (T* t = Next(nIndex))
	*			{...}
	*/
	T*						Next(xint32& nIndex);

	/*
	* Next的const版本
	*/
	const T*				Next(xint32& nIndex) const;
	
	/*
	* 值为指针时的Next版本
	*/
	T						NextRef(xint32& nIndex) const;

	/*
	* 同时需要键和值的遍历版本
	*/
	const XHashNode<K, T>*	NextNode(xint32& nIndex) const;

	/*
	* ...
	*/
	xint32					GetGranularity() const;
	void					SetGranularity(xint32 nNewGranularity);

private:
	static void				ResizeIntArray(xint32** ppIntArray, xint32 nOldSize, xint32 nNewSize);

private:
	xint32							m_nInitialSize;
	xint32							m_nGranularity;
	xint32							m_nTableSize;
	xint32*							m_pHash;
	xint32*							m_pIndexChain;
	xint32							m_nIndexChainSize;
	XSparseArray< XHashNode<K, T> >	m_SparseArray;
};

////////////////////////////////////////////////////////////////////
//	Implementations
template<typename K, typename T>
XHashTable<K, T>::XHashTable(xint32 nInitialSize, xint32 nNewGranularity, xint32 nTableSize):
	m_nInitialSize(nInitialSize),
	m_nGranularity(nNewGranularity),
	m_nTableSize(nTableSize),
	m_pHash(NULL),
	m_pIndexChain(NULL),
	m_nIndexChainSize(0),
	m_SparseArray(nInitialSize, nNewGranularity)
{
	ASSERT(nInitialSize > 0 && nNewGranularity > 0 && nTableSize > 0 && (nTableSize & (nTableSize - 1)) == 0);
}

template<typename K, typename T>
XHashTable<K, T>::XHashTable(const XHashTable<K, T>& other) :
	m_pHash(NULL),
	m_pIndexChain(NULL)
{
	*this = other;
}

template<typename K, typename T>
XHashTable<K, T>::~XHashTable()
{
	m_nInitialSize = 0;
	m_nGranularity = 0;
	m_nTableSize = 0;
	X_SAFEFREE(m_pHash);
	X_SAFEFREE(m_pIndexChain);
	m_nIndexChainSize = 0;
}

template<typename K, typename T>
XHashTable<K, T>& XHashTable<K, T>::operator=(const XHashTable<K, T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	m_nInitialSize = other.m_nInitialSize;
	m_nGranularity = other.m_nGranularity;
	m_nTableSize = other.m_nTableSize;
	m_nIndexChainSize = other.m_nIndexChainSize;
	m_SparseArray = other.m_SparseArray;

	X_SAFEFREE(m_pHash);
	X_SAFEFREE(m_pIndexChain);

	if (m_nTableSize && other.m_pHash)
	{
		m_pHash = (xint32*)XMemory::Malloc(m_nTableSize * sizeof(xint32));
		memcpy(m_pHash, other.m_pHash, m_nTableSize * sizeof(xint32));
	}

	if (m_nIndexChainSize)
	{
		m_pIndexChain = (xint32*)XMemory::Malloc(m_nIndexChainSize * sizeof(xint32));
		memcpy(m_pIndexChain, other.m_pIndexChain, m_nIndexChainSize * sizeof(xint32));
	}

	return *this;
}

template<typename K, typename T>
void XHashTable<K, T>::Set(const K& key, const T& value)
{
	if (m_nTableSize <= 0)
	{
		return;
	}

	T* pT = NULL;
	if (pT = Find(key))
	{
		*pT = value;
		return;
	}


	xint32 nHashKey = XHashNode<K, T>::GetHash(key, m_nTableSize);
	if (!m_pHash)
	{
		ResizeIntArray(&m_pHash, 0, m_nTableSize);
	}

	XHashNode<K, T> node;
	node.key = key;
	node.value = value;
	xint32 nIndex = m_SparseArray.Add(node);

	//	分配足够多的空间
	if (m_nIndexChainSize < m_SparseArray.Size())
	{
		xint32 nNewIndexChainSize = m_SparseArray.Size();
		ResizeIntArray(&m_pIndexChain, m_nIndexChainSize, nNewIndexChainSize);
		m_nIndexChainSize = nNewIndexChainSize;
	}

	m_pIndexChain[nIndex] = m_pHash[nHashKey];
	m_pHash[nHashKey] = nIndex;
}

template<typename K, typename T>
T* XHashTable<K, T>::Find(const K& key)
{
	if (m_nTableSize <= 0)
	{
		return NULL;
	}
	if (!m_pHash)
	{
		return NULL;
	}
	xint32 nHashKey = XHashNode<K, T>::GetHash(key, m_nTableSize);

	for (xint32 nIndex = m_pHash[nHashKey]; nIndex != X_INDEX_NONE; nIndex = m_pIndexChain[nIndex])
	{
		XHashNode<K, T>& node = m_SparseArray.Get(nIndex);
		if (XHashNode<K, T>::KeyEqual(node.key, key))
		{
			return &(node.value);
		}
	}

	return NULL;
}

template<typename K, typename T>
const T* XHashTable<K, T>::Find(const K& key) const
{
	if (m_nTableSize <= 0)
	{
		return NULL;
	}
	if (!m_pHash)
	{
		return NULL;
	}
	xint32 nHashKey = XHashNode<K, T>::GetHash(key, m_nTableSize);

	for (xint32 nIndex = m_pHash[nHashKey]; nIndex != X_INDEX_NONE; nIndex = m_pIndexChain[nIndex])
	{
		const XHashNode<K, T>& node = m_SparseArray.Get(nIndex);
		if (XHashNode<K, T>::KeyEqual(node.key, key))
		{
			return &(node.value);
		}
	}

	return NULL;
}

template<typename K, typename T>
T XHashTable<K, T>::FindRef(const K& key) const
{
	if (m_nTableSize <= 0)
	{
		return (T)NULL;
	}
	if (!m_pHash)
	{
		return (T)NULL;
	}
	xint32 nHashKey = XHashNode<K, T>::GetHash(key, m_nTableSize);

	for (xint32 nIndex = m_pHash[nHashKey]; nIndex != X_INDEX_NONE; nIndex = m_pIndexChain[nIndex])
	{
		const XHashNode<K, T>& node = m_SparseArray.Get(nIndex);
		if (XHashNode<K, T>::KeyEqual(node.key, key))
		{
			return node.value;
		}
	}

	return (T)NULL;
}

template<typename K, typename T>
T* XHashTable<K, T>::Next(xint32& nIndex)
{
	if (nIndex == X_INDEX_NONE)
	{
		return NULL;
	}

	xint32 nSparseSize = m_SparseArray.Size();
	if (nSparseSize == 0)
	{
		nIndex = X_INDEX_NONE;
		return NULL;
	}
	ASSERT(nIndex >= 0 && nIndex < nSparseSize);

	while (nIndex < nSparseSize && !m_SparseArray.IsUsed(nIndex))
	{
		nIndex++;
	}

	if (nIndex == nSparseSize)
	{
		nIndex = X_INDEX_NONE;
		return NULL;
	}


	T* pT = &(m_SparseArray.Get(nIndex).value);

	nIndex++;

	//	遍历完成
	if (nIndex == nSparseSize)
	{		
		nIndex = X_INDEX_NONE;
	}

	return pT;
}

template<typename K, typename T>
const T* XHashTable<K, T>::Next(xint32& nIndex) const
{
	if (nIndex == X_INDEX_NONE)
	{
		return NULL;
	}

	xint32 nSparseSize = m_SparseArray.Size();
	if (nSparseSize == 0)
	{
		nIndex = X_INDEX_NONE;
		return NULL;
	}
	ASSERT(nIndex >= 0 && nIndex < nSparseSize);

	while (nIndex < nSparseSize && !m_SparseArray.IsUsed(nIndex))
	{
		nIndex++;
	}

	if (nIndex == nSparseSize)
	{
		nIndex = X_INDEX_NONE;
		return NULL;
	}


	const T* pT = &(m_SparseArray.Get(nIndex).value);

	nIndex++;

	//	遍历完成
	if (nIndex == nSparseSize)
	{		
		nIndex = X_INDEX_NONE;
	}

	return pT;
}

template<typename K, typename T>
T XHashTable<K, T>::NextRef(xint32& nIndex) const
{
	if (nIndex == X_INDEX_NONE)
	{
		return (T)NULL;
	}

	xint32 nSparseSize = m_SparseArray.Size();
	if (nIndex < 0 || nIndex >= nSparseSize)
	{
		nIndex = X_INDEX_NONE;
		return (T)NULL;
	}

	while (nIndex < nSparseSize && !m_SparseArray.IsUsed(nIndex))
	{
		nIndex++;
	}

	if (nIndex == nSparseSize)
	{
		nIndex = X_INDEX_NONE;
		return (T)NULL;
	}


	T t = m_SparseArray.Get(nIndex).value;

	nIndex++;

	//	遍历完成
	if (nIndex == nSparseSize)
	{		
		nIndex = X_INDEX_NONE;
	}

	return t;
}

template<typename K, typename T>
const XHashNode<K, T>* XHashTable<K, T>::NextNode(xint32& nIndex) const
{
	if (nIndex == X_INDEX_NONE)
	{
		return NULL;
	}

	xint32 nSparseSize = m_SparseArray.Size();
	if (nSparseSize == 0)
	{
		nIndex = X_INDEX_NONE;
		return NULL;
	}
	ASSERT(nIndex >= 0 && nIndex < nSparseSize);

	while (nIndex < nSparseSize && !m_SparseArray.IsUsed(nIndex))
	{
		nIndex++;
	}

	if (nIndex == nSparseSize)
	{
		nIndex = X_INDEX_NONE;
		return NULL;
	}


	const XHashNode<K, T>& node = m_SparseArray.Get(nIndex);
	nIndex++;

	//	遍历完成
	if (nIndex == nSparseSize)
	{		
		nIndex = X_INDEX_NONE;
	}

	return &node;
}

template<typename K, typename T>
xbool XHashTable<K, T>::Remove(const K& key)
{
	xint32 nHashKey = XHashNode<K, T>::GetHash(key, m_nTableSize);
	if (!m_pHash)
	{
		return xfalse;
	}
	xint32 nLastIndex = X_INDEX_NONE;
	for (xint32 nIndex = m_pHash[nHashKey]; nIndex != X_INDEX_NONE; nIndex = m_pIndexChain[nIndex])
	{
		if (XHashNode<K, T>::KeyEqual(m_SparseArray.Get(nIndex).key, key))
		{
			if (nLastIndex == X_INDEX_NONE)
			{
				m_pHash[nHashKey] = m_pIndexChain[nIndex];
			}
			else
			{
				m_pIndexChain[nLastIndex] = m_pIndexChain[nIndex];
			}
			m_SparseArray.Remove(nIndex);
			return xtrue;
		}

		nLastIndex = nIndex;
	}

	return xfalse;
}

template<typename K, typename T>
void XHashTable<K, T>::Clear(xbool bReleaseMem)
{
	if (bReleaseMem)
	{
		X_SAFEFREE(m_pHash);
		X_SAFEFREE(m_pIndexChain);
		m_nIndexChainSize = 0;
	}
	else
	{
		//	设置默认值为-1
		if (m_pHash)
		{
			memset(m_pHash, 0xFF, m_nTableSize * sizeof(xint32));
		}

		if (m_nIndexChainSize)
		{
			memset(m_pIndexChain, 0xFF, m_nIndexChainSize * sizeof(xint32));
		}
	}

	m_SparseArray.Clear(bReleaseMem);
}


template<typename K, typename T>
void XHashTable<K, T>::ReleaseContents(xbool bReleaseMem)
{

	//	Release SparseArray contents
	xint32 nIndex = 0;
	while (T t = NextRef(nIndex))
	{
		X_SAFERELEASE_INTERFACE(t);
	}

	xint32 nNum = m_SparseArray.Num();
	m_SparseArray.Clear(bReleaseMem);
	if (!bReleaseMem)
	{
		m_SparseArray.Resize(nNum);
	}

	if (bReleaseMem)
	{
		X_SAFEFREE(m_pHash);
		X_SAFEFREE(m_pIndexChain);
		m_nIndexChainSize = 0;
	}
	else
	{
		//	设置默认值为-1
		if (m_pHash)
		{
			memset(m_pHash, 0xFF, m_nTableSize * sizeof(xint32));
		}

		if (m_nIndexChainSize)
		{
			memset(m_pIndexChain, 0xFF, m_nIndexChainSize * sizeof(xint32));
		}
	}
}

template<typename K, typename T>
void XHashTable<K, T>::DeleteContents(xbool bReleaseMem)
{
	//	Delete SparseArray contents
	xint32 nIndex = 0;
	while (T t = NextRef(nIndex))
	{
		X_SAFEDELETE(t);
	}

	xint32 nNum = m_SparseArray.Num();
	m_SparseArray.Clear(bReleaseMem);
	if (!bReleaseMem)
	{
		m_SparseArray.Resize(nNum);
	}

	if (bReleaseMem)
	{
		X_SAFEFREE(m_pHash);
		X_SAFEFREE(m_pIndexChain);
		m_nIndexChainSize = 0;
	}
	else
	{
		//	设置默认值为-1
		if (m_pHash)
		{
			memset(m_pHash, 0xFF, m_nTableSize * sizeof(xint32));
		}

		if (m_nIndexChainSize)
		{
			memset(m_pIndexChain, 0xFF, m_nIndexChainSize * sizeof(xint32));
		}
	}
}

template<typename K, typename T>
xint32 XHashTable<K, T>::Num() const
{
	return m_SparseArray.Num();
}

template<typename K, typename T>
X_INLINE xint32 XHashTable<K, T>::GetGranularity() const
{
	return m_nGranularity;
}

template<typename K, typename T>
void XHashTable<K, T>::SetGranularity(xint32 nNewGranularity)
{
	m_nGranularity = nNewGranularity;
	
	xint32 nNewIndexChainSize = m_nIndexChainSize + m_nGranularity;
	nNewIndexChainSize -= nNewIndexChainSize % m_nGranularity;
	ResizeIntArray(&m_pIndexChain, m_nIndexChainSize, nNewIndexChainSize);
	m_nIndexChainSize = nNewIndexChainSize;
}

template<typename K, typename T>
void XHashTable<K, T>::ResizeIntArray(xint32** ppIntArray, xint32 nOldSize, xint32 nNewSize)
{
	if (nOldSize == nNewSize)
	{
		return;
	}

	xint32* pOldIntArray = *ppIntArray;
	xint32 nNewSizeInByte = nNewSize * sizeof(xint32);
	xint32 nOldSizeInByte = nOldSize * sizeof(xint32);
	*ppIntArray = (xint32*)XMemory::Malloc(nNewSizeInByte);
	if (nOldSize && nNewSize)
	{
		xint32 nMin = nNewSizeInByte < nOldSizeInByte ? nNewSizeInByte : nOldSizeInByte;
		memcpy(*ppIntArray, pOldIntArray, nMin);
	}
	if (nNewSizeInByte > nOldSizeInByte)
	{
		memset(*ppIntArray + nOldSize, 0xFF, nNewSizeInByte - nOldSizeInByte);
	}
	X_SAFEFREE(pOldIntArray);
}


////////////////////////////////////////////////////////////////////
//	XHashNode
template<typename T>
struct XHashNode<XString, T>
{
	XString key;
	T value;
	static xbool KeyEqual(const XString& strKey0, const XString& strKey1){ return strKey0 == strKey1; }
	static xint32 GetHash(const XString& strKey, xint32 nTableMask)
	{ 
		return XString::Hash(strKey.CStr()) & (nTableMask - 1);
	}
};

template<typename T>
struct XHashNode<const xchar*, T>
{
	const xchar* key;
	T value;
	static xbool KeyEqual(const xchar* const& szKey0, const xchar* const& szKey1){ return 0 == strcmp(szKey0, szKey1); }
	static xint32 GetHash(const xchar* const& szKey, xint32 nTableMask)
	{ 
		return XString::Hash(szKey) & (nTableMask - 1);
	}
};

template <typename K, typename T>
struct XHashNode<K*, T>
{
	K* key;
	T  value;
	static xbool KeyEqual(K* const& key0, K* const& key1){ return key0 == key1; }
	static xint32 GetHash(K* const& key, xint32 nTableMask){ return (xuptrint)key & (nTableMask - 1); }
};

#endif