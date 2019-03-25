/******************************************************************************

@File         XETriggerUtil.h

@Version       1.0

@Created      2019, 1, 4 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_TRIGGER_UTIL_H_
#define _XE_TRIGGER_UTIL_H_
#include "XEEventUtil.h"
#include "XECustomEvent.h"

struct XETriggerData
{
	XETriggerData()
		: nTriggerState(0)
		, eEventType(XEEventUtil::EVENT_NONE)
		//, pLuaCustomEvent(NULL)
		, fDelayTime(0.0f)
		, bFirstExec(xtrue)
		, bTriggerRepeat(xtrue)
		, nAddIndex(-1)
	{
	}

	XETriggerData(xint32 _nTriggerState, XEEventUtil::XEEventType _eEventType, const XEVariant& _eventData,
		const XString& _strSender, const XString& _strExecutable, xfloat32 _fDelay, xbool _bTriggerRepeat)
		: nTriggerState(_nTriggerState)
		, eEventType(_eEventType)
		, eventData(_eventData)
		, strSender(_strSender)
		, strExecutable(_strExecutable)
		//, pLuaCustomEvent(NULL)
		, fDelayTime(_fDelay)
		, bFirstExec(xtrue)
		, bTriggerRepeat(_bTriggerRepeat)
		, nAddIndex(-1)
	{
		
	}

	~XETriggerData()
	{
		//pLuaCustomEvent = NULL;
	}

	
	xint32						nTriggerState; //The state when event is executing, eg. overlap begin/stay/end.
	XEEventUtil::XEEventType	eEventType; //specific event type
	XEVariant					eventData; //the data that event needs.
	XString						strSender; //sender actor name, may be empty according to specific event.
	XString						strExecutable;//executor actor name, may be empty according to specific event.
	//XECustomEvent*				pLuaCustomEvent;//only lua script trigger will use it.(not serialized)
	xfloat32					fDelayTime; //delay time in ms.
	xbool						bFirstExec; //is first execed or not.(not serialized)
	xbool						bTriggerRepeat; //can repeat trigger or not.
	xint32						nAddIndex; //now is not used.(not serialized)
};

enum TriggerState
{
	Triger_None = 0,
	Triger_Overlap_Begin = 1 << 0, //Overlap_Begin
	Trigger_Overlap_Stay = 1 << 1, //Overlap_Stay
	Trigger_Overlap_End = 1 << 2, //Overlap_End
};
enum TriggerOverlapCheckType
{
	TriggerOverlapCheck_AABB, //aabb intersect or not
	TriggerOverlapCheck_Pos, //move actor pos is in Trigger actor aabb or not.
};

#endif
