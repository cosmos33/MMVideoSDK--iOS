//
//  XESSceneLowVersionVideoConfig.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESSCENELOWVERSIONVIDEOCONFIG_H_
#define XESSCENELOWVERSIONVIDEOCONFIG_H_

#include "core/XESObject.h"
#include "scene/XESScene.h"
#include "filter/XESSceneVideoConfig.h"
#include "rapidjson/document.h"

XESCENE_NAMESPACE_BEGIN

class SceneLowVersionVideoConfig : public SceneVideoConfig {
    
public:
    SceneLowVersionVideoConfig();
    virtual         ~SceneLowVersionVideoConfig() override;
    virtual void    Release() override;
    
    XES_SCENE_TYPE_DEFINE(SCENE_TYPENAME);
    static const XString  SCENE_TYPENAME;
    
public:
    
    struct LightConfigLow : public LightConfig {
        XVECTOR3 m_Dir;
        XCOLORBASE m_Color;
        xfloat32 m_Intensity;
    };
    
    struct AnimationConfigLow : public AnimationConfig {
        XString m_Path;   // Folder & triggerType 兼容
    };
    
    struct ModelConfigLow : public ModelConfig {
        XString m_Path;   // Folder  faceTrack 兼容
        XVECTOR3 m_Position;
        
        XString m_FacerigConfigPath;
    };
    
    struct ParticleConfigLow : public ParticleConfig {
        XString m_Path;   // Folder 兼容
        XVECTOR3 m_Position;
    };
    
    xfloat32  m_fFovFront;
    xfloat32  m_fFovBack;
    
public:
    
    virtual void LoadConfig(const XString& mJsonBuffer,const XString& mScenePath) override;
    
    void LoadModel(ModelConfigLow* mConfig, const RAPIDJSON_NAMESPACE::Value& modelJson, const XString& mScenePath);
    
    void LoadParticle(ParticleConfigLow* mConfig, const RAPIDJSON_NAMESPACE::Value &particleJson,  const XString& mScenePath);
    
};

XESCENE_NAMESPACE_END

#endif /* XESSCENELOWVERSIONVIDEOCONFIG_H_ */
