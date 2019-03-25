/******************************************************************************

@File         XESeqBindingActor.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_BINDING_ACTOR_H
#define XE_SEQ_BINDING_ACTOR_H
#include "XESeqBindingTransform.h"

class XESeqBindingActor 
	:public XESeqBindingTransform
{
	friend class XESeqBindingActorInstance;
public:
	XESeqBindingActor();
	virtual ~XESeqBindingActor();
public:
	virtual void                 Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*          Serialize(XMLElement* pEleParent) override;
	virtual XETrackBase*         SetupComponentTrack(XETreeNode::Manager* pNodeMgr);
	X_FORCEINLINE const XString& GetBindActorName()const{ return m_strBindActorName; }
	X_FORCEINLINE void           SetBindActorName(const XString& strName){ m_strBindActorName = strName; }
	X_FORCEINLINE const XString& GetBindAssetPath(){ return m_strBindAssetPath; }
	X_FORCEINLINE void           SetBindAssetPath(const XString& strAssetPath){ m_strBindAssetPath = strAssetPath; }
public:
	XE_USER_NODE_CAST(XESeqBindingActor)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	XString              m_strBindActorName;
	XString				 m_strBindAssetPath;
};

#endif // XE_SEQ_BINDING_ACTOR_H
