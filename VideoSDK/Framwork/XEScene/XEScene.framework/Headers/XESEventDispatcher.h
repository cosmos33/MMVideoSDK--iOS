//
//  XESEventDispatcher.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESEVENTDISPATCHER_H_
#define XESEVENTDISPATCHER_H_

#include "core/XESObject.h"
#include "core/events/XESEventListener.h"
#include "core/events/XESCustomEvent.h"
#include "core/events/XESCustomEventListener.h"

#include <set>
#include <vector>

class XEActor;

XESCENE_NAMESPACE_BEGIN

class Event;
class TouchEvent;

class EventDispatcher : public Object {
    
public:
    
    static EventDispatcher* GetInstance();
    
    // Add Listeners
    void AddEventListener(EventListener* pListener, XEActor* pActor);
    
    void AddEventListenerWithFixedPriority(EventListener* pListener, xint32 nFixedPriority);
    
    CustomEventListener* AddCustomEventListener(const XString& mEventName, const std::function<void(CustomEvent*)>& callback);
    
    
    // Remove Listeners
    void RemoveEventListener(EventListener* pListener);
    
    void RemoveEventListenersForType(EventListener::Type eListenerType);
    
    void RemoveEventListenersForTarget(XEActor* pTarget, xbool recursive = xfalse);
    
    void RemoveCustomEventListeners(const XString& mCustomEventName);
    
    void RemoveAllEventListeners();
    
    
    // Pause & Resume
    void PauseEventListenersForTarget(XEActor* pTarget, xbool recursive = xfalse);
    
    void ResumeEventListenersForTarget(XEActor* pTarget, xbool recursive = xfalse);
    
    // listener priority
    void SetPriority(EventListener* pListener, xint32 nFixedPriority);
    
    
    void SetEnabled(xbool bEnabled) { m_bEnabled = bEnabled; };
    
    X_INLINE xbool IsEnabled() const { return m_bEnabled; };
    
    
    // Dispatch Event
    void DispatchEvent(Event* pEvent);
    
    xbool DispatchTouchHitTestEvent(Event* pEvent);
    
    void DispatchCustomEvent(const XString &mEventName, void* mUserData = nullptr);
    
public:
    
    EventDispatcher();
    
    virtual ~EventDispatcher() override;
    virtual void Release() override;
    
    
protected:
    class EventListenerVector;
    
    void AddEventListener(EventListener* listener);
    
    void ForceAddEventListener(EventListener* listener);
    
    EventListenerVector* GetListeners(const EventListener::ListenerID& listenerID);
    
    void RemoveEventListenersForListenerID(const EventListener::ListenerID& listenerID);
    
    // Sort
    void SortEventListeners(const EventListener::ListenerID& listenerID);
    
    void SortEventListenersOfSceneGraphPriority(const EventListener::ListenerID& listenerID, XEActor* rootActor);
    
    void SortEventListenersOfFixedPriority(const EventListener::ListenerID& listenerID);
    
    /** Updates all listeners
     *  1) Removes all listener items that have been marked as 'removed' when dispatching event.
     *  2) Adds all listener items that have been marked as 'added' when dispatching event.
     */
    void UpdateListeners(Event* pEvent);
    
    void DispatchTouchEvent(TouchEvent* pTouchEvent);
    
    void AssociateActorAndEventListener(XEActor* pActor, EventListener* listener);
    
    void DissociateActorAndEventListener(XEActor* pActor, EventListener* listener);
    
    void DispatchEventToListeners(EventListenerVector* listeners, const std::function<xbool(EventListener*)>& onEvent);
    
    void DispatchTouchEventToListeners(EventListenerVector* listeners, const std::function<xbool(EventListener*)>& onEvent);
    
    void ReleaseListener(EventListener* listener);
    
    void VisitTarget(XEActor* pActor, xbool bRootActor);
    
    void CleanToRemovedListeners();
    
protected:
    
    friend class Scene;
    
    class EventListenerVector
    {
    public:
        EventListenerVector();
        ~EventListenerVector();
        size_t Size() const;
        bool Empty() const;
        
        void Push_back(EventListener* item);
        void ClearSceneGraphListeners();
        void ClearFixedListeners();
        void Clear();
        
        inline std::vector<EventListener*>* GetFixedPriorityListeners() const { return _fixedListeners; };
        inline std::vector<EventListener*>* GetSceneGraphPriorityListeners() const { return _sceneGraphListeners; };
        inline ssize_t GetGt0Index() const { return _gt0Index; };
        inline void SetGt0Index(ssize_t index) { _gt0Index = index; };
    private:
        std::vector<EventListener*>* _fixedListeners;
        std::vector<EventListener*>* _sceneGraphListeners;
        ssize_t _gt0Index;
    };
    
    enum class DirtyFlag
    {
        NONE = 0,
        FIXED_PRIORITY = 1 << 0,
        SCENE_GRAPH_PRIORITY = 1 << 1,
        ALL = FIXED_PRIORITY | SCENE_GRAPH_PRIORITY
    };
    
    void SetDirtyForActor(XEActor* pActor);
    
    void SetDirty(const EventListener::ListenerID& listenerID, DirtyFlag flag);
    
    void UpdateDirtyFlagForSceneGraph();
    
protected:
    
    xbool       m_bEnabled;
    xint32      m_nInDispatch;
    
    xint32  m_nActorPriorityIndex;
    
    /** Listeners map */
    XHashTable<EventListener::ListenerID, EventListenerVector*> m_ListenerMap;
    
    /** The map of dirty flag */
    XHashTable<EventListener::ListenerID, DirtyFlag> m_PriorityDirtyFlagMap;
    
    /** The map of node and event listeners */
    XHashTable<XEActor*, std::vector<EventListener*>*> m_ActorListenersMap;
    
    /** The map of node and its event priority */
    XHashTable<XEActor*, int> m_ActorPriorityMap;
    
    /** key: Global Z Order, value: Sorted Nodes */
    XHashTable<float, std::vector<XEActor*>> m_GlobalZOrderActorMap;
    
    /** The listeners to be added after dispatching event */
    std::vector<EventListener*> m_ToAddedListeners;
    
    /** The listeners to be removed after dispatching event */
    std::vector<EventListener*> m_ToRemovedListeners;
    
    /** The nodes were associated with scene graph based priority listeners */
    std::set<XEActor*> m_DirtyActors;
    
    std::set<XString> m_InternalCustomListenerIDs;
    
};

XESCENE_NAMESPACE_END

#endif /* XESEVENTDISPATCHER_H_ */
