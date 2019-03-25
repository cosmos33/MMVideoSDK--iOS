//
//  XESAccelerationEventListener.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESACCELERATIONEVENTLISTENER_H_
#define XESACCELERATIONEVENTLISTENER_H_

#include "core/events/XESEventListener.h"

XESCENE_NAMESPACE_BEGIN

class Acceleration;

class AccelerationEventListener : public EventListener {
    
public:
    static const ListenerID LISTENER_ID;
    
    static AccelerationEventListener* Create();
    
    virtual ~AccelerationEventListener() override;
    virtual void Release() override;
    
    virtual xbool CheckAvailable() override;
    virtual AccelerationEventListener* Clone() override;

XESCENE_CONSTRUCTOR_ACCESS:
    AccelerationEventListener();

    xbool Init(const std::function<void(const Acceleration*, Event* event)>& callback);

    xbool Init();

public:
    
    typedef std::function<void(const Acceleration*, Event*)> AccelerationCallback;
    
    AccelerationCallback   OnAccelerationChangeCallback;
    
private:
    
    friend class EventDispatcher;
};

XESCENE_NAMESPACE_END

#endif /* XESACCELERATIONEVENTLISTENER_H_ */
