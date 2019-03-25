//
//  XESEventListener.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESEVENTLISTENER_H_
#define XESEVENTLISTENER_H_

#include "core/XESObject.h"
#include <iostream>
#include <functional>

class XEActor;

XESCENE_NAMESPACE_BEGIN

class Event;

class EventListener : public Object {
    
public:
    enum Type {
        UNKNOWN,
        TOUCH_ONE_BY_ONE,
        TOUCH_ALL_AT_ONCE,
        FACE,
        EXPRESSION,
        ATTITUDE,
        ACCELERATION,
        CVBODY,
        CVOBJECT,
        HAND,
        CUSTOM
    };
    
    typedef XString ListenerID;

public:
    
    EventListener();
    
    bool Init(Type eType, const ListenerID& listenerID, const std::function<void(Event*)>& fCallback);

public:
    
    virtual ~EventListener() override;
    virtual void Release() override;
    
    virtual xbool CheckAvailable() = 0;
    
    virtual EventListener* Clone() = 0;
    
    X_INLINE void SetEnabled(xbool bEnabled) { m_bEnabled = bEnabled; }
    
    X_INLINE xbool IsEnabled() const { return m_bEnabled; }
    
protected:
    
    X_INLINE Type GetType() const { return m_eType; }
    
    X_INLINE xbool IsPause() const { return m_bPause; }
    X_INLINE xbool IsRegistered() const { return m_bRegistered; }
    
    X_INLINE void SetPause(xbool bPause) { m_bPause = bPause; }
    X_INLINE void SetRegistered(xbool bRegistered) { m_bRegistered = bRegistered; }
    
    X_INLINE const ListenerID& GetListenerID() const { return m_ListenerID; }
    
    X_INLINE xint32 GetFixedPriority() const { return m_nFiexdPriority; }
    X_INLINE void SetFixedPriority(xint32 nFiexdPriority) { m_nFiexdPriority = nFiexdPriority; }
    
    X_INLINE XEActor* GetAssociatedActor() const { return m_Actor; }
    X_INLINE void   SetAssociatedActor(XEActor* pActor) { m_Actor = pActor; }
    
protected:
    
    Type    m_eType;
    ListenerID  m_ListenerID;
    
    xbool   m_bEnabled;
    xbool   m_bPause;
    xbool   m_bRegistered;
    
    // 优先级
    xint32  m_nFiexdPriority;
    
    XEActor*    m_Actor;
    
    std::function<void(Event*)> m_fOnEvent;
    
    friend class EventDispatcher;
};

XESCENE_NAMESPACE_END

#endif /* XESEVENTLISTENER_H_ */
