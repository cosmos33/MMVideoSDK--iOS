/******************************************************************************

@File         XESeqBindingActorCameraInstance.h

@Version       1.0

@Created      2018,3, 28

@HISTORY:

******************************************************************************/
#ifndef _XE_SEQ_BINDING_ACTOR_CAMERA_INSTANCE_H
#define _XE_SEQ_BINDING_ACTOR_CAMERA_INSTANCE_H
#include "XESeqBindingActorInstance.h"
class XESeqBindingActorCamera;
class XESeqBindingActorCameraInstance 
	:public XESeqBindingActorInstance
{
public:
	XESeqBindingActorCameraInstance(XESeqBindingActorCamera* pNodeTl);
	virtual ~XESeqBindingActorCameraInstance();
public:
	virtual void             SetTime(xint32 nMicrosecond) override;//in microsecond.
	virtual xbool            AcceptActor(XEActor* pActor) override;
	XESeqBindingActorCamera* GetSeqBindingActorCameraTemplate();
public:
	X_FORCEINLINE void       SetActive(xbool bActive){ m_bActive = bActive; }
public:
	XE_USER_NODE_CAST(XESeqBindingActorCameraInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	xbool  m_bActive;//Whether active or not.
};

#endif // _XE_SEQ_BINDING_ACTOR_CAMERA_INSTANCE_H
