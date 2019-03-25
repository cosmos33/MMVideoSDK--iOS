#ifndef ARKitUtil_h
#define ARKitUtil_h

#include "xcommon/XMath3D.h"
#include "xcommon/XGlobalFuncs.h"

namespace ARKit
{
    enum EScreenOrientation
    {
        /** The orientation is not known */
        Unknown,
        
        /** The orientation is portrait with the home button at the bottom */
        Portrait,
        
        /** The orientation is portrait with the home button at the top */
        PortraitUpsideDown,
        
        /** The orientation is landscape with the home button at the right side */
        LandscapeLeft,
        
        /** The orientation is landscape with the home button at the left side */
        LandscapeRight,
        
        /** The orientation is as if place on a desk with the screen upward */
        FaceUp,
        
        /** The orientation is as if place on a desk with the screen downward */
        FaceDown
    };
    
    class Const
    {
    public:
        static XVECTOR3 PositionFromTransform(const matrix_float4x4& transform)
        {
            return XVECTOR3(transform.columns[3].x, transform.columns[3].y, -transform.columns[3].z);
        }
        
        static XMATRIX4 ToXTransform(const matrix_float4x4 &matRawYUp)
        {
            XMATRIX4 matResult = XG_IdentityMatrix();
            matResult = XMATRIX4(matRawYUp.columns[0][0], matRawYUp.columns[0][1], matRawYUp.columns[0][2], matRawYUp.columns[0][3],
                                 matRawYUp.columns[1][0], matRawYUp.columns[1][1], matRawYUp.columns[1][2], matRawYUp.columns[1][3],
                                 matRawYUp.columns[2][0], matRawYUp.columns[2][1], matRawYUp.columns[2][2], matRawYUp.columns[2][3],
                                 matRawYUp.columns[3][0], matRawYUp.columns[3][1], matRawYUp.columns[3][2], matRawYUp.columns[3][3]);
            
            XMATRIX4 matTranslate = XG_Translate(matRawYUp.columns[3][0], matRawYUp.columns[3][1], -matRawYUp.columns[3][2]);
            XQUATERNION quat;
            quat.ConvFromMatrix(matResult);
            quat.z = -quat.z;
            quat.w = -quat.w;
            
            XMATRIX4 matRotate;
            quat.ConvToMatrix(matRotate);
            
            matResult = matRotate * matTranslate;
            return matResult;
        }
    };
}

#endif /* ARKitUtil_h */
