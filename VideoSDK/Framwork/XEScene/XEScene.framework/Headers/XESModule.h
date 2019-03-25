//
//  XESModule.h
//  XEScene
//
//  Created by momo783 on 07/03/2018.
//

#ifndef XESMODULE_H_
#define XESMODULE_H_

#include "core/XESObject.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class World;

class Module : public Object {
    
public:
    
    enum ModuleType {
        MAKER,
        TRIGGER,
        DETECTOR
    };
    
    Module(XEActor* pActor, ModuleType eType);
    
    virtual ~Module() override;
    virtual void Release() override;
    
    virtual void Tick(xfloat32 fDelta) = 0;
    
    virtual const XString&  GetTypeName() const { return MODULE_TYPENAME; }
    
    X_INLINE ModuleType GetModuleType() const { return m_moduleType; }
    X_INLINE XEActor* GetTarget() const { return m_pActor; }
    
protected:
    
    XEActor*    m_pActor;
    ModuleType  m_moduleType;
    
    static const XString MODULE_TYPENAME;
};

XESCENE_NAMESPACE_END

#endif /* XESMODULE_H_ */
