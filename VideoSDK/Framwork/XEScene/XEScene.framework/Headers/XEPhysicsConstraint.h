/******************************************************************************

@File         XEPhysicsConstraint.h

@Version       1.0

@Created      2018,8, 29

@HISTORY:

******************************************************************************/

#ifndef XE_PHYSICS_CONSTRAINT_H
#define XE_PHYSICS_CONSTRAINT_H

#include "XEUserNode.h"
class XEPhysicsSkeletalBody;
class IXConstraint;

class XEPhysicsConstraint : public XEUserNode
{
public:
											XEPhysicsConstraint();
	virtual								    ~XEPhysicsConstraint();
	const xchar*							GetBone1Name();//bone name
	const xchar*							GetBone2Name();//bone name
	virtual void							Release() override;
	void								    SetXPhysicsConstraint(IXConstraint* pConstraint){ m_pPhyConstraint = pConstraint; }
	IXConstraint*						    GetXPhysicsConstraint(){ return m_pPhyConstraint; }
	void									SetSkeletalBodyName(XString strAttachBodyName,XString strOtherBodyName);
	XString									GetAttachSkeletalBodyName(){ return m_strAttachSkeletalBodyNodeName; }
	XString									GetAttachOtherSkeletalBodyName(){ return m_strAttachOtherSkeletalBodyNodeName; }
public:
	XE_USER_NODE_CAST(XEPhysicsConstraint)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

private:
	IXConstraint*							m_pPhyConstraint;
	XString									m_strAttachSkeletalBodyNodeName;//当前约束节点所属的父body节点
	XString									m_strAttachOtherSkeletalBodyNodeName;//当前约束关联的另一个body节点
};

#endif