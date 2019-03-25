/******************************************************************************

@File         XEEventList.h

@Version       1.0

@Created      2018,6,12 

@HISTORY:

******************************************************************************/
#ifndef _XE_EVENT_LIST_H
#define _XE_EVENT_LIST_H
#include "XEEventBase.h"
#include "XEIteratorWrapper.h"

class XEWorld;
class XEEventList 
	: public XMemBase
	, public XClass
{
public:
	XEEventList() :m_pOwnerWorld(NULL){}
	virtual ~XEEventList();
	typedef XArray<XEEventBase*> EventArray;
	typedef IteratorWrapper<XEEventBase*> EventIterator;
public:
	X_FORCEINLINE void            SetWorld(XEWorld* pWorld){ m_pOwnerWorld = pWorld; }
	X_FORCEINLINE XEWorld*        GetWorld()const{ return m_pOwnerWorld; }
	X_FORCEINLINE static xbool    IsNullEvent(const XEEventBase* pEvent){ return pEvent != NULL_EVENT; }
	X_FORCEINLINE void            SetName(const XString& szName){ m_strName = szName; }
	X_FORCEINLINE const XString&  GetName()const{ return m_strName; }
	void                          PushBack(XEEventBase* pEvent);
	void                          PopBack();
	XString                       GetValidEventName(const xchar* pPrefix = "Event");
	XEEventBase*&                 Front();
	XEEventBase*&                 Back();
	xbool                         Remove(XEEventBase* pEvent);
	xbool                         Has(const XEEventBase* pEvent) const;
	XEEventBase*                  Find(const XString& szEventType, const XString& szEventName);
	xbool                         IsEmpty()const;
	EventIterator                 GetEventIterator() const;
	void                          Release();
	X_CLASS_DEF(XEEventList)
protected:						  
	static  XEEventBase*          NULL_EVENT;
	EventArray                    m_aEvents;
	XString                       m_strName;
	XEWorld*                      m_pOwnerWorld;//if the world owner is not null, can only be ticked and executed in the claim world.
public:
	static const XString          EVENT_LIST_FLEXIBLE_EVENT;//the events suit for the specific occasions flexibly, that means "flexible"
	static const XString          EVENT_LIST_GLOBAL_EVENT;//the events that outside the world. Maybe in the outer space?
	static const XString          EVENT_LIST_CUSTOM_EVENT;//events defined for custom-used.  will not be removed automatically.
};


#endif // _XE_EVENT_LIST_H
