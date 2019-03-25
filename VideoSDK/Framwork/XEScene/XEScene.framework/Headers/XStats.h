/******************************************************************************

 @File         XStats.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XStats.

 @HISTORY:

******************************************************************************/
#ifndef _X_STATS_H_
#define _X_STATS_H_

#include "XSys.h"
#include "XMemBase.h"

class XStatBase;
class XStatGroup : public XMemBase
{
public:
						XStatGroup(const xchar* szName);
	virtual				~XStatGroup();

	virtual void		Frame();
	virtual xuint32		Render(xint32 x, xint32 y);

public:
	xchar				m_szName[MAX_PATH];
	xbool				m_bShow;
	XStatBase*			m_pFirstStat;
	XStatGroup*			m_pNext;
};
extern XStatGroup*		g_pXFirstStatGroup;


class XStatBase : public XMemBase
{
public:
						XStatBase(XStatGroup* pGroup, const xchar* szName)
						{
							strncpy(m_szName, szName, MAX_PATH);
							this->m_pNext = pGroup->m_pFirstStat;
							pGroup->m_pFirstStat = this;
						}
	virtual				~XStatBase(){}

	virtual	void		Frame() = 0;
	virtual	void		Render(xint32 x, xint32 y) = 0;

public:
	xchar				m_szName[MAX_PATH];
	XStatBase*			m_pNext;
};

template <class T> 
T XInitStatValue() 
{
	return 0;
}

template<class T>
class XStat : public XStatBase
{
public:
						XStat(XStatGroup* pGroup, const xchar* szName);
	virtual				~XStat() {}

	virtual void		Frame();
	virtual void		Render(xint32 x, xint32 y) = 0;

public:
	T					m_Value;
	static const xint32 STAT_HISTORY_SIZE = 20;
	T					m_History[STAT_HISTORY_SIZE];
	xint32				m_nHistoryHead;
};

template<class T>
XStat<T>::XStat(XStatGroup* pGroup, const xchar* szName)
:XStatBase(pGroup, szName),
 m_Value(XInitStatValue<T>()),
m_nHistoryHead(0)
{
	for( xint32 i = 0; i < STAT_HISTORY_SIZE; i++)
	{
		m_History[i] = XInitStatValue<T>();
	}
}

template<class T>
void XStat<T>::Frame()
{
	m_History[m_nHistoryHead] = m_Value;
	m_nHistoryHead = (m_nHistoryHead + 1) % STAT_HISTORY_SIZE;

	m_Value = XInitStatValue<T>();
}

class XStatCounter : public XStat<xuint32>
{
public:
						XStatCounter(XStatGroup* pGroup, const xchar* szName)
									:XStat<xuint32>(pGroup, szName)
						{}
	virtual				~XStatCounter() {}

	virtual void		Render(xint32 x, xint32 y);
};


#endif //_X_STATS_H_