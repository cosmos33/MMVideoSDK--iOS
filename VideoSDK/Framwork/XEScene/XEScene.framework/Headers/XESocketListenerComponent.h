/******************************************************************************

@File         XESocketListenerComponent.h

@Version       1.0

@Created      2018, 2, 6

@HISTORY:

******************************************************************************/
#ifndef _XE_SOCKET_LISTENER_COMPONENT_H
#define _XE_SOCKET_LISTENER_COMPONENT_H
#include "XESocketListenerBase.h"

class XEActorComponent;
class XESocketListenerComponent 
	:public XESocketListenerBase
{
public:
	XESocketListenerComponent();
	virtual ~XESocketListenerComponent();
public:
	virtual const XString            GetTypeName() const override;
	virtual void                     OnSocketUpdate(const XMATRIX4& matWorld) override;
	X_FORCEINLINE void               AcceptComponent(XEActorComponent* pComponent){ m_pComponent = pComponent; }
	X_FORCEINLINE XEActorComponent*  GetComponent(){ return m_pComponent; }
protected:
	XEActorComponent* m_pComponent;
};

#endif // _XE_SOCKET_LISTENER_COMPONENT_H
