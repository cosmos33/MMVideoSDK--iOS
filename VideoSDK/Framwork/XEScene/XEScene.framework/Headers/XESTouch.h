//
//  XESTouch.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESTOUCH_H_
#define XESTOUCH_H_

#include "core/XESObject.h"

XESCENE_NAMESPACE_BEGIN

class Touch : public Object {
    
public:
    enum DispatchMode {
        ALL_AT_ONE,
        ONE_BY_ONE
    };
    
    Touch();
    
    void        SetTouchInfo(xint32 nId, xfloat32 x, xfloat32 y);
    void        SetTouchInfo(xint32 nId, xfloat32 x, xfloat32 y, xfloat32 fForce, xfloat32 fMaxForce);
    
    XVECTOR2    GetLocation();
    XVECTOR2    GetStartLocation();
    XVECTOR2    GetPreviousLocation();
    XVECTOR2    GetDelta();
    
    XVECTOR2    GetLocationInView();
    XVECTOR2    GetStartLocationInView();
    XVECTOR2    GetPreviousLocationInView();
    
    X_INLINE    xint32 GetID() { return m_nId; }
    X_INLINE    xfloat32 GetCurrentForce() { return m_fCurForce; }
    X_INLINE    xfloat32 GetMaxForce() { return m_fMaxForce; }
    
protected:
    
    xint32  m_nId;
    xbool   m_bStratPointCaptured;
    
    XVECTOR2    m_vStartPoint;
    XVECTOR2    m_vPoint;
    XVECTOR2    m_vPrevPoint;
    
    xfloat32    m_fCurForce;
    xfloat32    m_fMaxForce;
    
};

XESCENE_NAMESPACE_END

#endif /* XESTOUCH_H_ */
