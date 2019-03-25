//
//  XESSceneADFilter.h
//  FaceDecorationKit
//
//  Created by momo783 on 19/04/2018.
//

#ifndef XESSCENENEWADFILTER_H_
#define XESSCENENEWADFILTER_H_

#include "filter/XESSceneFilter.h"
#include "core/XESGeometry.h"
#include "rapidjson/document.h"

XESCENE_NAMESPACE_BEGIN

class SceneNewADConfig : public SceneConfig {
public:
    SceneNewADConfig();
    virtual         ~SceneNewADConfig();
    virtual void    Release() override;
    
    XES_SCENE_TYPE_DEFINE(SCENE_TYPENAME);
    static const XString  SCENE_TYPENAME;
    
public:
    
    struct TimeLine {
        xfloat32 m_fStart;
        xfloat32 m_fEnd;
        XString m_tickTarget;
    };
    
    enum ARADLayoutType
    {
        ADLayoutTypeCenter = 0,
        ADLayoutTypeTop,
        ADLayoutTypeLeft,
        ADLayoutTypeBottom,
        ADLayoutTypeRight
    };
    
    struct ReferenceElement {
        ARADLayoutType layoutType;
        XString reference;
        XArray<XString> layoutTargets;
    };
    
    XArray<XArray<ReferenceElement *>> m_references;
    XArray<xint32> m_trackIds;
    
    TimeLine m_timeLine;
    
    virtual void LoadConfig(const XString& mJsonBuffer, const XString& mScenePath) override;
    
};

class SceneNewADFilter : public SceneFilter
{
public:
    
    SceneNewADFilter();
    virtual         ~SceneNewADFilter() override;
    virtual void    Release() override;
    
    virtual void    LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID) override;
    virtual void    Tick(xfloat32 fTickTime) override;
    
    void            UpdateRelationLocationFrame(xint32 trackId, Rect rFrame);
    void            TickTimeLineAndFrameSequence(xfloat32 fTime, xint32 nFrame);
    
protected:
    
    XString SceneLoadPatch(const XString& scenePath, const XString& sceneID);
    
    void LoadSceneActor(const XString& relativeScenePath, const XString& sceneID);
    
    void LoadLogicAndRegisterEventListener();
    
    XVECTOR3 HitScreenPoint(const XVECTOR2 &vScreenPoint, xfloat32 reference_z);


protected:
    
    xfloat32 m_fPreTime;
    
};

XESCENE_NAMESPACE_END

#endif /* XESSCENEADFILTER_H_  */
