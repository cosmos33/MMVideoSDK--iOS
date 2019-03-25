//
//  XESModuleTriggerTouch.h
//  XEScene
//
//  Created by momo783 on 07/03/2018.
//

#ifndef XESMODULETRIGGERTOUCH_H_
#define XESMODULETRIGGERTOUCH_H_

#include "filter/modules/XESModuleTrigger.h"
#include <vector>

class XEActor;

XESCENE_NAMESPACE_BEGIN

class Touch;
class TouchEventListenerAllAtOne;

class ModuleTriggerTouch : public ModuleTrigger {
    
public:
    ModuleTriggerTouch(XEActor* pActor);
    virtual ~ModuleTriggerTouch() override;
    
    static  const XString   MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
    void SetCallBackSkipTime(xint32 nSkipTimes);
    
public:
    typedef std::function<void(XEActor*, Touch*, xbool, xbool)> TriggerClickCallBack;
    typedef std::function<void(XEActor*, Touch*, xbool)> TriggerMoveCallBack;
    typedef std::function<void(XEActor*, const std::vector<Touch*>&, xfloat32,xbool)> TriggerPinchCallBack;
    
    TriggerClickCallBack     OnTouchClickEvent;
    TriggerMoveCallBack      OnTouchMoveEvent;
    TriggerPinchCallBack     OnTouchPinchEvent;
    
protected:
    
    xbool m_TouchClick;
    xbool m_TouchLongClick;
    
    xint32 m_TouchMoves;
    xint32 m_TouchMoveId;
    
    xbool m_TouchPinch;
    XVECTOR2 m_TouchPinchBegin; // x -> dis ; y -> scale;
    
    XVECTOR2 m_TouchMoveBeginPoint;
    
    xint32   m_nSkipTimes;
    xint32   m_nCallTimes;
    
    TouchEventListenerAllAtOne *m_pTouchEventListener;
};

XESCENE_NAMESPACE_END

#endif /* XESMODULETRIGGERTOUCH_H_ */
