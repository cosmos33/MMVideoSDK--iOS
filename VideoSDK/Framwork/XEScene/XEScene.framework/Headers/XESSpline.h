//
// Created by momo783 on 02/07/2018.
//

#ifndef XES_XESSPLINE_H
#define XES_XESSPLINE_H

#include "XESObject.h"
#include "XESPoints.h"

XESCENE_NAMESPACE_BEGIN

class Spline  : public Object {

public:
    
    static Spline* Create(Points* pPoints, xfloat32 fTension);
    
    Spline(Points* pPoints, xfloat32 fTension);

    virtual ~Spline();
    virtual void Release() {};

    virtual XVECTOR3 GetPoint(xfloat32 fDurationScale); /* 0.0 ~ 1.0 */

    static void DestoryLine(Spline* pSpline);

protected:

    Points* m_Points;

    xfloat32 m_fTension;

};

class CatmullRomSpline : public Spline {
public:

    static CatmullRomSpline* Create(Points* pPoints);
    
    CatmullRomSpline(Points* pPoints) : Spline(pPoints, 0.5f) {}

    virtual ~CatmullRomSpline() {}
    virtual void Release() {}

};

XESCENE_NAMESPACE_END


#endif //XES_XESSPLINE_H
