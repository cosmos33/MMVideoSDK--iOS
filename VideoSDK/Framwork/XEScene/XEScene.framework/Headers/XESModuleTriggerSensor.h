//
//  XESModuleTriggerSensor.h
//  XEScene
//
//  Created by momo783 on 07/03/2018.
//

#ifndef XESMODULETRIGGERSENSOR_H_
#define XESMODULETRIGGERSENSOR_H_

#include "filter/modules/XESModuleTrigger.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class EventListener;
class ModuleTriggerSensor : public ModuleTrigger {
    
public:
    enum SensorType {
        ATTITUDE,
        ACCELERATION
    };
    
    static  const XString   MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
public:
    ModuleTriggerSensor(XEActor* pActor, SensorType eType);
    virtual ~ModuleTriggerSensor() override;
    
    X_INLINE SensorType GetSensorType() const { return m_eSensorType; }
    
    
    typedef std::function<void(XEActor*, XVECTOR3, xbool)> SensorTriggerCallBack;
    
    SensorTriggerCallBack OnSensorTriggerEvent;
    
    void SetSensorCallbackInterval(xfloat32 fInterval);
    
protected:
    
    SensorType m_eSensorType;
    
    EventListener *m_pListener;
    
};

XESCENE_NAMESPACE_END

#endif /* XESMODULETRIGGERSENSOR_H_ */
