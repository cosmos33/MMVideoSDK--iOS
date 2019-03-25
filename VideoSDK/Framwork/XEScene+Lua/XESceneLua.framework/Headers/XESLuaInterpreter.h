/******************************************************************************

@File         LuaInterpreter.h

@Version       1.0

@Created      2018,10, 8

@Description  Lua Interpreter for xecore.

@HISTORY:

******************************************************************************/
#ifndef _XE_LUA_INTERPRETER_H_
#define _XE_LUA_INTERPRETER_H_

#include "XMemBase.h"
#include "XESDefine.h"
#include "XESLuaStack.h"
#include "XEScriptInterpreter.h"

XESCENE_NAMESPACE_BEGIN

    class LuaInterpreter : public XEScriptInterpreterPool::XEScriptInterpreter {
    public:
        LuaInterpreter(LuaStack *pLuaStack);

        virtual                ~LuaInterpreter();

    public:
        virtual xbool Execute(const xchar *pCodeBuffer, XEScriptInstance *pScriptIns, xint32 &assignedID) override;

        virtual xbool GarbageClean(XEScriptInstance *pScriptIns) override;

        virtual xbool OnHolderEntrance(XEScriptInstance *pScriptIns) override;

        virtual xbool OnHolderRelease(XEScriptInstance *pScriptIns) override;

        virtual xbool OnHolderTick(XEScriptInstance *pScriptIns, xfloat32 fIntervalMs) override;

        virtual xbool OnHolderRender(XEScriptInstance *pScriptIns, XEViewport *pViewport) override;

    protected:
        LuaStack *m_pLuaStack;
        xint32 m_nObjIndex;//will start from 1
    };

XESCENE_NAMESPACE_END

#endif // _XE_LUA_INTERPRETER_H_
