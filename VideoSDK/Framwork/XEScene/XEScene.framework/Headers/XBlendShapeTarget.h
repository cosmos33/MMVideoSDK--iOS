/******************************************************************************

@File         XBlendShapeTarget.h

@Version       1.0

@Created      2017, 4, 16

@Description

@HISTORY:

******************************************************************************/

#ifndef _X_BLENDSHAPE_TARGET_H_
#define _X_BLENDSHAPE_TARGET_H_

#include "XMemBase.h"
#include "XArray.h"
#include "XString.h"
#include "XSkinData.h"
#include "XBlendShapeManager.h"
#include <utility>

#define UPDATEBLENDSHAPE_ASYNC 0

#if UPDATEBLENDSHAPE_ASYNC
#include <future>
#endif

struct XBlendShapeTarget : public XMemBase
{
							XBlendShapeTarget() = default;
	xbool					DoSave(XFileBase* pFile) const;
	xbool					DoLoad(XFileBase* pFile);

	/*
	* BlendShape顶点信息
	*
	* @param	vPositionDelta   相对于源位移的偏移
	* @param	vTangentZDelta   相对于源法线的偏移
	* @param	nMeshVertexIndex 在mesh中的顶点索引
	*/
	struct BlendShapeVertex
	{
		XVECTOR3			  vPositionDelta;
		XVECTOR3			  vTangentZDelta;
		xint32				  nMeshVertexIndex;
	};

	XString                   strBShpTargetName;
	XArray<BlendShapeVertex>  aBShpVertices;
	xint32                    nTargetMeshVertexNum;			// 当前未使用
	xint32                    nTargetMeshVertexStartIndex;		// 当前未使用
};

struct XBlendShapeChannel : public XMemBase
{
								XBlendShapeChannel() = default;
	xbool						DoSave(XFileBase* pFile) const;
	xbool						DoLoad(XFileBase* pFile, xuint32 loadVersion);

	struct TargetPair
	{
		xint32 index;
		xfloat32 value;
	};
	XString						strChannelName;
	xfloat32					defaultValue = 0.0f;
	XArray<TargetPair>			aTargets;	
};

struct XMeshBlendShapeTarget : public XMemBase
{	
										XMeshBlendShapeTarget() = default;
	xbool								DoSave(XFileBase* pFile) const;
	xbool								DoLoad(XFileBase* pFile, xuint32 loadVersion);

	XString								strTargetMeshName;

	/*
	* 对应原始网格的索引	
	* @notice 原始网格在fbx转换时，可能会拆分成多个网格。此外的索引，记录着此网格对应的原始网格是那个。
	*/
	xint32								nOriginalMeshIndex = -1;		
	XArray<XBlendShapeTarget>			aTargets;
	XArray<XBlendShapeChannel>			aChannels;	
};


class XSkinBlendShapeWeight
{
	friend class XSkinBlendShapeTarget;
public:
	/*
	* 权重对应网格的类型
	*
	* @notice 一般权重调节都是基于fbx中的网格，所以非特殊情况都是OriginalMesh类型
	*
	* @param	RawMesh		对应转换模型时输出的网格
	* @param	OriginalMesh   对应fbx中的原始网格  
	*/
	enum MeshWeightType
	{
		RawMesh,
		OriginalMesh,
	};
public:
                                        XSkinBlendShapeWeight() : m_pTargetBlendShapeTarget(NULL), m_eMeshWeightType(MeshWeightType::OriginalMesh) {}
                                        XSkinBlendShapeWeight(XSkinBlendShapeWeight&& other);
	XSkinBlendShapeWeight&				operator=(const XSkinBlendShapeWeight& other);
	XSkinBlendShapeWeight&				operator=(XSkinBlendShapeWeight&& other);

	MeshWeightType						GetMeshWeightType() const { return m_eMeshWeightType; }

	const XSkinBlendShapeTarget*		m_pTargetBlendShapeTarget;
	MeshWeightType						m_eMeshWeightType;
	/*
	* @notice 二级数组意义 [mesh index][morph channel index]
	*/
	XArray<XArray<xfloat32>>				m_afWeights;
	
};

