/******************************************************************************

@File         XEActor.h

@Version       1.0

@Created      2017,9, 20

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEACTOR_H
#define XEACTOR_H
#include "XArray.h"
#include "XFileBase.h"
#include "XWorld.h"
#include "XEActorComponent.h"
#include "XCustomGeometry.h"
#include "XEFactoryActorUtil.h"
#include "XEFactoryExtendParamUtil.h"
#include "XEBindUserNodeData.h"
#include "XEUtility.h"
#include "XEHitResult.h"
#include "XEAttachDetachRules.h"

class XEChildActorComponent;
class XEWorld;
class XEViewport;
class XEScriptContainerInstance;

class XEActor :public XEEventReceiver
{
public:
	typedef XArray<XEActor*> XEAttachChildren;
	typedef XArray<IXEExtendParam*> XEActorExtendParamList;
	enum EDrawDebugType
	{
		EDD_DRAW_NONE = 0,
		EDD_DRAW_AUXILIARY = 1 << 0,//such as camera frustum..
		EDD_DUMMY_SHAPE = 1 << 1,// draw dummy
		EDD_BOUNDINGBOX = 1 << 2//draw bounding box
	};


public:
	XEActor();
	virtual ~XEActor();

protected:
	class DelayLoadBindUserNodeDestroyer :public XEUtility::XEDelayDestroyer
	{
	public:
		DelayLoadBindUserNodeDestroyer() :m_pActor(NULL){}
		virtual ~DelayLoadBindUserNodeDestroyer(){}
		//functions that should be override.
		virtual xbool ShouldBeDeleted()override;
		virtual void  Release()override{}
	public:
		XEActor*	  m_pActor;
	};
public:
	virtual void                 Deserialize(const XMLElement* pEleActor);
	virtual XMLElement*          Serialize(XMLElement* pEleParent);
	virtual xbool                LoadScript(const xchar* pScriptPath);//full relative path
	virtual	const XString&	     GetTypeName() const{ return ACTOR_TYPENAME; }
	virtual void			     Serialize(XFileBase *pFile) {}
	virtual void                 Initialize(XEWorld* pWorld);
	virtual void                 Tick(xfloat32 fDelMs, xbool bForceTick = xtrue);// in milliseconds.
	virtual void                 PresentPhysics(xfloat32 fDel);
	virtual void                 Render(XEViewport* pViewport);
	virtual void				 RenderDrawDebug(XEViewport* pViewport);
	virtual void                 Release();
	virtual xbool                SetRootComponent(XEActorComponent* pRootComponent);
	/************************************************************************/
	/* KeepWorldTransform by default*/
	/* DEPRECATED */
	/************************************************************************/
	virtual void                 AttachToActor(XEActor* pActor);//KeepWorldTransform by default
	virtual void                 AttachToActor(XEActor* pActor, const XEAttachRules& attachRules);
	virtual void                 AttachToActorNode(XEActor* pParentActor, const xchar* szBindNodeName);//SnapToTargetNotIncludingScale by default
	virtual void                 AttachToActorNode(XEActor* pParentActor, const xchar* szBindNodeName, const XEAttachRules& attachRules);
	/************************************************************************/
	/* KeepWorldTransform by default*/
	/* DEPRECATED */
	/************************************************************************/
	virtual void                 DetachFromActor();
	virtual void                 DetachFromActor(const XEDetachmentTransformRules& detachRules);

	virtual XCusAABB             GetCusAABB() const;
	virtual xbool                RayPick(XEHitResult& hr);
	virtual xbool                RayPick(XEHitResult& hr, const XVECTOR2& vScreenPoint, XViewport* viewport);
	virtual XEHitResult          RayPick(const XVECTOR2& vScreenPoint, XViewport* pViewport);
	virtual void                 FocusActor(xbool bFocus){};
	virtual void                 OnSocketUpdate(const XMATRIX4& matWorld);//connect and bind to socket.
	virtual void                 SetActorLocation(const xfloat32 fX, const xfloat32 fY, const xfloat32 fZ);
	virtual void                 SetActorLocation(const XVECTOR3& loc);
	virtual void                 SetActorRotation(const xfloat32 fRoll, const xfloat32 fYaw, const xfloat32 fPitch );//in radians.
	virtual void                 SetActorRotation(const XQUATERNION& rot);

#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet  GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy);	
	XEPropertyObjectSet          GetPropertyObjectComponentTree(XEPropertyObjectProxy* pPropertyObjectProxy);
