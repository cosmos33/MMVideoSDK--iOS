/******************************************************************************

@File         XClassReflector.h

@Version       1.0

@Created      2018/12/17

@HISTORY:

******************************************************************************/
#ifndef _XE_CLASS_REFLECTOR_H_
#define _XE_CLASS_REFLECTOR_H_
#include "XString.h"
#include "XArray.h"
#include "XClass.h"

#define X_CLASS_REGISTER(T) static xbool __class_reg_single = XClassReflector::RegisterClass<T>(#T)
#define X_CLASS_REGISTER_MULTI(T, K) static xbool __class_reg_##K = XClassReflector::RegisterClass<T>(#T)
#define X_SPAWN_INSTANCE_FROM_CLASS_NAME(C) XClassReflector::New(C)
#define X_SPAWN_INSTANCE_WITH_INSTANCE(I) XClassReflector::New(I->GetClassName())

class XClassExtend
	:public XClass
{
public:
	virtual ~XClassExtend(){}
	virtual const xchar* GetClassName()const override{ return "XClassExtend"; }
	virtual void* New(){ return NULL; }
};

class XClassReflector
{
public:
	virtual ~XClassReflector(){}
public:
	template<typename T, typename N>
    static xbool RegisterClass(const N& n);
	template<typename T>
	static T* Cast(void* instance)
	{
		return reinterpret_cast<T*>(instance);
	}
	static XArray<XClassExtend*>& GetClassContainer();
	static void* New(XClass* instance);
	static void* New(const XString& szClassName);
	static XString GetClassStatiitics();
protected:
	struct XClassContainer
	{
		XArray<XClassExtend*> _container;
		~XClassContainer();
	};
};

template<typename T>
class XClassReflectorWithType
	:public XClassExtend
{
public:
	XClassReflectorWithType(const XString& szName){ _name = szName; }
	virtual const xchar* GetClassName()const override{ return _name.CStr(); }
protected:
	virtual void* New() override
	{
		return new T();
	}
	XString _name;
};

template<typename T,typename N>
xbool XClassReflector::RegisterClass(const N& n)
{
    XString s(n);
	XArray<XClassExtend*>& container = GetClassContainer();
    for (xint32 i = 0; i < container.Num(); ++i)
    {
        if (0 == s.CompareNoCase(container[i]->GetClassName()))
            return xfalse;
    }
    container.Add(new XClassReflectorWithType<T>(s));
    return xtrue;
}

#endif // _XE_CLASS_REFLECTOR_H_
