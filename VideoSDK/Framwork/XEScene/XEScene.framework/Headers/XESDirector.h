//
//  XESDirector.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESDIRECTOR_H_
#define XESDIRECTOR_H_

#include "core/XESObject.h"
#include "scene/XESWindow.h"
#include "scene/XESScene.h"
#include "XECore/XEGame.h"
#include "XECore/XEEngine/XEEngine.h"
#include "platform/armodule/XESARModule.h"

#include <map>
#include <iostream>

class IXEDressupManager;

class IXAnimationManager;

enum PLATFORM_OS {
    PLATFORM_OS_NONE,
    PLATFORM_OS_IOS,
    PLATFORM_OS_ANDROID
};

XESCENE_NAMESPACE_BEGIN

    class EventDispatcher;

    class ActionManager;

    class Director : public Object, public XEEngine::XEFrameListener {

    private:

        Director();

        virtual ~Director() override;

        virtual void Release() override;

    public:

        static Director *GetInstance();

        static X_FORCEINLINE XString GetVersion(){
            return XESCENE_VERSION;
        }
        
        static PLATFORM_OS GetPlatform();
        
    public:

        X_FORCEINLINE xbool IsRunning() { return m_bRunning; }

        xbool Run(const xchar *mBasePath, const xchar *mLibraryPath);

        xbool Run(const xchar *mBasePath, const xchar *mLibraryPath, int nwidht, int height);

        void End();

        void Render();

        void Render(const xchar *mSceneID);

        void ResizeWindow(xfloat32 mWidth, xfloat32 mHeight);

    public:
        
        X_FORCEINLINE Window *GetWindow() { return m_wCurrentWindow; }

        X_FORCEINLINE XEGame *GetGame() { return m_gCurrentGame; }

        X_FORCEINLINE XEEngine *GetEngine() { return m_eUseEngine; }

    public:

        void ClearBackground();

        void EnableClearColor(xbool bClearColor);

    public:

        void PushScene(Scene *mScene);

        void PopScene();

        Scene *GetTopScene();

        void PresentScene(Scene *mScene, const xchar *mSceneID);

        void DissmissScene(const xchar *mSceneID);

        Scene *GetPresentScene(const xchar *mSceneID);

        XArray<Scene *> GetRunningScene();

    public:

        X_FORCEINLINE xbool ARIsActive() const { return m_bARActive; }

        void ActiveARSupport(xbool bActive, xbool bInternal = true);

#if ARKIT_SUPPORT
        void* InternalARSessionDelegate();
#endif

        void RegisterARModule(AR::ARModule *pARModule);

        X_FORCEINLINE AR::ARModule *GetARModule() { return m_pARModule; };

    public:

        virtual void OnPreFrame() override;

        virtual void OnPostFrame() override;

        virtual void OnFrameSizeChanged() override;

    public:
        // Events
        EventDispatcher *GetEventDispatcher();

        void SetEventDispatcher(EventDispatcher *pEventDispatcher = nullptr);

    public:
        // Actions
        ActionManager *GetActionManager();

        void SetActionManager(ActionManager *pActionManager = nullptr);

    public:

        X_FORCEINLINE XString GetBasePath() const { return m_sBasePath; }

        X_FORCEINLINE XString GetLibraryPath() const { return m_sLibraryPath; }

    public:

        IXAnimationManager *GetAnimationManager();

        IXEDressupManager *GetDressupManager();

    public:
        void queryTask(std::function<void()> task);

    protected:

        xbool m_bRunning;

        xbool m_bARActive;
        xbool m_bInternal;

        XString m_sBasePath;
        XString m_sLibraryPath;

        Window *m_wCurrentWindow;

        XEGame *m_gCurrentGame;

        XEEngine *m_eUseEngine;

        XEEngine::XEFrameListener *m_lFrameListener;

        XArray<Scene *> m_aSceneStack;

        XHashTable<XString, Scene *> m_mSceneCollection;

        Scene *m_RnederScene;

        xuint32 m_fStartTime;

        EventDispatcher *m_pEventDispatcher;

        ActionManager *m_pActionManager;

        AR::ARModule *m_pARModule;

        XArray<std::function<void()> > _taskQueue;
    };

XESCENE_NAMESPACE_END

#endif /* XESDIRECTOR_H_ */
