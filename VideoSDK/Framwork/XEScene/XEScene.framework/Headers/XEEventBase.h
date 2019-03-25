/******************************************************************************

@File         XEEventBase.h

@Version       1.0

@Created      2018,6,12

@HISTORY:

******************************************************************************/
#ifndef _XE_EVENT_BASE_H
#define _XE_EVENT_BASE_H
#include "XMemBase.h"
#include "XString.h"
#include "XArray.h"
#include "XEVariant.h"
#include "XClassReflector.h"
#include "XEEventReceiver.h"

class XEEventList;
class XEWorld;

enum eEventStatus
{ 
	EVENT_STATUS_READY, 
	EVENT_STATUS_EXPLAIN,
	EVENT_STATUS_ENTRANCE, 
	EVENT_STATUS_TRIGGER, 
	EVENT_STATUS_RESTORE, 
	EVENT_STATUS_CUSTOM, 
	EVENT_STATUS_RELEASE,
};//reference by others.

class XEEventBase
	: public XMemBase
	, public XClass
{
	friend class XEEventManager;
public:
	enum eEventRemoveMode{ ERM_AUTO, ERM_MANUAL };
	enum eEventExecuteMode{ EEM_AUTO, EEM_MANUAL };
	XEEventBase() :m_fEventCountdown(0.f), m_bRemoved(xfalse), m_eEventRemoveMode(ERM_AUTO), m_eEventExecuteMode(EEM_AUTO), m_bTickable(xtrue), m_sender(NULL), m_executable(NULL), m_eEventStatus(EVENT_STATUS_READY){}
	virtual ~XEEventBase(){}
	class Listener
	{
		friend class XEEventBase;
	protected:
		virtual void                           Ls_OnCountdowning(XEEventBase* pEvent, xbool bFinished, xfloat32 fcurTime);//indicated that whether the counting-down is finished or not.
	};
	typedef XArray<Listener*>                  ListenerArray;
	typedef void*                              Sender;
	typedef void*                              Executeable;
public:
	virtual void                               Tick(xfloat32 fInterval);//in milliseconds.
	virtual void                               Release(){}
	virtual void                               Execute(XEWorld* pWorld = NULL){}
	virtual xbool                              IsReceiverInChannel(const XString& szChannelName) const{ return xtrue; }//to determine the channel here.
	virtual XEEventList*                       GetEventList(XEWorld* pWorld = NULL, xbool* pHasTheEvent = NULL);//override this if you want to change the event list. World of NULL as default
	virtual const XString&                     GetTypeName()const{ return EVENT_TYPENAME; }
	X_FORCEINLINE void                         SetData(const XEVariant& val){ m_eventData = val; }
	X_EES_LINE X_FORCEINLINE const XEVariant&  GetData()const{ return m_eventData; }
	X_FORCEINLINE XEVariant&                   GetData(){ return m_eventData; }
	X_FORCEINLINE void                         SetSender(Sender who){ m_sender = who; }
	X_FORCEINLINE Sender                       GetSender()const{ return m_sender; }
	X_FORCEINLINE void                         SetExcutable(Executeable what){ m_executable = what; }
	X_FORCEINLINE Executeable                  GetExcutable()const{ return m_executable; }
	X_FORCEINLINE void                         SetName(const XString& szName){ m_strEventName = szName; }
	X_FORCEINLINE const XString&               GetName() const{ return m_strEventName; }
	X_FORCEINLINE void                         AddListener(Listener* pListener){ m_aListeners.AddUnique(pListener); }
	X_FORCEINLINE xbool                        RemoveListener(Listener* pListener){ return m_aListeners.Remove(pListener); }
	X_FORCEINLINE void                         SetRemove(){ m_bRemoved = xtrue; }
	X_FORCEINLINE xbool                        IsRemoved(){ return m_bRemoved; }
	X_FORCEINLINE void                         SetRemoveMode(eEventRemoveMode erm){ m_eEventRemoveMode = erm; }
	X_FORCEINLINE eEventRemoveMode             GetRemoveMode()const{ return m_eEventRemoveMode; }
	X_FORCEINLINE void                         SetExecuteMode(eEventExecuteMode eem){ m_eEventExecuteMode = eem; }
	X_FORCEINLINE eEventExecuteMode            GetExecuteMode()const{ return m_eEventExecuteMode; }
	X_FORCEINLINE void                         SetReserve(){ m_bRemoved = xfalse; }
	X_FORCEINLINE void                         SetTickable(xbool bEnable){ m_bTickable = bEnable; }
	X_FORCEINLINE xbool                        IsTickable(){ return m_bTickable; }
	X_FORCEINLINE void                         SetCountdownTime(xfloat32 fMilliseconds){ m_fEventCountdown = fMilliseconds; }
	X_FORCEINLINE xfloat32                     GetCountdownTime()const{ return m_fEventCountdown; }
	X_FORCEINLINE void                         SetEventStatus(eEventStatus erm){ m_eEventStatus = erm; }
	X_FORCEINLINE eEventStatus                 GetEventStatus()const{ return m_eEventStatus; }//is ready to execute?
	X_CLASS_DEF(XEEventBase)
public:
	template<typename T>
	T*                                         GetSender() const;
	template<typename T>		              
	T*                                         GetExecuteable() const;
protected:						              
	virtual void                               ProcessFromReceiver(XEEventReceiver* rc);
public:							              
	static const XString                       EVENT_TYPENAME;
protected:						              
	XString                                    m_strEventName;
	xfloat32                                   m_fEventCountdown;//in milliseconds.
	eEventRemoveMode                           m_eEventRemoveMode;//auto by default.
	eEventExecuteMode                          m_eEventExecuteMode;//auto by default.
	ListenerArray                              m_aListeners;
	xbool                                      m_bRemoved;
	xbool                                      m_bTickable;//can be ticked?
	Sender                                     m_sender;
	Executeable                                m_executable;
	XEVariant                                  m_eventData;
	eEventStatus				               m_eEventStatus;
};
template<typename T>
T* XEEventBase::GetSender() const
{
	return reinterpret_cast<T*>(m_sender);
}

template<typename T>
T* XEEventBase::GetExecuteable() const
{
	return reinterpret_cast<T*>(m_executable);
}

#define XE_EVENT_TYPE_DEF(T)         virtual const XString& GetTypeName()const override{return T;}
#endif // _XE_EVENT_BASE_H
