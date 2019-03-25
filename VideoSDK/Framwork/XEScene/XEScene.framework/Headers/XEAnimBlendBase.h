/******************************************************************************

@File         XEAnimBlendBase.h

@Version       1.0

@Created      2018,9, 27

@HISTORY:

******************************************************************************/
#ifndef _XE_ANIM_BLEND_ELE_BASE_H
#define _XE_ANIM_BLEND_ELE_BASE_H

#include "XEFactoryUserNodeUtil.h"

class XEAnimMonController;
class XEAnimBlend;

class XEAnimBlendBase
	: public XEUserNode
{
public:
	XEAnimBlendBase(){}
	virtual ~XEAnimBlendBase(){}
	typedef XArray<XEAnimBlendBase*>      AnimBlendBaseList;
public:
	virtual xbool                       Verify(AnimBlendBaseList* pUnsuggestedList = NULL);
	XEAnimBlend*                        GetAnimBlend();
	X_EES_LINE const XEAnimBlend*       GetAnimBlend() const;
public:
	XE_USER_NODE_CAST(XEAnimBlendBase)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_ANIM_BLEND_ELE_BASE_H
