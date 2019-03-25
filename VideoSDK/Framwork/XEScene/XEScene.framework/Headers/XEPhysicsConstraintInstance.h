/******************************************************************************

@File         XEPhysicsConstraintInstance.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_PHYSICS_CONSTRAINT_INSTANCE_H
#define XE_PHYSICS_CONSTRAINT_INSTANCE_H

#include "XEUserNode.h"
#include "IXConstraint.h"

class XEPhysicsConstraint;
class XEPhysicsConstraintInstance
	: public XEUserNodeInstance
{
public:
	XEPhysicsConstraintInstance(XEPhysicsConstraint* pConstraintTemp);
	virtual                               ~XEPhysicsConstraintInstance();
public:
#if X_PLATFORM_WIN_DESKTOP			       
	virtual XEPropertyObjectSet            GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif								       
	XEPhysicsConstraint*				   GetPhysicsConstraintTemplate();
	void								   ReCreateSkeletalPhysicsInstance();
	void								   SetSelected(xbool bSelected){ m_bIsSelected = bSelected; }
	xbool								   IsSelected(){ return m_bIsSelected; }
	virtual void                           Render(XEViewport* pViewport) override;
	xfloat32							   GetConstraintSize(){ return m_fConstraintSize; }
	void								   SetConstraintSize(xfloat32 fSize){ m_fConstraintSize = fSize; }
public:
	XE_USER_NODE_CAST(XEPhysicsConstraintInstance)
		XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
		static const XString  NODE_TYPENAME;
protected:
	xbool								   m_bIsSelected;
	XCOLORBASE							   m_clrConstraintColor;
	xfloat32							   m_fConstraintSize;//not Serilize
};

#endif // XE_PHYSICS_CONSTRAINT_INSTANCE_H
