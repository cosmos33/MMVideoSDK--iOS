//
//  XESAction.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESACTION_H_
#define XESACTION_H_

#include "core/XESObject.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class Action : public Object {
    
public:
    static const xint32 INVALID_TAG;
    
    virtual Action* Clone() const { XESAssert(0);return nullptr; }

    virtual Action* Reverse() const { XESAssert(0);return nullptr; }
    
    virtual void Start(XEActor* pActor);
    
    virtual xbool IsDone();
    
    virtual void Stop();
    
    virtual void Tick(xfloat32 fDelta);  /** Time Tick */
    
    virtual void Update(xfloat32 fTime); /** 0 ~ 1.0 */
    
    // Action's Description
    virtual XString Description();
    
    X_INLINE XEActor* GetTarget() const { return m_pTarget; }
    X_INLINE XEActor* GetOriginalTarget() const { return m_pOriginalTaget; }
    
    void  SetTarget(XEActor* pTarget) { m_pTarget = pTarget; }
    
    X_INLINE xint32  GetTag() const {  return m_nTag; }
    X_INLINE xuint32 GetFlags() const { return m_uFlags; }
    
    void  SetTag(xint32 nTag) { m_nTag = nTag; }
    void  SetFlags(xuint32 uFlags) { m_uFlags = uFlags; }
    
    
    virtual ~Action() override;
    virtual void Release() override;
    
protected:
    
    Action();
    
    void  SetOriginalTarget(XEActor* pOriginalTarget) { m_pOriginalTaget = pOriginalTarget; }
    
protected:
    
    XEActor*  m_pTarget;
    XEActor*  m_pOriginalTaget;
    
    xint32    m_nTag;
    xuint32   m_uFlags;
    
};

/**
 *  Finite Time Action, Base Class, Do not can be created
 */
class FiniteTimeAction : public Action {
    
public:
    
    X_INLINE xfloat32 GetDuration() const { return m_Duration; }
    
    X_INLINE void  SetDuration(xfloat32 mDuration) { m_Duration = mDuration; }
    
    virtual FiniteTimeAction* Clone() const override {
        XESAssert(0); return nullptr;
    }
    
    virtual FiniteTimeAction* Reverse() const override {
        XESAssert(0); return nullptr;
    }
    
protected:
    
    FiniteTimeAction();
    
public:
    virtual ~FiniteTimeAction() override;
    virtual void Release() override;
    
protected:
    
    xfloat32    m_Duration;
    
};

XESCENE_NAMESPACE_END

#endif /* XESACTION_H_ */
