/******************************************************************************

@File         XECanvas3DTextureComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XECANVAS3DTEXTURECOMPONENT_H
#define XECANVAS3DTEXTURECOMPONENT_H
#include "XEActorComponent.h"
#include "XTexture.h"

class XECanvas3DTextureComponent:public XEActorComponent
{
public:
	XECanvas3DTextureComponent();
	~XECanvas3DTextureComponent(){};
public:
	virtual void                 Release() override;
	virtual xbool                LoadAsset(const xchar* pTexPath);
	virtual void                 Render(XEViewport* pViewport) override;
	virtual void                 Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*          Serialize(XMLElement* pEleParent) override;
public:
	XE_COMPONENT_CAST(XECanvas3DTextureComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XECanvas3DTextureComponent)
	static const XString         COMPONENT_TYPENAME;
public:
	XVECTOR3*                    m_pShapeVertsp;
	XCOLORBASE*                  m_pColors;
	XVECTOR2*                    m_pTexcoord;
	xint32                       m_iVertNum;

	xint32*                      m_pIndices;
	xint32                       m_iIndexNum;

	IXTexture*                   m_pTex;
	xbool                        m_bZEnable;
	XString                      m_szAssetPath;
	XVECTOR3*                    m_pVertLocation;
};

#endif // XECANVAS3DTEXTURECOMPONENT_H
