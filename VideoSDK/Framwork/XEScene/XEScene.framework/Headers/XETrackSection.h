/******************************************************************************

@File         XETrackSection.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_SECTION_H
#define XE_TRACK_SECTION_H
#include "XETrackBase.h"

class XETrackSection :public XETrackBase
{
public:
	XETrackSection();
	virtual ~XETrackSection();
public:
	virtual void         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent)override;
protected:
	xint32               m_nStartTime;
	xint32               m_nEndTime;
public:
	XE_USER_NODE_CAST(XETrackSection)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // XE_TRACK_SECTION_H
