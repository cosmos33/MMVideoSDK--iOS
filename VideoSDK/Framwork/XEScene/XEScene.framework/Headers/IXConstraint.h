#ifndef _IX_CONSTRAINT_H_
#define _IX_CONSTRAINT_H_

#include "XMemBase.h"
#include "XMath3D.h"
#include "XBase3DTypes.h"

enum EConstraintMotion
{
	// No constraint against this axis.
	CM_FREE,
	// Limited freedom along this axis.
	CM_LIMITED,
	// Fully constraint against this axis.
	CM_LOCKED,

	CM_NUM,
};

struct XConstraintBaseParams
{
	XConstraintBaseParams()
		: Stiffness(0.5f)
		, Damping(0.5f)
		, Restitution(0.5f)
		, ContactDistance(-1.0f)
		, bSoftConstraint(xfalse) {}

	// Stiffness of the soft constraint. Only used when Soft Constraint is on.
	xfloat32 Stiffness;

	// Damping of the soft constraint. Only used when Soft Constraint is on.
	xfloat32 Damping;

	// Controls the amount of bounce when the constraint is violated. A restitution value of 1 will bounce back with the same velocity the limit was hit. A value of 0 will stop dead.
	xfloat32 Restitution;

	// Determines how close to the limit we have to get before turning the joint on. Larger value will be more expensive, but will do a better job not violating constraints. A smaller value will be more efficient, but easier to violate.
	xfloat32 ContactDistance;

	// Whether we want to use a soft constraint (spring).
	xbool bSoftConstraint;
};

/** Distance constraint */
struct XLinearConstraint : public XConstraintBaseParams
{
	XLinearConstraint()
		: XConstraintBaseParams()
		, Limit(0.0f)
		, XMotion(CM_LOCKED)
		, YMotion(CM_LOCKED)
		, ZMotion(CM_LOCKED) {}

	// The distance allowed between between the two joint reference frames. Distance applies on all axes enabled (one axis means line, two axes implies circle, three axes implies sphere)
	xfloat32 Limit;

	// Indicates the linear constraint applied along the X-axis. Free implies no constraint at all. Locked implies no movement along X is allowed. Limited implies the distance in the joint along all active axes must be less than the Distance provided.
	EConstraintMotion XMotion;

	// Indicates the linear constraint applied along the Y-axis. Free implies no constraint at all. Locked implies no movement along Y is allowed. Limited implies the distance in the joint along all active axes must be less than the Distance provided.
	EConstraintMotion YMotion;

	// Indicates the linear constraint applied along the Z-axis. Free implies no constraint at all. Locked implies no movement along Z is allowed. Limited implies the distance in the joint along all active axes must be less than the Distance provided.
	EConstraintMotion ZMotion;
};

/** Cone constraint */
struct XConeConstraint : public XConstraintBaseParams
{
	XConeConstraint()
		: XConstraintBaseParams()
		, Swing1LimitDegrees(45.0f)
		, Swing2LimitDegrees(45.0f)
		, Swing1Motion(CM_LOCKED)
		, Swing2Motion(CM_LOCKED) {}

	// Angle of movement along the XY plane. This defines the first symmetric angle of the cone.
	xfloat32 Swing1LimitDegrees;

	// Angle of movement along the XZ plane. This defines the second symmetric angle of the cone.
	xfloat32 Swing2LimitDegrees;

	// Indicates whether the Swing1 limit is used.
	EConstraintMotion Swing1Motion;

	// Indicates whether the Swing2 limit is used.
	EConstraintMotion Swing2Motion;
};

/** Angular roll constraint */
struct XTwistConstraint : public XConstraintBaseParams
{
	XTwistConstraint()
		: XConstraintBaseParams()
		, TwistLimitDegrees(45.0f)
		, TwistMotion(CM_LOCKED) {}

	// Symmetric angle of roll along the X-axis.
	xfloat32 TwistLimitDegrees;

	// Indicates whether the Swing1 limit is used.
	EConstraintMotion TwistMotion;
};

class IXModelInstance;
class IXConstraint : public XMemBase
{
public:
	virtual								~IXConstraint() {}

	virtual const xchar*				GetBone1Name() const = 0;
	virtual const xchar*				GetBone2Name() const = 0;

	virtual const XVECTOR3&				GetBone1Pos() const = 0;
	virtual XVECTOR3&					GetBone1Pos() = 0;
	virtual const XVECTOR3&				GetBone2Pos() const = 0;
	virtual XVECTOR3&					GetBone2Pos() = 0;
	virtual const XVECTOR3&				GetBone1PriAxis() const = 0;
	virtual XVECTOR3&					GetBone1PriAxis() = 0;
	virtual const XVECTOR3&				GetBone2PriAxis() const = 0;
	virtual XVECTOR3&					GetBone2PriAxis() = 0;
	virtual const XVECTOR3&				GetBone1SecAxis() const = 0;
	virtual XVECTOR3&					GetBone1SecAxis() = 0;
	virtual const XVECTOR3&				GetBone2SecAxis() const = 0;
	virtual XVECTOR3&					GetBone2SecAxis() = 0;

	virtual const XLinearConstraint&	GetLinearConstraint() const = 0;
	virtual XLinearConstraint&			GetLinearConstraint() = 0;
	virtual const XConeConstraint&		GetConeConstraint() const = 0;
	virtual XConeConstraint&			GetConeConstraint() = 0;
	virtual const XTwistConstraint&		GetTwistConstraint() const = 0;
	virtual XTwistConstraint&			GetTwistConstraint() = 0;

	virtual void						DebugDraw(IXModelInstance* pModelIns, const XCOLORBASE& Color = XCOLORBASE(0.0f, 1.0f, 0.0f, 1.0f), xfloat32 fDrawSize = 0.01f) const = 0;
};

#endif