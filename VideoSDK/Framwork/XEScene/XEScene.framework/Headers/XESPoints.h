//
//  XESPoints.h
//  XEScene
//
//  Created by momo783 on 23/02/2018.
//

#ifndef XESPOINTS_H_
#define XESPOINTS_H_

#include "core/XESObject.h"

#include <vector>

XESCENE_NAMESPACE_BEGIN

class Points : public Object {
    
public:
    static Points* Create(xint32 nSize);
    
    Points();
    virtual ~Points() override;
    virtual void Release() override;
    
    void AddControlPoint(const XVECTOR3& cPoint);
    
    void InsertControlPoint(const XVECTOR3& cPoint, xint32 index);
    
    void ReplaceControlPoint(const XVECTOR3& cPoint, xint32 index);
    
    XVECTOR3 GetControlPointAt(xint32 index);
    
    void RemoveControlPointAt(xint32 index);
    
    xint32 Num() const;
    
    void ReverseInline();
    
    Points* Reverse() const;
    
    virtual Points* Clone() const;
    
    const std::vector<XVECTOR3>* GetControlPoints() const { return m_pControlPoints; };
    
    void SetControlPoints(std::vector<XVECTOR3>* cPoints);
    
protected:
    
    std::vector<XVECTOR3>* m_pControlPoints;
};

extern XVECTOR3 CardinalSplineAt(XVECTOR3& p0, XVECTOR3& p1, XVECTOR3& p2, XVECTOR3& p3, xfloat32 tension, xfloat32 t);

XESCENE_NAMESPACE_END

#endif /* XESPOINTS_H_ */
