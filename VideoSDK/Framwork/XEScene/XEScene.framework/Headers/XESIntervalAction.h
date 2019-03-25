//
//  XESIntervalAction.h
//  XEScene
//
//  Created by momo783 on 09/02/2018.
//

#ifndef XESINTERVALACTION_H_
#define XESINTERVALACTION_H_

#include "core/actions/XESAction.h"
#include <vector>

XESCENE_NAMESPACE_BEGIN

class IntervalAction : public FiniteTimeAction {
    
public:

    // 累计Tick时间
    X_INLINE xfloat32 GetElapsed() { return m_fElapsed; }
    
    
    void SetAmplitudeRate(xfloat32 mRate);
    xfloat32 GetAmplitudeRate();
    
    virtual xbool IsDone() override;
    
    virtual void Tick(xfloat32 fDelta) override;  /** Time Tick */
    
    virtual void Start(XEActor *pActor) override;
    
    virtual IntervalAction* Clone() const override {
        XESAssert(0); return nullptr;
    }
    
    virtual IntervalAction* Reverse() const override {
        XESAssert(0); return nullptr;
    }
    
protected:
    xbool InitWithDuration(xfloat32 mDuration);
    
protected:
    
    xbool m_bFirstTick;
    xfloat32 m_fElapsed;
};

/**
 *  Move Action
 */
class MoveBy : public IntervalAction {
    
public:
    
    static MoveBy* Create(xfloat32 mDuration, const XVECTOR3& dPos);
    
    virtual MoveBy* Clone() const override;
    virtual MoveBy* Reverse() const override;
    
    virtual void Start(XEActor* pActor) override;
    
    virtual void Update(xfloat32 fTime) override;
    
protected:
    MoveBy() {};
    
    virtual ~MoveBy() override {};
    virtual void Release() override {};
    
    xbool InitWithDuration(xfloat32 mDuration, const XVECTOR3& dPos);
    
protected:
    
    XVECTOR3 m_PositionDelta;
    XVECTOR3 m_StartPosition;
    XVECTOR3 m_PreViousPosition;
    
};

class MoveTo : public MoveBy {
    
public:
    
    static MoveTo* Create(xfloat32 mDuration, const XVECTOR3& dPos);
    
    virtual MoveTo* Clone() const override;
    virtual MoveTo* Reverse() const override;
    
    virtual void Start(XEActor* pActor) override;
    
protected:
    MoveTo(){};
    
    virtual ~MoveTo() override {};
    virtual void Release() override {};
    
    xbool InitWithDuration(xfloat32 mDuration, const XVECTOR3& dPos);
    
protected:
    
    XVECTOR3 m_EndPosition;
    
};

/**
 *  Scale Action
 */

class ScaleTo : public IntervalAction {
    
public:
    
    static ScaleTo* Create(xfloat32 mDuration, float s);
    static ScaleTo* Create(xfloat32 mDuration, float sx, float sy, float sz);
    
    //
    virtual ScaleTo* Clone() const override;
    virtual ScaleTo* Reverse(void) const override;
    virtual void Start(XEActor* pActor) override;

    virtual void Update(xfloat32 fTime) override;
    
protected:
    ScaleTo() {}
    virtual ~ScaleTo() override {};
    virtual void Release() override {};
    
    xbool InitWithDuration(xfloat32 mDuration, float s);
    xbool InitWithDuration(xfloat32 mDuration, float sx, float sy, float sz);
    
protected:
    XVECTOR3 m_Scale;
    XVECTOR3 m_StartScale;
    XVECTOR3 m_EndScale;
    XVECTOR3 m_DeltaScale;
};

class ScaleBy : public ScaleTo {
    
public:
    
    static ScaleBy* Create(xfloat32 mDuration, float s);
    static ScaleBy* Create(xfloat32 mDuration, float sx, float sy, float sz);
    
    //
    virtual ScaleBy* Clone() const override;
    virtual ScaleBy* Reverse(void) const override;
    virtual void Start(XEActor* pActor) override;
    
protected:
    ScaleBy() {}
    virtual ~ScaleBy() override {};
    virtual void Release() override {};
};

/**
 *  Rotate Action
 */
class RotateBy : public IntervalAction {
    
public:
    
    static RotateBy* Create(xfloat32 mDuration, const XVECTOR3& mDelatAngle);
    
    //
    virtual RotateBy* Clone() const override;
    virtual RotateBy* Reverse(void) const override;
    virtual void Start(XEActor* pActor) override;
    
