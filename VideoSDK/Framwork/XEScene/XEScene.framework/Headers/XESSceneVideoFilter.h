//
//  SceneFilter.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESSCENEVIDEOFILTER_H_
#define XESSCENEVIDEOFILTER_H_

#include "scene/XESScene.h"
#include "filter/XESSceneFilter.h"
#include "filter/XESSceneVideoConfig.h"

#include "XECore/XEAnimation/XEAnimComponentPlayList.h"

XESCENE_NAMESPACE_BEGIN

class Face;

class SceneVideoFilter : public SceneFilter ,public XEAnimComponentPlayList::Listener
{
public:
    
    SceneVideoFilter();
    virtual         ~SceneVideoFilter() override;
    
    // Load Scene
    virtual void    LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID) override;
    
    virtual void    Tick(xfloat32 fTickTime) override;
    
    virtual void    Release() override;
    
protected:
    
    XString SceneLoadPatch(const XString& scenePath, const XString& sceneID);
    
    // 加载场景逻辑
    virtual void LoadSceneActor(const XString& relativeScenePath, const XString& sceneID);
    
    // 核心逻辑
    virtual void LoadLogicAndRegisterEventListener();
    
    virtual void LoadCommonLogicAndRegisterEventListener();
    
protected:
    // 动画listener
    XVECTOR3        HitTestScreenPoint(XVECTOR2 point, xfloat32 distance);
    XVECTOR3        HitScreenPoint(const XVECTOR2 &vScreenPoint, const XVECTOR3 &vPos);
    
    xbool           RayPick(XEActor* pActor, XVECTOR2 vScreenPoint);
    
    XEActor*        PlaneHintActor();
    void            SetPlaneHintActor(XVECTOR3 vLocation, XVECTOR3 vScale, xint32 nAnimationIndex);
    
    void            PlayAnimation(XEActor* pActor, xint32 nAnimationIndex);
    
    virtual void    Ls_StepMove(xfloat32 fTime) override;
    virtual void    Ls_PlayStateChange(XEAnimController::EPlayControlState state) override;
    virtual void    Ls_PlayOneTimeFinished(xbool bReversePlaying) override;
    virtual void    Ls_PlayItemFinished(xint32 nFinishedItemIndex, const XEModelComponent* pHolderComponent,const XEAnimComponentPlayList* pPlayList) override;
    
protected:
    
    XEActor *m_EmptyActor;
    
    // Animation
    XHashTable<XEActor*, xbool> m_AnimationStatus;
    
    // Touch
    XHashTable<XEActor*, xbool> m_TouchClicks;
    
    XHashTable<XEActor*, xint32> m_TouchMoves;
    
    XHashTable<XEActor*, xint32> m_TouchMoveId;
    XHashTable<XEActor*, XVECTOR2> m_TouchMoveBeginOffset;
    
    XHashTable<XEActor*, xbool> m_TouchPinchs;
    XHashTable<XEActor*, XVECTOR2> m_TouchPinchBegin; // x -> dis ; y -> scale;
    XHashTable<XEActor*, XVECTOR3> m_TouchPinchBeginScale;
    
    XHashTable<XEActor*, xbool> m_RaySuccessMap;
    
    // AR
    xbool m_bARObjectPlaced;
    xbool m_bAttitudeEnabled;
    
    // Joint
    XHashTable<XEActor*,XHashTable<xint32, XEActor*>> m_JointParticles;

};

XESCENE_NAMESPACE_END

#endif /* XESSCENEVIDEOFILTER_H_ */
