/******************************************************************************

@File         XEPhysicsShapeElemInstance.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_PHYSICS_SHAPE_ELEM_INSTANCE_H
#define XE_PHYSICS_SHAPE_ELEM_INSTANCE_H

#include "XEUserNode.h"
#include "IXSkeletalBody.h"

class XEPhysicsShapeElem;
class XEPhysicsSkeletalRootInstance;
class XEPhysicsShapeElemInstance
	: public XEUserNodeInstance
{
public:
	XEPhysicsShapeElemInstance(XEPhysicsShapeElem* pShapeElem);
	virtual                               ~XEPhysicsShapeElemInstance();
public:
#if X_PLATFORM_WIN_DESKTOP			       
	virtual XEPropertyObjectSet				GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif								       
	XEPhysicsShapeElem*						GetPhysicsShapeElemTemplate();
	XSphylShapeElem&						GetXPhysicsShapeElem();
	xint32									GetXPhysicsShapeElemIndex();
	xbool									UpdateBodyShape(xint32 nIndex, XSphylShapeElem& pShapeElem);
	virtual void                            Render(XEViewport* pViewport) override;

public:
	XE_USER_NODE_CAST(XEPhysicsShapeElemInstance)
		XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
		static const XString  NODE_TYPENAME;

private:
	XSphylShapeElem							m_SphylShapeElem;
};

#endif // XE_PHYSICS_SHAPE_ELEM_INSTANCE_H
