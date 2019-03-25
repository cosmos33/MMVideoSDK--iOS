/******************************************************************************

@File         XESeqBindingActorCamera.h

@Version       1.0

@Created      2018,3, 28

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_BINDING_ACTOR_CAMERA_H
#define XE_SEQ_BINDING_ACTOR_CAMERA_H
#include "XESeqBindingActor.h"
class XEActor;
class XESeqBindingActorCamera :public XESeqBindingActor
{
public:
	XESeqBindingActorCamera();
	virtual ~XESeqBindingActorCamera();
public:
	virtual void         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*  Serialize(XMLElement* pEleParent) override;
	virtual XETrackBase* SetupComponentTrack(XETreeNode::Manager* pNodeMgr) override;
	X_FORCEINLINE void   SetActive(xbool bActive){ m_bActive = bActive; }
public:
	XE_USER_NODE_CAST(XESeqBindingActorCamera)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	xbool  m_bActive;//in runtime mode. don't need to serialize/deserialize.
};

#endif // XE_SEQ_BINDING_ACTOR_CAMERA_H
