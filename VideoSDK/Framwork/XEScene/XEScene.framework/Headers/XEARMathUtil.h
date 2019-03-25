//
// Created by MOMO_ZSX on 2018/7/31.
//

#ifndef AR_ANDROID_UTIL_H
#define AR_ANDROID_UTIL_H

#include "XTypes.h"
#include "XMath3D.h"
#include "XGlobalFuncs.h"


namespace AR
{

#define HALF_PI			(1.57079632679f)
#define FASTASIN_HALF_PI (1.5707963050f)
#define MIN_VSLUE        (0.000001)


    class XEARMathUtil
    {
    public:
        static xfloat32 FastAsin(xfloat32 Value)
        {
            // Clamp input to [-1,1].
            xbool nonnegative = (Value >= 0.0f);
            xfloat32 x = abs(Value);
            xfloat32 omx = 1.0f - x;
            if (omx < 0.0f)
            {
                omx = 0.0f;
            }
            xfloat32 root = sqrt(omx);
            // 7-degree minimax approximation
            float result = ((((((-0.0012624911f * x + 0.0066700901f) * x - 0.0170881256f) * x + 0.0308918810f) * x - 0.0501743046f) * x + 0.0889789874f) * x - 0.2145988016f) * x + FASTASIN_HALF_PI;
            result *= root;  // acos(|x|)
            // acos(x) = pi - acos(-x) when x < 0, asin(x) = pi/2 - acos(x)
            return (nonnegative ? FASTASIN_HALF_PI - result : result - FASTASIN_HALF_PI);
        }

        static XVECTOR3 GetScaleFromMatrix(const XMATRIX4& mat)
        {
            return XVECTOR3(mat.GetRow(0).Magnitude(),mat.GetRow(1).Magnitude(),mat.GetRow(2).Magnitude());
        }

        static void EliminateScaleFromMatrix(XMATRIX4& mat)
        {
            XMATRIX4 matScale(XMATRIX4::IDENTITY);
            XVECTOR3 vScale = GetScaleFromMatrix(mat);
            matScale.Scale(vScale.x,vScale.y,vScale.z);
            matScale.Inverse();
            mat = matScale * mat;
        }

        static xfloat32 Atan2(xfloat32 Y, xfloat32 X)
        {
            //return atan2f(Y,X);
            // atan2f occasionally returns NaN with perfectly valid input (possibly due to a compiler or library bug).
            // We are replacing it with a minimax approximation with a max relative error of 7.15255737e-007 compared to the C library function.
            // On PC this has been measured to be 2x faster than the std C version.

            const xfloat32 absX = fabsf(X);
            const xfloat32 absY = fabsf(Y);
            const xbool yAbsBigger = (absY > absX);
            xfloat32 t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
            xfloat32 t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

            if (t0 == 0.f)
                return 0.f;

            xfloat32 t3 = t1 / t0;
            xfloat32 t4 = t3 * t3;

            static const xfloat32 c[7] = {
                    +7.2128853633444123e-03f,
                    -3.5059680836411644e-02f,
                    +8.1675882859940430e-02f,
                    -1.3374657325451267e-01f,
                    +1.9856563505717162e-01f,
                    -3.3324998579202170e-01f,
                    +1.0f
            };

            t0 = c[0];
            t0 = t0 * t4 + c[1];
            t0 = t0 * t4 + c[2];
            t0 = t0 * t4 + c[3];
            t0 = t0 * t4 + c[4];
            t0 = t0 * t4 + c[5];
            t0 = t0 * t4 + c[6];
            t3 = t0 * t3;

            t3 = yAbsBigger ? (0.5f * XENGINE_PI) - t3 : t3;
            t3 = (X < 0.0f) ? XENGINE_PI - t3 : t3;
            t3 = (Y < 0.0f) ? -t3 : t3;

            return t3;
        }

