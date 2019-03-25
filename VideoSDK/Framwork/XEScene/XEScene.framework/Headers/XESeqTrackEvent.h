/******************************************************************************

@File         XESeqTrackEvent.h

@Version       1.0

@Created      2018,12, 29

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_TRACK_EVENT_H
#define XE_SEQ_TRACK_EVENT_H
#include "XETrackVirtual.h"
#include "XETrackVariant.h"

class XESeqTrackEvent 
	:public XETrackVirtual<XETrackVariant>
{
	friend class XESeqBindingEventInstance;
public:
	XESeqTrackEvent();
	virtual ~XESeqTrackEvent();
public:
	virtual void                 Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*          Serialize(XMLElement* pEleParent) override;
	X_FORCEINLINE xbool          IsEventTickable()const{ return m_bEventTickable; }
	X_FORCEINLINE void           SetEventTickable(xbool bEnable){ m_bEventTickable = bEnable; }
public:
	XE_USER_NODE_CAST(XESeqTrackEvent)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	xbool                        m_bEventTickable;
};

#endif // XE_SEQ_TRACK_EVENT_H
