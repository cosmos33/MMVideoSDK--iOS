/******************************************************************************

@File         XEAnimMonNotify.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_MON_NOTIFY_PLAY_CONTROL_H
#define XE_ANIM_MON_NOTIFY_PLAY_CONTROL_H
#include "XEAnimMonNotify.h"
class XEAnimMonNotifyPlayControl
	:public XEAnimMonNotify
{
public:
	XEAnimMonNotifyPlayControl();
	virtual ~XEAnimMonNotifyPlayControl();
public:
	XE_USER_NODE_CAST(XEAnimMonNotifyPlayControl)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_ANIM_MON_NOTIFY_PLAY_CONTROL_H
