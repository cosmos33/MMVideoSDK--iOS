/******************************************************************************

@File         XSkinData.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/
#ifndef _X_SKIN_DATA_H_
#define _X_SKIN_DATA_H_

#include "XMemBase.h"
#include "XBase3DTypes.h"
#include "XArray.h"
#include "XCustomGeometry.h"
#include "XInternalResource.h"
#include "XRefCount.h"
#include "XHashTable.h"

#define X_SKIN_LOD_MAX_NUM 4

class XFileBase;
class XSkeleton;
class IXMaterial;
class XXMLExtendTool;

typedef XTypeVertexBuffer<XBaseVertex>            XLocalVertexVB;
typedef XTypeVertexBuffer<XSkinMeshVertex>        XSkinVertexVB;
typedef XTypeVertexBuffer<XBlendShapeMeshVertex>  XBlendShapeVertexVB;

class XSkinData : public XMemBase, public XRefCount
{
	friend class XModelManager;
	friend class XHashTable < XString, XSkinData* >;

public:
	enum XMeshType
	{
		XMT_STATIC_MESH = 0,
		XMT_SKIN_MESH,
		XMT_NUM
	};

	struct BoneNameAndOBB
	{
		XString strBoneName;
		XCusOBB boneOBB;
	};

	/*
	* RawMesh
	* @notice	mesh从加载后，会根据一些限制进行切分，RawMesh是未切分之前的mesh
	*/
	struct XRawMesh
	{
		xint32 nStartVertex;
		xint32 nVertices;
	};

	struct IndexPairAndNormal
	{
		xuint32 vertexIndex;
		xuint32 uniqueIndex;
		XVECTOR4 normal;
	};

	/*
	* RenderMesh
	* @notice	mesh从加载后，会根据一些限制进行切分，RenderMesh是切分之后的mesh
	*/
	struct XRenderMesh
	{
		                                XRenderMesh();
		                                ~XRenderMesh();
		xbool                           GetTriVertex(xint32 nTriIndex, XSkinMeshVertex outVertices[3], xuint32 outIndices[3]) const;
		void                            CreateVertexDef();
		void                            SelectIBByMtl(IXIndexBuffer** ppOutIB, xint32* pOutStartIndex) const;


        xint32                          nVertices;
        xint32                          nFaces;
        xint32                          nStartVertex;
        xint32                          nStartIndex;
        xint32                          nRawMeshIndex;
        XString                         strName;
        xint32                          nMaxBonePerVertex;
		XMeshType                       eMeshType;
		xbool                           bBShpMesh;

		XArray<XString>                 aBoneNames;
		XArray<XMATRIX4>                aBoneInitMats;
		XHashTable<XString, XMATRIX4>   mapInitMats;

		XCusAABB                        initAABB;
		xbool                           bSupportUV1;
		XArray<xuint32>                 aUniqueNormalIndices;
		XArray<IndexPairAndNormal>      aNonBShpMeshInBShpMeshVertices;
		XArray<xuint32>                 aVerts;
		XArray<xuint32>                 aRenderVertexIndexToRawVertexIndexMap;
		IXVertexBuffer*                 pRefVB;
		IXIndexBuffer*                  pRefIB;
		XVertexDesc*                    pVertexDef[XMT_NUM];
		XArray<XString>                 aTextureNames;
	};


	struct XLOD
	{
		                           XLOD();
		virtual                    ~XLOD();

		void                       SaveMeshBinary(XFileBase* pFile, xint32 nMeshIndex) const;
#if (defined _DEBUG) && !(defined SERIALIZE_BINARY) 
		void                       SaveMeshText(XXMLExtendTool *pMeshArchive, xint32 nMeshIndex) const;
#endif
		void                       CalculateBoneOBB(XArray<XString> & aBoneNames, XArray<XCusOBB> & aBoneOBBs) const;

		XCusAABB                   m_initAABB;
		xuint32                    m_nUniqueNormalVertexNum;

		// 拆分后渲染的网格
		XArray<XRenderMesh*>       m_XRenderMeshes;
		// 拆分前的网格
		XArray<XRawMesh*>	       m_aRawMeshes;

		IXIndexBuffer*             m_aIB[XMT_NUM];
		IXVertexBuffer*            m_aVB[XMT_NUM];

		XArray<BoneNameAndOBB>          m_aBoneNameAndOBBs;
		XArray<XSkinMeshVertex>         m_aSkinExtraSpeedTreeVBForSave;
		XArray<xuint32>                 m_aSkinIBForSave;
	};

