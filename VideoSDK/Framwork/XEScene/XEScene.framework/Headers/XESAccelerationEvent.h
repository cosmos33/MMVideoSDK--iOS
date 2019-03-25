//
//  XESAccelerationEvent.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESACCELERATIONEVENT_H_
#define XESACCELERATIONEVENT_H_

#include "core/events/XESEvent.h"
#include "core/XESSensor.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class AccelerationEvent : public Event {
    
public:
    
    AccelerationEvent();
    
    virtual ~AccelerationEvent() override;
    virtual void Release() override;
    
    X_INLINE const Acceleration* GetAcceleration() const { return m_pAcceleration; }
    
    void  SetAcceleration(Acceleration* pAcceleration) { m_pAcceleration = pAcceleration; }
    
    
protected:
    
    Acceleration* m_pAcceleration;

};

XESCENE_NAMESPACE_END

#endif /* XESACCELERATIONEVENT_H_ */
