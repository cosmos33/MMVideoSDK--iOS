//
//  XESSceneADFilter.h
//  FaceDecorationKit
//
//  Created by momo783 on 19/04/2018.
//

#ifndef XESSCENEADFILTER_H_
#define XESSCENEADFILTER_H_

#include "filter/XESSceneFilter.h"
#include "core/XESGeometry.h"
#include "rapidjson/document.h"

XESCENE_NAMESPACE_BEGIN

class SceneADConfig : public SceneConfig {
    
public:
    SceneADConfig();
    virtual         ~SceneADConfig();
    virtual void    Release() override;
    
public:
    
    struct TimeLine {
        xfloat32 m_fStart;
        xfloat32 m_fEnd;
    };
    
    struct TimeTrack {
        XString m_strTarget;
        xint32  m_nAnimationIndex;
        TimeLine m_timeLine;
    };
    
    XString m_strReference;
    XArray<TimeTrack*>  m_timeTracks;
    
    virtual void LoadConfig(const XString& mJsonBuffer, const XString& mScenePath) override;
    
};

class SceneADFilter : public SceneFilter
{
public:
    
    SceneADFilter();
    virtual         ~SceneADFilter() override;
    virtual void    Release() override;
    
    virtual void    LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID) override;
    virtual void    Tick(xfloat32 fTickTime) override;
    
    void            UpdateRelationLocationFrame(Rect rFrame);
    void            TickTimeLineAndFrameSequence(xfloat32 fTime, xint32 nFrame);
    
protected:
    
    XString SceneLoadPatch(const XString& scenePath, const XString& sceneID);
    
    void LoadSceneActor(const XString& relativeScenePath, const XString& sceneID);
    
    void LoadLogicAndRegisterEventListener();
    
    XVECTOR3 HitScreenPoint(const XVECTOR2 &vScreenPoint);
    
protected:
    
    xfloat32 m_fPreTime;
    
};

XESCENE_NAMESPACE_END

#endif /* XESSCENEADFILTER_H_  */