public:

	void                           Release();
	xint32                         GetLODNum() const { return m_aLODs.Num(); }
	const XLOD*                    GetLOD(xint32 index) const;
	XLOD*                          GetLOD(xint32 index);

	void                           GetRenderMesh(const xchar* szMeshName, XArray<XRenderMesh*>& aOutRenderMeshes, xint32 nLODIndex = 0);
	const XRawMesh*                GetRawMesh(const xchar* szMeshName, xint32 nLODIndex = 0) const; 
	XRawMesh*                      GetRawMesh(const xchar* szMeshName, xint32 nLODIndex = 0);
	xint32                         GetVersion() const { return m_nVersion; }
	xint32                         GetRenderMeshNum(xint32 nLODIndex = 0) const;
	const XRenderMesh*             GetRenderMesh(xint32 nMeshIndex, xint32 nLODIndex = 0) const;
	XRenderMesh*                   GetRenderMesh(xint32 nMeshIndex, xint32 nLODIndex = 0);
	xint32                         GetRawMeshNum(xint32 nLODIndex = 0) const;

	const XCusAABB&                GetInitAABB(xint32 nLODIndex = 0) const;
	const xchar*                   GetFileName() const { return m_strFileName; }	
	
	const IXVertexBuffer*          GetVBByMeshType(XMeshType eMeshType, xint32 nLODIndex = 0) const;
	IXVertexBuffer*                GetVBByMeshType(XMeshType eMeshType, xint32 nLODIndex = 0);

	const IXIndexBuffer*           GetIBByMeshType(XMeshType eMeshType, xint32 nLODIndex = 0) const;
	IXIndexBuffer*		           GetIBByMeshType(XMeshType eMeshType, xint32 nLODIndex = 0);
	
	void                           SetLODVBAndIBs(const XArray<XSkinMeshVertex>& aSkinVA, const XArray<xint32>& aSkinIA, const XArray<xint32>& aSkinAdjIA, xint32 nLODIndex = 0);
	void                           SaveBinary() const;

#if (defined _DEBUG) && !(defined SERIALIZE_BINARY) 
	void                           SaveText() const;
#endif

	//	这个函数本来是private函数，SkinData在读取数据时，调用这个函数，在内部对VB和IB进行初始化。
	//	但是如果SkinData是通过IXSkinDataManager::CreateSkinData创建的，此时VB和IB为NULL，需要在外部主动初始化VB和IB，因此将这个函数权限修改为public
	void                           InitVBAndIB(XMeshType eMeshType, xint32 nVBSize, xint32 nIBSize, xint32 nLODIndex = 0);
	//	只在对fbx进行转换时使用
	void                           AddRenderMesh(XRenderMesh* pRenderMesh, xint32 nLODIndex = 0);
	const XArray<BoneNameAndOBB>&  GetBoneNamesAndOBBs(xint32 nLODIndex = 0) const { return m_aLODs[nLODIndex]->m_aBoneNameAndOBBs; }

	// 重新计算Skindata，以及RendeMesh的AABB;
	// @notice 只有运行中，skindata的顶点位置信息有修改，才会用到;
	void						   UpdateInitAABB();
private:

                                   XSkinData();
                                   ~XSkinData();

	xuint32                        m_nFlags;
	xuint32                        m_nVersion;
	XString                        m_strFileName;
	XArray<XLOD*>                  m_aLODs;
};

#endif
