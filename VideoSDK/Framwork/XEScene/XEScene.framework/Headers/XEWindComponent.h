/******************************************************************************

@File         XEWindComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEWIND_COMPONENT_H
#define XEWIND_COMPONENT_H
#include "XEPrimitiveComponent.h"
#include "XLightBase.h"
class XEWindComponent 
	:public XEActorComponent
{
public:
	XEWindComponent();
	~XEWindComponent();
public:
	virtual void               Release() override;
	virtual void               Render(XEViewport* pViewport) override;
	virtual void               Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*        Serialize(XMLElement* pEleParent) override;
#if X_PLATFORM_WIN_DESKTOP	  
	virtual void               GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif						  
public:
	XCOLORBASE				   GetWindColor() const;
	xbool                      SetWindColor(const XCOLORBASE& color);
	void					   SetWindSpeed(const xfloat32& fSpeed);
	xfloat32				   GetWindSpeed();
private:
	void					   SetWindDir(const XVECTOR3& vWindDir);
	XVECTOR3				   GetWindDir();
protected:
	// Override this method for custom behavior.
	virtual xbool              MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual xbool              ApplyWorldTransformImpl(const XMATRIX4& mat) override;
public:
	XE_COMPONENT_CAST(XEWindComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEWindComponent)
	static const XString COMPONENT_TYPENAME;
private:
	XCOLORBASE				   m_pColor;
	XVECTOR3				   m_vWindRotate;
	XVECTOR3				   m_vOriginDir;
};

#endif // XEWIND_COMPONENT_H