/******************************************************************************

@File         XESequencerInstance.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef _XE_SEQUENCER_INSTANCE_H
#define _XE_SEQUENCER_INSTANCE_H
#include "XESeqBase.h"

class XESequencer;
class XESeqBinding;
class XETrackBase;
class XESeqAnimController;
class XEActor;
class XEWorld;

class XESequencerInstance 
	:public XESeqBaseInstance
{
public:
	XESequencerInstance(XESequencer* pNodeTl);
	virtual ~XESequencerInstance();
public:
	virtual void                       Tick(xfloat32 fInterval) override;
	virtual void                       Release() override;
	virtual void                       Apply() override;
	virtual Manager*                   GetNodeManager() override{ return m_pNodeManager; }
	XESequencer*                       GetSequencerTemplate();
	void                               AcceptWorld(XEWorld* pWorld);// set to node manager
	XEWorld*                           GetWorld();// comes from node manager
	void							   ReleaseAllAnimResources();
public:
	X_EES_LINE X_FORCEINLINE const Manager* GetNodeManager() const{ return m_pNodeManager; }
	X_FORCEINLINE XESeqAnimController* GetSeqAnimController(){ return m_pSeqAnimController; }
public:
	XE_USER_NODE_CAST(XESequencerInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
private:
	XETreeNode::Manager*               m_pNodeManager;//node manager.
	XESeqAnimController*               m_pSeqAnimController;
};

#endif // _XE_SEQUENCER_INSTANCE_H
