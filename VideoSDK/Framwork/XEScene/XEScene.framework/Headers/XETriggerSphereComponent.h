/******************************************************************************

@File         XETriggerSphereComponent.h

@Version       1.0

@Created      2018, 12, 20 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_TRIGGER_SPHERE_COMPONENT_H
#define XE_TRIGGER_SPHERE_COMPONENT_H
#include "XEShapeComponent.h"

class XETriggerSphereComponent
	: public XEShapeComponent
{
public:
	XETriggerSphereComponent();
	virtual ~XETriggerSphereComponent();

	//XEActorComponent Interface Begin
	virtual void					Render(XEViewport* pViewport) override;
	virtual void					Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*				Serialize(XMLElement* pEleParent) override;

#if X_PLATFORM_WIN_DESKTOP	  
	virtual void					GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif	
	//XEActorComponent Interface End


	void							SetSphereRadius(xfloat32 fVal);
	X_FORCEINLINE const xfloat32	GetSphereRadius(){ return m_fRadius; }

protected:
	void							UpdateInitAABB();
public:
	XE_COMPONENT_CAST(XETriggerSphereComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XETriggerSphereComponent)
	static const XString COMPONENT_TYPENAME;
protected:
	xfloat32						m_fRadius;
};
#endif //XE_TRIGGER_SPHERE_COMPONENT_H