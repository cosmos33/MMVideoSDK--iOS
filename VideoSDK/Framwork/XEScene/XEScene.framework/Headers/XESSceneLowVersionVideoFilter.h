//
//  SceneLowVersionVideoFilter.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESSCENELOWVERSIONVIDEOFILTER_H_
#define XESSCENELOWVERSIONVIDEOFILTER_H_

#include "scene/XESScene.h"
#include "filter/XESSceneVideoFilter.h"
#include "filter/XESSceneLowVersionVideoConfig.h"

XESCENE_NAMESPACE_BEGIN

class SceneLowVersionVideoFilter : public SceneVideoFilter
{
public:
    
    SceneLowVersionVideoFilter();
    virtual         ~SceneLowVersionVideoFilter() override;
    
    // Load Scene
    virtual void    LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID) override;
    
    virtual void    Tick(xfloat32 fTickTime) override;
    
    virtual void    Release() override;
    
protected:
    
    // 加载场景逻辑
    virtual void LoadSceneActor(const XString& relativeScenePath, const XString& sceneID) override;
};

XESCENE_NAMESPACE_END

#endif /* XESSCENELOWVERSIONVIDEOFILTER_H_ */
