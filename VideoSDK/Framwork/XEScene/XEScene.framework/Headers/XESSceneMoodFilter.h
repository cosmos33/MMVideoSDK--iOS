//
//  SceneFilter.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESSCENEMOODFILTER_H_
#define XESSCENEMOODFILTER_H_

#include "scene/XESScene.h"
#include "filter/XESSceneFilter.h"
#include "XECore/XEAnimation/XEAnimComponentPlayList.h"
#include "filter/mood/XESMoodFaceTrack.h"
#include "rapidjson/document.h"

XESCENE_NAMESPACE_BEGIN

class SceneMoodConfig : public SceneConfig {

public:
    SceneMoodConfig();
    virtual         ~SceneMoodConfig();
    virtual void    Release() override;

    XES_SCENE_TYPE_DEFINE(SCENE_TYPENAME);
    static const XString  SCENE_TYPENAME;

public:

    struct AnimationConfig {
        XString m_Name;
        xbool m_AutoTrigger;
    };

    struct ActionConfig {
        XString m_Type;
        XString m_ShowAction;

        XString m_Layout;
        XString m_Target;

        xint32  m_TriggerType;
        xint32  m_AnimationIndex;
    };

    struct ModelConfig {
        XString m_Name;

        XArray<AnimationConfig*> m_Animtions;
        XHashTable<XString, ActionConfig*> m_Actions;

        xbool  m_bAutoPlay;
    };

    struct ParticleConfig {
        XString m_Name;

        XHashTable<XString,ActionConfig*> m_Actions;
    };

    XArray<ModelConfig*> m_Models;

    XArray<ParticleConfig*> m_Particles;

public:

    virtual void LoadConfig(const XString& mJsonBuffer, const XString& mScenePath) override;

protected:


    virtual void LoadModel(ModelConfig* mConfig, const RAPIDJSON_NAMESPACE::Value& modelJson,const XString& mScenePath);

    virtual void LoadParticle(ParticleConfig* mConfig, const RAPIDJSON_NAMESPACE::Value& particleJson);

};

class Face;
class SceneMoodFilter : public SceneFilter ,public XEAnimComponentPlayList::Listener
{
public:

    SceneMoodFilter();
    virtual         ~SceneMoodFilter() override;
    
    // Load Scene
    virtual void    LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID) override;
    
    virtual void    Tick(xfloat32 fTickTime) override;
    
    virtual void    Release() override;
    
protected:
    
    XString SceneLoadPatch(const XString& scenePath, const XString& sceneID);
    
    // 加载场景逻辑
    virtual void LoadSceneActor(const XString& relativeScenePath, const XString& sceneID);

    virtual void LoadCommonLogicAndRegisterEventListener();

    void HandleFaceTrackAction(const Face* face, xbool bTracking);
    
protected:
    // 动画listener
    XVECTOR3        HitTestScreenPoint(XVECTOR2 point, xfloat32 distance);
    XVECTOR3        HitScreenPoint(const XVECTOR2 &vScreenPoint, const XVECTOR3 &vPos);

    void            PlayAnimation(XEActor* pActor, xint32 nAnimationIndex);
    
    virtual void    Ls_StepMove(xfloat32 fTime) override;
    virtual void    Ls_PlayStateChange(XEAnimController::EPlayControlState state) override;
    virtual void    Ls_PlayOneTimeFinished(xbool bReversePlaying) override;
    virtual void    Ls_PlayItemFinished(xint32 nFinishedItemIndex, const XEModelComponent* pHolderComponent,const XEAnimComponentPlayList* pPlayList) override;
    
protected:
    
    XEActor *m_EmptyActor;

    MoodFaceTrack *m_pFaceTrack;
    
    // Animation
    XHashTable<XEActor*, xbool> m_AnimationStatus;

    // Action Map
    XHashTable<XEActor*, SceneMoodConfig::ActionConfig*> m_FaceTrackingActionMaps;
    XHashTable<XEActor*, SceneMoodConfig::ActionConfig*> m_FaceExpressionActionMaps;

};

XESCENE_NAMESPACE_END

#endif /* XESSCENEMOODFILTER_H_ */