class XModel;
struct XSkinModelBlendShapeWeight
{
public:
                                        XSkinModelBlendShapeWeight();
                                        XSkinModelBlendShapeWeight(const XModel* pTargetSkinModel, XSkinBlendShapeWeight::MeshWeightType meshType = XSkinBlendShapeWeight::MeshWeightType::OriginalMesh);
                                        
                                        XSkinModelBlendShapeWeight(const XSkinModelBlendShapeWeight& other);
                                        XSkinModelBlendShapeWeight(XSkinModelBlendShapeWeight&& other);
	XSkinModelBlendShapeWeight&			operator=(const XSkinModelBlendShapeWeight& other);
	XSkinModelBlendShapeWeight&			operator=(XSkinModelBlendShapeWeight&& other);

	xbool                               IsEmpty() const { return m_aWeights.Num() == 0; }

	void                                AdditiveBlendFrom(const XSkinModelBlendShapeWeight& morphWeights, xfloat32 fBlendWeight);
	void                                LerpBlendFrom(const XSkinModelBlendShapeWeight& morphWeights, xfloat32 fBlendWeight);
	void                                OverrideFrom(const XSkinModelBlendShapeWeight& morphWeights);
	void                                ClearValueToZero();

	friend xbool                        operator==(const XSkinModelBlendShapeWeight& left, const XSkinModelBlendShapeWeight& right);
	friend xbool                        operator!=(const XSkinModelBlendShapeWeight& left, const XSkinModelBlendShapeWeight& right) { return !(left == right); }	

#if UPDATEBLENDSHAPE_ASYNC
	void								SetInUseByBlendShapeInstance(xbool inUse) const;

	mutable std::atomic<xbool>			m_bInUseByBShpInstance;	
#endif	
	const XModel*						m_pTargetSkinModel = NULL;
	/*
	* @notice 二级数组意义 [skin index][morph target index]
	*/
	XArray<XArray<XSkinBlendShapeWeight>>	m_aWeights;

private:
	void								MultiplyWeight(xfloat32 fBlendWeight);    
};

class XThreadMutex;

struct BlendShapeWeightBufferWithMutex
{
     BlendShapeWeightBufferWithMutex(const XSkinModelBlendShapeWeight& weights, XThreadMutex* pBShpWeightMutex)
          : weights(weights), pBShpWeightMutex(pBShpWeightMutex) {}

	const XSkinModelBlendShapeWeight&        weights;
	XThreadMutex*							 pBShpWeightMutex;
};

class XSkinBlendShapeTarget : public IBlendShapeAsset
{
public:
	struct RangePair
	{
		xint32 e1;
		xint32 e2;
	};
public:
                                             XSkinBlendShapeTarget() = default;
                                             ~XSkinBlendShapeTarget();
                                             XSkinBlendShapeTarget(XSkinBlendShapeTarget const& other) = delete;
                                             XSkinBlendShapeTarget(XSkinBlendShapeTarget&& other);
	XSkinBlendShapeTarget&                   operator =(XSkinBlendShapeTarget const& other) = delete;
	XSkinBlendShapeTarget&                   operator =(XSkinBlendShapeTarget&& other);

	void                                     Release();

	static const XString&                    FileExtension() { static XString strExtension = ".mph"; return strExtension; }

	xint32                                   GetMeshBShpTargetNum() const { return m_aMeshBShpTargets.Num(); }
	xint32	                                 GetOriginalMeshNum() const { return m_anOriginalMeshIndexToRawMeshStartIndex.Num() - 1; }
	
	/*
	* 获取网格的BlendShapeTarget
	*
	* @param	nMeshIndex 对应转换模型后拆分的网格索引
	*/
	const XMeshBlendShapeTarget*			GetMeshBShpTarget(xint32 nMeshIndex) const { return m_aMeshBShpTargets[nMeshIndex]; }

