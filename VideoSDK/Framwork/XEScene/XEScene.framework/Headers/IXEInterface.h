#ifndef _XE_IXEINTERFACE_H_
#define _XE_IXEINTERFACE_H_

#include <functional>
#include <map>
#include <string>
#include <sstream>

typedef unsigned long IX_OBJ_PTR;
class IXEInterface;
struct FuncHolder
{
	FuncHolder(const char* n, IXEInterface* i) :func_name_(n), func_interface_(i){}
	std::string func_name_;
	IXEInterface* func_interface_;
	bool operator < (const FuncHolder& fh) const
	{
		std::ostringstream ss,fh_ss;
		   ss << (IX_OBJ_PTR)func_interface_
			  << '.'
			  << func_name_
			  << '\0';
		fh_ss << (IX_OBJ_PTR)fh.func_interface_
			  << '.' 
			  << fh.func_name_ 
			  << '\0';
		return ss.str() < fh_ss.str();
	}
	bool operator == (const FuncHolder& fh) const
	{
		return func_name_ == fh.func_name_ && func_interface_ == fh.func_interface_;
	}
};
typedef std::function<IXEInterface*(void)> ConstructInterface;
struct ObjectHolder
{
	ObjectHolder(const char* n, const ConstructInterface& c) :class_name_(n), construct_method_(c){}
	std::string class_name_;
	ConstructInterface construct_method_;
};

template<typename T>
class ClassAutoCollector
{
public:
	ClassAutoCollector(){ T::CollectClass(); }
	virtual ~ClassAutoCollector(){}
};

//typedef xbase::hash_map<XString, XENode*> XENodeMap;


typedef std::map<FuncHolder, void*> FunctionMap;
typedef std::map<IX_OBJ_PTR, ObjectHolder> ObjectMap;
typedef std::map<std::string, ConstructInterface> InterfaceMap;

class IXEInterface
{
public:
			 IXEInterface(){}
	virtual ~IXEInterface(){}
public:
	virtual void RegisterFuncMap(const char* funcName, ...){}
	static FunctionMap& GetFuncMap()
	{
		static FunctionMap insFuncMap;
		return insFuncMap;
	}
	static void* GetFunc(const char* funcName, IXEInterface* obj)
	{
		auto f = GetFuncMap().find(FuncHolder(funcName, obj));
		if (f == GetFuncMap().end()) return NULL;
		return f->second;
	}
	static ObjectMap& GetObjMap()
	{
		static ObjectMap objMap;
		return objMap;
	}
	static InterfaceMap& GetInterfaceMap()
	{
		static InterfaceMap interafceMap;
		return interafceMap;
	}
	static IXEInterface* MirrorXEInterface(const IXEInterface* src)
	{
		auto i = GetObjMap().find((IX_OBJ_PTR)src);
		if (i == GetObjMap().end()) return NULL;
		return i->second.construct_method_();
	}
	static IXEInterface* PawnXEInterface(const char* className)
	{
		auto i = GetInterfaceMap().find(className);
		if (i == GetInterfaceMap().end())
			return NULL;
		return i->second();
	}
	static const char* GetInterfaceClass(const IXEInterface* obj)
	{
		auto i = GetObjMap().find((IX_OBJ_PTR)obj);
		if (i == GetObjMap().end()) return NULL;
		return i->second.class_name_.c_str();
	}
};

#define MACRO_STR_MATCH(a,b) 0 == strcmp(#a, b)
#define MACRO_FUNC_DEF(funcType,funcName) typedef std::function<funcType> Func_##funcName
#define MACRO_FUNC_USE(funcClass,funcName) funcClass##::Func_##funcName
#define MACRO_FUNC_CREATE(funcClass,fName,obj) funcClass##::CreateXEFunction(#fName,obj)
#define MACRO_FTC(funcName) #funcName
#define MACRO_FUNC_REG_CREATE(funcFirstName, ...) RegisterFuncMap(funcFirstName,__VA_ARGS__,NULL)
#define MACRO_FUNC_REG_DEF() void RegisterFuncMap(const char* funcName, ...){\
	va_list ap;\
	va_start(ap, funcName);\
	const char* x = funcName;\
				while(NULL != x){\
	IXEInterface::GetFuncMap().insert(std::make_pair(FuncHolder(x,this),CreateXEFunction(x, this)));\
	x = va_arg(ap, char *);\
	}\
	va_end(ap);\
}
#define MACRO_FUNC_GET(funcName,caller) IXEInterface::GetFunc(#funcName,caller)
#define MACRO_FUNC_GET_BYVAL(funcVal,caller) IXEInterface::GetFunc(funcVal,caller)

#define MACRO_INTERFACE_DEF()\
static NATIVEBUNDLE_EXPORT IXEInterface* CreateXEInterface();\
static NATIVEBUNDLE_EXPORT void* CreateXEFunction(const char* pFunctionName, IXEInterface* obj);
#define MARCRO_INTERFACE_DEF_BODY(className)\
IXEInterface* className##::CreateXEInterface()
#define MARCRO_INTERFACE_FUNC_DEF_BODY(className)\
void* className##::CreateXEFunction(const char* pFunctionName, IXEInterface* obj)

#define MACRO_CLASS_COLLECT_DEF(className)\
static ClassAutoCollector<##className##> classCollector_;\
static void CollectClass();
#define MARCRO_CLASS_COLLECT_BODY_DEF(className)\
ClassAutoCollector<className##> className##::classCollector_;\
void className##::CollectClass()


#define MACRO_INTERFACE_CREATE(funcClass) funcClass##::CreateXEInterface()
#define MARCRO_INTERFACE_MIRROR(obj) IXEInterface::MirrorXEInterface(obj)
#define MARCRO_INTERFACE_PAWN(className) IXEInterface::PawnXEInterface(className)
#define MARCRO_INTERFACE_NAME(obj) IXEInterface::GetInterfaceClass(obj)

#define MACRO_INTERFACE_REG_DEF(objClass)\
IXEInterface::GetInterfaceMap().insert(std::make_pair(#objClass,CreateXEInterface))

#define MACRO_INTERFACE_REG_OBJ(obj,objClass)\
IXEInterface::GetObjMap().insert(std::make_pair((IX_OBJ_PTR)obj, ObjectHolder(#objClass, CreateXEInterface)));\
return obj

#endif