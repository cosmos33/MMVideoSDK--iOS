//
//  SceneFilterManager.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESSCENEFILTERMANAGER_H_
#define XESSCENEFILTERMANAGER_H_

#include "core/XESObject.h"
#include "core/XESGeometry.h"
#include "filter/XESSceneFilter.h"

XESCENE_NAMESPACE_BEGIN

class SceneFilterManager : public Object
{
public:
    
    static SceneFilterManager* GetInstance();
    
    void   LoadScene(const XString& scenePath, const XString& sceneID);
    
    void   UnloadScene(const XString& sceneID);


public:
    void   RotateCamera(xbool bPositionFront);
    
    void   EnabledRecoreding(xbool bEnabled);
    
    X_INLINE xbool CameraPositionIsFront() const { return m_bCameraPositionFront; }
    X_INLINE xbool RecoredingEnabled() const { return m_bEnableRecoreding; }
    
    void   UpdateRelationLocationFrame(Rect rFrame, const XString& sceneID);
    void   UpdateRelationLocationFrame(xint32 trackId, Rect rFrame, const XString& sceneID);
    void   TickTimeLineAndFrameSequence(xfloat32 fTime, xint32 nFrame, const XString& sceneID);
    
    Rect   GetActorLocationFrame(XString strActorName);
    
protected:
    void   UnloadAllScene();
    SceneFilter* LoadSceneFilter(const SceneConfig* pConfig);
    
    friend class Director;
    
private:
                    SceneFilterManager();
    virtual         ~SceneFilterManager();
    virtual void    Release();
    
protected:
    
    XHashTable<XString, SceneFilter*> m_pFilters;
    
    xbool m_bEnableRecoreding;
    xbool m_bCameraPositionFront;
    
};

XESCENE_NAMESPACE_END

#endif /* XESSCENEFILTERMANAGER_H_ */
