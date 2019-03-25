/******************************************************************************

@File         XEAnimBlendLayerTrack.h

@Version       1.0

@Created      2018,9, 27

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_BLEND_LAYER_TRACK_H
#define XE_ANIM_BLEND_LAYER_TRACK_H
#include "XEAnimBlendBase.h"
class XEAnimBlendLayerTrack :public XEAnimBlendBase
{
	friend class XEAnimBlendLayerTrackInstance;
public:	
	XEAnimBlendLayerTrack();
	virtual ~XEAnimBlendLayerTrack();
public:
	virtual void         Deserialize(const XMLElement* pEleMontage, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent) override;
	virtual xbool        Verify(AnimBlendBaseList* pUnsuggestedList = NULL) override;
public:
	XE_USER_NODE_CAST(XEAnimBlendLayerTrack)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	XString m_strBlendLayerName;

};

#endif // XE_ANIM_BLEND_LAYER_TRACK_H
