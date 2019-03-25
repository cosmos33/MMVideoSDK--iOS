//
//  SceneFilter.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESSCENEFILTER_H_
#define XESSCENEFILTER_H_

#include "core/XESObject.h"
#include "scene/XESScene.h"

XESCENE_NAMESPACE_BEGIN

extern const XString ROTATE_CAMERA_EVENT_ID;
extern const XString ENABLED_RECOREDING_EVENT_ID;

extern const XString BACK_CAMREA_ACTOR_ID;
extern const XString FRONT_CAMREA_ACTOR_ID;

class SceneConfig : public Object {
    
public:
    static  const XString   SCENE_TYPENAME;
    virtual const XString&  TypeName() const { return SCENE_TYPENAME; }
    
public:
    SceneConfig();
    virtual         ~SceneConfig();
    virtual void    Release();
    
    virtual void    LoadConfig(const XString& mJsonBuffer, const XString& mScenePath);
    
public:
    
    X_INLINE XString    GetName()       const { return m_strName; }
    X_INLINE XString    GetVersion()    const { return m_strVersion; }
    X_INLINE XString    GetScenePath()  const { return m_strScenePath; }
    
    void    SetName(const XString& strName)             { m_strName = strName; };
    void    SetVersion(const XString& strVersion)       { m_strVersion = strVersion; };
    void    SetScenePath(const XString& strScenePath)   { m_strScenePath = strScenePath; };
    
    
protected:
    
    XString m_strName;
    XString m_strVersion;
    
    XString m_strScenePath;
    
};

class SceneFilter : public Object
{
public:
    
                    SceneFilter();
    virtual         ~SceneFilter();
    
    // Load Scene
    virtual void    LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID);
    
    // Tick
    virtual void    Tick(xfloat32 fTickTime) = 0;
    
    virtual void    Release() override;
    
    
    X_INLINE Scene* GetScene() const {
        return m_pScene;
    }
    
    X_INLINE SceneConfig* GetConfig() const {
        return m_pSceneConfig;
    }
    
protected:
    
    Scene*  m_pScene;
    SceneConfig* m_pSceneConfig;
    
};

#define XES_SCENE_TYPE_DEFINE(T) const XString& TypeName()const override{return T;}

XESCENE_NAMESPACE_END

#endif /* XESSCENEFILTER_H_ */
