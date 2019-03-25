//
//  XEARAnchor.h
//  AR
//
//  Copyright © 2018年 MOMO_ZSX. All rights reserved.
//

#ifndef XEARAnchor_h
#define XEARAnchor_h

#include "XMath3D.h"
#include "XTypes.h"
#include "XMemBase.h"
#include "XEARMathUtil.h"
#include "XEAREnumType.h"

namespace AR
{
   class XEARAnchor : public XMemBase
   {
   public:
       XEARAnchor():m_eTrackingStatus(EATS_AR_TRACKING_STATE_STOPPED),m_matTransformInWorld(XG_IdentityMatrix()){}
       virtual                      ~XEARAnchor(){}
       inline void                  SetIdentifier(const XString& strID){m_strIdentifier = strID;}
       inline XString               GetIdentifier(){return m_strIdentifier;}
       inline XString               GetIdentifier()const {return m_strIdentifier;}
       
       inline void                  SetTransform(XMATRIX4 matTransformInWorld){m_matTransformInWorld = matTransformInWorld;}
       inline XMATRIX4              GetTransform(){return m_matTransformInWorld;}
       inline XMATRIX4              GetTransform()const {return m_matTransformInWorld;}
       
       virtual void                  SetArTrackingState(AR::EArTrackingState eStatus){m_eTrackingStatus = eStatus;}
       virtual AR::EArTrackingState      GetArTrackingState(){return m_eTrackingStatus; }
       virtual AR::EArTrackingState      GetArTrackingState() const {return m_eTrackingStatus; }
       template<typename T>
       T*                           CaseAnchor();

#if ARKIT_SUPPORT
       //仅iOS 12支持
       inline void                  SetName(const XString& strName){m_strName = strName;}
       inline XString               GetName(){return m_strName;}
       inline XString               GetName()const{return m_strName;}
#endif
   protected:
       XString                      m_strIdentifier;//唯一的ID
       XString                      m_strName;//for ios 12,目前无效
       XMATRIX4                     m_matTransformInWorld;//世界空间
       AR::EArTrackingState             m_eTrackingStatus;//追踪状态
   };
    
    template<typename T>
    T* XEARAnchor::CaseAnchor()
    {
        return dynamic_cast<T*>(this);
    }

    ////////////////////////////////////////////////////////XEARPlaneAnchor
   class XEARPlaneAnchor : public  XEARAnchor
   {
   public:
       XEARPlaneAnchor() :m_vCenter(XVECTOR3(0)) ,m_vExtent(XVECTOR3(0)),m_ePlaneType(EPT_AR_PLANE_HORIZONTAL_UPWARD_FACING){}
       virtual                      ~XEARPlaneAnchor(){}

       inline void                  SetPlaneAnchorAlignment(AR::EArPlaneType eAlignment){m_ePlaneType = eAlignment;}
       inline AR::EArPlaneType          GetPlaneAnchorAlignment(){return m_ePlaneType;}
       inline AR::EArPlaneType          GetPlaneAnchorAlignment() const {return m_ePlaneType;}

       inline void                  SetCenter(const XVECTOR3 vCenter){m_vCenter = vCenter;}
       inline XVECTOR3              GetCenter(){return m_vCenter;}
       inline XVECTOR3              GetCenter()const {return m_vCenter;}

       inline void                  SetExtent(const XVECTOR3 vExtent){m_vExtent = vExtent;}
       inline XVECTOR3              GetExtent(){return m_vExtent;}
       inline XVECTOR3              GetExtent()const {return m_vExtent;}
   protected:
       AR::EArPlaneType                 m_ePlaneType;//平面类型
       XVECTOR3                     m_vCenter;//世界坐标系
       XVECTOR3                     m_vExtent;//平面长宽
   };
    
    //update for other anchor
}

#endif /* XEARAnchor_h */
