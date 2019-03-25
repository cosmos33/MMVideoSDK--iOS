/******************************************************************************

@File         XEAnimatableModelComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEANIMATABLEMODELCOMPONENT_H
#define XEANIMATABLEMODELCOMPONENT_H
#include "XEModelComponent.h"
#include "XEAnimController.h"
#include "XEPhysicsSkeletalRootInstance.h"
#include "XCurve.h"
class XEViewport;
class XAnimMultiLayer;
class IXSkeletalPhysicsInstance;
class IXAnimationBase;
class XEAnimBlendLayer;
class XEAnimatableModelComponent
	: public XEModelComponent
{
public:
	struct AnimLayerData
	{
		enum{ AnimLayerDataIndexNone = -2, AnimLayerDataIndexNotSet = -1};
		xint32               nLayerIndex;
		XString              szPath;
		xbool                bActive;//layer whether actived or not.
		xbool				 bIsMontageAsset; //it is montage seq asset or not.
		AnimLayerData() :nLayerIndex(AnimLayerDataIndexNone), bActive(xfalse), bIsMontageAsset(xfalse){}
	};
	typedef XArray<AnimLayerData> AnimLayerArray;
	         XEAnimatableModelComponent();
	virtual ~XEAnimatableModelComponent();
public:
	class ModelAnimController: public XEAnimController
	{
	public:
		ModelAnimController();
		ModelAnimController(XEAnimatableModelComponent* pModelComponent);
		virtual ~ModelAnimController();
	public:
		virtual void                        Tick(xfloat32 fInterval) override;
		virtual xint32                      GetTimeLength() const override;
		virtual void                        SetTime(xint32 nTime) override;
		virtual XAnimMultiLayer*            GetPrimitiveAnimController();
		void								AssignCustomPrimitiveAnimController(XAnimMultiLayer* pPlayer);//pPlayer should be deleted outside.
		XAnimMultiLayer*                    GetCustomPrimitiveAnimController();
		void                                SetAnimEndTime(xfloat32 fEndTime);
		xfloat32                            GetSequenceDuration(const xchar* pSeqName);
		xfloat32                            GetBlendSequenceDuration(const char* pBlendLayerName, const xchar* pSeqName);
		void                                ActiveAllLayers();
		void                                DeactiveAllLayers();
		void                                SetAnimatableModelComponent(XEAnimatableModelComponent* pCmp){ m_pModelComponent = pCmp; }
		XEAnimatableModelComponent*         GetAnimatableModelComponent(){ return m_pModelComponent; }
		X_CLASS_DEF(XEAnimatableModelComponent::ModelAnimController)

		virtual void						Play();//goto 0, and play again.
		virtual void						Resume();
		virtual void						Stop();
		virtual void						Pause();

	protected:
		void                                _SetPrimitiveAnimController(XAnimMultiLayer* pAnimMultiLayer);
		XAnimMultiLayer*                    _GetPrimitiveAnimController();
	protected:
		XEAnimatableModelComponent*         m_pModelComponent;
	};
public:
	virtual xbool                           LoadAsset(const xchar* pPath) override;
	virtual void                            Release() override;
	virtual void                            Empty() override;
	virtual void                            Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void							Render(XEViewport* pViewport) override;
	virtual void                            Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*                     Serialize(XMLElement* pEleParent) override;
#if X_PLATFORM_WIN_DESKTOP
	virtual void                            GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif
	virtual XEAnimController*               AssignAnimationController();//to assign an animation controller, if it was not exist yet.
	virtual XEAnimController*               GetAnimController() override;//could be montage animation controller or model-animation controller.
	virtual const XEAnimController*         GetAnimController() const override;//could be montage animation controller or model-animation controller.
	XEAnimController*                       GetExplicitAnimationController();//the seq-animation controller.
	const XEAnimController*                 GetExplicitAnimationController() const;//the seq-animation controller.
	virtual const xchar*                    GetCurPlayAnimation() override;
	X_FORCEINLINE XAnimMultiLayer*&         GetAnimMultiLayer(){ return m_pPrimitiveAnimController; }
public:
	XAnimMultiLayer*                        AddAnimSequence(const xchar* pPath, const xbool bActive = xfalse, const xbool bPlay = xfalse, xbool bExclusively = xtrue,xbool bIsMontageAsset = xfalse);//bIsMontageAsset, this asset is montage seq asset or not.
	XAnimMultiLayer*                        AddAnimBlendSequence(const xchar* pLayerName, const xchar* pPath, const xfloat32 fStartTime, const xfloat32 fEndTime, const xint32 eBlendType, const xbool bActive = xfalse, const xbool bPlay = xfalse, xbool bExclusively = xtrue);
	void                                    SetAnimBlendTime(const xchar* pLayerName, const xchar* pPath, xfloat32 fStartTime, xfloat32 fEndTime);
	XAnimMultiLayer*                        AddLayer(const xchar* pLayerName,  const xbool bActive = xfalse, const xbool bPlay = xfalse, xbool bExclusively = xtrue);
	XAnimMultiLayer*                        AddLayerAnimSequence(const xchar* pLayerName, const char* pAssetPath/*, const xbool bActive = xfalse, const xbool bPlay = xfalse, xbool bExclusively = xtrue*/);
	void                                    RemoveAllAnimSequence();
	void                                    ActiveLayer(const xchar* pLayerName, xbool bPlay = xtrue, xbool bExclusively = xtrue);//layer-name is the path.
	void                                    ActiveAllLayers(xbool bPlay = xtrue);
	void									ActiveSeqLayers(xbool bPlay = xtrue);
	void                                    DeacitveLayer(const xchar* pLayerName);
	void                                    DeacitveAllLayers();
	xbool                                   HasActiveLayer();
	xbool                                   HasLayer(const xchar* pLayerName);
	const xchar*                            GetFirstActiveLayerName() const;
	AnimLayerData&                          GetAnimLayerData(const xchar* pLayerName);
	AnimLayerData&                          GetAnimLayerData(const xint32 nLayerIndex = 0);
	const AnimLayerData&                    GetAnimLayerData(const xint32 nLayerIndex = 0) const;
	const AnimLayerArray&                   GetAnimLayerArray() const { return m_aAnimLayer; };

