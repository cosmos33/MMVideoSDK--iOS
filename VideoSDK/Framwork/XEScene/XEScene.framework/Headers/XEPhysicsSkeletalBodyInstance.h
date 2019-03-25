/******************************************************************************

@File         XEPhysicsSkeletalBodyInstance.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_PHYSICS_SKELETAL_BODY_INSTANCE_H
#define XE_PHYSICS_SKELETAL_BODY_INSTANCE_H

#include "XEUserNode.h"

class XEPhysicsSkeletalBody;
class XEPhysicsConstraintInstance;
class IXSkeletalBody;

class XEPhysicsSkeletalBodyInstance
	: public XEUserNodeInstance
{
public:
	XEPhysicsSkeletalBodyInstance(XEPhysicsSkeletalBody* pPhysicsBody);
	virtual                               ~XEPhysicsSkeletalBodyInstance();
public:
#if X_PLATFORM_WIN_DESKTOP			       
	virtual XEPropertyObjectSet            GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif								       
	XEPhysicsSkeletalBody*                 GetPhysicsBodyTemplate();
	IXSkeletalBody*						   GetIXPhysicsBody();
	void								   ReCreateSkeletalPhysicsInstance();
	void								   RemoveConstraintInstance(XEUserNodeInstance* pConstraintIns);
	virtual void                           Render(XEViewport* pViewport) override;
	void								   SetSelected(xbool bSelected){ m_bIsSelected = bSelected; }
	xbool								   IsSelected(){ return m_bIsSelected; }
public:
	XE_USER_NODE_CAST(XEPhysicsSkeletalBodyInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	xbool								   m_bIsSelected;
	XCOLORBASE							   m_clrBodyColor;
};

#endif // XE_PHYSICS_SKELETAL_BODY_INSTANCE_H
