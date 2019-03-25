//
//  XESModuleTrigger.h
//  XEScene
//
//  Created by momo783 on 07/03/2018.
//

#ifndef XESMODULETRIGGER_H_
#define XESMODULETRIGGER_H_

#include "filter/modules/XESModule.h"
#include <functional>

class XEActor;

XESCENE_NAMESPACE_BEGIN
class Face;

class ModuleTrigger : public Module {
    
public:
    
    enum TriggerType {
        FACE,
        TOUCH,
        SENSOR,
        CV
    };
    
public:
    
    ModuleTrigger(XEActor* pActor, TriggerType tType);
    
    virtual void Tick(xfloat32 fTick) override;
    
    X_INLINE TriggerType GetTriggerType() const { return m_tType; }
    
    static  const XString MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
public:
    
    virtual ~ModuleTrigger() override;
    virtual void Release() override;
    
protected:
    
    TriggerType m_tType;
    
};


XESCENE_NAMESPACE_END

#endif /* XESMODULETRIGGER_H_ */
