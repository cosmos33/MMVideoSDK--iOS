/******************************************************************************

@File         XETriggerBoxComponent.h

@Version       1.0

@Created      2018, 12, 20 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_TRIGGER_BOX_COMPONENT_H
#define XE_TRIGGER_BOX_COMPONENT_H
#include "XEShapeComponent.h"

class XETriggerBoxComponent
	: public XEShapeComponent
{
public:
	XETriggerBoxComponent();
	virtual ~XETriggerBoxComponent();

	//XEActorComponent Interface Begin
	virtual void					Render(XEViewport* pViewport) override;
	virtual void					Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*				Serialize(XMLElement* pEleParent) override;	

#if X_PLATFORM_WIN_DESKTOP	  
	virtual void					GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif	
	//XEActorComponent Interface End

	void							SetBoxExtent(const XVECTOR3& vExt);
	X_FORCEINLINE const XVECTOR3&	GetBoxExent(){ return m_vBoxExtents; }

protected:
	void							UpdateInitAABB();
public:
	XE_COMPONENT_CAST(XETriggerBoxComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XETriggerBoxComponent)
	static const XString COMPONENT_TYPENAME;

protected:
	XVECTOR3					m_vBoxExtents;
	
};
#endif //XE_TRIGGER_BOX_COMPONENT_H