public://skeletal body
	virtual xbool							LoadPhysicalAsset(const xchar* pPath, RigidActorType eType = (RigidActorType)-1) override;
	void									SetRenderBodyShapeDebug(xbool bRender){ m_bIsRenderDebug = bRender; }
	xbool									IsRenderBodyShapeDebug(){ return m_bIsRenderDebug; }
// 	void									SetAllBodiesSimulatePhysics(xbool bSimulate);
// 	xbool									GetAllBodiesSimulatePhysics(){ return m_bIsSimulateAllBody; }
	void									BuildPhysicsSkeletalRootInstance();
	xbool									DestroyPhysicsSkeletalRootInstance();
	void									SetIXSkeletalPhysicsInstance(IXSkeletalPhysicsInstance* pIns){ m_pSkeletalPhysicsInstance = pIns; }
	IXSkeletalPhysicsInstance*				GetIXSkeletalPhysicsInstance(){ return m_pSkeletalPhysicsInstance; }
	XEPhysicsSkeletalRootInstance*			GetPhysicsSkeletalRootInstance(){ return m_pPhysicsSkeletalRootInstance; }
	void									CreateSkeletalPhysicsInstance();

	xbool									AttachWeightCurveToLayer(const xchar* pLayerName, FInterpCurve<xfloat32>* pCurve);
	xbool									DetachWeightCurveToLayer(const xchar* pLayerName);
	void									SetCurAttachWeightVal(const xchar* pLayerName, xfloat32 fWeight);
	xint32									GetLayerInterBlendType(const xchar* pLayerName);
	void									SetLayerInterBlendType(const xchar* pLayerName, xint32 type);
	void									GetLayerInterBlendTypeNames(const xchar* pLayerName, XArray<XString>& arNameList);
	xint32								    GetLayerInterBlendTypeByDesc(const xchar* pLayerName, const XString &strDesc);
	void									RemoveAnimLayer(const xchar* pLayerName);

	xbool                                   IsInnerPrimitiveAnimController()const{ return m_bInnerPrimitiveAnimController; }
	void                                    MarkAsInnerPrimitiveAnimController(bool bMark){ m_bInnerPrimitiveAnimController = bMark; }//set to true if you want to pass the controller to this and being managed by this.
public:
	XE_COMPONENT_CAST(XEAnimatableModelComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEAnimatableModelComponent)
	static const XString COMPONENT_TYPENAME;
protected:
	virtual xbool                           MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual xbool                           ApplyWorldTransformImpl(const XMATRIX4& mat) override;
protected:

	AnimLayerArray                          m_aAnimLayer;
	ModelAnimController*                    m_pAnimController;
	XAnimMultiLayer*                        m_pPrimitiveAnimController;

	XEPhysicsSkeletalRootInstance*			m_pPhysicsSkeletalRootInstance;
	xbool									m_bIsRenderDebug;
	//xbool									m_bIsSimulateAllBody;
	xbool                                   m_bInnerPrimitiveAnimController;//for inner used, safe delete multilayer.
};

#endif // XEANIMATABLEMODELCOMPONENT_H
