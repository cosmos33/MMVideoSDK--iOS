//
//  SceneVideoConfig.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESSCENEVIDEOCONFIG_H_
#define XESSCENEVIDEOCONFIG_H_

#include "filter/XESSceneFilter.h"
#include "rapidjson/document.h"

XESCENE_NAMESPACE_BEGIN

class SceneVideoConfig : public SceneConfig {
    
public:
    SceneVideoConfig();
    virtual         ~SceneVideoConfig();
    virtual void    Release() override;
    
    XES_SCENE_TYPE_DEFINE(SCENE_TYPENAME);
    static const XString  SCENE_TYPENAME;
    
public:
    
    enum ShowType {
        FRONT = 1 << 0,
        BACK  = 1 << 1,
        ALL = FRONT | BACK,
    };
    
    struct LightConfig {
        XString m_Name;
    };
    
    struct AnimationConfig {
        XString m_Name;
        xbool m_AutoTrigger;
    };
    
    struct ActionConfig {
        XString m_Type;
        
        XString m_ShowAction;
        
        xint32  m_TriggerType;
        xint32  m_AnimationIndex;
        
        xfloat32 m_MinScale;
        xfloat32 m_MaxScale;
        
        xfloat32 m_Distance;
        
        XArray<xint32> m_joints;
        
        xfloat32 m_fJointOffsetScale;
        
    };
    
    struct ModelConfig {
        XString m_Name;
        ShowType m_ShowType;
        
        XArray<AnimationConfig*> m_Animtions;
        XHashTable<XString, ActionConfig*> m_Actions;
        
        xbool  m_bAutoPlay;
        
        XString m_strFacerig;
        XHashTable<XString, XString> m_tFacerigStates;
        XString m_facerigset;
    };
    
    struct ParticleConfig {
        XString m_Name;
        ShowType m_ShowType;
        
        XHashTable<XString,ActionConfig*> m_Actions;
    };
    
    LightConfig *dirLight;
    
    LightConfig *envLight1;
    LightConfig *envLight2;
    
    XArray<ModelConfig*> m_Models;
    
    XArray<ParticleConfig*> m_Particles;
    
    ModelConfig *m_pPlaneHit;
    
    ShowType  m_eGyroEnableType;
    
    xbool   m_AREnable;
    
public:
    
    virtual void LoadConfig(const XString& mJsonBuffer, const XString& mScenePath) override;
    
    static xbool ShouldShow(ShowType eShowType);
    static xbool ShouldShow(ShowType eShowType,xbool bFront);
    
protected:
    
    virtual void LoadCommon(const RAPIDJSON_NAMESPACE::Document& document);
    
    virtual void LoadModel(ModelConfig* mConfig, const RAPIDJSON_NAMESPACE::Value& modelJson,const XString& mScenePath);
    
    virtual void LoadParticle(ParticleConfig* mConfig, const RAPIDJSON_NAMESPACE::Value& particleJson);
    
};

XESCENE_NAMESPACE_END

#endif /* XESSCENEVIDEOFILTER_H_ */
