//
//  XESModuleMDetector.h
//  XEScene
//
//  Created by momo783 on 07/03/2018.
//

#ifndef XESMODULEDETECTOR_H_
#define XESMODULEDETECTOR_H_

#include "filter/modules/XESModule.h"
#include "core/XESGeometry.h"

#include <functional>

class XEActor;

XESCENE_NAMESPACE_BEGIN

class ModuleMaker;

class ModuleDetector : public Module {
    
public:
    enum DType {
        GO_THROUGH,
        OUT_SCREEN,
        RAY_DETECT
    };
    
public:
    
    ModuleDetector(XEActor* pActor, DType dType);
    
    virtual void Tick(xfloat32 fTick) override;
    
    X_INLINE DType GetDType() const { return m_dType; }
    
    static  const XString   MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
    
public:
    
    typedef std::function<void(const XEActor*, xbool bDetected)> DetectorSuccessCallBack;
    
    DetectorSuccessCallBack OnDetectedCallback;
    
    typedef std::function<void(const XEActor*)> DetectorTimeoutCallBack;
    
    DetectorTimeoutCallBack OnDetectedTimeoutCallback;
    
public:
    
    virtual ~ModuleDetector() override;
    virtual void Release() override;
    
protected:
    
    DType  m_dType;
    
};

class ModuleDetectPass : public ModuleDetector {
    
public:
    
    ModuleDetectPass(XEActor* pActor, XEActor* pPostionTarget, ModuleMaker*pTarget);
    
    virtual void Tick(xfloat32 fTick) override;
    
    static  const XString   MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
public:
    
    XVECTOR3 m_TargetPosition;
    XVECTOR3 m_Offset;
    
    XVECTOR3 m_AABBSize;
    XCusAABB m_ThroughAABB;
    
protected:
    
    XEActor* m_pPositionTarget;
    ModuleMaker* m_pTarget;
    
    XHashTable<XEActor*, xbool> m_ActorPass;
    
    virtual ~ModuleDetectPass() override;
    virtual void Release() override;
    
    
};

class ModuleDetectOut : public ModuleDetector {
    
public:
    
    ModuleDetectOut(XEActor* pActor);
    
    virtual void Tick(xfloat32 fTick) override;
    
    static  const XString MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
    xbool  m_bPause;
    
public:
    
    void SetScreenBounds(Rect vRect);
    
protected:
    
    XVECTOR2 m_vMin;
    XVECTOR2 m_vMax;
    
    virtual ~ModuleDetectOut() override;
    virtual void Release() override;
    
    XVECTOR3 HitScreenPoint(const XVECTOR2& vScreenPoint, const XVECTOR3& vPos);
    
};

XESCENE_NAMESPACE_END

#endif /* XESMODULEDETECTOR_H_ */
