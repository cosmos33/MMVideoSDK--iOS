//
// Created by momo783 on 06/05/2018.
//

#ifndef XES_XESSCRIPTENGINEMANAGER_H
#define XES_XESSCRIPTENGINEMANAGER_H

#include "script/XESScriptEngine.h"
#import "filter/XESSceneFilter.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

    class ScriptEngineManager : public Object {

    public:
        static ScriptEngineManager *GetInstance();

        std::function<SceneConfig *(const char *,const char *)> MakeScriptSceneConfig;
        std::function<SceneFilter *()> MakeScriptSceneFilter;

        ScriptEngine *GetScriptEngine();

        void SetScriptEngine(ScriptEngine *pScriptEngine);

        void RemoveScriptEngine();

        static void SendActorEventToLua(XEActor *pActor, xint32 nAction);

        static void DestoryInstance();

    private:

        ScriptEngineManager() : m_ScriptEngine(nullptr) {
        };

        virtual ~ScriptEngineManager() override;

        void Release() override;

    protected:

        ScriptEngine *m_ScriptEngine;

    };

XESCENE_NAMESPACE_END


#endif //XES_XESSCRIPTENGINEMANAGER_H
