//
//  SceneVideoGameFilter.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESSCENEVIDEOGAMEFILTER_H_
#define XESSCENEVIDEOGAMEFILTER_H_

#include "scene/XESScene.h"
#include "filter/modules/XESModule.h"
#include "filter/XESSceneVideoFilter.h"
#include "filter/XESSceneVideoGameConfig.h"

XESCENE_NAMESPACE_BEGIN

class MessageHandler;
class SceneVideoGameFilter : public SceneVideoFilter
{
public:
    
    SceneVideoGameFilter();
    virtual         ~SceneVideoGameFilter() override;
    
    virtual void    LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID) override;
    
    virtual void    Tick(xfloat32 fTickTime) override;
    
    virtual void    Release() override;
    
protected:
    
    virtual void    LoadLogicAndRegisterEventListener() override;
    
    virtual void    Ls_StepMove(xfloat32 fTime) override;
    virtual void    Ls_PlayStateChange(XEAnimController::EPlayControlState state) override;
    virtual void    Ls_PlayItemFinished(xint32 nFinishedItemIndex, const XEModelComponent* pHolderComponent,const XEAnimComponentPlayList* pPlayList) override;
    
    void            AddModule(XEActor* pActor, Module* pModule);
    void            RemoveModule(XEActor *pActor, XString moduleTypeName);
    Module*         FindModule(XEActor* pActor, XString moduleTypeName);
    
protected:
    
    struct ModuleElement {
        XEActor* m_pActor;
        XHashTable<XString, Module*> m_Modules;
    };
    
    XHashTable<XEActor*, ModuleElement*> m_ModuleMap;
    
    MessageHandler *m_pMessageHandler;
    
    friend class MessageHandler;
    
};

XESCENE_NAMESPACE_END

#endif /* XESSCENEVIDEOGAMEFILTER_H_ */
