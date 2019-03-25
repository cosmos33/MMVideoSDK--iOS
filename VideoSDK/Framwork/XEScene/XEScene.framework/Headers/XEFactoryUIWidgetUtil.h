#ifndef _XEFACTORYUIWIDGETUTIL_H
#define _XEFACTORYUIWIDGETUTIL_H
#include "XPlatform.h"
#include  "XArray.h"
#include "XESingleton.h"

class XUINode;

class IXEUIWidgetFactory : public XMemBase
{
public:
	typedef XArray<IXEUIWidgetFactory*>			UIWIdgetFactoryArray;
	IXEUIWidgetFactory(const XString& _typeName):m_strTypeName(_typeName){}
	virtual ~IXEUIWidgetFactory(){}
public:

	virtual XUINode* CreateUIWidget() = 0;
	XString  GetFactoryType(){ return m_strTypeName; }

private:
	XString m_strTypeName;
};

// #define BUILD_UIWIDGETFACTORY(T, FN) \
// template<typename T> \
// class XEUIWidgetFactory_##FN : public IXEUIWidgetFactory \
// { \
// public: \
// 	XEUIWidgetFactory_##FN(const XString& _typeName) : IXEUIWidgetFactory(_typeName){} \
// 	virtual XUINode*  CreateUIWidget() \
// 	{ \
// 		T* pNode = T::##FN(); \
// 		return pNode; \
// 	} \
// };
// BUILD_UIWIDGETFACTORY(T, CreateWithTTF)
// BUILD_UIWIDGETFACTORY(T, Create)

template<typename T>
class XEUIWidgetFactory_Create : public IXEUIWidgetFactory
{
public:
	XEUIWidgetFactory_Create(const XString& _typeName) : IXEUIWidgetFactory(_typeName){}
	virtual XUINode*  CreateUIWidget()
	{
		T* pNode = T::Create();
		return pNode;
	}
};

template<typename T>
class XEUIWidgetFactory_CreateWithSystem : public IXEUIWidgetFactory
{
public:
	XEUIWidgetFactory_CreateWithSystem(const XString& _typeName) : IXEUIWidgetFactory(_typeName){}
	virtual XUINode*  CreateUIWidget()
	{
		T* pNode = T::CreateWithSystemFont();
		return pNode;
	}
};


#define CREATE_UIWIDGETFACTORY(T, FN, V) (new XEUIWidgetFactory_##FN<T>(V))


class XEUIWidgetFactoryManager
	: public XESingleton<XEUIWidgetFactoryManager>
{
public:
	XEUIWidgetFactoryManager() :m_bIsCollected(xfalse){}
	~XEUIWidgetFactoryManager();;
	void                       CollectFactory();
	void                       ReleaseFactory();
	IXEUIWidgetFactory*		   GetFactory(const XString &strComponentTypeName);
	xbool                      AddFactory(IXEUIWidgetFactory* pFactory);

	XArray<XString>			   GetAllFactoryType();

private:
	IXEUIWidgetFactory::UIWIdgetFactoryArray m_aUIWidgetFactories;
	xbool m_bIsCollected;
};
#endif//_XEFACTORYUIWIDGETUTIL_H