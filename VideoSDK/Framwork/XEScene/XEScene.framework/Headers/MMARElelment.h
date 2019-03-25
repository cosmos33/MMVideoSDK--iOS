//
//  MMARElelment.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESMMARELELMENT_H_
#define XESMMARELELMENT_H_

#include "core/XESObject.h"

class XEActor;
class XEActorComponent;

XESCENE_NAMESPACE_BEGIN

class Scene;

class ARElement : public Object
{
public:
    enum ElementType {
        MODEL,
        PARTICLE
    };
    
public:
    static XString InitScene(xbool nAsPush = xtrue);
    static void DestoryScene();
    
    static void SetCameraDir(const XVECTOR3& vDir);
    
    static XMATRIX4 GetMatrix(XVECTOR3 vDir, XVECTOR3 vRoate,xfloat32 fScale, XVECTOR3 vPos);
    
    static void SetSSAAEnabled(xbool bEnabled);
    static void SetFXAAEnabled(xbool bEnabled);
    
public:
    
    static ARElement* CreateModelElement(XString mModlePath);
    
    void   AddAnimation(XString mAnimationPath, xbool isLoop);

    void   PlayAnimation(xint32 nAnimationIndex);

    void   AutoSizeFit();
    void   AutoSizeFit(xfloat32 fScale);

    void   FitToScreenRectangles(const XVECTOR2 &vSreenPosMin, const XVECTOR2 &vSreenPosMax, XVECTOR3 &vRetPos);

    void RemoveAnimWrapper(XString mAnimationPath);
    void RemoveAnimWrapperForAddIndex(xint32 nAnimationIndex);
    void RemoveAllAnimWrapper();

public:
    
    static  ARElement* CreateParticleElement(XString strPath);
    
    void    Play();
    
public:
    
    void        SetHidden(xbool bHidden);
    xbool       IsHidden();
    
    void        SetElementLocation(XVECTOR3 vLocation);
    XVECTOR3    GetElementLocation();
    
    void        SetElementMatrix(const XMATRIX4& matrix);
    
    void        SetElementScale(XVECTOR3 vScale);
    
    void        SetScreenLocation(XVECTOR2 vScreenLocation);
    
    void        RotateX(xfloat32 fDeltaRadian);
    void        RotateY(xfloat32 fDeltaRadian);
    void        RotateZ(xfloat32 fDeltaRadian);
    
    void        SetOutline(xfloat32 nLineWidth, XCOLORBASE& xLineColor);
    
    X_INLINE XString GetElementName() const { return m_ElementName; }
    
    static  void DeleteElement(ARElement* pElement);
    
protected:
    
    ARElement(ElementType eType);
    
    virtual ~ARElement() override;
    virtual void Release() override;
    
    X_FORCEINLINE ElementType GetElementType() const { return m_ElementType; }
    
    static Scene* GetSharedScene();
    
    static XString CreateElementName();
    
    xfloat32  DichotomyGetNearestPos(const XVECTOR2 &vSreenPosMin, const XVECTOR2 &vSreenPosMax, const XCusAABB &OriAABB,
                                     const XVECTOR3 &vOri, const XVECTOR3 &vDir, xfloat32 fMinDistance, xfloat32 fMaxDistance);
    
    xbool     JudgeOut2DRect(const XCusAABB &AABB, const XVECTOR2 &vSreenPosMin,const XVECTOR2 &vSreenPosMax,
                             XVECTOR2 *p2DAABBMin = NULL, XVECTOR2 *p2DAABBMax = NULL);
    
protected:
    
    XEActor*    m_pActor;
    XEActorComponent*   m_pComponent;
    ElementType m_ElementType;
    
    XString     m_ElementName;
};

XESCENE_NAMESPACE_END

#endif /* XESMMARELELMENT_H_ */
