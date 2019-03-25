//
//  XESSensor.h
//  XEScene
//
//  Created by momo783 on 01/03/2018.
//

#ifndef XESSENSOR_H_
#define XESSENSOR_H_

#include "core/XESObject.h"

XESCENE_NAMESPACE_BEGIN

// 姿态
class Attitude : public Object {
    
public:
    
    Attitude() {};
    virtual ~Attitude() override {};
    virtual void Release() override {};
    
public:
    
    // 欧拉角
    xfloat64 roll;
    xfloat64 pitch;
    xfloat64 yaw;
    
    // 旋转矩阵
    XMATRIX3 m_RotationMatrix;
    
    // 四元数
    XQUATERNION m_Quaternion;
    
XESCENE_CONSTRUCTOR_ACCESS:
    
    X_INLINE XVECTOR3 GetEulerAngle() const { return XVECTOR3(roll,pitch,yaw); }
    
    X_INLINE XMATRIX3 GetRotationMatrix() const { return m_RotationMatrix; }
    
    X_INLINE XQUATERNION GetQuaternion() const { return m_Quaternion; }
};

// 加速度计
class Acceleration : public Object {
    
public:
    
    Acceleration() : x(0),y(0),z(0),timestamp(0) {};
    
    virtual ~Acceleration() override {};
    virtual void Release() override {};
    
public:
    
    xfloat64    x;
    xfloat64    y;
    xfloat64    z;
    
    xfloat64 timestamp;
    
XESCENE_CONSTRUCTOR_ACCESS:
    
    X_INLINE XVECTOR3 GetAcc() const { return XVECTOR3(x,y,z); }
    
    X_INLINE xfloat64 GetTimestamp() const { return x; }
    
};


XESCENE_NAMESPACE_END

#endif /* XESSENSOR_H_ */
