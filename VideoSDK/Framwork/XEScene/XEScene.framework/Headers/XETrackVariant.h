/******************************************************************************

@File         XETrackVariant.h

@Version       1.0 

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_VARIANT_H
#define XE_TRACK_VARIANT_H

//could be any datas.
#include "XETrackBase.h"
class XETrackVariant 
	: public XETrackBase
{
public:
	XETrackVariant();
	virtual ~XETrackVariant();
public:
	virtual void            Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*     Serialize(XMLElement* pEleParent)override;
	virtual xbool           GetOutValueForInVal(xint32 nMicrosecond, void* pOutVal) override;
	virtual XEKeyframeBase* GetOutKeyframeForInVal(xint32 nMicrosecond) override;
public:
	XE_USER_NODE_CAST(XETrackVariant)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_TRACK_VARIANT_H
