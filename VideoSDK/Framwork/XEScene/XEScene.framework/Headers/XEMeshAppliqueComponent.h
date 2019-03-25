/******************************************************************************

@File         XEMeshAppliqueComponent.h

@Version       1.0

@Created      2018, 10, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/


#ifndef _XE_MESH_APPLIQUE_COMPONENT_H_
#define _XE_MESH_APPLIQUE_COMPONENT_H_

#include "XEModelComponent.h"
// #include "XSkin.h"
// #include "XSkinData.h"
#include "XModelInstance.h"


class XEMeshAppliqueComponent : public XEActorComponent
{
public:

	enum XEPasteType
	{
		XE_APLQ_PT_UV = 0,
		XE_APLQ_PT_NUM
	};


	/*
	@param
	strAppliqueModelFile	:	补丁模型路径
	strOriginSkin			:	原模型被补的skin名字 （不是路径）
	strOriginMeshName		:	原模型被补的mesh
	eType					:	补丁方式， XE_APLQ_PT_UV： 通过UV匹配
	vPosToUVOffset			:	位置转UV的偏移，只有在 eType == XE_APLQ_PT_UV时有效
	fUVMatchDevi			:	匹配UV时的误差范围，因为误差，匹配时有可能匹配失败，所以此值最好为最小UV间隔的一半; (只有在 eType == XE_APLQ_PT_UV时有效)；
	fExpansionMesh			:	补丁网格，每个顶点向外位移距离，（理论上补丁网格和原模型会完全贴附，但是可能由于计算误差，
	                            导致由微小的间隙而出现的Z冲突，此值为补救方法。原模型为静态模型时，现状是不需要此值）

	@notice
	1. UV补丁模型制作方式：依照原模型UV展开图，制作同样形状的补丁网格，使补丁网格的顶点的位置值xy，等于原模型顶点的uv值；
	2. 补丁方式，要求补丁模型不可以存在拆分，否则逻辑会过于复杂。
	3. UV补丁方式，对uv精度要求很高，所以尽量不要在UV展开图上出现距离太近顶点；	
	4. 补丁模型的位置，除了按原模型UV展开图对齐外；还要求，三角网格的各边能完全对上；（在顶点一一对应的前提下，可能因为拆分四边形顺序不一样，而导致三角网格线不对应；）
	*/
	struct XEAppliqueInfo
	{
		XString strAppliqueModelFile;
		XString strOriginSkin;
		XString strOriginMeshName;
		XEPasteType eType;
		XVECTOR2 vPosToUVOffset;
		xfloat32 fPosToUVScale;
		xfloat32 fUVMatchDevi;
		xfloat32 fExpansionMesh;
		XEAppliqueInfo() : strAppliqueModelFile(""), strOriginSkin(""), strOriginMeshName(""), eType(XE_APLQ_PT_UV),
			vPosToUVOffset(0.0f), fPosToUVScale(1.0f), fUVMatchDevi(0.005f), fExpansionMesh(0.002f){}
	};



	struct XEMeshAppliqueOperater
	{
		//XSkinData::XRenderMesh *pRefRenderMesh;
		xint32 nRefRenderMeshIndex;
		xint32 nOriginRenderMeshIndex;
		XArray<xint32> vToOriginVertexIndexs;

		XEMeshAppliqueOperater() : /*pRefRenderMesh(NULL), */nRefRenderMeshIndex(-1){}
		void Release();
	};
	struct XEAppliqueOperater
	{
		XEAppliqueInfo inputInfo;
		xint32 nOriginSkinIndex;
		xint32 nOriginRawMeshIndex;

		XEModelComponent *pRefModelComponent;
// 		IXModelInstance *pRefModelIns;
// 		XSkin *pRefSkin;
		XString strRefSkin;
		xint32 nRefSkinIndex;
		XArray<XEMeshAppliqueOperater*> vMeshAppliqueOperaters;

		XEAppliqueOperater() : nOriginSkinIndex(-1), nOriginRawMeshIndex(-1), pRefModelComponent(NULL), strRefSkin(""), /*pRefModelIns(NULL), pRefSkin(NULL),*/ nRefSkinIndex(-1){}
		void Release();
	};

