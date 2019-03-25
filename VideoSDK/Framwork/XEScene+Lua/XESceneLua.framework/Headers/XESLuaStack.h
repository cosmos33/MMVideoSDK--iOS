//
// Created by momo783 on 13/05/2018.
//

#ifndef XES_XESLUASTACK_H
#define XES_XESLUASTACK_H

#include "core/XESObject.h"
#include "XESLuaValue.h"
#include "XEncryptionDog.h"

extern "C" {
#include "lua.h"
#include "tolua++.h"
};

#include <functional>

XESCENE_NAMESPACE_BEGIN

class LuaStack : public Object {

public:

    static LuaStack* Create();

    static LuaStack* Attach(lua_State *L);

    virtual ~LuaStack() override;

    void Release() override;

    X_INLINE lua_State* GetLuaState() const { return m_LuaState; }
    
    virtual void    AddSearchPath(const char* path);
    
    virtual void    AddLuaLoader(lua_CFunction func);
    
    virtual int     Reload(const char* moduleFileName);
    
    virtual void    RemoveScriptObjectByObject(void* object);
    
    virtual void    RemoveScriptHandler(int nHandler);
    
    virtual int     ReallocateScriptHandler(int nHandler);
    
    virtual int     ExecuteString(const xchar *codes, xbool bAsScript = xfalse);
    
    virtual int     ExecuteScriptFile(const XString& filename);
    
    virtual int     ExecuteGlobalFunction(const XString& functionName);
    
    virtual void    Clean(void);
    
    virtual void    PushInt(int intValue);
    virtual void    PushFloat(float floatValue);
    virtual void    PushLong(long longValue);
    virtual void    PushBoolean(bool boolValue);
    virtual void    PushString(const char* stringValue);
    virtual void    PushString(const char* stringValue, int length);
    virtual void    PushNil(void);
    virtual void    PushObject(void* objectValue, const char* typeName);
    virtual void    PushLuaValue(const LuaValue& value);
    virtual void    PushLuaValueDict(const LuaValueDict& dict);
    virtual void    PushLuaValueArray(const LuaValueArray& array);
    virtual bool    PushFunctionByHandler(int nHandler);

    virtual int     ExecuteFunction(int numArgs);

    virtual int     ExecuteFunctionByHandler(int nHandler, int numArgs);

    template <class T>
            int     ExecuteFunctionReturnArray(int handler,int numArgs,int numResults,XArray<T>& resultArray);

    virtual int     ExecuteFunction(int handler, int numArgs, int numResults, const std::function<void(lua_State*,int)>& func);

    virtual bool    HandleAssert(const XString& msg);

    int LuaLoadBuffer(lua_State *L, const char *chunk, int chunkSize, const char *chunkName,xbool encrypted = xfalse);

    std::string CombinString(const char* str1, const char* str2);

    void SetSecretKey(const char *key);
private:

    std::string DecodeStr(const char* Data,int DataByte,int& OutByte);

protected:
    LuaStack()
    : m_LuaState(nullptr)
    ,m_nCallFromLua(0) {};

    xbool Init();
    xbool InitWithLuaState(lua_State *L);

    lua_State* m_LuaState;

    xint32 m_nCallFromLua;
    
    XEncryptionDog m_dog;

};

template <class T>
int LuaStack::ExecuteFunctionReturnArray(int handler,int numArgs,int numResults,XArray<T>& resultArray)
{
    int top = lua_gettop(m_LuaState);
    if (PushFunctionByHandler(handler))                 /* L: ... arg1 arg2 ... func */
    {
        if (numArgs > 0)
        {
            lua_insert(m_LuaState, -(numArgs + 1));         /* L: ... func arg1 arg2 ... */
        }
        int functionIndex = -(numArgs + 1);
        if (!lua_isfunction(m_LuaState, functionIndex))
        {
            XESLog("value at stack [%d] is not function", functionIndex);
            lua_pop(m_LuaState, numArgs + 1); // remove function and arguments
            lua_settop(m_LuaState,top);
            return 0;
        }

        int traceback = 0;
        lua_getglobal(m_LuaState, "__G__TRACKBACK__");                         /* L: ... func arg1 arg2 ... G */
        if (!lua_isfunction(m_LuaState, -1))
        {
            lua_pop(m_LuaState, 1);                                            /* L: ... func arg1 arg2 ... */
        }
        else
        {
            lua_insert(m_LuaState, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
            traceback = functionIndex - 1;
        }

        int error = 0;
        ++m_nCallFromLua;
        error = lua_pcall(m_LuaState, numArgs, numResults, traceback);                  /* L: ... [G] ret1 ret2 ... retResults*/
        --m_nCallFromLua;
        if (error)
        {
            if (traceback == 0)
            {
                XESLog("[LUA ERROR] %s", lua_tostring(m_LuaState, - 1));        /* L: ... error */
                lua_pop(m_LuaState, 1); // remove error message from stack
            }
            else                                                            /* L: ... G error */
            {
                lua_pop(m_LuaState, 2); // remove __G__TRACKBACK__ and error message from stack
            }
            lua_settop(m_LuaState,top);
            return 0;
        }

        // get return value,don't pass LUA_MULTRET to numResults,
        if (numResults <= 0)
        {
            lua_settop(m_LuaState,top);
            return 0;
        }

        for (int i = 0 ; i < numResults; i++)
        {
            if (lua_type(m_LuaState, -1) == LUA_TBOOLEAN) {

                bool value = lua_toboolean(m_LuaState, -1);
                resultArray.Add(value);

            }else if (lua_type(m_LuaState, -1) == LUA_TNUMBER) {

                double value = lua_tonumber(m_LuaState, -1);
                resultArray.Add(value);

            }else if (lua_type(m_LuaState, -1) == LUA_TSTRING) {

                const char* value = lua_tostring(m_LuaState, -1);
                resultArray.Add(XString(value));

            }else{

                resultArray.Add(static_cast<XMemBase*>(tolua_tousertype(m_LuaState, -1, nullptr)));
            }
            // remove return value from stack
            lua_pop(m_LuaState, 1);                                                /* L: ... [G] ret1 ret2 ... ret*/
        }
        /* L: ... [G]*/

        if (traceback)
        {
            lua_pop(m_LuaState, 1); // remove __G__TRACKBACK__ from stack      /* L: ... */
        }
    }
    lua_settop(m_LuaState,top);
    return 1;
}

XESCENE_NAMESPACE_END

#endif //XES_XESLUASTACK_H
