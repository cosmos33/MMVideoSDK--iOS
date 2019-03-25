/******************************************************************************

@File         XESocketListenerUserNodeIns.h

@Version       1.0

@Created      2018, 2, 6

@HISTORY:

******************************************************************************/
#ifndef _XE_SOCKET_LISTENER_USER_NODE_H
#define _XE_SOCKET_LISTENER_USER_NODE_H
#include "XESocketListenerBase.h"

//for instance only.
//in runtime.
class XEUserNodeInstance;
class XESocketListenerUserNodeIns 
	:public XESocketListenerBase
{
public:
	XESocketListenerUserNodeIns();
	virtual ~XESocketListenerUserNodeIns();
public:
	virtual const XString       GetTypeName() const override;
	virtual void                OnSocketUpdate(const XMATRIX4& matWorld) override;
	virtual const XString       GetName() const override;
public:
	X_FORCEINLINE void          AcceptUserNodeIns(XEUserNodeInstance* pUserNodeIns){ m_pBindUserNodeIns = pUserNodeIns; }
protected:
	XEUserNodeInstance*         m_pBindUserNodeIns;
};

#endif // _XE_SOCKET_LISTENER_USER_NODE_H
