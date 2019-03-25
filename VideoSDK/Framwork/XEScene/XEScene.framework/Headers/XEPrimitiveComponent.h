/******************************************************************************

@File         XEPrimitiveComponent.h

@Version       1.0

@Created      2018, 3, 8

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_PRIMITIVE_COMPONENT_H
#define XE_PRIMITIVE_COMPONENT_H
#include "XEActorComponent.h"
#include "IXRigidBody.h"
#include "XModelInstance.h"
//containing physics properties.

class XEActor;
class IXPhysicsRes;
class IXSkeletalPhysicsInstance;

//phy asset for no amin model
class XEPrimitiveComponent :public XEActorComponent
{
public:
	XEPrimitiveComponent();
	virtual ~XEPrimitiveComponent();

public:
	virtual void			Release() override;
	virtual void            Empty() override;
	virtual XMLElement*		Serialize(XMLElement* pEleParent) override;
	virtual void			SetDeleted(xbool bDelete) override;

public:
	//////////////////////////////////////////////////////////////////////////
	void					EmptyPhysics();
	void					SetPhysicalAssetPath(const xchar* szPath){ m_strPhysicalAssePath = szPath; }
	const XString&			GetPhysicalAssetPath() const { return m_strPhysicalAssePath; }
	virtual xbool           LoadPhysicalAsset(const xchar* pPath, RigidActorType eType = (RigidActorType)-1){ return xfalse; }
	xbool					IsLoadedPhysicalRes()const { return m_bLoadedPhysicalRes; }
	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////Rigid body
	xbool					IsGravityEnabled()const;
	void					SetGravityEnabled(xbool bSet);
	xbool					GetShapeMaterial(XShapeMaterial& shapeMaterial);
	void					SetShapeMaterial(const XShapeMaterial& shapeMaterial);
	xbool					IsSimulatePhysics() const;
	void					SetSimulatePhysics(xbool bSimulate);
	xfloat32				GetMass() const;
	void					SetMass(xfloat32 f);
	xfloat32				GetLinearDamping() const;
	void					SetLinearDamping(xfloat32 fLinearDamping);
	xfloat32				GetAngularDamping() const;
	void					SetAngularDamping(xfloat32 fAngularDamping);
	RigidActorType			GetRigidType() const;
	void					SetRigidType(xint32 nSel);
	const XArray<XString>&	GetRigidTypeNameList(){ return m_aPhysicsRigidTypeName; }
	xbool					IsCCDEnabled() const;
	void					SetRigidCCDEnabled(xbool bSet);
	XVECTOR3				GetLinearVelocity() const;
	void					SetLinearVelocity(const XVECTOR3& vVelocity);
	XVECTOR3				GetAngularVelocity() const;
	void					SetAngularVelocity(const XVECTOR3& vVelocity);
	//////////////////////////////////////////////////////////////////////////Rigid body
protected:
	xbool					CreateRigidAndRes(RigidActorType eType, XBaseCoordSpace* pBindObject, const xchar* szPath);
	void					RemoveRigidBody();
protected:
	// Override this method for custom behavior.
	virtual xbool			MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual xbool			ApplyWorldTransformImpl(const XMATRIX4& mat) override;
public:
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME);
	X_CLASS_DEF(XEPrimitiveComponent)
	static const XString    COMPONENT_TYPENAME;

protected:
	XString							m_strPhysicalAssePath;
	xbool							m_bLoadedPhysicalRes;

	//rigid body
	IXRigidBody*					m_pPhysicsRigidBody;

	//skeletal instance
	IXSkeletalPhysicsInstance*		m_pSkeletalPhysicsInstance;
private:
	XArray<XString>					m_aPhysicsRigidTypeName;
};

#endif // XE_PRIMITIVE_COMPONENT_H
