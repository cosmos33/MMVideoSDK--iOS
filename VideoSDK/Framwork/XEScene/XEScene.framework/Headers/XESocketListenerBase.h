/******************************************************************************

@File         XESocketListenerBase.h

@Version       1.0

@Created      2018, 2, 6

@HISTORY:

******************************************************************************/
#ifndef XE_SOCKET_LISTENER_UTILITY_H
#define XE_SOCKET_LISTENER_UTILITY_H

//instance only.
#include "XEBindSocketInstance.h"
#include "tinyxml2_XEngine.h"
using namespace tinyxml2_XEngine;

class XESocketListenerBase 
	: public XEBindSocketInstance::Listener
{
public:
	XESocketListenerBase() : m_strListenerName("Unknown"){}
	virtual ~XESocketListenerBase(){}
	typedef XArray<XESocketListenerBase*> SocketListenerBaseList;
public:
	virtual const XString          GetName() const override{ return m_strListenerName; }
	virtual void                   SetName(const XString& strName) override{ m_strListenerName = strName; }
	virtual const XString          GetTypeName() const = 0;
	template<typename T>
	T* CastSocketListener()
	{
		return dynamic_cast<T>(this);
	}
protected:
	XString m_strListenerName; 
};

#endif // XE_SOCKET_LISTENER_UTILITY_H
