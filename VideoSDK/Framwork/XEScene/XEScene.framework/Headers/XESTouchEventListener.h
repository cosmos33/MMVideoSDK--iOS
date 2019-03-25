//
//  XESTouchEventListener.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESTOUCHEVENTLISTENER_H_
#define XESTOUCHEVENTLISTENER_H_

#include "core/events/XESEventListener.h"

#include <vector>
#include <iostream>

XESCENE_NAMESPACE_BEGIN

class Touch;
typedef std::function<bool(Touch*, Event*)> TouchTitTestCallback;

class TouchEventListenerOneByOne : public EventListener {
    
XESCENE_CONSTRUCTOR_ACCESS:
    TouchEventListenerOneByOne();
    xbool Init();
    
public:
    static const XString LISTENER_ID;
    
    static TouchEventListenerOneByOne* Create();
    
    virtual ~TouchEventListenerOneByOne() override;
    virtual void Release() override;
    
    void SetSwallowTouches(xbool bNeedSwallow);
    
    xbool IsSwallowTouches();
    
    virtual TouchEventListenerOneByOne* Clone() override;
    virtual xbool CheckAvailable() override;
    
public:
    
    TouchTitTestCallback OnTouchHitTest;
    
    typedef std::function<bool(Touch*, Event*)> TouchBeganCallback;
    typedef std::function<void(Touch*, Event*)> TouchCallback;
    
    TouchBeganCallback OnTouchBegan;
    TouchCallback OnTouchMoved;
    TouchCallback OnTouchEnded;
    TouchCallback OnTouchCancelled;
    
private:
    
    xbool m_bNeedSwallow;
    std::vector<Touch*> m_vClaimedTouches;
    
    friend class EventDispatcher;
    
};

class TouchEventListenerAllAtOne : public EventListener {
    
XESCENE_CONSTRUCTOR_ACCESS:
    TouchEventListenerAllAtOne();
    xbool Init();
    
public:
    static const XString LISTENER_ID;
    
    static TouchEventListenerAllAtOne* Create();
    
    virtual ~TouchEventListenerAllAtOne() override;
    virtual void Release() override;
    
    virtual TouchEventListenerAllAtOne* Clone() override;
    virtual xbool CheckAvailable() override;
    
public:
    
    TouchTitTestCallback OnTouchHitTest;
    
    typedef std::function<void(const std::vector<Touch*>&, Event*)> TouchesCallback;
    
    TouchesCallback OnTouchesBegan;
    TouchesCallback OnTouchesMoved;
    TouchesCallback OnTouchesEnded;
    TouchesCallback OnTouchesCancelled;
    
    
    
private:
    
    friend class EventDispatcher;
};

XESCENE_NAMESPACE_END

#endif /* XESTOUCHEVENTLISTENER_H_ */
