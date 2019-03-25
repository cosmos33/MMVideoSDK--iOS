/******************************************************************************

@File         XEOutlineComponent.cpp

@Version       1.0

@Created      2018, 11, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_OUTLINE_COMPONENT_H_
#define _XE_OUTLINE_COMPONENT_H_

#include "XEAnimatableModelComponent.h"


/*
	用于对模型描边的专用组件

	@notice :
	对模型描边需要两个pass,一个是渲染轮廓线，一个风格化渲染。当前引擎不支持多pass,所以此处需要另一个Component专门用来渲染轮廓线。
	又因为当前引擎不支持在模型实例上,单独修改材质属性（实例skin对应材质修改，会同时影响其他同模板的实例），所以此处创建特定的Component
	来处理这些逻辑。 如果之后不管在引擎层，还是XECore层，支持了材质的单独编辑，或者可以考虑去掉此Component，也或者考虑使用上的方便，而保留此
	Component;
	当前此component的描边，支持骨骼动画的同步处理；
*/
class XEOutlineComponent : public XEAnimatableModelComponent
{
public:
	XE_COMPONENT_CAST(XEOutlineComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEOutlineComponent)
											XEOutlineComponent();
	virtual									~XEOutlineComponent();

	static const XString					COMPONENT_TYPENAME;
	virtual void							Initialize(XEActor* pWorld) override;
	virtual void							Release() override;
	virtual XMLElement*						Serialize(XMLElement* pEleParent) override;
	virtual void							Deserialize(const XMLElement* pEleComponent) override;
	virtual void							Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void							Render(XEViewport* pViewport) override;

	xbool									UpdateOutline();
	void									SetOutlineWidth(xfloat32 fLineWidth, xbool bApplyToMtl = xtrue);
	xfloat32								GetOutlineWidth() const { return m_fOutlineWidth; }
	void									SetOutlineColor(const XCOLORBASE &color, xbool bApplyToMtl = xtrue);
	const XCOLORBASE&						GetOutlineColor() const { return m_clrOutline; }

protected:

	virtual xbool                           LoadAsset(const xchar* pPath) override { return xfalse; }

#if X_PLATFORM_WIN_DESKTOP
	virtual void                            GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif

	xbool									GenerateOutlineModel();
	xbool									ReleaseOutlineModel();
	void									SynOutlineToRootModel();
	void									SynchBoneToRootModel(const IXModelInstance *pRootModelIns, const XSkinData::XRenderMesh *pOriginRenderMesh,
																const IXModelInstance *pOutlineModelIns, XSkinData::XRenderMesh *pOutlineRenderMesh);
	void									SynchMorphToRootModel();


	XModel*									EmbedRootModel(XModel *pSourceModel);
	//XSkin*									EmbedSkin(XSkin *pSourceSkin, xbool bSetMaterail = xtrue);
	void									SynParamToMaterialIns();


	xbool									m_bGenerated;
	xfloat32								m_fOutlineWidth;
	XCOLORBASE								m_clrOutline;
};

#endif

