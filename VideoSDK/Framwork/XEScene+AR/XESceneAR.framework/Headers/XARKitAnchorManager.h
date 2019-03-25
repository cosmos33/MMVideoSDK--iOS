#ifndef ARKitPlaneManager_h
#define ARKitPlaneManager_h

#if ARKIT_SUPPORT
#import <ARKit/ARKit.h>

#include "xcommon/XHashTable.h"
#include "platform/armodule/XEARAnchor.h"

namespace AR {

class XARKitAnchorManager
{
public:
    XARKitAnchorManager(){}
    virtual                 ~XARKitAnchorManager(){}
    
    virtual xbool           Init();
    virtual xbool           Release();
    
    API_AVAILABLE(ios(11.0))
    virtual XEARAnchor*     CreateAnchor(ARAnchor* pARKitAnchor);
    API_AVAILABLE(ios(11.0))
    void                    UpdateAnchor(ARAnchor* pARKitAnchor);
   
    void                    RelaseAnchorById(XString steID);
    void                    GetAllPlaneAnchors(XArray<AR::XEARPlaneAnchor*>& aPlanes);
    XEARAnchor*             GetAnchorById(XString strID);
    
    //for remove
    void                    SetAnchorNoTracking(XString strID);
    void                    RemoveNoTrackingAnchor();//移除不追踪的锚点，也就是在Remove回调中标记为待移除的锚点
    
private:
    API_AVAILABLE(ios(11.0))
    XEARPlaneAnchor*        CreatePlaneAnchor(ARPlaneAnchor* pPlaneAnchor);
     API_AVAILABLE(ios(11.0))
    XEARAnchor*             CreateCommonAnchor(ARAnchor* pARKitAnchor);
    API_AVAILABLE(ios(11.0))
    void                    UpdatePlaneBoundary(ARPlaneAnchor* pPlaneAnchor,XEARPlaneAnchor* pPlane);
    API_AVAILABLE(ios(11.0))
    virtual void            UpdatePlaneAnchor(ARPlaneAnchor* pPlaneAnchor);
    API_AVAILABLE(ios(11.0))
    virtual void            UpdateCommonAnchor(ARAnchor* pARKitAnchor);
    API_AVAILABLE(ios(11.0))
    AR::EArPlaneType        ConvertToARPlaneType(ARPlaneAnchorAlignment eAlignment);
private:
    XHashTable<XString ,XEARAnchor*>        m_tbIDToAnchor;
};

extern XARKitAnchorManager*                  g_pARKitAnchorManager;
    
}

#endif
#endif /* ARKitPlaneManager_h */

