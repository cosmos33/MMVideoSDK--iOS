/******************************************************************************

@File         XEAnimMonElementInstance.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef _XE_ANIM_MON_ELEMENT_INSTANCE_H
#define _XE_ANIM_MON_ELEMENT_INSTANCE_H
#include "XEAnimMonBaseInstance.h"

//in microseconds.
class XEPropertyObjectProxy;
class XEAnimMonElement;
class XEAnimMontageInstance;

class XEAnimMonElementInstance 
	:public XEAnimMonBaseInstance
{
public:
	XEAnimMonElementInstance(XEAnimMonElement* pNodeTl);
	virtual ~XEAnimMonElementInstance();
public:
	XE_USER_NODE_CAST(XEAnimMonElementInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
public:
	XEAnimMontageInstance*            GetAnimMontageInstance();
	XEAnimMonElement*                 GetAnimMonElementTemplate();
	virtual xint32                    GetActualDuration(){ return 0; }

#if X_PLATFORM_WIN_DESKTOP
	XEPropertyObjectSet GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
};

#endif // _XE_ANIM_MON_ELEMENT_INSTANCE_H
