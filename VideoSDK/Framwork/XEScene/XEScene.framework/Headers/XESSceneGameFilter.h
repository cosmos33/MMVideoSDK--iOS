//
// Created by momo783 on 09/05/2018.
//

#ifndef XES_XESSCENEGAMEFILTER_H
#define XES_XESSCENEGAMEFILTER_H

#include "filter/XESSceneFilter.h"
#include "filter/games/XESGameMessageHandler.h"

XESCENE_NAMESPACE_BEGIN

class SceneGameFilterConfig : public SceneConfig {

public:
    SceneGameFilterConfig();
    virtual         ~SceneGameFilterConfig();
    virtual void    Release() override;
    
    XES_SCENE_TYPE_DEFINE(SCENE_TYPENAME);
    static const XString  SCENE_TYPENAME;

public:

    virtual void LoadConfig(const XString& mJsonBuffer, const XString& mScenePath) override;

};

class Module;
class Message;

class SceneGameFilter : public SceneFilter {
public:
    SceneGameFilter();

    virtual         ~SceneGameFilter() override;

    virtual void    Release() override;

    virtual void    LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID) override;

    virtual void    Tick(xfloat32 fTickTime) override;

    virtual xbool   CustomHandleMessage(Message* pMessage) { return xfalse; };

public:
    void       AddModule(XEActor* pActor, Module* pModule);

    void       RemoveModule(XEActor *pActor, XString moduleTypeName);

    Module*    FindModule(XEActor* pActor, XString moduleTypeName);

protected:

    XEActor *m_pEmptyActor;

    XHashTable<XEActor*, XHashTable<XString, Module*>*> m_ModuleMap;

    GameMessageHandler *m_MessageHandler;

    friend class GameMessageHandler;
};

XESCENE_NAMESPACE_END


#endif //XES_XESSCENEGAMEFILTER_H