#endif
	template<typename castType>  
	castType*                    CastActor();
	template<typename castType>
	const castType*              CastActor() const;
protected:
	virtual void                 RenderDummyShape(XEViewport* pViewport);
	virtual void                 RenderBoundingBox(XEViewport* pViewport);
	virtual XEWorld*             GetReceiverWorld() override{ return GetOwner(); }
public:						     
	XEActorComponent*            GetRootComponent();
	X_EES_LINE const XEActorComponent* GetRootComponent() const;
	XEActorComponent*            GetComponentOfIndex(xint32 nIndex);
	XEActor*                     GetParentActor() const;
	void                         GetChildActors(XEAttachChildren& child);
	void                         GetAllChildActors(XEAttachChildren& child);
	XVECTOR3                     GetActorLocation() const;
	XQUATERNION                  GetActorRotation() const;
	XVECTOR3                     GetActorScale() const;
	XVECTOR3                     GetActorLocalLocation() const;
	XQUATERNION                  GetActorLocalRotation() const;
	XVECTOR3                     GetActorLocalScale() const;
	void                         SetActorScale(const XVECTOR3& sca);
	XMATRIX4                     GetRawWorldTransform() const;
	XMATRIX4                     GetWorldTransform() const;
	xbool                        SetActorName(const XString& szActorName,XEWorld* pContext = NULL);
	//zsx:fix filterPath bug,区分大小写
	xbool						 ChangeSubActorFilterPath(const XString& strParentOriginName,const XString& strParentNewName);
	xbool                        IsSerialized(const XMLElement* pEleParent);
	xint32                       GetComponentValidIndex();
	xint32                       AddExtendParam( IXEExtendParam*  pExtendParam);
	xbool                        RemoveExtendParam( IXEExtendParam* pExtendParam, xbool bDeleteMemory = xtrue);
	IXEExtendParam*              GetExtendParam(const xint32 nIndex) const;
	IXEExtendParam*              GetExtendParam(const XString& strExtendParamName) const;
	XEActorExtendParamList&      GetExtendParam();
	xbool                        MergeToWorldTransform(const XMATRIX4& toMatrix);
	xbool                        ApplyWorldTransform(const XMATRIX4& matrix, xbool bSyncGuestFromParent = xtrue);
	xbool                        TravelToGuestWorld(XEWorld* pGuestWorld);//actor will be temporally travel to the guest world.
	xbool                        ReturnBackToOwnerWorld();//actor went back home.
	X_FORCEINLINE xbool          IsInGuestWorld()const{ return NULL != m_pGuest; }
public:
	xbool                        GetMergeRenderHidden(xint32 nBit = -1) const;
	xint32                       SetMergeRenderHidden(xint32 nMergeBit,xbool bHidden);
	xint32                       SetMergeRenderHiddenEnable(xint32 nMergeBit, xbool bEnable);
	void                         ResetMergeRenderHidden();
	void                         SetDeleted(xbool bDelete);
	void                         UpdateLocalTransformForChildComponent();
	void                         SetHidden(xbool bHide);
	void                         SetTransformMergeMode(xbool bMerge, xbool bRecursion = xtrue);
	xbool                        AttachBindingScriptAsset(const xchar* pAssetPath);//path will be fixed.
	void                         DetachBindingScriptInstance();
	xbool                        IsReferenceTarget() const { return m_bReferenceTarget; }
	void                         SetReferenceTargetFlag(xbool bReference);
	const XString&               GetReferenceTargetName() const { return m_szReferenceTarget; }
	void                         SetReferenceTargetName(XString szReference);
	xint32                       GetReferenctType() const { return m_nReferenceType; }
	xint32                       GetLayoutType()const { return m_nLayoutType; };
	void                         SetReferenceType(xint32 nType);
	void                         SetLayoutType(xint32 nType);
public:						     
	XEActorComponent*            AddActorComponent(const XString& szType);
	/** Get the forward (Z) vector (length 1.0) from this Actor, in world space.  */
	XVECTOR3                     GetActorForwardVector() const;
	/** Get the up (Y) vector (length 1.0) from this Actor, in world space.  */
	XVECTOR3                     GetActorUpVector() const;
	/** Get the right (X) vector (length 1.0) from this Actor, in world space.  */
	XVECTOR3                     GetActorRightVector() const;

	//rotation set methods. in world space.
	void				         SetForwardDirAndUp(const XVECTOR3& vForwardDir, const XVECTOR3& vUp);
	void				         SetPositionAndForwardDirUp(const XVECTOR3& vPosition, const XVECTOR3& vForwardDir, const XVECTOR3& vUp);
	void				         RotateX(xfloat32 fDeltaRadian);
	void				         RotateY(xfloat32 fDeltaRadian);
	void				         RotateZ(xfloat32 fDeltaRadian);
	void				         RotateAxis(const XVECTOR3& vRotateAxis, xfloat32 fDeltaRadian);
