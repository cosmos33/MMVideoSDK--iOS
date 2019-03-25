//
//  XESModuleManager.h
//  XEScene
//
//  Created by momo783 on 07/03/2018.
//

#ifndef XESMODULEMANAGER_H_
#define XESMODULEMANAGER_H_

#include "core/XESObject.h"
#include "filter/modules/XESModule.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class World;

class ModuleManager : public Object {
    
public:
    
    static ModuleManager* GetInstance();
    
    Module* CreateModule(Module::ModuleType eModuleType, XEActor* pActor, World* pWorld = NULL);
    
    Module* GetModule(XEActor* pActor);
    
    void ClearModules(XEActor* pActor);
    
protected:
    
    ModuleManager();
    
    virtual ~ModuleManager() override;
    virtual void Release() override;
    
protected:
    
    XHashTable<XEActor*, Module*> m_Modules;
    
};

XESCENE_NAMESPACE_END

#endif /* XESMODULEMANAGER_H_ */
