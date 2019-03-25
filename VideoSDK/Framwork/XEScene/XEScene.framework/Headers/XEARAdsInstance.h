/******************************************************************************

@File         XEARAdsInstance.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef _XE_ARADS_INSTANCE_H
#define _XE_ARADS_INSTANCE_H

#include "XEARAdsBase.h"

class XEARAds;
class XEARAdsBinding;
class XEARAdsAnimController;
class XETrackBase;
class XEActor;
class XEWorld;

class XEARAdsInstance
	:public XEARAdsBaseInstance
{
public:
	XEARAdsInstance(XEARAds* pNodeTl);
	virtual ~XEARAdsInstance();
public:
	virtual void                         Tick(xfloat32 fInterval) override;
	virtual void                         Release() override;
	virtual void                         Apply() override;
	virtual Manager*                     GetNodeManager() override{ return m_pNodeManager; }
	XEARAds*                             GetARAdsTemplate();
	void                                 AcceptWorld(XEWorld* pWorld);//set to node manager
	XEWorld*                             GetWorld();//comes from node manager
public:
	X_EES_LINE X_FORCEINLINE const Manager* GetNodeManager() const{ return m_pNodeManager; }
	X_FORCEINLINE XEARAdsAnimController* GetARAdsAnimController(){ return m_pARAdsAnimController; }

public:
	void								 GetBindNodeIns(XETreeNode::NodeList& nl);
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
private:
	XETreeNode::Manager*               m_pNodeManager;//node manager.
	XEARAdsAnimController*             m_pARAdsAnimController;
};

#endif // _XE_ARADS_INSTANCE_H
