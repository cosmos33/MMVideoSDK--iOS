/******************************************************************************

@File         XEAnimMonBase.h

@Version       1.0

@Created      2017,12, 27

@HISTORY:

******************************************************************************/
#ifndef _XE_ANIM_MON_BASE_H
#define _XE_ANIM_MON_BASE_H

#include "XEFactoryUserNodeUtil.h"

class XEAnimMonController;
class XEAnimMontage;

class XEAnimMonBase 
	: public XEUserNode
{
public:
	XEAnimMonBase(){}
	virtual ~XEAnimMonBase(){}
	typedef XArray<XEAnimMonBase*>      AnimMonBaseList;
public:
	virtual xbool                       Verify(AnimMonBaseList* pUnsuggestedList = NULL);
	XEAnimMontage*                      GetAnimMontage();
	X_EES_LINE const XEAnimMontage*     GetAnimMontage() const;
public:
	XE_USER_NODE_CAST(XEAnimMonBase)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_ANIM_MON_BASE_H
