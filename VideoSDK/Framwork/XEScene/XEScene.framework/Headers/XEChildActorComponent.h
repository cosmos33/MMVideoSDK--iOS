/******************************************************************************

@File         XEChildActorComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_CHILD_ACTOR_COMPONENT_H
#define XE_CHILD_ACTOR_COMPONENT_H
#include "XEActorComponent.h"
#include "XEUtility.h"
//containing an actor.
class XEActor;
class XEChildActorComponent :public XEActorComponent
{
public:
	XEChildActorComponent();
	~XEChildActorComponent();
public:
	virtual void           Release() override;
	virtual void           Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*    Serialize(XMLElement* pEleParent) override;
	virtual void           Tick(xfloat32 fDel, xbool bForceTick = xtrue);
	virtual void           SetHidden(xbool bHide) override;
	void                   UpdateTransformFromGuestActor();
	void				   UpdateTranformFromParentUserNode();

public:
	X_FORCEINLINE XEActor* GetGuestActor(){ return m_pGuestActor; }
	X_FORCEINLINE void     SetGuestActor(XEActor* pActor){ m_pGuestActor = pActor; }
protected:
	// Override this method for custom behavior.
	virtual xbool          MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual xbool          ApplyWorldTransformImpl(const XMATRIX4& mat) override;
	virtual XMATRIX4       GetRawWorldTransformImpl() const override;
private:
	xbool				   IsSerializedGuestActor();
	xbool				   IsCopyProcess();
protected:
	XEActor* m_pGuestActor;//guest actor
public:
	XE_COMPONENT_CAST(XEChildActorComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEChildActorComponent)
	static const XString  COMPONENT_TYPENAME;
};

#endif // XE_CHILD_ACTOR_COMPONENT_H
