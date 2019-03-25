//
//  XESSpeed.h
//  XEScene
//
//  Created by momo783 on 09/02/2018.
//

#ifndef XESSPEED_H_
#define XESSPEED_H_

#include "core/actions/XESAction.h"
#include "core/actions/XESIntervalAction.h"

XESCENE_NAMESPACE_BEGIN

class Speed : public Action {
    
public:

    static  Speed* Create(IntervalAction* mAction, xfloat32 fSpeed);
    
    
    X_INLINE xfloat32 GetSpeed() const { return m_fSpeed; }
    X_INLINE IntervalAction* GetInnerAction() const { return m_pInnerAction; }

    X_INLINE void SetSpeed(xfloat32 aSpeed) { m_fSpeed = aSpeed; }
    
    virtual void Start(XEActor *pActor) override;
    
    virtual Speed* Clone() const override;
    virtual Speed* Reverse() const override;
    
    virtual void Stop() override;
    
    virtual void Tick(xfloat32 fDelta) override;
    
    virtual xbool IsDone() override;
    
protected:
    Speed();
    virtual ~Speed() override;
    virtual void Release() override;
    
    xbool InitWithAction(IntervalAction* mAction, xfloat32 fSpeed);
    
protected:
    
    xfloat32 m_fSpeed;
    IntervalAction* m_pInnerAction;
    
};

XESCENE_NAMESPACE_END

#endif /* XESSPEED_H_ */
