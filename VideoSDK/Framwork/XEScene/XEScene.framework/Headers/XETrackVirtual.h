/******************************************************************************

@File         XETrackVirtual.h

@Version       1.0  Some tracks that with implicit features, usually are the tracks that don't need to be displayed, or unique in the global.

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_VIRTUAL_H
#define XE_TRACK_VIRTUAL_H
#include "XETrackBase.h"

template<typename T>//T is a track class
class XETrackVirtual : public T
{
public:
	XETrackVirtual(){}
	virtual ~XETrackVirtual(){}
public:
	virtual void            Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*     Serialize(XMLElement* pEleParent) override;
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

template<typename T>
const XString XETrackVirtual<T>::NODE_TYPENAME = "TrackBase.Virtual";//do not use.

template<typename T>
void XETrackVirtual<T>::Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr /*= NULL*/)
{
	T::Deserialize(pEleParent, pNodeMgr);
}

template<typename T>
XMLElement* XETrackVirtual<T>::Serialize(XMLElement* pEleParent)
{
	XMLElement* pEleNode = T::Serialize(pEleParent);
	return pEleNode;
}

#endif // XE_TRACK_VIRTUAL_H
