//
//  SceneVideoGameConfig.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESSCENEVIDEOGAMECONFIG_H_
#define XESSCENEVIDEOGAMECONFIG_H_

#include "filter/XESSceneVideoConfig.h"
#include "core/XESGeometry.h"
#include "rapidjson/document.h"

XESCENE_NAMESPACE_BEGIN

class SceneVideoGameConfig : public SceneVideoConfig {
    
public:
    SceneVideoGameConfig();
    virtual         ~SceneVideoGameConfig();
    virtual void    Release() override;
    
    XES_SCENE_TYPE_DEFINE(SCENE_TYPENAME);
    static const XString  SCENE_TYPENAME;
    
public:
    
    struct GameModuleConfig  {
        XString m_strType;
    };
    
    struct GameMakerModuleConfig : public GameModuleConfig {
        xint32 m_nLimit;
        xfloat32 m_fLifeTime;
    };
    
    struct GameActionConfig {
        XString  m_Action;
        
        xfloat32 m_fVelocity;
        XVECTOR3 m_vRatate;
        
        XString  m_Target;
        
        xint32   m_nAnimationIndex;
    };
    
    // Trigger Category
    struct GameTirggerModuleConfig : public GameModuleConfig {
        XString m_tType;
        XString m_tSubType;
        XHashTable<XString, GameActionConfig*> m_Actions;
        
        XString m_TriggerTime;
    };
    
    
    struct GameDetectorModuleConfig : public GameModuleConfig {
        
        XString m_dType;
    };
    
    struct GameDetectorPassModuleConfig : public GameDetectorModuleConfig {
        
        XString m_dTarget;
        XVECTOR3 m_dTargetPosition;
        
        XVECTOR3 m_Offset;
        XVECTOR3 m_AABBSize;
        
    };
    
    struct GameDetectorOutModuleConfig : public GameDetectorModuleConfig {
        
        Rect m_ScreenBounds;
    };
    
    struct ModelGameConfig : public ModelConfig {
        
        XArray<GameModuleConfig*> m_Modules;
    };
    
    struct ParticleGameConfig : public ParticleConfig {
        
        XArray<GameModuleConfig*> m_Modules;
    };
    
    virtual void LoadConfig(const XString& mJsonBuffer, const XString& mScenePath) override;
    
protected:
    
    virtual void LoadCommon(const RAPIDJSON_NAMESPACE::Document& document) override;
    
    virtual void LoadModel(ModelConfig* mConfig, const RAPIDJSON_NAMESPACE::Value& modelJson,const XString& mScenePath) override;
    
    virtual void LoadParticle(ParticleConfig* mConfig, const RAPIDJSON_NAMESPACE::Value& particleJson) override;
    
};
XESCENE_NAMESPACE_END

#endif /* XESSCENEVIDEOGAMECONFIG_H_ */
