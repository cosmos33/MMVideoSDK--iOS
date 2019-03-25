/******************************************************************************

@File         XEAnimSocketMounterInstance.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef _XE_ANIM_SOCKET_MOUNTER_INS_H
#define _XE_ANIM_SOCKET_MOUNTER_INS_H
#include "XEUserNode.h"

class XEModelComponent;
class XEAnimMonController;
class XEMovementAttacher;
class XEViewport;
class XEBindSocketInstance;
class XESocketListenerUserNodeIns;
class XEActorComponent;
class XEAnimSocketMounter;
class XEBindSocket;

//for previewing only.
class XEAnimSocketMounterInstance 
	: public XEUserNodeInstance
{
public:
	XEAnimSocketMounterInstance(XEAnimSocketMounter* pNodeTl);
	virtual ~XEAnimSocketMounterInstance();
public:
	virtual void                                  Tick(xfloat32 fInterval)override;
	virtual void                                  Render(XEViewport* pViewport)override;
	virtual void                                  Release() override;
	virtual void                                  Apply() override;
	virtual Manager*                              GetNodeManager() override { return m_pNodeManager; }

#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet                   GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy)override;
#endif

public:
	xbool                                         AcceptSkinModel(XEModelComponent* pComponentFromWorld);
	void                                          BindXESocketsIns();//bind sockets instance according to the template node.
	void                                          UnbindXESocketsIns();
	void                                          GetBindXESocketIns(XArray<XEBindSocketInstance*>& arrSokcetIns)const;
	XEBindSocketInstance*                         GetFirstSocketInsWithAnyListener();//return the first socket that owning any listener(s)
	XEAnimSocketMounter*                          GetSocketMounterTemplate();
	X_EES_LINE const XEAnimSocketMounter*         GetSocketMounterTemplate() const;

	X_FORCEINLINE XEModelComponent*               GetSkinModelComponent(){ return m_pSkinModelTarget; }
	X_FORCEINLINE XEMovementAttacher*             GetMovementAttacher(){ return m_pMovementAttacher; }
public:
	XE_USER_NODE_CAST(XEAnimSocketMounterInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	XEMovementAttacher*                           m_pMovementAttacher;
	XEModelComponent*                             m_pSkinModelTarget;//may have nothing.
	XETreeNode::Manager*                          m_pNodeManager;//node manager.
};

#endif // _XE_ANIM_SOCKET_MOUNTER_INS_H
