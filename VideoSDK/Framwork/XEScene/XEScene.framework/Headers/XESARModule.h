//
// Created by momo783 on 06/06/2018.
//

#ifndef XES_ARMODULE_H
#define XES_ARMODULE_H

#include "xcommon/XTexture.h"
#include "core/XESDefine.h"
#include "platform/armodule/XEARAnchor.h"
#include "platform/armodule/XEAREnumType.h"

namespace AR {

    struct HitTestResult
    {
        /**
         The type of the hit-test result.
         */
        AR::EARHitTestResultType    eHitTestResultType;
        /*
         ARKit: The distance from the camera to the intersection in meters.
         ARCore:屏幕坐标对应近平面点到交叉点的距离
         */
        xfloat32                fDistanceToImpactPoint;
        XMATRIX4                mTransform;//交点处的变化矩阵
        XVECTOR3                vImpactPoint;//交点(ARKit，ARCore)
        /*
         The anchor that the hit-test intersected.
         An anchor will only be provided for existing plane result types.
         */
        XEARAnchor*             pAnchor;
    };
    
    /********************************ARSessionStatusListener  START****************************/
    class ARSessionStatusListener
    {
    public:
        virtual void AddAnchors(XArray<AR::XEARAnchor *> aAnchors){}
        virtual void UpdateAnchors(XArray<AR::XEARAnchor *> aAnchors){}
        virtual void RemoveAnchors(XArray<AR::XEARAnchor *> aAnchors){}
    };
    /********************************ARSessionStatusListener END****************************/

    
    class ARModule
    {
    public:
        virtual xbool           Init(XViewport &vViewport,AR::EARStartMode eMode = ESM_Internal) = 0;
        virtual xbool           Release() = 0;
        virtual void            Tick() = 0;
        virtual xbool           GetCameraViewMatrix(XMATRIX4 &viewMatrix) = 0;
        virtual void            GetFeaturePoints(XArray<XVECTOR3> &aPoints) = 0;
        virtual void            GetAllPlaneAnchors(XArray<AR::XEARPlaneAnchor *> &aPlaneAnchors) = 0;

        virtual void            HitTest(const XVECTOR2 &vScreenPosition, XArray<HitTestResult> &aResults) = 0;
        virtual xfloat32        GetCameraFOV() = 0;
        virtual void            StopTrackingSession() = 0;
        virtual xbool           ResetTrackingSession(void *env = NULL, void *context = NULL, void *activity = NULL) = 0;
        virtual void            SetScreenOrientation(xint32 nOri,XViewport* pViewPort = NULL) = 0;
        virtual XMATRIX4        GetTransformFromDeviceOrientation(const xint32& nMode, const XVECTOR3 &vAixs) = 0;
        virtual void            SetARSessionStatusListener(ARSessionStatusListener* pSessionListener) = 0;
        virtual AR::EARStartMode    GetStartMode() { return ESM_Internal; };
#if ARKIT_SUPPORT
        /**
         * 获取ARKit返回的Y纹理
         *
         * @return IXTexture2D*                指向2D纹理指针
         */
        virtual IXTexture2D*	GetCameraYTexture() = 0;

        /**
         * 获取ARKit返回的CbCr纹理
         *
         * @return IXTexture2D*                指向2D纹理指针
         */
        virtual IXTexture2D*	GetCameraCbcrTexture() = 0;
        
        virtual void*           GetDelegate() = 0;
#endif

#if X_PLATFORM_ANDROID
        /**
         * 获取Tango返回的纹理（使用OES扩展纹理，For Tango and ARCore）
         *
         * @return IXTexture2D*                指向2D纹理指针
         */
        virtual IXTexture2D*    GetCameraTexture() = 0;
#endif

    };
};


#endif //XES_XESARMODULE_H