public:
	xbool                        m_bReferenceTarget;
	xint32                       m_nReferenceType;
	xint32                       m_nLayoutType;
	XString                      m_szReferenceTarget;
	xbool                        m_bHidden;
	xbool                        m_bHiddenInGame;
	xint32                       m_nMergeHidden;
	static const XString         ACTOR_TYPENAME;//will be set to "EmptyAcotr"
	static const XString         RC_CHANNEL;
	XString                      m_szActorName;//instance name, will generated automatically or set manually.
	XE_EVENT_CHANNEL_TYPE_DEF(RC_CHANNEL)
	X_CLASS_DEF(XEActor)
	X_FORCEINLINE xbool			 IsHidden(){ return m_bHidden; }
	X_FORCEINLINE void           SetHiddenInGame(xbool bHide){ m_bHiddenInGame = bHide; }
	X_FORCEINLINE xbool          IsHiddenInGame(){ return m_bHiddenInGame; }
	X_FORCEINLINE void           SetBoundingBoxColor(XCOLOR clVal){ m_clBoundingBoxColor = clVal; }
	X_FORCEINLINE XCOLOR         GetBoundingBoxColor(){ return m_clBoundingBoxColor; }
	X_FORCEINLINE const XString& GetActorName() const { return m_szActorName; }
	X_FORCEINLINE void           SetActorTickEnabled(bool bEnable){ m_bEnaleTick = bEnable; }
	X_FORCEINLINE XEWorld*       GetOwner() const{ return m_pOwner; }
	X_FORCEINLINE void           SetOrder(const xint32 nOrder){ m_nOrder = nOrder; }
	X_FORCEINLINE xint32         GetOrder()const{ return m_nOrder; }
	X_FORCEINLINE xbool          IsDeleted()const{ return m_bDeleted; }
	//X_FORCEINLINE xbool          IsModified()const { return m_bModified; }
	xbool						 IsModified()const;
	X_FORCEINLINE void           SetModified(xbool bModified){ m_bModified = bModified; }
	X_FORCEINLINE xint32         GetPickMask()const{ return m_nPickMask; }
	X_FORCEINLINE xint32         GetPickPriority()const{ return m_nPickPriority; }
	X_FORCEINLINE xbool          IsPickEnable()const{ return m_nPickMask&XEHitResult::XHR_EnableHit; }
	X_FORCEINLINE void           SetPickMask(const xint32 nMask){ m_nPickMask = nMask; }
	X_FORCEINLINE void           SetPickPriority(const xint32 nPriority){ m_nPickPriority = nPriority; }
	X_FORCEINLINE void           SetFilterPath(XString szFilterPath){ szFilterPath.ToLower(); m_szFilterPath = szFilterPath; };
	X_FORCEINLINE void           SetFilterPath(XString szFilterPath, xbool bIsToLower){ if (bIsToLower){ szFilterPath.ToLower(); } m_szFilterPath = szFilterPath; };//zsx fix editor folder bug
	X_FORCEINLINE const XString& GetFilterPath()const{ return m_szFilterPath; }
	X_FORCEINLINE xbool          IsTransformMergeMode()const{ return m_bTransformMergeMode; }
	X_FORCEINLINE void           SetDrawDebugType(const xint32 nDebug){ m_nDrawDebugType = nDebug; }//actor common---need to Serialize.
	X_FORCEINLINE xint32		 GetDrawDebugType(){ return m_nDrawDebugType; }
	X_FORCEINLINE xbool			 IsDrawAuxiliary(){ return m_nDrawDebugType & EDD_DRAW_AUXILIARY; }
	X_FORCEINLINE void			 SetDrawDebugTypeBySelected(const xint32 nSelect){ m_nDrawDebugTypeBySelected = nSelect; }//not Serialize.
	X_FORCEINLINE xint32		 GetDrawDebugTypeBySelected(){ return m_nDrawDebugTypeBySelected; }
	X_FORCEINLINE xbool			 IsDrawAuxiliaryBySelected(){ return m_nDrawDebugTypeBySelected & EDD_DRAW_AUXILIARY; }
	X_FORCEINLINE xbool			 IsBoundingBoxVisibleBySelected(){ return m_nDrawDebugTypeBySelected  & EDD_BOUNDINGBOX; }
	X_FORCEINLINE xbool			 IsBoundingBoxVisible(){ return m_nDrawDebugType & EDD_BOUNDINGBOX; }
	X_FORCEINLINE xbool          IsDummyShapeVisible(){ return m_nDrawDebugType & EDD_DUMMY_SHAPE; }
	X_FORCEINLINE XECollisionChannelMeta     GetCollisionChannel() const{ return m_eCollisionChannel; }
	X_FORCEINLINE void                       SetCollisionChannel(const XECollisionChannelMeta& ccm){ m_eCollisionChannel = ccm; }
	X_FORCEINLINE XEScriptContainerInstance* GetScriptContainerInstance(){ return m_pScriptContainerInstance; }

