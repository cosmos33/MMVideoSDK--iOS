
#ifndef _XE_SEQ_BINDING_ACTOR_LIGHT_INSTANCE_H
#define _XE_SEQ_BINDING_ACTOR_LIGHT_INSTANCE_H
#include "XESeqBindingActorInstance.h"
class XESeqBindingActorLight;
class IXLightBase;

class XESeqBindingActorLightInstance
	:public XESeqBindingActorInstance
{
public:
	XESeqBindingActorLightInstance(XESeqBindingActorLight* pNodeTl);
	virtual ~XESeqBindingActorLightInstance();
public:
	virtual void             SetTime(xint32 nMicrosecond) override;//in microsecond.
	virtual xbool            AcceptActor(XEActor* pActor) override;
	XESeqBindingActorLight* GetSeqBindingActorCameraTemplate();
public:
	X_FORCEINLINE void       SetActive(xbool bActive){ m_bActive = bActive; }
public:
	XE_USER_NODE_CAST(XESeqBindingActorLightInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	xbool  m_bActive;//Whether active or not.
private:
	void				SetColorParam(xint32 nMicrosecond, XEUserNode* Node, IXLightBase* pLight);
};

#endif
