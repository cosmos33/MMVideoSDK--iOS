//
//  XESAttitudeEventListener.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESATTITUDEEVENTLISTENER_H_
#define XESATTITUDEEVENTLISTENER_H_

#include "core/events/XESEventListener.h"

XESCENE_NAMESPACE_BEGIN

class Attitude;

class AttitudeEventListener : public EventListener {

XESCENE_CONSTRUCTOR_ACCESS:
    AttitudeEventListener();
    xbool Init();
    
public:
    static const ListenerID LISTENER_ID;
    
    static AttitudeEventListener* Create();
    
    virtual ~AttitudeEventListener() override;
    virtual void Release() override;
    
    virtual xbool CheckAvailable() override;
    virtual AttitudeEventListener* Clone() override;
    
public:
    
    typedef std::function<void(const Attitude*, Event*)> AttitudeCallback;
    
    AttitudeCallback   OnAttitudeChangeCallback;
    
private:
    
    friend class EventDispatcher;
};

XESCENE_NAMESPACE_END

#endif /* XESATTITUDEEVENTLISTENER_H_ */
