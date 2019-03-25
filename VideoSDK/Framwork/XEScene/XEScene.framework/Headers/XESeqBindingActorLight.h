#ifndef XE_SEQ_BINDING_ACTOR_POINTLIGHT_H
#define XE_SEQ_BINDING_ACTOR_POINTLIGHT_H
#include "XESeqBindingActor.h"
class XEActor;
class XESeqBindingActorLight :public XESeqBindingActor
{
public:
	XESeqBindingActorLight();
	virtual ~XESeqBindingActorLight();
public:
	virtual void                 Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*          Serialize(XMLElement* pEleParent) override;
	virtual XETrackBase*         SetupComponentTrack(XETreeNode::Manager* pNodeMgr,const XString& ActorType);
	virtual XETrackBase*         SetupColorTrack(XETreeNode::Manager* pNodeMgr, XETrackBase* pBase);
	X_FORCEINLINE void           SetActive(xbool bActive){ m_bActive = bActive; }
	X_FORCEINLINE const XString& GetActorType()const{ return m_strActorType; }
public:
	XE_USER_NODE_CAST(XESeqBindingActorLight)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	xbool  m_bActive;//in runtime mode. don't need to serialize/deserialize.
	XString m_strActorType;
};
#endif