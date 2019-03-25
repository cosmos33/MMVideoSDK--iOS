/******************************************************************************

@File         XEEventManager.h

@Version       1.0

@Created      2018,6,12

@HISTORY:

******************************************************************************/
#ifndef _XE_EVENT_MANAGER_H
#define _XE_EVENT_MANAGER_H
#include "XESingleton.h"
#include "XEEventList.h"
#include "XEIteratorWrapper.h"
#include "XEGame.h"

//further more, add channels to event,please.
class XEEventManager 
	: public XESingleton<XEEventManager>
	, public XEGame::TickListener
{
public:
	XEEventManager();
	~XEEventManager();
	typedef XArray<XEEventList*>          EventListArray;
	typedef XArray<XEEventReceiver*>      EventReceiverArray;
	typedef IteratorWrapper<XEEventList*> EventListIterator;
protected:
	virtual  void      Tick(xfloat32 fDel);//in seconds. to tick the event list whose owner world is null.
	void               BroadcastEvent(XEWorld* pBroadcastWorld, XEEventBase* pEventToBroadcast);//broadcast the event in the world, the world may be NULL.
public:
	void               Tick(xfloat32 fDel, XEWorld* pWorld);//in seconds.to tick the event list with the claim owner world. 
	XEEventBase*       SendEvent(XEEventBase::Sender sender, XEEventBase::Executeable executeable, const xchar* pEventType, XEWorld* pWorld);//put in an event with the claim type of the specific world. return the event instance that has been put in.
	xbool              ConsumeEventNow(XEEventBase* pEventToConsume, XEWorld* pWorld);//usally is the custom event. remove it by manual.
	void               AddEventReceiver(XEEventReceiver* pReceiver);//weak pointer.
	xbool              RemoveEventReceiver(XEEventReceiver* pReceiver);//weak pointer.
	XEEventList*       CreateEventList(XEWorld* pWorld = NULL,const xchar* pListName = NULL);//if the listName is NULL, will give a unique one.
	xint32             GetEventListForWorld(const XEWorld* pWorld, EventListArray& ea);
	xint32             GetEventListForName(const xchar* pName, EventListArray& ea);
	xint32             GetEventReceiversForChannel(const xchar* pChannelName, EventReceiverArray& era);//warning: the receiver will not release the memory. Release it by yourself.
	XEEventReceiver*   FindEventReceiver(const xchar* pChannelName, const xchar* pReceiverName);
	XEEventList*       FindEventList(const XEWorld* pWorld, const xchar* pName);
	XString            GetValidEventListName(const xchar* pPrefix = "EventList");
	XString            GetValidEventReceiverName(const xchar* pPrefix = "EventReceiver");
	EventListIterator  GetEventListIterator() const;
	void               Release();
	void               ReleaseEventsInWorld(const XEWorld* pWorld);

public:
	//export scripting support
	static XEEventManager* GetManager();
protected:
	EventListArray     m_aEventLists;
	EventReceiverArray m_aEventRecivers;
};

#endif // _XE_EVENT_MANAGER_H
