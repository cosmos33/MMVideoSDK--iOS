#ifndef _XSKELANIMCONTROLLER_H_
#define _XSKELANIMCONTROLLER_H_

#include "XAnimController.h"

class IXAnimationBase;
struct XSkeletonMap;
class XModel;
class XSkeleton;

class XSkelAnimController : public XAnimController
{
public:
	XSkelAnimController(const xchar* szName, IXAnimationBase* pAsset);
    virtual                         ~XSkelAnimController();

									X_CLASS_DEF(XSkelAnimController);   // fix flk for lua
	virtual xfloat32				GetStartTime() const override;
	virtual xfloat32				GetEndTime() const override;
    virtual void                    Update(const UpdateParam& context, XAnimInstance& instData) override;
    virtual xuint32                 Type() const override { return SKEL_ANIMCONTROLLER; }
    virtual bool					Serialize(XXMLExtendTool& ar) override { return false; }

    virtual void                    BindSkeleton(XSkeleton* pSkeleton);
	virtual void					BindSkinModel(const XModel* pSkinModel){}
    // AddRef
    virtual void                    SetAnimation(IXAnimationBase* pAnimation);

    virtual IXAnimationBase*		GetAnimation();
    virtual const IXAnimationBase*	GetAnimation() const;
protected:
    IXAnimationBase*				m_pAnimation;
    XSkeleton*                      m_pSkeleton;
    XSkeletonMap*					m_pSkeletonMap;
};

#endif