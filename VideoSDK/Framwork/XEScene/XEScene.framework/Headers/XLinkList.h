/******************************************************************************

@File         XLinkList.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/
#ifndef _X_LINK_LIST_H_
#define _X_LINK_LIST_H_

#include "XTypes.h"

//	双向循环链表
template<typename T>
class XLinkList
{
public:
					XLinkList();
					~XLinkList();

	bool			IsListEmpty() const;
	bool			IsInList() const;
	xint32			Num() const;
	void			Clear();

	void			InsertBefore(XLinkList& node);
	void			InsertAfter(XLinkList& node);
	void			AddToEnd(XLinkList& node);
	void			AddToFront(XLinkList& node);

	void			Remove();

	T*				Next();
	T*				Prev();
	
	T*				Owner();
	void			SetOwner(T* pObj);

	XLinkList*		ListHead();
	XLinkList*		NextNode();
	XLinkList*		PrevNode();

private:
	XLinkList*		m_pHead;
	XLinkList*		m_pNext;
	XLinkList*		m_pPrev;
	T*				m_pOwner;
};

template<typename T>
XLinkList<T>::XLinkList() :
	m_pHead(this),
	m_pNext(this),
	m_pPrev(this),
	m_pOwner(NULL)
{}

template<typename T>
XLinkList<T>::~XLinkList()
{
	Clear();
}

template<typename T>
bool XLinkList<T>::IsListEmpty() const
{
	return m_pHead->m_pNext == m_pHead;
}

template<typename T>
bool XLinkList<T>::IsInList() const
{
	return m_pHead != this;
}

template<typename T>
xint32 XLinkList<T>::Num() const
{
	XLinkList<T> *pNode;
	xint32 nNum = 0;
	for (pNode = m_pHead->m_pNext; pNode != m_pHead; pNode = pNode->m_pNext) 
	{
		nNum++;
	}

	return nNum;
}

template<typename T>
void XLinkList<T>::Clear()
{
	if (m_pHead == this) 
	{
		while (m_pNext != this) 
		{
			m_pNext->Remove();
		}
	}
	else 
	{
		Remove();
	}
}

template<typename T>
void XLinkList<T>::InsertBefore(XLinkList& node)
{
	if (&node == this)
	{
		return;
	}

	Remove();

	m_pNext				= &node;
	m_pPrev				= node.m_pPrev;
	node.m_pPrev		= this;
	m_pPrev->m_pNext	= this;
	m_pHead				= node.m_pHead;
}

template<typename T>
void XLinkList<T>::InsertAfter(XLinkList& node)
{
	if (&node == this)
	{
		return;
	}

	Remove();

	m_pPrev				= &node;
	m_pNext				= node.m_pNext;
	node.m_pNext		= this;
	m_pNext->m_pPrev	= this;
	m_pHead				= node.m_pHead;
}

template<typename T>
void XLinkList<T>::AddToEnd(XLinkList& node)
{
	InsertBefore(*node.m_pHead);
}

template<typename T>
void XLinkList<T>::AddToFront(XLinkList& node)
{
	InsertAfter(*node.m_pHead);
}

template<typename T>
void XLinkList<T>::Remove()
{
	m_pPrev->m_pNext = m_pNext;
	m_pNext->m_pPrev = m_pPrev;

	m_pNext = this;
	m_pPrev = this;
	m_pHead = this;
}

template<typename T>
T* XLinkList<T>::Next() 
{
	if (!m_pNext || (m_pNext == m_pHead)) 
	{
		return NULL;
	}
	return m_pNext->m_pOwner;
}

template<typename T>
T* XLinkList<T>::Prev()
{
	if (!m_pPrev || (m_pPrev == m_pHead)) 
	{
		return NULL;
	}
	return m_pPrev->m_pOwner;
}

template<typename T>
T* XLinkList<T>::Owner()
{
	return m_pOwner;
}

template<typename T>
void XLinkList<T>::SetOwner(T* pObj)
{
	m_pOwner = pObj;
}

template<typename T>
XLinkList<T>* XLinkList<T>::ListHead()
{
	return m_pHead;
}

template<typename T>
XLinkList<T>* XLinkList<T>::NextNode()
{
	if (m_pNext == m_pHead) 
	{
		return NULL;
	}
	return m_pNext;
}

template<typename T>
XLinkList<T>* XLinkList<T>::PrevNode()
{
	if (m_pPrev == m_pHead) 
	{
		return NULL;
	}
	return m_pPrev;
}

#endif