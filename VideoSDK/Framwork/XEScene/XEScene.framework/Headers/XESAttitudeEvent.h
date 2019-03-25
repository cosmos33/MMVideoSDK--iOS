//
//  XESAttitudeEvent.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESATTITUDEEVENT_H_
#define XESATTITUDEEVENT_H_

#include "core/XESSensor.h"
#include "core/events/XESEvent.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class AttitudeEvent : public Event {
    
public:
    
    AttitudeEvent();
    
    virtual ~AttitudeEvent() override;
    virtual void Release() override;
    
    X_INLINE const Attitude* GetAttitude() const { return m_pAttitude; }
    
    void  SetAttitude(Attitude* pAttitude) { m_pAttitude = pAttitude; }
    
    
protected:
    
    Attitude* m_pAttitude;
    
};

XESCENE_NAMESPACE_END

#endif /* XESATTITUDEEVENT_H_ */
