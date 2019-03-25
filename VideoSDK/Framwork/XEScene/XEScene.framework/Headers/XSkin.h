/******************************************************************************

@File         XSkin.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/
#ifndef _X_SKIN_H_
#define _X_SKIN_H_

#include "XMemBase.h"
#include "XString.h"
#include "XArray.h"
#include "XRefCount.h"
#include "XHashTable.h"
#include "XCustomGeometry.h"

class XSkin;
class XSkinData;
class XXMLExtendTool;
class IXMaterialInstance;
class XSkinBlendShapeTarget;

class IXSkinUpatedListener : public XMemBase
{
public:
	virtual void Update(XSkin* pUpdatedSkin) = 0;
};

class XSkin : public XMemBase, public XRefCount
{
	friend class XModelInstance;
	friend class XModelManager;
	friend class XHashTable<XString, XSkin*>;

public:
	struct XMeshInfo
	{
		XString               strName;
		xint32                nRawMeshIndex;
		IXMaterialInstance*   pMaterialIns;

		// cloth info
		xbool							bCloth;
		XString							strClothName;
		XString							strClothMaterialName;	// 用于自动匹配，模型导出时设置，之后不修改

		XMeshInfo()
		{
			nRawMeshIndex = -1;
			pMaterialIns = NULL;

			bCloth = xfalse;
			strClothName = "";
		}
	};

public:
	void                           Release();
	const xchar*                   GetSkinDatXFile() const;
	xint32                         GetRenderMeshRawIndex(const xchar* szMeshName, xint32 nLODIndex = 0) const;
	const xchar*                   GetSkeletonFile() const;
	const xchar*                   GetSkinFile() const;
	xint32                         GetLODNum() const { return m_aMeshInfos.Num(); }
	xint32                         GetRawMeshNum(xint32 nLODIndex = 0) const;
	const xchar*                   GetRawMeshName(xint32 nRawMeshIndex, xint32 nLODIndex = 0) const;
	const IXMaterialInstance*      GetRawMeshMtlIns(const xchar* szMeshName, xint32 nLODIndex = 0) const;
	IXMaterialInstance*            GetRawMeshMtlIns(const xchar* szMeshName, xint32 nLODIndex = 0);
	
	void						   SetRawMeshMtlIns(const xchar* szMeshName, const xchar* szMtlIns, xint32 nLODIndex = 0);
	/*
		设置rawmesh对应的材质
		@notice SetRawMeshMtlIns中未设置skin,morph宏，是错误的逻辑，此处为了防止影响外部调用；此处另加设置材质的函数。
	*/
	void						   SetRawMeshMtlInsApplyMacros(const xchar* szMeshName, const xchar* szMtlIns, xint32 nLODIndex = 0);

	xint32                         GetRenderMeshNum(xint32 nLODIndex = 0) const;
	const xchar*                   GetRenderMeshName(xint32 nRenderMeshIndex, xint32 nLODIndex = 0) const;
	const XSkinData*               GetSkinData() const { return m_pSkinData; }
	XSkinData*                     GetSkinData(){ return m_pSkinData; }
	void                           SetSkinData(const xchar* szSkinDatXFile);

	xbool                          HasBlendShapeTargets() const { return GetBlendShapeTargetNum() > 0; }
	xint32                         GetBlendShapeTargetNum() const { return m_apBlendShapeTargets.Num(); }
	XSkinBlendShapeTarget*         GetBlendShapeTarget(xint32 nIndex) { return m_apBlendShapeTargets[nIndex]; }
	const XSkinBlendShapeTarget*   GetBlendShapeTarget(xint32 nIndex) const { return m_apBlendShapeTargets[nIndex]; }
	xbool                          HasBlendShapeTarget(xint32 nRenderMeshIndex) const;	

	void                           SetSkeletonFile(const xchar* szSkeletonFile);
	void                           Save(xbool bRecursive = xfalse) const;
 	void                           AddSkinUpdatedListener(IXSkinUpatedListener* pListener);
 	void                           RemoveSkinUpdatedListener(IXSkinUpatedListener* pListener);
	xint32                         GetCorrespondingRenderMeshStartIndex(const xchar* szRawMeshName, xint32 nLODIndex = 0) const;
	xint32                         GetCorrespondingRenderMeshNum(const xchar* szRawMeshName, xint32 nLODIndex = 0) const;
	xint32                         GetFaceNum() const;

	xbool                          IsCloth(const xchar* szMeshName);
	const xchar*                   GetClothName(const xchar* szMeshName);
	void                           SetClothName(const xchar* szMeshName, const xchar* szClothName);
	const xchar*				   GetClothMaterialName(const xchar* szMeshName);

	/*
	*	添加XSkinBlendShapeTarget
	*	@notice 一般XSkinBlendShapeTarget信息由文件读取，此函数只用于特殊情况
	*/
	xbool						   AddBlendShapeTarget(XSkinBlendShapeTarget *pBlendShape);
private:
                                   XSkin();
                                   ~XSkin();
	void                           ResponseUpdated();
	const IXMaterialInstance*      GetRenderMeshMtlIns(xint32 nMeshIndex, xint32 nLODIndex = 0) const;
	IXMaterialInstance*            GetRenderMeshMtlIns(xint32 nMeshIndex, xint32 nLODIndex = 0);

	XString                        m_strSkinFile;
	XString                        m_strSkeletonFile;
	XArray<XString>                m_astrBShpTargetFiles;
	XArray<XArray<XMeshInfo> >     m_aMeshInfos;
	XSkinData*                     m_pSkinData;
	XArray<XSkinBlendShapeTarget*>      m_apBlendShapeTargets;
	XArray<IXSkinUpatedListener*>       m_aSkinUpdatedListeners;
};

#endif