/******************************************************************************

@File         XEActorFactory.h

@Version       1.0

@Created      2017,9, 20

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_FACTORY_ACTOR_UTIL_H
#define _XE_FACTORY_ACTOR_UTIL_H
#include "XMemBase.h"
#include "XArray.h"
#include "XESingleton.h"

class XEActor;
class XEWorld;
class IXEActorFactory : public XMemBase
{
public:
    typedef XArray<IXEActorFactory*> ActorFactoryArray;
    IXEActorFactory(){}
    virtual ~IXEActorFactory(){}
public:
	virtual XEActor*           CreateActor(XEWorld* pWorld, const xchar* pActorName = NULL) = 0;
	virtual const XString&     GetActorTypeName() = 0;
    virtual void               ReleaseActor(XEActor *pActor);
};

template<typename T>
class XEActorFactory : public IXEActorFactory
{
public:
    virtual XEActor*          CreateActor(XEWorld* pWorld, const xchar* pActorName = NULL);    
    virtual const XString&    GetActorTypeName();
};

class XEActorFactoryManager
: public XESingleton<XEActorFactoryManager>
{
public:
	XEActorFactoryManager() :m_bIsCollected(xfalse){}
    ~XEActorFactoryManager();
	void                                  CollectFactory();
	void                                  ReleaseFactory();
    IXEActorFactory::ActorFactoryArray&   GetFactoryList(){ return m_aActorFactories; }
    IXEActorFactory*                      GetFactory(const XString &strActorTypeName);
    xbool                                 AddFactory(IXEActorFactory* pFactory);
private:
	template<typename T>
	xbool                                 _Register();
	void                                  _RegSystemMetaCollisionChannel(const XString& strActorTypeName);
private:
    IXEActorFactory::ActorFactoryArray m_aActorFactories;
	xbool m_bIsCollected;
};

template<typename T>
class __ACTOR_AUTO_REG
{
public:
	__ACTOR_AUTO_REG();
};

//implement with template.
template<typename T>
XEActor* XEActorFactory<T>::CreateActor(XEWorld* pWorld, const xchar* pActorName /*= NULL*/)
{
	T* p = new T;
	if (NULL != pActorName)
		p->SetActorName(pActorName, pWorld);
	p->Initialize(pWorld);
	return p;
}

template<typename T>
const XString& XEActorFactory<T>::GetActorTypeName()
{
	return T::ACTOR_TYPENAME;
}

template<typename T>
xbool XEActorFactoryManager::_Register()
{
	IXEActorFactory* pFactory = new XEActorFactory<T>();
	if (!AddFactory(pFactory))
	{
		X_SAFEDELETE(pFactory);
		return xfalse;
	}
	//THE TYPE OF THE ACTOR.
	_RegSystemMetaCollisionChannel(T::ACTOR_TYPENAME);
	return xtrue;
}

template<typename T>
__ACTOR_AUTO_REG<T>::__ACTOR_AUTO_REG()
{
	IXEActorFactory* pFactory = new XEActorFactory<T>();
	if (!XEActorFactoryManager::GetInstance()->AddFactory(pFactory))
		X_SAFEDELETE(pFactory);
}

//warning: use this in the executable-module-only(outer.)
#define REGISTER_ACTOR_FACTORY(T) static __ACTOR_AUTO_REG<T> aar

#endif // _XE_FACTORY_ACTOR_UTIL_H
