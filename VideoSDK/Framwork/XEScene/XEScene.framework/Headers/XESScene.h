//
//  XESScene.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESCENE_H_
#define XESCENE_H_

#include "core/XESObject.h"
#include "scene/XESWorld.h"
#include "XECore/XEEngine/XEViewport.h"
#import "IX2DPhysicalScene.h"
#import "IX2DPhysicalManager.h"

#include <functional>
#include <set>

class IXModelInstance;

XESCENE_NAMESPACE_BEGIN

    class Rect;

    enum {
        ACTOR_CREATE,
        ACTOR_DESTORY,
    };

    class Scene : public Object, public World::WorldListener {

    private:

        Scene();

        Scene(const XString &mSceneID);

    public:

        virtual ~Scene() override;

        virtual void Release() override;

        static Scene *CreateScene(const char *mSceneID);

        xfloat32 SceneTickTime();

    public:

        X_FORCEINLINE XString GetSceneID() {
            return m_vSceneID;
        }

        X_FORCEINLINE World *GetWorld() {
            return m_pSceneWorld;
        }

        static xbool IsActorInTheBackOfCamera(XEActor *pActor);

        static xbool IsActorInScreen(XEActor *pActor);

        static Rect GetActorScreenFrame(XEActor *pActor);

        static Rect GetActorScreenFrameWithSkeleton(XEActor *pActor);

        static Rect GetActorScreenFrameWithSkeleton(XEActor *pActor, xfloat32 fixScale);

        static XVECTOR2 GetActorDetectScreenPosition(XEActor *pActor);

        IX2DPhysicalScene *Create2DPhysicalScene(const xchar *szSceneName, const XVECTOR2 &vGravity = XVECTOR2(0.0f, -9.8f));

    public:

        typedef std::function<void(xfloat32 fDel)> SceneTickCallback;

        SceneTickCallback OnTickCallback;

        std::function<void()> onStart = nullptr;
        std::function<void()> onEnd = nullptr;
        std::function<void()> onPause = nullptr;
        std::function<void()> onResume = nullptr;

    private:
        virtual void OnWorldAddActor(XEActor *aActor) override;

        virtual void OnWorldWillRemoveActor(XEActor *aActor) override;

        virtual void OnWorldUpdateActor(XEActor *aActor, XString strOldActorName) override;

        virtual void OnWorldTick(xfloat32 fDel) override;

        static Rect GetScreenFrameWithAABB(XCusAABB aabb);

    protected:

        void PauseSceneForAction();

        void ResumeSceneForAction();

    protected:

        XString m_vSceneID;

        World *m_pSceneWorld;

        std::set<XString> m_sActorNames;

        xuint32 m_fStartTime;

        friend class Director;

        IX2DPhysicalScene *_2DPhysicalScene;

    };

XESCENE_NAMESPACE_END

#endif /* XESCENE_H_ */
