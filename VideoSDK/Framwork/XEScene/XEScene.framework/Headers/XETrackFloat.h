/******************************************************************************

@File         XETrackFloat.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_FLOAT_H
#define XE_TRACK_FLOAT_H
#include "XETrackBase.h"
#include "XCurve.h"

class XETrackFloat 
	: public XETrackBase
{
public:
	XETrackFloat();
	virtual ~XETrackFloat();
public:
	virtual void            Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*     Serialize(XMLElement* pEleParent)override;
	virtual xbool           GetOutValueForInVal(xint32 nMicrosecond, void* pOutVal) override;
	virtual void            SyncSortKeyframes() override;
public:
	FInterpCurve<xfloat32>* GetCurve();
	void*                   GetCurve(xbool);
	xbool                   ReBuildKeyframeFromCurve(XETreeNode::Manager* pNodeMgr);
protected:
	FInterpCurve<xfloat32>* m_pCurve;//only one curve, must be xfloat32.
public:
	XE_USER_NODE_CAST(XETrackFloat)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_TRACK_FLOAT_H
