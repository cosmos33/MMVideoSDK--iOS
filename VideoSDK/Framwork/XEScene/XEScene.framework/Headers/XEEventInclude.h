/******************************************************************************

@File         XEEventInclude.h

@Version       1.0

@Created      2018, 6, 14

@Description  The class ids of each class in X Editor 

@HISTORY:

******************************************************************************/
#ifndef _XE_EVENT_INCLUDE_H
#define _XE_EVENT_INCLUDE_H

#include "XEEventManager.h"
#include "SpecificEvent/XEActorMovementEvent.h"
#include "SpecificEvent/XEActorVisibleEvent.h"
#include "SpecificEvent/XEPlayAnimationEvent.h"
#include "SpecificEvent/XESpawnParticleSystemEvent.h"
#include "SpecificEvent/XEVariantDataEvent.h"
#include "SpecificEvent/XECustomEvent.h"

//utile receivers
#include "UtilReceiver/XEGlobalReceiver.h"
#include "UtilReceiver/XEVariantDataReceiver.h"
#include "UtilReceiver/XECustomEventReceiver.h"

#endif // _XE_EVENT_INCLUDE_H
