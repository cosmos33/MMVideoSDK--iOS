#ifndef _H_ARSYSTEM_H_
#define _H_ARSYSTEM_H_

#include "AREngine.h"
#include "xcommon/XMemBase.h"

namespace AR {

    enum EARSessionStatus
    {
        ESS_NONE,
        ESS_ADD_ANCHOR,
        ESS_UPDATE_ANCHOR,
        ESS_REMOVE_ANCHOR
    };
    
class IXARPlane;
class ARKitTexture;
class IXARSystem : public XMemBase
{
public:
	IXARSystem(){}
    virtual ~IXARSystem(){}
    virtual xbool			Init(XViewport &vViewport,AR::EARStartMode eMode) = 0;
	virtual xbool			Release() = 0;
	virtual void			Tick() = 0;
	virtual xbool			GetCameraViewMatrix(XMATRIX4& viewMatrix) = 0;
    virtual void			HitTest(const XVECTOR2& vScreenPosition, XArray<HitTestResult>& aResults) = 0;
	virtual void            GetFeaturePoints(XArray<XVECTOR3>& aPoints) = 0;
	virtual xfloat32 		GetCameraFOV() = 0;
	virtual void            StopTrackingSession() = 0;
	virtual xbool           ResetTrackingSession(void *env, void *context, void *activity ) = 0;
    virtual void            GetAllPlaneAnchors(XArray<AR::XEARPlaneAnchor *> &aPlaneAnchors) = 0;
    virtual void            SetScreenOrientation(xint32 nOri,XViewport* pViewPort/* = NULL*/) = 0;
    virtual XMATRIX4        GetTransformFromDeviceOrientation(const xint32& nMode, const XVECTOR3 &vAixs) = 0;
    virtual AR::EARStartMode    GetStartMode() = 0;
    
#if ARKIT_SUPPORT
	virtual IXTexture2D*	GetCameraYTexture() = 0;
	virtual IXTexture2D*	GetCameraCbcrTexture() = 0;
    virtual void*           GetDelegate() = 0;
#endif

#if X_PLATFORM_ANDROID
	virtual IXTexture2D*	GetCameraTexture() = 0;
    virtual XMATRIX4        ConvertModelMatrixForLeftHandSpace(const XMATRIX4& matModelRightHand) = 0;
    virtual XMATRIX4        ConvertCameraViewForLeftHandSpace(const XMATRIX4& matViewRightHand) = 0;
    virtual xfloat32        CalculateCameraFOVForLeftSpace(const XMATRIX4& matProjectRightHand) = 0;
    virtual void            SetHitTestListener(ARCoreHitTestListener *pListener) = 0;

	virtual void			SaveLeftSpaveProjectMatrix(const XMATRIX4& matProjectInRightSpace) = 0;
	virtual void			SaveLeftSpaveCameraViewMatrix(const XMATRIX4& matCameraViewInRightSpace) = 0;
    virtual void            UpdateAnchorStatus(XArray<AR::XEARAnchor *> aOriginAnchors,xbool bConvertInner = xfalse) = 0;

#endif
    
    virtual void             SetARSessionStatusListener(ARSessionStatusListener* pSessionListener) = 0;

};
    
}

#endif
