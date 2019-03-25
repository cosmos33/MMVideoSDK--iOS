#ifndef _IX2DRIGIDBODY_H_
#define _IX2DRIGIDBODY_H_

#include "XMath3D.h"

enum X2DRigidBodyType
{
	X_STATIC = 0,
	X_KINEMATIC,
	X_DYNAMIC
};

struct X2DRigidBodyDesc
{
	X2DRigidBodyDesc()
		: eType(X_STATIC)
		, vPosition(0.0f)
		, fAngle(0.0f)
		, vLinearVelocity(0.0f)
		, fAngularVelocity(0.0f)
		, fLinearDamping(0.0f)
		, fAngularDamping(0.0f)
		, bAllowSleep(xtrue)
		, bAwake(xtrue)
		, bFixedRotation(xfalse)
		, bBullet(xfalse)
		, bActive(xtrue)
		, pUserData(NULL)
		, fGravityScale(1.0f)
	{}
	X2DRigidBodyType	eType;
	XVECTOR2			vPosition;
	xfloat32			fAngle;
	XVECTOR2			vLinearVelocity;
	xfloat32			fAngularVelocity;
	xfloat32			fLinearDamping;
	xfloat32			fAngularDamping;
	xbool				bAllowSleep;
	xbool				bAwake;
	xbool				bFixedRotation;
	xbool				bBullet;
	xbool				bActive;
	void*				pUserData;
	xfloat32			fGravityScale;
};

struct X2DFilter
{
	X2DFilter()
	{
		categoryBits = 0x0001;
		maskBits = 0xFFFF;
		groupIndex = 0;
	}
	xuint16 categoryBits;
	xuint16 maskBits;
	xint16 groupIndex;
};

class IX2DShape;
struct X2DFixtureDesc
{
	X2DFixtureDesc()
		: pShape(NULL)
		, pUserData(NULL)
		, fFriction(0.2f)
		, fRestitution(0.0f)
		, fDensity(0.0f)
		, bSensor(xfalse)
	{
		bSensor = false;
	}
	IX2DShape*		pShape;
	void*			pUserData;
	xfloat32		fFriction;
	xfloat32		fRestitution;
	xfloat32		fDensity;		// usually in kg/m^2.
	xbool			bSensor;
	X2DFilter		filter;
};

class IX2DRigidBody : public XMemBase
{
public:
	virtual ~IX2DRigidBody(){}
	virtual void		CreateFixture(const X2DFixtureDesc* def) = 0;
	virtual void		CreateFixture(IX2DShape* pShape, xfloat32 fDensity) = 0;
	virtual XVECTOR2	GetPosition() const = 0;
	virtual xfloat32	GetAngle() const = 0;
};

#endif
