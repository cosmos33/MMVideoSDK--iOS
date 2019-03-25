//
//  XESFace.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESFACE_H_
#define XESFACE_H_

#include "core/XESObject.h"
#include "core/XESGeometry.h"

XESCENE_NAMESPACE_BEGIN

class Face : public Object {
    
public:
    enum Expression {
        NONE            = 0,
        
        MOUTH_OPENING   = 1 << 0,
        MOUTH_OPEN      = 1 << 1,
        
        LEFT_EYE_OPEN   = 1 << 2,
        LEFT_EYE_CLOSING = 1 << 3,
        LEFT_EYE_BLINK  = 1 << 4,
        
        RIGHT_EYE_OPEN  = 1 << 5,
        RIGHT_EYE_CLOSING = 1 << 6,
        RIGHT_EYE_BLINK = 1 << 7,
        
        EYE_BLINK       = 1 << 8,
        
        SMILE           = 1 << 9,
        DUCKFACE        = 1 << 10,
        
        NOD             = 1 << 11
    };

    Face();
    virtual ~Face() override;
    virtual void Release() override;
    
    Face* Clone();
    
public:
    // 人脸追踪ID
    xint32 m_nTrackId;
    
    // 姿态
    xfloat32    m_fPitch;
    xfloat32    m_fYaw;
    xfloat32    m_fRoll;
    
    // 人脸区域
    Rect    m_rBounds;
    
    // 人脸96点
    XArray<XVECTOR2> m_aLandmarks;
    
XESCENE_CONSTRUCTOR_ACCESS:
    
    X_INLINE xint32 GetTrackId() const { return m_nTrackId; }
    
    X_INLINE XVECTOR3 GetEulerAngle() const { return XVECTOR3(m_fPitch,m_fYaw,m_fRoll); }
    
    X_INLINE Rect GetBounds() const { return m_rBounds; }
    
    X_INLINE XArray<XVECTOR2> GetLandmarks() const { return m_aLandmarks; }
    
public:
    xint32  m_nExpression;
    
XESCENE_CONSTRUCTOR_ACCESS:
    
    X_INLINE xint32 GetExpression() const { return m_nExpression; }
    
public:
    // 人脸3D信息
    XMATRIX3    m_mCameraMatrix;
    XMATRIX3    m_mRotationMatrix;
    
    XVECTOR3    m_vRotationVector;
    XVECTOR3    m_vTranslationVector;
    
    XMATRIX4    m_mProjectionMatrix;
    XMATRIX4    m_mModelViewMatrix;
    
    XMATRIX4    GetModelViewMatrix();
    
public:
    // Facerig
    XVECTOR3    m_vFaceRigEulerVector;
    XArray<xfloat32> m_aFacerigStates;

};

class Expression : public Object {
public:
    enum Eye {
        E_CLOSE = 0,
        E_OPEN  = 1
    };

    enum Mouth {
        M_NOTHING = 0,
        M_DUZUI   = 1,
        M_SMILE   = 2,
        M_OPEN    = 3
    };

    enum Head {
        H_MIDDLE = 0,
        H_LEFT   = 1,
        H_IGHT  = 2,
        H_UP     = 3,
        H_DOWN   = 4
    };

    enum Neck {
        N_MIDDLE = 0,
        N_LEFT   = 1,
        N_RIGHT  = 2,
    };

public:

    Expression();

    virtual ~Expression() override;

    virtual void Release() override;

public:

    Eye m_leye;
    Eye m_reye;
    Mouth m_mouth;
    Head  m_head;
    Neck  m_neck;

    XString expression();
};

XESCENE_NAMESPACE_END

#endif /* XESFACE_H_ */
