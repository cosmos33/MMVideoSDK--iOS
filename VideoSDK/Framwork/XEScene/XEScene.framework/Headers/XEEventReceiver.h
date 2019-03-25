/******************************************************************************

@File         XEReceiver.h

@Version       1.0

@Created      2018,6,15

@HISTORY:

******************************************************************************/
#ifndef _XE_EVENT_RECEIVER_H
#define _XE_EVENT_RECEIVER_H
#include "XMemBase.h"
#include "XString.h"
#include "XClassReflector.h"
class XEWorld;
class XEEventBase;
class XEEventReceiver
	: public XMemBase
	, public XClass
{
public:
	XEEventReceiver();
	virtual ~XEEventReceiver();
public:
	virtual XEWorld*             GetReceiverWorld(){ return NULL; }//the receiver channel world.
	virtual void                 SetReceiverWorld(XEWorld* pWorld){}
	virtual const XString&       GetReceiverChannel() const{ return RC_CHANNEL; }
	virtual void                 RespondOnEvent(XEEventBase* pEvent){};
	virtual void                 RespondOnEventTick(XEEventBase* pEvent, xfloat32 fInterval){};//in milliseconds.
	X_FORCEINLINE void           SetName(const XString& szName){ m_strChannelName = szName; }
	X_FORCEINLINE const XString& GetName()const{ return m_strChannelName; }
	template<typename T>
	T*                           CastReceiver();
	static const  XString        RC_CHANNEL;
	X_CLASS_DEF(XEEventReceiver)
protected:
	XString                      m_strChannelName;
};

template<typename T>
T* XEEventReceiver::CastReceiver()
{
	if (T::RC_CHANNEL == GetReceiverChannel())
		return static_cast<T*>(this);
	return NULL;
}


static xbool __matchAnyChannel(const xchar* c0, ...)
{
	if (NULL == c0)
		return xfalse;
	XString szChannelBend = c0;
	va_list ap;
	va_start(ap, c0);
	for (const xchar* x = va_arg(ap, xchar*); NULL != x; x = va_arg(ap, xchar*))
	{
		if (0 == szChannelBend.CompareNoCase(x))
		{
			va_end(ap);
			return xtrue;
		}
	}
	va_end(ap);
	
	return xfalse;
}
#define XE_EVENT_CHANNEL_TYPE_DEF(T) virtual const XString& GetReceiverChannel() const override{ return T; }
#define XE_MATCH_ANY_CHANNEL(c0,...) __matchAnyChannel(c0,__VA_ARGS__, NULL)
#endif // _XE_EVENT_RECEIVER_H
