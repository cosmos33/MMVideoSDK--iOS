#ifndef ARKitPlaneManager_h
#define ARKitPlaneManager_h

#if ARKIT_SUPPORT
#import <ARKit/ARKit.h>

#include "xcommon/XHashTable.h"
#include "platform/armodule/XESARPlane.h"
#include "platform/armodule/XEARAnchor.h"

namespace AR {

class XARKitPlaneManager
{
public:
    XARKitPlaneManager(){}
    virtual                 ~XARKitPlaneManager(){}
    
    virtual xbool           Init();
    virtual xbool           Release();
    
    API_AVAILABLE(ios(11.0))
    virtual xbool           CreatePlane(ARPlaneAnchor* pPlaneAnchor);
    API_AVAILABLE(ios(11.0))
    virtual void            UpdatePlane(ARPlaneAnchor* pPlaneAnchor);
    
    virtual void            ReleaseNoTrackingPlanes(XArray<xint32>& aPlaneIds);
    
    virtual void            RelasePlane(xint32 nID);
    virtual void            RelaseAllPlanes();
    virtual void            GetAllPlanes(XArray<AR::IXARPlane*>& aPlanes,EPlaneType ePlaneType);
    
    virtual xint32          GetPlaneCount(EPlaneType ePlaneType = EPlaneType::EPT_ARPLANE_ALL);
    
    AR::EPlaneType ConvertToARPlaneType(ARPlaneAnchorAlignment eAlignment);

    
private:
    void                    UpdatePlaneBoundary(ARPlaneAnchor* pPlaneAnchor,IXARPlane* pPlane);

private:
    XHashTable<xint32 ,IXARPlane*>       m_tbARKitPlane;
};

extern XARKitPlaneManager*               g_pARKitPlaneManager;
    
}

#endif
#endif /* ARKitPlaneManager_h */

