//
//  XESCVAboutEvent.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESCVABOUTEVENT_H_
#define XESCVABOUTEVENT_H_

#include "core/events/XESEvent.h"
#include "core/XESCVAbout.h"

XESCENE_NAMESPACE_BEGIN

class CVBodyEvent : public Event {
    
public:
    
    enum EventCode {
        DEFAULT,
        TRACKING
    };
    
    CVBodyEvent(EventCode nEventCode);
    
    virtual ~CVBodyEvent() override;
    virtual void Release() override;
    
    X_INLINE EventCode GetEventCode() const { return m_nEventCode; }
    
    X_INLINE XArray<CVBody*>& GetBodys() { return m_aBodys; }
    
    void  SetBodys(XArray<CVBody*> aBodys) { m_aBodys = aBodys; }
    
    
protected:
    
    EventCode m_nEventCode;
    
    XArray<CVBody*> m_aBodys;
};

class CVObjectEvent : public Event {
    
public:
    
    enum EventCode {
        DEFAULT,
        TRACKING
    };
    
    CVObjectEvent(EventCode nEventCode);
    
    virtual ~CVObjectEvent() override;
    virtual void Release() override;
    
    X_INLINE EventCode GetEventCode() const { return m_nEventCode; }
    
    X_INLINE XArray<CVObject*> GetObjects() const { return m_aObjects; }
    
    void  SetObjects(XArray<CVObject*> aObjects) { m_aObjects = aObjects; };
    
    
protected:
    
    EventCode m_nEventCode;

    XArray<CVObject*> m_aObjects;
};

XESCENE_NAMESPACE_END

#endif /* XESCVABOUTEVENT_H_ */
