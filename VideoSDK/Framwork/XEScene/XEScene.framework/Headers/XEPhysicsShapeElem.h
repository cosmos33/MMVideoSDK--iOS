/******************************************************************************

@File         XEPhysicsShapeElem.h

@Version       1.0

@Created      2018,8, 29

@HISTORY:

******************************************************************************/

#ifndef XE_PHYSICS_SHAPE_ELEME_H
#define XE_PHYSICS_SHAPE_ELEME_H

#include "XEUserNode.h"
#include "IXSkeletalBody.h"

class XEPhysicsSkeletalBody;
class XEPhysicsShapeElem : public XEUserNode
{
public:
											XEPhysicsShapeElem();
	virtual								    ~XEPhysicsShapeElem();
	virtual void                            Release() override;
	void									SetXPhyShapeElem(xint32 nIndex, XSphylShapeElem& ele);
	XSphylShapeElem&						GetXPhyShapeElem(){ return m_PhylShapeElem; }
	xint32									GetShapeIndex(){ return m_nShapeIndex; }
	xbool									UpdateBodyShape(xint32 nIndex, XSphylShapeElem& pShapeElem);
	void									SetAttachSkeletalBodyNode(XEPhysicsSkeletalBody* pNode){ m_pAttachSkeletalBodyNode = pNode; }
public:
	XE_USER_NODE_CAST(XEPhysicsShapeElem)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

private:
	XSphylShapeElem							m_PhylShapeElem;
	xint32									m_nShapeIndex;
	XEPhysicsSkeletalBody*					m_pAttachSkeletalBodyNode;
};

#endif