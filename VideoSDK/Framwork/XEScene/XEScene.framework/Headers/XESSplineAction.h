//
//  XESSplineAction.h
//  XEScene
//
//  Created by momo783 on 09/02/2018.
//

#ifndef XESSPLINEACTION_H_
#define XESSPLINEACTION_H_

#include "core/XESPoints.h"
#include "core/actions/XESIntervalAction.h"

XESCENE_NAMESPACE_BEGIN

/**
 *  http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 */

class SplineTo : public IntervalAction {
    
public:
    static SplineTo* Create(xfloat32 mDuration, Points* pPoints, xfloat32 fTension);
    
    SplineTo();
    virtual ~SplineTo() override;
    virtual void Release() override;
    
    xbool InitWithDuration(xfloat32 mDuration, Points* pPoints, xfloat32 fTension);
    
    X_INLINE Points* GetPoints() const { return m_pPoints; }
    X_INLINE void SetPoints(Points* pPoints) {
        if (m_pPoints) {
            X_SAFEDELETE(m_pPoints);
        }
        m_pPoints = pPoints;
    }
    
    virtual void UpdatePosition(XVECTOR3& vPos);
    
    // Override
    virtual void Start(XEActor *pActor) override;
    
    virtual SplineTo* Clone() const override;
    virtual SplineTo* Reverse() const override;
    
    virtual void Update(xfloat32 fTime) override;
    
protected:
    
    Points* m_pPoints;
    
    xfloat32 m_fDeltaT;
    xfloat32 m_fTension;
    
    XVECTOR3 m_PreviousPosition;
    XVECTOR3 m_AccumulatedDiff;
    
};

class SplineBy : public SplineTo {
    
public:
    static SplineBy* Create(xfloat32 mDuration, Points* pPoints, xfloat32 fTension);
    
    SplineBy();
    
    virtual void Start(XEActor *pActor) override;
    
    virtual SplineBy* Clone() const override;
    virtual SplineBy* Reverse() const override;
    
    virtual void UpdatePosition(XVECTOR3& vPos) override;
    
protected:
    
    XVECTOR3 m_StartPosition;
};

/**
 *  http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 */

class CatmullRomTo : public SplineTo {
    
public:
    static CatmullRomTo* Create(xfloat32 fDuration, Points* pPoints);
    
    xbool InitWithDuration(xfloat32 fDuration, Points* pPoints);
    
    // Override
    virtual CatmullRomTo* Clone() const override;
    virtual CatmullRomTo* Reverse() const override;
};

class CatmullRomBy : public CatmullRomTo {
    
public:
    static CatmullRomBy* Create(xfloat32 fDuration, Points* pPoints);
    
    xbool InitWithDuration(xfloat32 fDuration, Points* pPoints);
    
    // Override
    virtual CatmullRomBy* Clone() const override;
    virtual CatmullRomBy* Reverse() const override;
};

XESCENE_NAMESPACE_END

#endif /* XESSPLINEACTION_H_ */
