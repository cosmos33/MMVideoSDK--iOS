//
//  XESModuleMaker.h
//  XEScene
//
//  Created by momo783 on 07/03/2018.
//

#ifndef XESMODULEMAKER_H_
#define XESMODULEMAKER_H_

#include "filter/modules/XESModule.h"
#include <functional>

class XEActor;

XESCENE_NAMESPACE_BEGIN

class ModuleMaker : public Module {
    
public:
    
    ModuleMaker(XEActor* pActor, World* pWorld);

    XEActor* MakeActor();
    
    void SetActorUsing(XEActor* pActor, xbool bUsing);
    
    void SetAllActroUsing(xbool bUsing);
    
    virtual void Tick(xfloat32 fTick) override;
    
    static  const XString MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
public:
    
    void SetLimitCount(xint32 nLimit) { m_nLimit = nLimit; }
    
    void SetLifeTime(xfloat32 fTime) { m_fLifeTime = fTime; }
    
    typedef std::function<void(const XEActor*)> ActorLifeTimeoutCallBack;

    ActorLifeTimeoutCallBack OnActorTimeOut;
    
public:
    
    virtual ~ModuleMaker() override;
    virtual void Release() override;
    
protected:
    
    World*   m_pWorld;
    
    XArray<XEActor*> m_Actors;
    XHashTable<XEActor*, xbool> m_ActorStatus;
    XHashTable<XEActor*, xfloat32> m_ActorTimes;
    
    xint32   m_nLimit;
    xfloat32 m_fLifeTime;
    
    friend class ModuleDetectPass;
    
};

XESCENE_NAMESPACE_END

#endif /* XESMODULEMAKER_H_ */
