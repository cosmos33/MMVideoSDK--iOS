#ifndef _XANIMINSTANCEDATA_H_
#define _XANIMINSTANCEDATA_H_

#include "XSkeletonMask.h"
#include "XGlobalFuncs.h"
#include "XPose.h"
#include "XAnimParameterPack.h"
#include "XBlendShapeTarget.h"

class XFileBase;

enum class EOutputAccumlateType
{
    eOutputNoAcc,
    eOutputAccOverwrite,
    eOutputAccBlending,
    eOutputAccAdditive,
};

enum class EEventTriggerPolicy
{
    eEventTriggerImmediate,
    eEventTriggerQueued,
    eEventTriggerIgnore
};

struct XAnimInstance
{
    XAnimInstance()
        : CurrentPose(nullptr)
        , OutAccType(EOutputAccumlateType::eOutputNoAcc)
        , InBoneMask(nullptr)
        , InBlendWeight(1.0f)
        , ParamPack()
        , EventTriggerPolicy(EEventTriggerPolicy::eEventTriggerQueued)
		, OutMorphAccType(EOutputAccumlateType::eOutputNoAcc)
    {
    }

    XFullPose*						CurrentPose;
    XPose							OutPose;
    XPose                           OutSpeed;
    EOutputAccumlateType			OutAccType;
    XSkeletonMask					InBoneMask;
    xfloat32						InBlendWeight;
	XAnimParam						ParamPack;
    EEventTriggerPolicy             EventTriggerPolicy;
	XSkinModelBlendShapeWeight		OutMorphWeights;
	EOutputAccumlateType			OutMorphAccType;
};

#endif
