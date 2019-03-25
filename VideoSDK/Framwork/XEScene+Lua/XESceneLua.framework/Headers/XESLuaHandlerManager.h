//
// Created by momo783 on 14/05/2018.
//

#ifndef XES_XESLUAHANDLERMANAGER_H
#define XES_XESLUAHANDLERMANAGER_H

#include "core/XESObject.h"

extern "C" {
#include "tolua++.h"
}
#include <map>
#include <vector>

XESCENE_NAMESPACE_BEGIN

class LuaHandlerManager : public Object {

public:
    enum class HandlerType : xint32 {

        ACTOR           = 0,
        CALL_FUNC       = 1,
        TOUCHS          = 2,
        ACCELEROMETER   = 3,

        EVENT_ACC           = 10,
        EVENT_CUSTOM        = 11,

        EVENT_TOUCH_BEGAN       = 12,
        EVENT_TOUCH_MOVED       = 13,
        EVENT_TOUCH_ENDED       = 14,
        EVENT_TOUCH_CANCELLED   = 15,

        EVENT_TOUCHES_BEGAN     = 16,
        EVENT_TOUCHES_MOVED     = 17,
        EVENT_TOUCHES_ENDED     = 18,
        EVENT_TOUCHES_CANCELLED = 19,

        EVENT_FACE_LOST         = 20,
        EVENT_FACE_TRACKING     = 21,

        EVENT_ATTITUDE          = 22,
        EVENT_ACCELEROMETER     = 23,

        EVENT_SCHEDULE_CALLBACK = 24,

        XEANIMATIONPLAY_STEPMOVE_CALLNACK = 27,
        XEANIMATIONPLAY_PLAYSTATECHANGE_CALLNACK = 28,
        XEANIMATIONPLAY_ONETIMEFINISHED_CALLNACK = 29,

        ARSESSIONSTATUS_ADD         = 30,
        ARSESSIONSTATUS_UPDATE      = 31,
        ARSESSIONSTATUS_REMOVE      = 32,
        
        EVENT_HAND_CALLBACK         = 33,
        EVENT_OBJECT_CALLBACK       = 34,
        EVENT_BODY_CALLBACK         = 35,
        EVENT_EXPRESSION_CALLBACK   = 36,

        EVENT_CUSTOM_BEGAN = 10000,
        EVENT_CUSTOM_ENDED = 11000,

    };

    typedef xint32 Handler;
    typedef std::pair<HandlerType, Handler> HandlerPair;
    typedef std::vector<HandlerPair> VecHandlerPairs;
    typedef std::map<void*,VecHandlerPairs> MapObjectHandlers;

public:

    static  LuaHandlerManager* GetInstance();

    static void DestoryInstance();

    void AddObjectHandler(void* object,Handler handler,LuaHandlerManager::HandlerType handlerType);

    void RemoveObjectHandler(void* object,LuaHandlerManager::HandlerType handlerType);

    Handler GetObjectHandler(void* object,LuaHandlerManager::HandlerType handlerType);

    void RemoveObjectAllHandlers(void* object);

    LuaHandlerManager::HandlerType AddCustomHandler(void* object, Handler handler);

public:

    LuaHandlerManager();

    ~LuaHandlerManager() override;

    void Release() override;

private:

    void Init(void);

    MapObjectHandlers m_mapObjectHandlers;

    static LuaHandlerManager* g_LuaHandlerManager;

};

XESCENE_NAMESPACE_END

TOLUA_API int tolua_handler_manager_open(lua_State* tolua_S);

#endif //XES_XESLUAHANDLERMANAGER_H
