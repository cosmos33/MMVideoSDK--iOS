/******************************************************************************

@File         XELightComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XELIGHTCOMPONENT_H
#define XELIGHTCOMPONENT_H
#include "XEPrimitiveComponent.h"
#include "XLightBase.h"
class XELightComponent 
	:public XEPrimitiveComponent
{
public:
	XELightComponent();
	~XELightComponent();
public:
	virtual void               Release() override;
	virtual void               Render(XEViewport* pViewport) override;
	virtual void               Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*        Serialize(XMLElement* pEleParent) override;
#if X_PLATFORM_WIN_DESKTOP
	virtual void               GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif
public:
	void                       SetAsDirLight(const XCOLORBASE& color, const XVECTOR3& vDir, const xfloat32 fLuminance);	
	void                       SetAsEnvLight(const XCOLORBASE& color, const xuint32 index, const xfloat32 fLuminance);
	void                       SetAsPointLight(const XPointLightDesc&desc);
	void                       SetAsSpotLight(const XSpotLightDesc&desc);
	void          			   SetLightRadius(xfloat32 fRadius);
	void					   SetLightFallOffExponent(xfloat32 fFallOffExponent);
	void					   SetLightConeInnerAngle(xfloat32 fAngle);
	void					   SetLightConeOuterAngle(xfloat32 fAngle);
	//void					   
	XVECTOR3				   GetDirLightDir() const;
	XCOLORBASE				   GetLightColor() const;
	xbool                      SetLightColor(const XCOLORBASE& color );
	xfloat32                   GetLightLuminance() const;
	xbool                      SetLightLuminance(const xfloat32 fLuminance);

public:
	X_FORCEINLINE IXLightBase* GetLight(){ return m_pLight; }
	X_FORCEINLINE IXLightBase* GetLight()const{ return m_pLight; }
	X_FORCEINLINE xuint32      GetLightIndex(){ return m_uLightIndex; }
protected:
	// Override this method for custom behavior.
	virtual xbool              MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual xbool              ApplyWorldTransformImpl(const XMATRIX4& mat) override;

public:
	XE_COMPONENT_CAST(XELightComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XELightComponent)
	static const XString COMPONENT_TYPENAME;
private:
	IXLightBase*               m_pLight;
	xuint32                    m_uLightIndex;
};

#endif // XELIGHTCOMPONENT_H
