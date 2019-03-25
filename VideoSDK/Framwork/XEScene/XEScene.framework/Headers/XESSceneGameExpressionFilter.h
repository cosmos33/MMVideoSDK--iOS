//
// Created by momo783 on 10/05/2018.
//

#ifndef XES_XESSCENEGAMEEXPRESSIONFILTER_H
#define XES_XESSCENEGAMEEXPRESSIONFILTER_H

#include "filter/games/XESSceneGameFilter.h"
#include "core/XESGeometry.h"

XESCENE_NAMESPACE_BEGIN

class Expression;

class SceneGameExpressionFilter : public SceneGameFilter {

public:

    SceneGameExpressionFilter();

    ~SceneGameExpressionFilter() override;

    void Release() override;

    void LoadScene(SceneConfig* pSceneConfig, const XString& mSceneID) override;

    void Tick(xfloat32 fTickTime) override;

    xbool CustomHandleMessage(Message *pMessage) override;

protected:
    
    void DispatchExpressions(const XArray<Expression*>& pExpressions);
    
    XVECTOR3 TransformScreenPosToWorld(const XVECTOR2& vScreenPos, const XVECTOR3& vPos);
    
    xbool ActorInBounds(const XEActor& pActor, Rect bounds);
    
protected:

    XHashTable<XEActor*, XString> m_UsingActors;
    XHashTable<XEActor*, XString> m_ParticlesForActors;
    
    XHashTable<XEActor*, Rect> m_ActorTriggerBounds;
    
};

XESCENE_NAMESPACE_END

#endif //XES_XESSCENEGAMEEXPRESSIONFILTER_H
