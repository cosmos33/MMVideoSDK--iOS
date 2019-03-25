/******************************************************************************

@File         XEAnimMonNotifyCloth.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_MON_NOTIFY_CLOTH_H
#define XE_ANIM_MON_NOTIFY_CLOTH_H
#include "XEAnimMonNotify.h"
class XEAnimMonNotifyCloth
	:public XEAnimMonNotify
{
public:
	XEAnimMonNotifyCloth();
	virtual ~XEAnimMonNotifyCloth();
public:
	XE_USER_NODE_CAST(XEAnimMonNotifyCloth)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_ANIM_MON_NOTIFY_CLOTH_H
