//
//  XESTouchEvent.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESTOUCHEVENT_H_
#define XESTOUCHEVENT_H_

#include "core/events/XESEvent.h"
#include "core/XESTouch.h"

#include <vector>
#include <iostream>

XESCENE_NAMESPACE_BEGIN

class TouchEvent : public Event {
    
public:
    static const int MAX_TOUCHES;
    
    enum EventCode
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELLED,
        
        HITTEST
    };
    
    TouchEvent();
    virtual void Release();
    
    X_INLINE EventCode GetEventCode() const { return m_nEventCode; }
    X_INLINE const std::vector<Touch*>& GetTouches() const { return m_vTouches; }
    
    void SetEventCode(EventCode nEventCode) { m_nEventCode = nEventCode; }
    void SetTouches(const std::vector<Touch*>& touches) { m_vTouches = touches; }
    
private:
    
    EventCode m_nEventCode;
    
    friend class GLView;
    friend class Window;
    
    std::vector<Touch*> m_vTouches;
    
};

XESCENE_NAMESPACE_END

#endif /* XESTOUCHEVENT_H_ */