	const XString&							GetOriginalMeshName(xint32 nOriginalMeshIndex) const { return m_astrOriginalMeshNames[nOriginalMeshIndex]; }
	RangePair								GetOriginalMeshToRawMeshRange(xint32 nOriginalMeshIndex) const { return { m_anOriginalMeshIndexToRawMeshStartIndex[nOriginalMeshIndex], m_anOriginalMeshIndexToRawMeshStartIndex[nOriginalMeshIndex + 1] }; }
	
	XArray<XString>&						GetOriginalMeshNames() { return m_astrOriginalMeshNames; }
	const XArray<XString>&					GetOriginalMeshNames() const { return m_astrOriginalMeshNames; }

	/*
	* 获取原始网格与导出后网格的对应关系数组
	*/
	const XArray<xint32>&                    GetOriginalMeshIndexToRawMeshStartIndexMapping() const { return m_anOriginalMeshIndexToRawMeshStartIndex; }

	/*
	* @notice 慎重的修改m_anOriginalMeshIndexToRawMeshStartIndex的值
	*/
	XArray<xint32>&                          GetOriginalMeshIndexToRawMeshStartIndexMapping() { return m_anOriginalMeshIndexToRawMeshStartIndex; }	

	/*
	* 获取原始网格与渲染网格之间的对应关系数组
	*
	* @notice 由于网格对应骨头数的限制，网格可以会拆分成更多的网格(fix flk当前转换器，是限制了骨头的关联数，所以一般不会因为骨头再拆分)
	*/
	const XArray<xint32>&                    GetOriginalMeshIndexToRenderMeshStartIndexMapping() const { return m_anOriginalMeshIndexToRenderMeshStartIndex; }

	/*
	* @notice 慎重的修改m_anOriginalMeshIndexToRenderMeshStartIndex的值
	*/
	XArray<xint32>&                          GetOriginalMeshIndexToRenderMeshStartIndexMapping() { return m_anOriginalMeshIndexToRenderMeshStartIndex; }

	/*
	* 检查是SkinData与Blendshape是否匹配
	*
	* @notice 对于SkinData，并不一定是其一同生成的Blendshape才能匹配，只要此函数返回为true，就说明可以运行。
	*/
	xbool                                    IsTargetMatch(XSkinData& targetSkinData) const;

	virtual xbool                            DoSave(XFileBase* pFile) const override;
	virtual xbool                            DoLoad(XFileBase* pFile) override;

	XSkinBlendShapeWeight                    CreateBlendShapeWeightBuffer(XSkinBlendShapeWeight::MeshWeightType eMeshType) const;

	/*
	* 生成 m_anOriginalMeshIndexToRenderMeshStartIndex 对应关系
	*
	* @notice 加载的时间会被调用
	*/
	xbool								     BuildRuntimeMeshMapping(const XSkinData& buildTo);

	
	const XArray<XMeshBlendShapeTarget*>&    GetData() const { return m_aMeshBShpTargets; }
	XArray<XMeshBlendShapeTarget*>&		     GetData() { return m_aMeshBShpTargets; }

protected:
	virtual void						     OnReload() override;


	/*
	* 各网格的BlendShapeTarget
	*
	* @notice	 数组中的顺序，对应转换模型时输出的网格
	*/
	XArray<XMeshBlendShapeTarget*>           m_aMeshBShpTargets;

	XArray<XString>                          m_astrOriginalMeshNames;

	/*
	* 原始网格与导出后拆分网格的开始索引对应关系数组
	*
	* @notice	对应关系举例 . 如原始网格有3个， 而且原始网格1生成了3个网格。则对应关系缓存为[0,1,4,5]
	*		其中原始网格1对应的raw网格开始索引为1, 原始网格2对应的raw网格开始索引为4,而1到4之间的[1,2,3]都是对应原始网格1的。
	*/
	XArray<xint32>                           m_anOriginalMeshIndexToRawMeshStartIndex;

