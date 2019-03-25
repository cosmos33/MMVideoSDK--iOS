/******************************************************************************

@File         XEActorComponent.h

@Version       1.0

@Created      2017, 9, 20

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_ACTOR_COMPONENT_H
#define XE_ACTOR_COMPONENT_H
#include "XArray.h"
#include "XHashTable.h"
#include "XViewport.h"
#include "XCustomGeometry.h"
#include "XETransform.h"
#include "XESingleton.h"
#include "XEHitResult.h"
#include "tinyxml2_XEngine.h"
#include "XEFactoryActorComponentUtil.h"
#include "XEEventReceiver.h"

#define HIT_DEBUG_SHAPE_DISPALY 0

#if X_PLATFORM_WIN_DESKTOP
#include "XEFactoryPropertyObjectUtil.h"
#include "XEPropertyObjectBase.h"
#endif

using namespace tinyxml2_XEngine;

class XEActor;
class XEViewport;
class XEWorld;
class XEActorComponent
	:public XEEventReceiver
{
	friend class XEActor;
public:
	typedef XArray<XEActorComponent*> XEAttachChildren;
	typedef XArray<XEHitResult> XEHitResultList;
	XEActorComponent();
	virtual ~XEActorComponent(){};
public:
	virtual void                 Deserialize(const XMLElement* pEleComponent);
	virtual XMLElement*          Serialize(XMLElement* pEleParent);
	virtual	const XString&       GetTypeName() const{ return COMPONENT_TYPENAME; }
	virtual void                 Release();
	virtual void                 Empty();//empty any instance for this component itself.
	virtual void                 Tick(xfloat32 fDelMs, xbool bForceTick = xtrue);//in milliseconds.
	virtual void                 PresentPhysics(xfloat32 fDelMs);//in milliseconds.
	virtual void                 Render(XEViewport* pViewport);
	virtual void                 AttachToComponent(XEActorComponent* pParent);
	virtual void                 DetachFromParent();
	virtual void                 Initialize(XEActor* pActor);
	virtual XCusAABB             GetCusAABB(xfloat32* pfRadius = NULL) const;
	virtual xbool                RayPick(XEHitResult& hr, XEHitResultList& hitResultList);//including child.
	virtual xbool                RayPick(XEHitResult& hr, XEHitResultList& hitResultList, XViewport* viewport, const XVECTOR2& vScreenPoint);//easy access, including child
	virtual xbool                RayPick(XEHitResult& hr);//self only.
#if X_PLATFORM_WIN_DESKTOP
	virtual void                 GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po);
#endif
	virtual void                 UpdateForSerialize(){};
	virtual void                 SetDeleted(xbool bDelete);
	virtual void                 OnSocketUpdate(const XMATRIX4& matWorld);//connect and bind to socket.
	template<typename castType>
	castType*                    CastActorComponent();
	template<typename castType>
	const castType*              CastActorComponent() const;
	virtual void                 SetHidden(xbool bHide);
protected:
	//translate to world-matrix impl
	//Override this method for custom behavior.
	virtual xbool                ApplyWorldTransformImpl(const XMATRIX4& mat){ return xtrue; }
	virtual xbool                MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion){ return xtrue; }
	virtual XMATRIX4             GetRawWorldTransformImpl() const{ return GetWorldTransform(); }
	virtual XEWorld*             GetReceiverWorld() override{ return GetWorldOwner(); }
	virtual void                 OnParentEmpty(const XEActorComponent* pParentComponent){}//need to do something necessary while parent is set to empty.
public:
	xbool                        MergeToWorldTransform(const XMATRIX4& mat);
	xbool                        ApplyWorldTransform(const XMATRIX4& mat);
	XMATRIX4                     GetRawWorldTransform() const;
public:
	XEActorComponent*            GetAttachParentComponent();
	void                         GetAllChildComponents(XEAttachChildren& container);
	XEAttachChildren&            GetChildComponents();
	xbool                        HasChildComponent();
	//add/remove only!
	void                         AddChildComponent(XEActorComponent* pChild);
	void                         RemoveChildComponent(XEActorComponent* pChild);
	void                         SetActorOwner(XEActor* pActor);
	XEActor*                     GetActorOwner() const;
	void                         ReleaseActorOwner();
	xbool                        IsTransformMergeMode();
	XETransform&                 GetTransfrom();
	xbool                        IsSerialized(const XMLElement* pEleParent);
	XEWorld*                     GetWorldOwner();//can be override.
	X_EES_LINE const XEWorld*    GetWorldOwner() const;//can be override. 
	X_FORCEINLINE void           SetWorldOwner(XEWorld* pWorld){ m_pWorldOwner = pWorld; }
public:
	/** Get the forward (Z) vector (length 1.0) from this Component, in world space.  */
	XVECTOR3                     GetForwardVector() const;
	/** Get the up (Y) vector (length 1.0) from this Component, in world space.  */
	XVECTOR3                     GetUpVector() const;
	/** Get the right (X) vector (length 1.0) from this Component, in world space.  */
	XVECTOR3                     GetRightVector() const;

	//rotation set methods. in world space.
	//dir and up should be perpendicular.
	void				         SetForwardDirAndUp(const XVECTOR3& vForwardDir, const XVECTOR3& vUp);
	void				         SetPositionAndForwardDirUp(const XVECTOR3& vPosition, const XVECTOR3& vForwardDir, const XVECTOR3& vUp);

	void				         RotateX(xfloat32 fDeltaRadian);
	void				         RotateY(xfloat32 fDeltaRadian);
	void				         RotateZ(xfloat32 fDeltaRadian);
	void				         RotateAxis(const XVECTOR3& vRotateAxis, xfloat32 fDeltaRadian);

