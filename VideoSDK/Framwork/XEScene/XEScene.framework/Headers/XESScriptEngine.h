//
// Created by momo783 on 06/05/2018.
//

#ifndef XES_XESSCRIPTENGINE_H
#define XES_XESSCRIPTENGINE_H

#include "core/XESObject.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

struct ScriptData {

    void* m_NativeObject;

    void* m_Value;

    ScriptData(void* pObject, void* pValue)
    : m_NativeObject(pObject)
    , m_Value(pValue) {

    }

};

enum ScriptEventType
{
    ACTOR_EVENT = 0,
    CALL_FUNC_EVENT,
    TOUCH_EVENT,
    TOUCHS_EVENT,
    ACCELEROMEMTER_EVENT
};

struct ScriptEvent {

    ScriptEventType m_Type;

    void* m_Data;

    ScriptEvent(ScriptEventType eType, void* pDate)
    : m_Type(eType)
    , m_Data(pDate) {

    }

};

class ScriptEngine {

public:
    ScriptEngine();

    virtual ~ScriptEngine();

    virtual const XString& GetScritpType();
    
    virtual void AddSearchPath(const XString strPath) = 0;

    virtual void RemoveScriptObjectByObject(XMemBase* pObject) {};

    virtual void RemoveScriptHandler(xint32 nHandler) {};

    virtual xint32 ReallocateScriptHandler(xint32 nHandler) = 0;

    virtual xint32 ExecuteString(const XString& strCodes) = 0;

    virtual xint32 ExecuteScriptFile(const XString& strFileName) = 0;
    
    virtual xint32 StartGameScriptFile(const XString &strFileName) = 0;

    virtual xint32 ExecuteGlobalFunction(const XString& strFunction) = 0;

    virtual xint32 ExecuteActorEvent(XEActor* pActor, xint32 nAction) = 0;

    virtual xbool HandleAssert(const XString& msg) = 0;

    virtual xint32 SendEvent(ScriptEvent* pScriptEvent) = 0;

    virtual void SetSecretKey(const char *key) = 0;
};

XESCENE_NAMESPACE_END


#endif //XES_XESSCRIPTENGINE_H