	/*
	* 原始网格与渲染网格的索引对应关系数组
	*
	* @notice 对应方法与上面的类似， 此处是因为网格对应骨头数的限制，
	*		网格可以会拆分成更多的渲染网格	(fix flk当前转换器，是限制了骨头的关联数，所以一般不会因为骨头再拆分， 此外的渲染网格也与skin中的渲染网格不同步)
	*/
	XArray<xint32>                           m_anOriginalMeshIndexToRenderMeshStartIndex;

	XString                                  m_strTargetSkinDatXFile;
};


class XBlendShapeInstance
{
public:
	enum VertexType { Local,	Skin, Count };
	struct SkinBlendShapePack
	{
		struct BlendShapeVertexDefinePack
		{
            BlendShapeVertexDefinePack() : m_pVertexDefBShp(NULL) {}
            ~BlendShapeVertexDefinePack()	{ X_SAFEDELETE(m_pVertexDefBShp); }
			XVertexDesc*      m_pVertexDefBShp;
			VertexType        m_eVertexType = VertexType::Count;
		};

        SkinBlendShapePack() : m_pBShpLocalDynamicVB(NULL), m_pBShpSkinDynamicVB(NULL) {}
        ~SkinBlendShapePack() { Clear(); }
        SkinBlendShapePack(SkinBlendShapePack const& other) = delete;
        SkinBlendShapePack& operator=(SkinBlendShapePack const& other) = delete;
		void             Clear();

		XBlendShapeVertexVB* m_pBShpLocalDynamicVB;
		XBlendShapeVertexVB* m_pBShpSkinDynamicVB;
		XArray<BlendShapeVertexDefinePack> m_XBShpMeshVertexDefinePack; // [render mesh index]
	};

#if UPDATEBLENDSHAPE_ASYNC
	struct ResultGetter
	{
		ResultGetter() = default;
		ResultGetter(std::future<void> result);
		ResultGetter(ResultGetter&& other);
		ResultGetter& operator=(ResultGetter&& other);
		void Wait() const { if (result.valid()) result.wait(); }

		std::future<void> result;
	};
#endif

public:

                                   XBlendShapeInstance();
                                   ~XBlendShapeInstance();
                                   XBlendShapeInstance(const XModel* pSkinModel);
                                   XBlendShapeInstance(XBlendShapeInstance const& other) = delete;
                                   XBlendShapeInstance operator=(XBlendShapeInstance const& other) = delete;
                                   XBlendShapeInstance(XBlendShapeInstance&& other);
	XBlendShapeInstance&           operator=(XBlendShapeInstance&& other);

	void                           UpdateBlendShapeVertexBuffer(BlendShapeWeightBufferWithMutex BShpWeightBuffer, xbool& dirtyFlag);
#if UPDATEBLENDSHAPE_ASYNC
    void                           UpdateBlendShapeVertexBufferAsync(BlendShapeWeightBufferWithMutex BShpWeightBuffer, XBlendShapeInstance::ResultGetter& result, xbool& dirtyFlag);
#endif

	/*
	* 提交到GPU缓存
	*
	* @notice 在Render里，会被调用
	*/
	void                           CommitGPUBuffers();
	const XBlendShapeInstance::SkinBlendShapePack::BlendShapeVertexDefinePack* GetBlendShapeVertexDefinePack(xint32 nSkinIndex, xint32 nMeshIndex) const { return &m_apSkinBShpPacks[nSkinIndex]->m_XBShpMeshVertexDefinePack[nMeshIndex]; }

	void                           Clear() { m_apSkinBShpPacks.Clear(false); }

	XBlendShapeVertexVB*           GetBlendShapeVB(xint32 nSkinIndex, xint32 nMeshIndex);

private:

	void                           DoUpdateBlendShapeVertexBuffer(BlendShapeWeightBufferWithMutex BlendShapeWeightBuffer);
	void                           CreateVertexDefine(const XSkinData* pSkinData, xint32 nSkinIndex, xint32 nMeshIndex);

	XArray<SkinBlendShapePack*>    m_apSkinBShpPacks; // [skin index]
	const XModel*                  m_pTargetSkinModel = nullptr;

#if UPDATEBLENDSHAPE_ASYNC
	std::atomic<bool>              m_bUpdating;
#endif
};

#endif

