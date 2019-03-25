//
//  XESCustomEventListener.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESCUSTOMEVENTLINSTENER_H_
#define XESCUSTOMEVENTLINSTENER_H_

#include "core/events/XESEventListener.h"
#include <functional>

XESCENE_NAMESPACE_BEGIN

class CustomEvent;

class CustomEventListener : public EventListener {
    
public:
    
    virtual ~CustomEventListener() override;
    virtual void Release() override;
    
    static CustomEventListener* Create(const XString& mEventName, const std::function<void(CustomEvent*)>& fCallback);
    
    virtual xbool CheckAvailable() override;
    virtual CustomEventListener* Clone() override;
    
XESCENE_CONSTRUCTOR_ACCESS:
    CustomEventListener();
    xbool Init(const ListenerID& listenerId, const std::function<void(CustomEvent*)>& fCallback);
    
protected:
    
    std::function<void(CustomEvent*)> m_OnCustomEvent;
};

XESCENE_NAMESPACE_END

#endif /* XESCUSTOMEVENTLINSTENER_H_ */
