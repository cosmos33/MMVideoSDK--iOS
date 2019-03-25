/******************************************************************************

@File         XEAnimatableFaceRigComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_ANIMATABLE_FACE_RIG_COMPONENT_H
#define XE_ANIMATABLE_FACE_RIG_COMPONENT_H
#include "XEAnimatableModelComponent.h"
#include "XFaceRigAnim.h"
//containing an actor.
class XFaceRigAnim;
class XEAnimatableFaceRigComponent :public XEAnimatableModelComponent
{
public:
	XEAnimatableFaceRigComponent();
	virtual ~XEAnimatableFaceRigComponent();
public:
	virtual XEAnimController*     AssignAnimationController() override;//to assign an animation controller, if it was not exist yet.
#if X_PLATFORM_WIN_DESKTOP
	virtual void                  GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif
public:
	class FaceRigAnimController : public XEAnimatableModelComponent::ModelAnimController
	{
	public:
		FaceRigAnimController();
		FaceRigAnimController(XEAnimatableModelComponent* pModelComponent);
		virtual ~FaceRigAnimController();
	public:
		virtual void                    Tick(xfloat32 fInterval) override;
		virtual XAnimMultiLayer*        GetPrimitiveAnimController() override;
		//delegated call method, further information ,please visit Animation/XFaceRigAnim.h/XFaceRigAnim.h
		void							LoadSettingFile(const XString &strFileName);
		void							TickFaceRigParam(const FaceRigParam &param, xbool bClearAllBeforeApply = xtrue);
		void						    SetFaceRigBlendWeight(xfloat32 fBlendWeight);
		xfloat32					    GetFaceRigBlendWeight();
		xbool				            SetRotateModelOfNoBoneControl(xbool bEnable);
		xbool				            GetRotateModelOfNoBoneControl();
		xbool						    ReBindBoneControllerToSkinmodelInsSkeleton();
		void							ReSetFaceRigParam();
		void						    UnbingBoneController();
		X_CLASS_DEF(XEAnimatableFaceRigComponent::FaceRigAnimController)
	};
public:
	XE_COMPONENT_CAST(XEAnimatableFaceRigComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEAnimatableFaceRigComponent)
	static const XString COMPONENT_TYPENAME;
};

#endif // XE_ANIMATABLE_FACE_RIG_COMPONENT_H
