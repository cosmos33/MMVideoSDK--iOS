//
// Created by momo783 on 22/07/2018.
//

#ifndef XES_XESSCENEANIMOJIFILTER_H
#define XES_XESSCENEANIMOJIFILTER_H

#include "filter/XESSceneFilter.h"
#include "rapidjson/document.h"
#include "filter/animoji/XESAnimojiFaceTrack.h"

XESCENE_NAMESPACE_BEGIN

class SceneAnimojiConfig : public SceneConfig {

public:
    SceneAnimojiConfig();
    virtual         ~SceneAnimojiConfig();
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
    };

    struct ModelConfig {
        XString m_Name;

        XArray<AnimationConfig*> m_Animtions;
        XHashTable<XString, ActionConfig*> m_Actions;

        xbool  m_bAutoPlay;

        XString m_strFacerig;
        XHashTable<XString, XString> m_tFacerigStates;
        XString m_facerigset;
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
class SceneAnimojiFilter : public SceneFilter
{
public:

    SceneAnimojiFilter();
    virtual         ~SceneAnimojiFilter() override;

    // Load Scene
    virtual void    LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID) override;

    virtual void    Tick(xfloat32 fTickTime) override;

    virtual void    Release() override;

protected:

    // 加载场景逻辑
    virtual void LoadSceneActor(const XString& relativeScenePath, const XString& sceneID);

    virtual void LoadCommonLogicAndRegisterEventListener();

    void HandleFaceTrackAction(const Face* face, xbool bTracking);

protected:
    XVECTOR3    HitScreenPoint(const XVECTOR2 &vScreenPoint, const XVECTOR3 &vPos);

protected:

    XEActor *m_EmptyActor;

    AnimojiFaceTrack *m_pAnimojiFaceTrack;

    // Action Map
    XHashTable<XEActor*, SceneAnimojiConfig::ModelConfig*> m_ModelConfigMaps;
    XHashTable<XEActor*, SceneAnimojiConfig::ActionConfig*> m_FaceTrackingActionMaps;

};

XESCENE_NAMESPACE_END


#endif //XES_XESSCENEANIMOJIFILTER_H
