/******************************************************************************

@File         XEIteratorWrapper.h

@Version       1.0

@Created      2017, 12, 27

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
// Reference IteratorWrapper to that in OGRE.

#ifndef XE_ITERATOR_WRAPPER_H
#define XE_ITERATOR_WRAPPER_H
#include "XTypes.h"
template <typename T>
class IteratorWrapper
{
public:
	typedef T        PointerType;
	typedef T const* IteratorType;
private:
	IteratorWrapper();
protected:
	IteratorType m_begin;
	IteratorType m_current;
	IteratorType m_end;
public:
	//++m
	IteratorType& operator ++ ()
	{
		if (hasMoreElements())
			moveNext();
		return m_current;
	}
	//m++
	const IteratorType operator ++ (xint32)
	{
		IteratorType it = m_current;
		if (hasMoreElements())
			moveNext();
		return it;
	}
public:
	IteratorWrapper(IteratorType data, xint32 start, xint32 last)
		: m_begin(data + start), m_current(data + start), m_end(data + last)
	{
	}

	/** Returns true if there are more items in the collection. */
	bool hasMoreElements() const
	{
		return m_current != m_end;
	}


	/** Moves the iterator on one element. */
	void moveNext()
	{
		++m_current;
	}

	/** Seek the iterator on specific element quantity. */
	const IteratorType& seek(xint32 offset)
	{
		if (offset < 0)
			return m_end;

		while (offset>0 && hasMoreElements())
		{
			offset--;
			moveNext();
		}
		return m_current;
	}

	/** Bookmark to the begin of the underlying collection */
	const IteratorType& begin() { return m_begin; }


	/** Full access to the current  iterator */
	IteratorType& current(){ return m_current; }

	/** Bookmark to the end (one behind the last element) of the underlying collection */
	const IteratorType& end() { return m_end; }

};


#endif//XE_ITERATOR_WRAPPER_H