public:
	//local changed, by delta
	void                         DeltaLocalMove(const XVECTOR3& deltaMovement);
	void                         DeltaLocalRotation(const XVECTOR3& deltaRotateEuler);
	void                         DeltaLocalScale(const XVECTOR3& deltaScale);
public:
	XE_EVENT_CHANNEL_TYPE_DEF(RC_CHANNEL)
	X_CLASS_DEF(XEActorComponent)
	X_FORCEINLINE XVECTOR3       GetLocation() const      { return m_Transform.GetLocation(); }
	X_FORCEINLINE XQUATERNION    GetQuat()     const      { return m_Transform.GetQuaternion(); }
	X_FORCEINLINE XVECTOR3       GetScale()    const      { return m_Transform.GetScale(); }
	X_FORCEINLINE xint32         GetIndex()    const      { return m_nIndex; }
	X_FORCEINLINE xbool          IsDeleted()  const      { return m_bDeleted; }
	//X_FORCEINLINE xbool          IsModified()  const      { return m_bModified; }
	xbool						 IsModified()  const; //travel all children.--ylj
	X_FORCEINLINE xbool          IsHidden()    const      { return m_bHidden; }
	X_FORCEINLINE void           SetModified(xbool bModified){ m_bModified = bModified; }	
public:
	//derived.
	XVECTOR3                     GetWorldLocation() const;
	XQUATERNION                  GetWorldRotation() const;
	XVECTOR3                     GetWorldScale() const;
	const XMATRIX4&              GetWorldTransform() const;

	/// Convert a local space position to world space.
	XVECTOR3                     LocalToWorld(const XVECTOR3& position) const;
	/// Convert a local space position or rotation to world space.
	XVECTOR4                     LocalToWorld(const XVECTOR4& vector) const;
	/// Convert a world space position to local space.
	XVECTOR3                     WorldToLocal(const XVECTOR3& position) const;
	/// Convert a world space position or rotation to local space.
	XVECTOR4                     WorldToLocal(const XVECTOR4& vector) const;