        static void QuaternionToEuler(const XQUATERNION& quat, xfloat32& fRoll, xfloat32& fYaw,xfloat32& fPitch )
        {
            // y(yaw) is the up, and z(pitch) is the forward.
            //from urho3d
            xfloat32 x_ = quat.x;
            xfloat32 y_ = quat.y;
            xfloat32 z_ = quat.z;
            xfloat32 w_ = quat.w;

            // Derivation from http://www.geometrictools.com/Documentation/EulerAngles.pdf
            // Order of rotations: Z first, then X, then Y
            float check = 2.0f * (-y_ * z_ + w_ * x_);

            if (check < -0.995f)
            {
                fRoll   = -HALF_PI;
                fYaw    = 0.f;
                fPitch  = -Atan2(2.0f * (x_ * z_ - w_ * y_), 1.0f - 2.0f * (y_ * y_ + z_ * z_));
            }
            else if (check > 0.995f)
            {
                fRoll   = HALF_PI;
                fYaw    = 0.f;
                fPitch  = Atan2(2.0f * (x_ * z_ - w_ * y_), 1.0f - 2.0f * (y_ * y_ + z_ * z_));
            }
            else
            {
                fRoll   = FastAsin(check);
                fYaw    = Atan2(2.0f * (x_ * z_ + w_ * y_), 1.0f - 2.0f * (x_ * x_ + y_ * y_));
                fPitch  = Atan2(2.0f * (x_ * y_ + w_ * z_), 1.0f - 2.0f * (x_ * x_ + z_ * z_));
            }

            return;
        }

        static void EulerToQuaternion(xfloat32 fRoll, xfloat32 fYaw, xfloat32 fPitch, XQUATERNION& quat)
        {
            //from urho3d.
            // Order of rotations: Z first, then X, then Y (mimics typical FPS camera with gimbal _lock at top/bottom)

            xfloat32 x = fRoll *.5f;
            xfloat32 y = fYaw *.5f;
            xfloat32 z = fPitch *.5f;

            float sinX = sinf(x);//s1
            float cosX = cosf(x);//c1
            float sinY = sinf(y);//s2
            float cosY = cosf(y);//c2
            float sinZ = sinf(z);//s3
            float cosZ = cosf(z);//c3

            quat.w = cosY * cosX * cosZ + sinY * sinX * sinZ;//c2c1c3+s2s1s3
            quat.x = cosY * sinX * cosZ + sinY * cosX * sinZ;//c2s1c3+s2c1s3
            quat.y = sinY * cosX * cosZ - cosY * sinX * sinZ;//s2c1c3-c2s1s3
            quat.z = cosY * cosX * sinZ - sinY * sinX * cosZ;//c2c1s3-s2s1c3
            return;
        }

        static xbool IsEqualWithMatrixs(XMATRIX4 matTransform1, XMATRIX4 matTransform2)
        {
            XVECTOR3 vScale1 = GetScaleFromMatrix(matTransform1);
            XVECTOR3 vScale2 = GetScaleFromMatrix(matTransform2);

            EliminateScaleFromMatrix(matTransform1);
            EliminateScaleFromMatrix(matTransform2);

            XVECTOR3 vPos1 = matTransform1.GetTransPart();
            XVECTOR3 vPos2 = matTransform2.GetTransPart();

            XQUATERNION quat1(matTransform1);
            XVECTOR3 vEuler1(0);
            QuaternionToEuler(quat1,vEuler1.x,vEuler1.y,vEuler1.z);
            EulerToQuaternion(vEuler1.x,vEuler1.y,vEuler1.z,quat1);

            XQUATERNION quat2(matTransform1);
            XVECTOR3 vEuler2(0);
            QuaternionToEuler(quat2,vEuler2.x,vEuler2.y,vEuler2.z);
            EulerToQuaternion(vEuler2.x,vEuler2.y,vEuler2.z,quat2);

            xbool bIsPosSame = vPos1.IsEquals(vPos2,MIN_VSLUE);
            xbool bIsScaleSame = vScale1.IsEquals(vScale2,MIN_VSLUE);
            xbool bIsQuatSame = (abs(quat1.x - quat2.x) <= MIN_VSLUE) &&(abs(quat1.y - quat2.y) <= MIN_VSLUE) && (abs(quat1.z - quat2.z) <= MIN_VSLUE) &&  (abs(quat1.w - quat2.w) <= MIN_VSLUE);


            if (bIsPosSame && bIsScaleSame && bIsQuatSame)
                return  xtrue;
            return xfalse;
        }
    };
}

#endif //AR_ANDROID_UTIL_H
