//
// Created by momo783 on 13/05/2018.
//

#ifndef XES_XESLUACONVERSIONS_H
#define XES_XESLUACONVERSIONS_H

#include "core/XESDefine.h"
#include "core/XESGeometry.h"

extern "C" {
#include "lua.h"
#include "tolua++.h"
}

#include "XESLuaFix.h"

#include "XESLuaExport.h"

#include <map>
#include <unordered_map>
#include <vector>


#include "XUINode.h"
#include "XECore/XEActor.h"
#include "XAnimController.h"
#include "XEAnimController.h"
#include "platform/armodule/XESARModule.h"

using namespace XESCENE_NAMESPACE;

extern std::unordered_map<std::string, std::string> g_xe_luaType;

#if XES_DEBUG_LOG >= 1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err, const char* funcName = "");
#endif

extern bool luaval_to_int32(lua_State *L, int lo, int *outValue, const char *funcName = "");

extern bool luaval_to_number(lua_State *L, int lo, float *outValue, const char *funcName = "");

extern bool luaval_to_std_string(lua_State *L, int lo, std::string *outValue, const char *funcName = "");

template<class T>
void xmap_string_key_to_luaval(lua_State *L, const XHashTable<XString, T> &v) {
    lua_newtable(L);

    if (nullptr == L)
        return;

    xint32 index = 0;
    while (auto iter = v.NextNode(index)) {
        XString key = iter->key;
        T obj = iter->value;
        if (nullptr != dynamic_cast<XMemBase *>(obj)) {
            std::string name = typeid(*obj).name();
            auto typeIter = g_xe_luaType.find(name);
            if (g_xe_luaType.end() != typeIter) {
                lua_pushstring(L, key.CStr());
                toluafix_pushusertype(L, (void *) obj, typeIter->second.c_str());
                lua_rawset(L, -3);
            }
        }
    }
}

template<class T>
void array_to_luaval(lua_State *L, XArray<T> inValue) {
    lua_newtable(L);

    if (nullptr == L)
        return;

    std::string className = "";
    XString *strVal = nullptr;
    XHashTable<XString, T> *dictVal = nullptr;
    XArray<T> *arrVal = nullptr;
    xfloat64 *doubleVal = nullptr;
    xbool *boolVal = nullptr;
    xfloat32 *floatVal = nullptr;
    xint32 *intVal = nullptr;

    int indexTable = 1;

    for (xint32 i = 0; i < inValue.Num(); i++) {
        T obj = inValue[i];
        if (nullptr == obj)
            continue;

        std::string typeName = typeid(obj).name();
        auto iter = g_xe_luaType.find(typeName);
        if (g_xe_luaType.end() != iter) {
            className = iter->second;
            if (nullptr != dynamic_cast<XMemBase *>(obj)) {
                lua_pushnumber(L, (lua_Number) indexTable);
                toluafix_pushusertype(L, (void *) obj, className.c_str());
                lua_rawset(L, -3);
                //obj->retain();
                ++indexTable;
            }
        } else if ((strVal = (XString *) (obj))) {
            lua_pushnumber(L, (lua_Number) indexTable);
            lua_pushstring(L, strVal->CStr());
            lua_rawset(L, -3);
            ++indexTable;
        } else if ((dictVal = (XHashTable<XString, T> *) (obj))) {
            xmap_string_key_to_luaval(L, *dictVal);
        } else if ((arrVal = (XArray<T> *) (obj))) {
            array_to_luaval(L, *arrVal);
        } else if ((doubleVal = (xfloat64 *) (obj))) {
            lua_pushnumber(L, (lua_Number) indexTable);
            lua_pushnumber(L, (lua_Number) *doubleVal);
            lua_rawset(L, -3);
            ++indexTable;
        } else if ((floatVal = (xfloat32 *) (obj))) {
            lua_pushnumber(L, (lua_Number) indexTable);
            lua_pushnumber(L, (lua_Number) *floatVal);
            lua_rawset(L, -3);
            ++indexTable;
        } else if ((intVal = (xint32 *) (obj))) {
            lua_pushnumber(L, (lua_Number) indexTable);
            lua_pushinteger(L, (lua_Integer) *intVal);
            lua_rawset(L, -3);
            ++indexTable;
        } else if ((boolVal = (xbool *) (obj))) {
            lua_pushnumber(L, (lua_Number) indexTable);
            lua_pushboolean(L, *boolVal);
            lua_rawset(L, -3);
            ++indexTable;
        } else {
            XESAssert(false);// "the type isn't supported."
        }
    }
}

const char *typenameof(XClass *pObj);

const char *typenameof(XEActor *pObj);

const char *typenameof(XEActorComponent *pObj);

const char *typenameof(XAnimController *pObj);

const char *typenameof(XEAnimController *pObj);

const char *typenameof(AR::XEARAnchor *pObj);

const char *typenameof(XUINode *pObj);


#endif //XES_XESLUACONVERSIONS_H
