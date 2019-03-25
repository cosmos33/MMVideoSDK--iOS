/******************************************************************************

@File         XESocketListenerActor.h

@Version       1.0

@Created      2018, 2, 6

@HISTORY:

******************************************************************************/
#ifndef _XE_SOCKET_LISTENER_ACTOR_H
#define _XE_SOCKET_LISTENER_ACTOR_H
#include "XESocketListenerBase.h"

class XEActor;
class XESocketListenerActor 
	:public XESocketListenerBase
{
public:
	XESocketListenerActor();
	virtual ~XESocketListenerActor();
public:
	virtual const XString       GetTypeName() const override;
	virtual void                OnSocketUpdate(const XMATRIX4& matWorld) override;
public:
	X_FORCEINLINE void          AcceptActor(XEActor* pActor){ m_pBindActor = pActor; }
protected:
	XEActor* m_pBindActor;
};

#endif // _XE_SOCKET_LISTENER_ACTOR_H
