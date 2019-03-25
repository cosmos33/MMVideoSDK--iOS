//
//  XESModuleTriggerSensor.h
//  XEScene
//
//  Created by momo783 on 07/03/2018.
//

#ifndef XESMODULETRIGGERCV_H_
#define XESMODULETRIGGERCV_H_

#include "filter/modules/XESModuleTrigger.h"
#include "core/XESGeometry.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class CVObjectEventListener;
class ModuleTriggerCVObject : public ModuleTrigger {
    
public:
    ModuleTriggerCVObject(XEActor* pActor);
    virtual ~ModuleTriggerCVObject() override;
    
    typedef std::function<void(XEActor*, Rect)> CVObjectTriggerCallBack;
    
    CVObjectTriggerCallBack OnObjectTriggerEvent;
    
public:
    
    XString m_triggerTime;
    
    static  const XString MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
protected:
    CVObjectEventListener *m_pCVObjectEventListener;
};

XESCENE_NAMESPACE_END

#endif /* XESMODULETRIGGERCV_H_ */
