#ifndef _H_ARKITSYSTEM_H_
#define _H_ARKITSYSTEM_H_

#if ARKIT_SUPPORT

#import <ARKit/ARKit.h>

#include "IXARSystem.h"
#include "ios/ARKitSessionDelegate.h"

namespace AR {

class ARKitTexture;
class ARKitSystem : public IXARSystem
{
public:
	ARKitSystem();
	virtual                 ~ARKitSystem();
    virtual xbool			Init(XViewport &vViewport,AR::EARStartMode eMode);
	virtual xbool			Release();
	virtual void			Tick();
	virtual xbool			GetCameraViewMatrix(XMATRIX4& viewMatrix);
    //aResults可能不是按照由近及远的顺序排列
	virtual void			HitTest(const XVECTOR2& vScreenPosition, XArray<HitTestResult>& aResults);
    virtual void            GetFeaturePoints(XArray<XVECTOR3>& aPoints);

	virtual IXTexture2D*	GetCameraYTexture();
	virtual IXTexture2D*	GetCameraCbcrTexture();

    virtual xfloat32 		GetCameraFOV();
    virtual void            StopTrackingSession();
    virtual xbool           ResetTrackingSession(void *env, void *context, void *activity );
    virtual void            GetAllPlaneAnchors(XArray<AR::XEARPlaneAnchor *> &aPlaneAnchors);
    virtual void            SetScreenOrientation(xint32 nOri,XViewport* pViewPort/* = NULL*/);
    virtual XMATRIX4        GetTransformFromDeviceOrientation(const xint32& nMode, const XVECTOR3 &vAixs);
    virtual void*           GetDelegate() API_AVAILABLE(ios(11.0)) {return (__bridge void*)m_pSessionDelegate;}
    virtual AR::EARStartMode    GetStartMode(){return m_eMode;}

    void                    SessionDidUpdateFrame_Delegate(ARFrame* pFrame) API_AVAILABLE(ios(11.0));
    void                    SessionCameraProject_Delegate(ARCamera *pCamera) API_AVAILABLE(ios(11.0));
    void                    SessionDidAddAnchors_Delegate(NSArray<ARAnchor *> *anchors) API_AVAILABLE(ios(11.0));
    void                    SessionDidUpdateAnchors_Delegate(NSArray<ARAnchor*>* anchors) API_AVAILABLE(ios(11.0));
    void                    SessionDidRemoveAnchors_Delegate(NSArray<ARAnchor *> *anchors) API_AVAILABLE(ios(11.0));
    void                    SessionWasInterrupted_Delegate(ARSession *pSession) API_AVAILABLE(ios(11.0));
    void                    SessionInterruptionEnded_Delegate(ARSession *pSession) API_AVAILABLE(ios(11.0));

    void                    SetARSessionStatusListener(ARSessionStatusListener* pSessionListener);
    void                    RemoveARSessionStatusListener();

private:
    void                    SessionDidUpdateFrameForImage(ARFrame *pFrame) API_AVAILABLE(ios(11.0));
    void                    SessionDidUpdateFrameForCamera(matrix_float4x4 matLastStatus);
    void                    SetCloudData_Delegate(ARPointCloud *pPointCloud) API_AVAILABLE(ios(11.0));
    XVECTOR2                GetImageCoordinateForScreenPosition(XVECTOR2 vScreenPosition, xfloat32 fScreenWidth, xfloat32 fScreenHeight);

    xfloat32                GetHorizontalFieldOfView();
    xfloat32                GetVerticalFieldOfView();
    xfloat32                GetSystemVersion();
    void                    AddHitTestResults(NSArray<ARHitTestResult *> &pPlaneHitTestResults,XArray<HitTestResult>& aResults) API_AVAILABLE(ios(11.0));
    API_AVAILABLE(ios(11.0))
    xbool                   IsPlaneAnchorAlignmentSame(ARPlaneAnchorAlignment align);
    void                    CallbackSessionListener(NSArray<ARAnchor*>* anchors,EARSessionStatus eStatus);

private:
    ARSession*              m_pSession API_AVAILABLE(ios(11.0));
    ARKitSessionDelegate*   m_pSessionDelegate API_AVAILABLE(ios(11.0));
    ARFrame*                m_pCurFrame API_AVAILABLE(ios(11.0));
	ARKitTexture*			m_pYTexture;
	ARKitTexture*			m_pCbcrTexture;
    xbool                   m_bRunning;
    xbool                   m_bUpdating;
    XMATRIX4                m_matLastCamera;
    XMATRIX4                m_matCamera;
    XArray<XVECTOR3>        m_aFeaturePoints;
    xbool                   m_bIsARKitSupported;
    xint32                  m_nScreenOrientation;
    xfloat32                m_fFOV;
    XVECTOR2                m_vFocalLength;
    XVECTOR2                m_vImageResolution;
    xbool                   m_bCameraFOVUpdated;
    AR::EARStartMode            m_eMode;

    AR::ARSessionStatusListener*       m_pSessionListener;
};
}
#endif

#endif