public:
	XE_COMPONENT_CAST(XEMeshAppliqueComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEMeshAppliqueComponent)
											XEMeshAppliqueComponent();
	virtual									~XEMeshAppliqueComponent();

	static const XString					COMPONENT_TYPENAME;
	virtual void							Initialize(XEActor* pWorld) override;
	virtual void							Release() override;
	virtual XMLElement*						Serialize(XMLElement* pEleParent) override;
	virtual void							Deserialize(const XMLElement* pEleComponent) override;
	virtual void							Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void							Render(XEViewport* pViewport) override;


	const XEAppliqueOperater*				PasteMeshApplique(const XEAppliqueInfo &info);
	xbool									RemoveMeshApplique(const XEAppliqueOperater *pAppliqueOper);
	xbool									RemoveMeshApplique(xint32 nIndex);
	const XArray<XEAppliqueOperater*>&		GetAppliqueOperaters() const { return m_vAppliqueOperater; }

protected:

// 	struct XEAppliqueOperater;
// 	struct XEMeshAppliqueOperater;
	struct XESplitSubMeshBuff;
	xbool						GenerateAppliqueOperate(const XSkin *pOriginSkin, const XSkin *pAppqSkin, const XArray<XSkinData::XRenderMesh*> &vOriginRenderMesh,
		const XArray<xint32> &vOriginRenderMeshIndex, XEAppliqueOperater *pOperater);
	xbool						GenerateMeshAppliqueOperate(const XSkinData::XRenderMesh &OriginRenderMesh, const XEAppliqueInfo &inputInfo,
		const XArray<xbool> &vFilterVertex, XSkinData::XRenderMesh &DestRMesh, XArray<xint32> &vToOriginVertexIndexs);
	xbool						GenerateSkinDataOfMeshType(XSkinData *pOldSkinData, XSkinData::XMeshType eMeshType, xbool bBlendshape, XSkinData *pSkinData);
	xbool						CopySkinDataVB(XSkinData *pOldSkinData, XSkinData *pNewSkinData);
	xbool						MatchMeshUVOfVertexBuff(const XArray<const XSkinData::XRenderMesh*> &vOriginRenderMesh, const XEAppliqueInfo &inputInfo, const XSkinData::XRenderMesh *pDestRMesh,
		const XArray<xbool> &vFilterVertex, XArray<const XBaseVertex*> &vOriginVerTex, XArray<xint32> &vToOriginVertexIndexs);
	xbool						CreateNewModelAndSkinData(const XString &strModelIns, const XString &strSkeleton, const XString &strSkinData, XModel *&pModel, XSkinData *&pSkinData);
	xbool						SetMaterialInsToNewSkin(const XSkin *pApplique, xint32 nAppliRawMeshIndex, XSkin *pNewApplique);
	xbool						GenerateSkinBlendShapeTarget(XSkin *pNewAppLiqueSkin);

	template<class V, class E>
	xbool						SplitRenderMeshByOrigin(const XSkinData::XRenderMesh *pDestRMesh, const XArray<xint32> &vToOriginVertexIndex, XESplitSubMeshBuff &SplitSubBuf,
		XArray<xbool> &vFilterVertex, XArray<xint32> &vSubToOrigin);


	void						SynchPasteModelToOrigin(XEAppliqueOperater &AppliqueOperater);
	void						SynchPasteMeshToOrigin(IXModelInstance *pOriginModelIns, IXModelInstance *pRefModelIns, XSkin *pRefSkin, XEAppliqueOperater &AppliqueOperater, XEMeshAppliqueOperater &MeshAppliqueOperate);
	void						SynchSkeletonToOrigin(const XSkeleton &OriSkeIns, XSkeleton &SkeIns);

	virtual void				DeserializeApplique(const XMLElement* pAppliqueInfos);
	virtual void				SerializeApplique(XMLElement* pAppliqueInfos);

	void						DelayAppliqueOfDeserialize();


	// 贴片模型，modelins\skin都是新建的，不需要进行嵌入，此处直接添加记录 （应用于特殊业务，本身不应该存在）
	void						EmbedAppliqueDispose(XEModelComponent *pModelComponent);

	struct XESplitSubMeshBuff
	{
		IXVertexBuffer* pDataVB;
		IXIndexBuffer* pDataIB;
		XArray<XSkinData::XRenderMesh*> vSubMeshes;
		xbool bInited;
		XESplitSubMeshBuff(XSkinData::XMeshType eMeshType, xbool bDynamicVB, xint32 nInitVertexSize, xint32 nGrowSizeVB,
			xint32 nIndexStride, xbool bDynamicIB, xint32 nInitIndexSize, xint32 nGrowSizeIB);
		~XESplitSubMeshBuff() { Release(); }
		void Release();
	};


	XArray<XEAppliqueInfo>		 m_vDelayAppliqueOfDeserialize;
	XArray<XEAppliqueOperater*>  m_vAppliqueOperater;


};

#endif