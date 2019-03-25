/******************************************************************************

@File         XEEventUtil.h

@Version       1.0

@Created      2018, 12, 19 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_EVENT_UTIL_H
#define XE_EVENT_UTIL_H

#include "XString.h"
#include "XTypes.h"
#include "XArray.h"

namespace XEEventUtil
{
	enum XEEventType
	{
		EVENT_NONE = -1,
		ACTOR_MOVE_EVENT = 0,
		ACTOR_VISIBLE_EVENT,
		PLAY_ANIMATION_EVENT,
		SPAWN_PARTICLE_SYSTEM_EVENT,
		LUA_SCRIPT_EVENT,
		//VARIANT_DATA_EVENT,
		EVENTTYPE_NUM,
	};

	const XString&				GetEventTypeNameByType(XEEventType eType);
	XEEventType					GetEventTypeByName(const XString &str);
	const XArray<XString>&		GetAllEventType();

	void						GetTrimEventTypeName(XString& strEventName);
}

#endif //XE_EVENT_UTIL_H