    virtual void Update(xfloat32 fTime) override;
    
protected:
    RotateBy() {};
    
    virtual ~RotateBy() override {};
    virtual void Release() override {};
    
    xbool InitWithDuration(xfloat32 mDuration, const XVECTOR3& mDelatAngle);
    
protected:
    
    XVECTOR3 m_DeltaAngle;
    XVECTOR3 m_StartAngle;
    
};

class RotateTo : public IntervalAction {
    
public:
    
    static RotateTo* Create(xfloat32 mDuration, const XVECTOR3& mDstAngle);
    
    //
    virtual RotateTo* Clone() const override;
    virtual RotateTo* Reverse(void) const override;
    virtual void Start(XEActor* pActor) override;
    
    virtual void Update(xfloat32 fTime) override;
    
protected:
    RotateTo() {};
    
    virtual ~RotateTo() override {};
    virtual void Release() override {};
    
    xbool InitWithDuration(xfloat32 mDuration, const XVECTOR3& mDstAngle);
    void CalculateAngles(float &startAngle, float &diffAngle, float dstAngle);
    
protected:
    
    XVECTOR3 m_DstAngle;
    XVECTOR3 m_StartAngle;
    XVECTOR3 m_DiffAngle;
};

/**
 *  Repeat Action
 */
class Repeat : public IntervalAction {
  
public:
    
    static Repeat* Create(FiniteTimeAction* mAction, xuint32 mTimes);
    
    X_INLINE FiniteTimeAction* GetInnerAction() { return m_pInnerAction; }
    
    virtual void Start(XEActor *pActor) override;
    
    virtual Repeat* Clone() const override;
    virtual Repeat* Reverse() const override;
    
    virtual void Stop() override;
    
    virtual void Update(xfloat32 fTime) override;
    virtual xbool IsDone() override;
    
protected:
    Repeat();
    
    virtual ~Repeat() override;
    virtual void Release() override;
    
    xbool InitWithAction(FiniteTimeAction* mAction, xuint32 mTimes);
    
protected:
    
    xuint32 m_nTimes;
    xuint32 m_nTotal;
    
    xfloat32 m_fNextDt;
    xbool  m_bActionInstant;
    
    FiniteTimeAction* m_pInnerAction;
    
};

class RepeatForever : public IntervalAction {
public:
    
    static RepeatForever* Create(IntervalAction* mAction);
    
    X_INLINE FiniteTimeAction* GetInnerAction() { return m_pInnerAction; }
    
    virtual void Start(XEActor *pActor) override;
    
    virtual RepeatForever* Clone() const override;
    virtual RepeatForever* Reverse() const override;
    
    virtual void Tick(xfloat32 fDelta) override;
    virtual xbool IsDone() override;
    
protected:
    RepeatForever();
    
    virtual ~RepeatForever() override;
    virtual void Release() override;
    
    xbool InitWithAction(IntervalAction* mAction);
    
protected:
    
    IntervalAction* m_pInnerAction;
};


/**
 *  Sequence Action
 */
class Sequence : public IntervalAction {
    
public:
    static Sequence* Create(FiniteTimeAction* mAction1, ...) XESCENE_REQUIRES_NULL_TERMINATION;
    
    static Sequence* Create(const std::vector<XESCENE_NAMESPACE::FiniteTimeAction*>& mActions);
    
    static Sequence* CreateWithVariableList(FiniteTimeAction* mAction1, va_list args);
    
    static Sequence* CreateWithTwoActions(FiniteTimeAction* mAction1, FiniteTimeAction* mAction2);
    
    virtual void Start(XEActor *pActor) override;
    
    virtual Sequence* Clone() const override;
    virtual Sequence* Reverse() const override;
    
    virtual void Stop() override;
    
    virtual void Update(xfloat32 fTime) override;
    
protected:
    
    Sequence();
    
    virtual ~Sequence() override;
    virtual void Release() override;
    
    xbool Init(const std::vector<XESCENE_NAMESPACE::FiniteTimeAction*>& mActions);
    xbool InitWithTwoActions(FiniteTimeAction *pAction1, FiniteTimeAction *pAction2);
    
protected:
    
    FiniteTimeAction* m_pActions[2];
    
    xint32   m_iLast;
    xfloat32 m_fSplit;
    
};

XESCENE_NAMESPACE_END

#endif /* XESINTERVALACTION_H_ */
