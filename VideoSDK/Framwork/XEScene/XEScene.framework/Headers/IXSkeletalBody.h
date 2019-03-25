#ifndef _IX_SKELETAL_BODY_H_
#define _IX_SKELETAL_BODY_H_

#include "XMemBase.h"
#include "XMath3D.h"
#include "IXRigidBody.h"
#include "XBase3DTypes.h"

struct XSphylShapeElem
{
	XVECTOR3		vCenter;
	XQUATERNION		qRotation;
	xfloat32		fRadius;
	xfloat32		fLength;	// Cylinder height

	XSphylShapeElem()
		: vCenter(0, 0, 0)
		, qRotation(0, 0, 0, 1)
		, fRadius(1.0f)
		, fLength(1.0f) {}
};

class IXModelInstance;
class IXSkeletalBody : public XMemBase
{
public:
	virtual		~IXSkeletalBody() {}

	virtual const xchar*					GetBoneName() const = 0;

	virtual xbool							IsSimulatePhysics() const = 0;
	virtual void							SetSimulatePhysics(xbool bSimulatePhysics) = 0;

	virtual xfloat32						GetPhysicsBlendWeight() const = 0;
	virtual void							SetPhysicsBlendWeight(xfloat32 fPhysicsBlendWeight) = 0;

	virtual const XShapeMaterial&			GetMaterial() const = 0;
	virtual void							SetMaterial(const XShapeMaterial& mat) = 0;

	virtual xbool							IsGravityEnabled() const = 0;
	virtual void							SetGravityEnabled(xbool bSet) = 0;

	virtual xfloat32						GetMass() const = 0;
	virtual void							SetMass(xfloat32 fMass) = 0;

	virtual xfloat32						GetLinearDamping() const = 0;
	virtual void							SetLinearDamping(xfloat32 fLinearDamping) = 0;
	virtual xfloat32						GetAngularDamping() const = 0;
	virtual void							SetAngularDamping(xfloat32 fAngularDamping) = 0;

	virtual void							AttachShape(const XSphylShapeElem& ShapeElem) = 0;
	virtual void							DetachAllShapes() = 0;
	virtual const XArray<XSphylShapeElem>&	GetShapes() const = 0;
	virtual XArray<XSphylShapeElem>&		GetShapes() = 0;
	virtual void							SetShape(xint32 nShapeIndex, const XSphylShapeElem& ShapeElem) = 0;

	virtual void							DebugDraw(IXModelInstance* pModelIns, const XCOLORBASE& Color = XCOLORBASE(1.0f, 0.0f, 0.0f, 1.0f)) const = 0;
};

#endif