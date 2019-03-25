//
//  XESEvent.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESEVENT_H_
#define XESEVENT_H_

#include "core/XESObject.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class Event : public Object {
    
public:
    enum Type {
        TOUCH,
        FACE,
        EXPRESSION,
        ATTITUDE,
        ACCELERATION,
        CVBODY,
        CVOBJECT,
        HAND,
        CUSTOM
    };
    
    Event(Type mType);
    
public:
    
    virtual ~Event() override;
    
    virtual void Release() override;
    
    X_INLINE Type GetType() { return m_eType; }
    
    X_INLINE XEActor* GetTarget() { return m_pTraget; }
    
    X_INLINE xbool IsStopped() const { return m_bStopped; }
    
protected:
    
    X_INLINE    void SetTarget(XEActor* pActor) { m_pTraget = pActor; }
    
    Type        m_eType;
    XEActor*    m_pTraget;
    
    xbool       m_bStopped;
    
    friend class EventDispatcher;
    
};

XESCENE_NAMESPACE_END

#endif /* XESEVENT_H_ */
