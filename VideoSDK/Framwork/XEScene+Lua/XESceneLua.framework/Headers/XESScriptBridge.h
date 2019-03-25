//
// Created by HongjieFu on 2018/7/2.
//

#ifndef PODS_XESLUABRIDGE_H
#define PODS_XESLUABRIDGE_H

#include  <functional>
#include "core/XESDefine.h"
#include "XESLuaStack.h"

XESCENE_NAMESPACE_BEGIN

class ScriptBridge {
    
public:
    typedef std::function<void(const char *)> CallbackFunc;
    
    static std::string call(const char *handler, const char *action, const char *message);
    
    XESS_MANUAL static void callAsync(const char *handler, const char *action, const char *message, CallbackFunc callback);
    
    XESS_IGNORE static const char *nativeCall(const char *handler, const char *action, const char *message);
    
    XESS_IGNORE static void nativeCallAsync(const char *handler, const char *action, const char *message, CallbackFunc callback);
    
private:
    
    static xuint32 g_callID;
    
    static XHashTable<XString, CallbackFunc> g_callbacks;
    
    static int luaCallback(lua_State *tolua_S);
    
};


XESCENE_NAMESPACE_END

#endif //PODS_XESLUABRIDGE_H