protected:
	void                         UpdateWorldTransform() const;
	void                         MarkTransformDirty();
#if X_PLATFORM_WIN_DESKTOP
	enum ELostAssetType
	{
		ELAT_NONE,
		ELAT_MODEL_ASSET,//mdl
		ELAT_MOUNTER_ASSET,//mounter
		ELAT_ANIAMTION_ASSET,//animation
		ELAT_PHYSICAL_RIGID_ASSET,//rigid
		ELAT_PARTICLE_ASSET,//particle		
		ELAT_BLEND_ASSET,//blend
		ELAT_SEQ_ASSET,
		ELAT_ARADS_ASSET,
		ELAT_AUDIO_ASSET
	};
	xbool						 LoadAssetError(const xchar* szFilePath, ELostAssetType eType);
	xbool						 IsExistAssetPath(const xchar* szFilePath);
#endif
public:
	xbool                        MoveComponent(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion);
	xbool                        ScaleComponent(const XVECTOR3& vNewScale);
	void                         UpdateWorldTransformCommon() const;
	xfloat32                     GetDistanceToCamera(const XEWorld* pWorld = NULL) const;
protected:
	XEActorComponent*            m_pAttachParent;
	XEActor*                     m_pActorOwner;
	XEAttachChildren             m_attachChildren;
	XETransform                  m_Transform;
	xint32                       m_nIndex;
	xbool                        m_bDeleted;//features of marking deleted of a component will be delay.
	xbool                        m_bModified;
	xbool                        m_bHidden;
	XEWorld*                     m_pWorldOwner;//may belong to the world created by others.

#if X_PLATFORM_WIN_DESKTOP
protected:
	//properties
	XEPropertyObjectSet          m_setProperty;
	struct XELoadErrorData
	{
		XString					 strModelAssetPathTemp;//用于在加载错误时临时记录mdl路径
		XString					 strMounterAssetPathTemp;//用于在加载错误时临时记录Mounter路径
		XString					 strAnimationAssetPathTemp;//动画资源路径
		XString					 strPhysicalRigidAssetPathTemp;//物理刚体资源资源路径
		XString					 strParticleAssetPathTemp;//particle路径
		XString					 strSeqAssetPathTemp;//seq
		XString					 strBlendAssetPathTemp;//blend
		XString					 strARAdsAssetPathTemp;
		XString                  strAudioAssetPathTemp;
	};
	XELoadErrorData				 m_LoadErrorInfoData;//用于记录丢失的资源路径，以便序列化时保存
#endif
private:
	mutable xbool                m_bTransformDirty;
public:
	static const XString         COMPONENT_TYPENAME;   
	static const XString         RC_CHANNEL;
	static const xfloat32        DUMMY_SHAPE_RADIUS;
#if HIT_DEBUG_SHAPE_DISPALY
	XEHitResult                  renderHitResult;
#endif
};

template<typename castType>
castType* XEActorComponent::CastActorComponent()
{
	return dynamic_cast<castType*>(this);
}

template<typename castType>
const castType* XEActorComponent::CastActorComponent() const
{
	return dynamic_cast<const castType*>(this);
}

#define XE_COMPONENT_TYPE_DEF(T) virtual const XString& GetTypeName() const override{return T;}
#define XE_COMPONENT_CAST(T) static T* Cast(XEActorComponent* C){ return C?C->CastActorComponent<T>():NULL;} static XEActorComponent* ReverseCast(T* C){ return C;}
#define XE_GUARANTEE_NOT_DELETED if( m_bDeleted ) return
#define XE_GUARANTEE_NOT_DELETED_RETURN(R) if( m_bDeleted ) return R
#define XE_GUARANTEE_NOT_HIDDEN if( m_bHidden ) return
#define XE_GUARANTEE_NOT_HIDDEN_IN_GAME if (m_bHiddenInGame) return

#endif // XE_ACTOR_COMPONENT_H