#if X_PLATFORM_WIN_DESKTOP
	X_FORCEINLINE void			 SetRenameActorFlag(xbool bIsCanRename){ m_bIsCanRename = bIsCanRename; }//Whether the actor supports renaming
	X_FORCEINLINE xbool			 IsEnableRenameActor(){ return m_bIsCanRename; }
#endif

public:
	xbool				         ReCalculateParentMatrixByUserNode(XEActor* pParentActor,XMATRIX4& matOutParentMatrix);
	void						 UpdateBindDataFromParentUserNode(XEBindUserNodeData bBindUserNodeData);
	XEBindUserNodeData&			 GetBindUserNodeData();
	//设置实时改变的状态
	void					     SetUpdateTranfromFromUserNode(xbool bIsUpdate){ m_bIsUpdateTransformFromUserNode = bIsUpdate; }
	xbool			             GetIsUpdateTranformFromUserNode() const { return m_bIsUpdateTransformFromUserNode; }
	XEUtility::XEActorPropertySerializeFlag*	GetActorPropertySerializeFlag(){ return &m_SerializeFlag; }
	xbool						 IsChildActor(const XEActor* pChildActor);
protected:
	XEActorComponent*            m_pRootComponent;
	XEWorld*                     m_pOwner;	
	XEWorld*                     m_pGuest;//the guest world
	xbool                        m_bEnaleTick;
	xbool                        m_bDeleted;//will not be rendered if deleted.
	xbool                        m_bModified;
	xint32                       m_nOrder;
	xint32                       m_nPickMask;
	xint32                       m_nPickPriority;
	XCOLOR                       m_clBoundingBoxColor;
	XString                      m_szFilterPath;//default is /custom/ or /system/, in the case of embedding any actor, it changed into /custom/parentName1:actor/parentName2:actor/...
	XEActorExtendParamList       m_ExtendParamList;

	XCOLORBASE				     m_clrDrawDebugColor;
	xint32						 m_nDrawDebugType;
	xint32						 m_nDrawDebugTypeBySelected;//selected
	xbool						 m_bIsCanRename;//can rename?
	XECollisionChannelMeta       m_eCollisionChannel;

	XEBindUserNodeData			 m_BindUserNodeData;//bind parent actor's UserNode data
	xbool				         m_bIsUpdateTransformFromUserNode;
	XEUtility::XEActorPropertySerializeFlag   m_SerializeFlag;//doing copy actor useful
private:	
	friend class                 XEChildActorComponent;
	XEChildActorComponent*       m_pAsChildActorComponent;//component that belong to.
	xbool                        m_bTransformMergeMode;//merge-mode will separate the transform into engine-related and none-engine-related part.
	xint32                       m_nComponentIndexAssign;//to assign the component index.
	XEScriptContainerInstance*   m_pScriptContainerInstance;//script holder.
};

template<typename castType>
castType* XEActor::CastActor()
{
	return dynamic_cast<castType*>(this);
}

template<typename castType>
const castType* XEActor::CastActor() const
{
	return dynamic_cast<const castType*>(this);
}

#define XE_ACTOR_TYPE_DEF(T) virtual const XString& GetTypeName()const override{return T;}
#define XE_ACTOR_CAST(T) static T* Cast(XEActor* A){ return A?A->CastActor<T>():NULL;} static XEActor* ReverseCast(T* A){ return A;}

#endif // XEACTOR_H
