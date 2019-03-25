//
// Created by momo783 on 07/05/2018.
//

#ifndef XES_XESLUAENGINE_H
#define XES_XESLUAENGINE_H

#include "core/XESObject.h"
#include "script/XESScriptEngine.h"
#include "XESLuaStack.h"
#include "XESLuaHandlerManager.h"
#include "lua.h"
#include "XESLuaSystemHandler.h"
#include "XESLuaInterpreter.h"

#include <functional>

class XEActor;

XESCENE_NAMESPACE_BEGIN

    class LuaEngine : public ScriptEngine {

    public:

        xbool Init();

        virtual ~LuaEngine() override;

        void Release();

    public:

        static LuaEngine *GetInstance();

        LuaStack *GetLuaStack();

        virtual void AddSearchPath(const XString strPath) override;

        virtual void AddLuaLoader(lua_CFunction func);

        virtual int Reload(const XString strModuleFileName);

        virtual xint32 HandleEvent(LuaHandlerManager::HandlerType nType, void *pDate);

    public:
        // Script Engine Protocol

        virtual const XString &GetScritpType() override;

        virtual void RemoveScriptObjectByObject(XMemBase *pObject) override;

        virtual void RemoveScriptHandler(xint32 nHandler) override;

        virtual xint32 ReallocateScriptHandler(xint32 nHandler) override;

        virtual xint32 ExecuteString(const XString &strCodes) override;

        virtual xint32 ExecuteScriptFile(const XString &strFileName) override;
        
        virtual xint32 StartGameScriptFile(const XString &strFileName) override;

        virtual xint32 ExecuteGlobalFunction(const XString &strFunction) override;

        virtual xint32 ExecuteActorEvent(XEActor *pActor, xint32 nAction) override;

        virtual xbool HandleAssert(const XString &msg) override;

        virtual xint32 SendEvent(ScriptEvent *pScriptEvent) override;
        
        virtual void SetSecretKey(const char *key) override;
        
    protected:

        xint32 HandleActorEvent(void *pData);

        xint32 HandleCallFuncActionEvent(void *pData);

        xint32 HandleTouchEvent(void *pData);

        xint32 HandleTouchesEvent(void *pData);

        xint32 HandleAccelerometerEvent(void *pData);

        xint32 HandleEventTouch(LuaHandlerManager::HandlerType type, void *data);

        xint32 HandleEventTouches(LuaHandlerManager::HandlerType type, void *data);

        xint32 HandleFaceEvent(LuaHandlerManager::HandlerType type, void *data);

        xint32 HandleEventAcc(void *pData);

        xint32 HandleEventCustom(void *pData);

        xint32 HandleEventAttitude(void *pData);

        xint32 HandleEventAcceleration(void *pData);

        xint32 HandleEventSchedule(void *pData);

        xint32 HandleARSessionStatusCallback(void *pData,LuaHandlerManager::HandlerType type);
        
        xint32 HandleHandEventCallback(void *pData);
        
        xint32 HandleCVBodyEventCallback(void *pData);
        
        xint32 HandleCVObjectEventCallback(void *pData);
        
        xint32 HandleExpressionEventCallback(void *pData);


    private:

        LuaEngine() : m_Stack(nullptr) {
        }

        static LuaEngine *g_DefaultEngine;

        LuaStack *m_Stack;
        
        LuaInterpreter *_luaInterpreter;

        SystemEventHandler *_luaSystemHandler;

        xint32 HandleEventScriptBridge(void *pData);

        xint32 HandleAnimationPlayCallback(LuaHandlerManager::HandlerType type, void *pData);
    };

XESCENE_NAMESPACE_END


#endif //XES_XESLUAENGINE_H
