/******************************************************************************

@File         XEAttachDetachRules.h

@Version       1.0

@Created      2018, 9, 17

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_ATTACH_DETACH_RULES_H_
#define _XE_ATTACH_DETACH_RULES_H_

#include "XMemBase.h"

struct XEAttachRules
	:public XMemBase
{
	/** Various preset attachment rules. Note that these default rules do NOT by default weld simulated bodies */
	static const XEAttachRules KeepRelativeTransform;
	static const XEAttachRules KeepWorldTransform;
	static const XEAttachRules SnapToTargetNotIncludingScale;
	static const XEAttachRules SnapToTargetIncludingScale;

	enum EAttachmentRule
	{
		/** Keeps current relative transform as the relative transform to the new parent. */
		KeepRelative,
		/** Automatically calculates the relative transform such that the attached component maintains the same world transform. */
		KeepWorld,
		/** Snaps transform to the attach point */
		SnapToTarget,
	};

	XEAttachRules(EAttachmentRule InRule, xbool bInWeldSimulatedBodies);
	XEAttachRules(EAttachmentRule InLocationRule, EAttachmentRule InRotationRule, EAttachmentRule InScaleRule, xbool bInWeldSimulatedBodies);

	/** The rule to apply to location when attaching */
	EAttachmentRule LocationRule;

	/** The rule to apply to rotation when attaching */
	EAttachmentRule RotationRule;

	/** The rule to apply to scale when attaching */
	EAttachmentRule ScaleRule;

	//to be defined.
	/** Whether to weld simulated bodies together when attaching */
	xbool bWeldSimulatedBodies;
};


/** Rules for detaching components */
struct XEDetachmentTransformRules
	:public XMemBase
{
	/** Various preset detachment rules */
	static const XEDetachmentTransformRules KeepRelativeTransform;
	static const XEDetachmentTransformRules KeepWorldTransform;

	enum EDetachmentRule
	{
		/** Keeps current relative transform. */
		KeepRelative,

		/** Automatically calculates the relative transform such that the detached component maintains the same world transform. */
		KeepWorld,
	};

	XEDetachmentTransformRules(EDetachmentRule InRule, xbool bInCallModify);
	XEDetachmentTransformRules(EDetachmentRule InLocationRule, EDetachmentRule InRotationRule, EDetachmentRule InScaleRule, xbool bInCallModify);
	XEDetachmentTransformRules(const XEDetachmentTransformRules& AttachmentRules, xbool bInCallModify);

	/** The rule to apply to location when detaching */
	EDetachmentRule LocationRule;

	/** The rule to apply to rotation when detaching */
	EDetachmentRule RotationRule;

	/** The rule to apply to scale when detaching */
	EDetachmentRule ScaleRule;

	//to be defined.
	/** Whether to call Modify() on the components concerned when detaching */
	xbool bCallModify;
};

#endif


