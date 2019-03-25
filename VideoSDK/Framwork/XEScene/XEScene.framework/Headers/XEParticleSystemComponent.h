/******************************************************************************

@File         XEParticleSystemComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEPARTICLESYSTEMCOMPONENT_H
#define XEPARTICLESYSTEMCOMPONENT_H
#include "XEPrimitiveComponent.h"
#include "FxInstance.h"
#include "XEUtility.h"

class XEParticleSystemComponent :public XEPrimitiveComponent
{
public:
	XEParticleSystemComponent();
	~XEParticleSystemComponent(){}
public:
	virtual xbool                       LoadAsset(const xchar* pPath);
	virtual void                        Empty() override;
	virtual void                        Release() override;
	virtual void                        Render(XEViewport* pViewport) override;
	virtual void                        Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void                        Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*                 Serialize(XMLElement* pEleParent) override;
#if X_PLATFORM_WIN_DESKTOP
	virtual void                        GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
	virtual bool                        ExportAsset(const xchar* pProjectDir, const xchar* pExportPath, XArray<XEVector2s>& assetArray);
#endif
public:						     
	X_FORCEINLINE IFxInstance*			GetFxInstance(){ return m_pFxIns; }
	X_EES_LINE X_FORCEINLINE const IFxInstance*	GetFxInstance() const { return m_pFxIns; }
	X_FORCEINLINE const XString&		GetAssetPath() const { return m_szAssetPath; }
	xbool                               RestartParticleSystem() const;
	xbool                               Create();
	void                                SetTimeRadio(float fRadio){ m_fRadio = fRadio; };
protected:
	// Override this method for custom behavior.
	virtual xbool                       MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual XMATRIX4                    GetRawWorldTransformImpl() const override;
	virtual xbool                       ApplyWorldTransformImpl(const XMATRIX4& mat) override;
public:
	XE_COMPONENT_CAST(XEParticleSystemComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEParticleSystemComponent)
	static const XString COMPONENT_TYPENAME;
protected:
	IFxInstance*                        m_pFxIns;
	XString                             m_szAssetPath;

	float                               m_fRadio;
};

#endif // XEPARTICLESYSTEMCOMPONENT_H
