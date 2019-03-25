/******************************************************************************

@File         XEFactoryEventUtil.h

@Version       1.0

@Created      2018,6,12

@HISTORY:

******************************************************************************/
#ifndef _XE_FACTORY_EVENT_UTILITY_H
#define _XE_FACTORY_EVENT_UTILITY_H

#include "XEEventBase.h"
#include "XArray.h"
#include "XESingleton.h"

class IXEEventFactory : public XMemBase
{
public:
	typedef XArray<IXEEventFactory*> XEEventFactoryArray;
	IXEEventFactory(){}
	virtual ~IXEEventFactory(){}
public:
	virtual XEEventBase*                              CreateEvent() = 0;
	virtual const XString&	                          GetEventTypeName() = 0;
};

template<typename T>
class XEEventFactory : public IXEEventFactory
{
public:
	virtual XEEventBase*                              CreateEvent() override;
	virtual const XString&	                          GetEventTypeName() override;
};

class XEEventFactoryManager
	: public XESingleton<XEEventFactoryManager>
{
public:
	XEEventFactoryManager() :m_bIsCollected(xfalse){}
	~XEEventFactoryManager();
	void                                              CollectFactory();
	void                                              ReleaseFactory();
	IXEEventFactory*	                              GetFactory(const XString &strEventTypeName);
	xbool                                             AddFactory(IXEEventFactory* pFactory);
	const IXEEventFactory::XEEventFactoryArray&       GetFactoryList() const;
private:
	template<typename T>
	xbool                                             _Register();

private:
	IXEEventFactory::XEEventFactoryArray m_aFactories;
	xbool m_bIsCollected;
};

template<typename T>
class __EVENT_AUTO_REG
{
public:
	__EVENT_AUTO_REG();
};

//implement with template
template<typename T>
XEEventBase* XEEventFactory<T>::CreateEvent()
{
	T* pEvent = new T;
	return pEvent;
}

template<typename T>
const XString& XEEventFactory<T>::GetEventTypeName()
{
	return T::EVENT_TYPENAME;
}

template<typename T>
xbool XEEventFactoryManager::_Register()
{
	IXEEventFactory* pFactory = new XEEventFactory<T>();
	if (!AddFactory(pFactory))
	{
		X_SAFEDELETE(pFactory);
		return xfalse;
	}
	return xtrue;
}

template<typename T>
__EVENT_AUTO_REG<T>::__EVENT_AUTO_REG()
{
	IXEEventFactory* pFactory = new XEEventFactory<T>();
	if (!XEEventFactoryManager::GetInstance()->AddFactory(pFactory))
		X_SAFEDELETE(pFactory);
}

//warning: use this in the executable-module-only(outer.)
#define REGISTER_EVENT_FACTORY(T) static __EVENT_AUTO_REG<T> ar

#endif // _XE_FACTORY_EVENT_UTILITY_H
