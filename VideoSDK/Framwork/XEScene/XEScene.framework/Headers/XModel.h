/******************************************************************************

@File         XModel.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/
#ifndef _X_MODEL_H_
#define _X_MODEL_H_

#include "XMemBase.h"
#include "XString.h"
#include "XArray.h"
#include "XRefCount.h"
#include "XHashTable.h"
#include "XSkin.h"
#include "XSkeleton.h"
#include "XCustomGeometry.h"

class XXMLExtendTool;


static const xchar* MODEL_FILE_EXTENSION = "mdl";
static const xchar* SKIN_FILE_EXTENSION = "ski";
static const xchar* SKELETON_FILE_EXTENSION = "ske";
static const xchar* SKINDATA_FILE_EXTENSION = "mesh";
static const xchar* MATERIAL_FILE_EXTENSION = "mt";
static const xchar* MATERIALINSTANCE_FILE_EXTENSION = "mtins";

enum XModelType
{
	XSMT_ANIMAMODEL = 0,
	XSMT_STATICMODEL,
	XSMT_NUM
};

class IXModelInstance;

class XModel : public XMemBase, public XRefCount
{
	friend class XModelInstance;
	friend class XModelManager;
	friend class XHashTable<XString, XModel*>;

public:
	virtual void                        Release();
	virtual const xchar*                GetModelFile() const{ return m_strSkinModelFile; }
	virtual xint32                      GetSkinNum() const { return m_aSkin.Num(); }
	virtual xuint32                     GetVersion() const { return m_nVersion; }
	virtual const XSkin*                GetSkin(xint32 nIndex) const { ASSERT(nIndex >= 0 && nIndex < m_aSkin.Num()); return m_aSkin[nIndex]; }
	virtual XSkin*                      GetSkin(xint32 nIndex) { ASSERT(nIndex >= 0 && nIndex < m_aSkin.Num()); return m_aSkin[nIndex]; }
	virtual xbool                       AddSkin(const xchar* szSkinFile, xbool bReload, const xchar* szSkeletonPath = NULL);
	virtual void                        RemoveSkin(const xchar* szSkinFile);
	virtual void                        BindSkeleton(XSkeleton* pSkeleton);
	virtual XModelType	                GetModelType() const;
	virtual const xchar*                GetSkeletonFile() const;
	virtual XSkeleton*	                GetSkeleton() const { return m_pSkeleton; }
	virtual xbool		                SkinHaveBlendShapeTargets() const;
	virtual xint32		                GetFaceNum() const;
	virtual xint32						GetSkinIndexBySkinFileName(const xchar* szSkinFile, xbool bCmpFullPath = xtrue);

	virtual XCusOBB                     GetBoneOBB(xint32 nBoneIndex);
	virtual void                        Save(xbool bRecursive = xtrue) const;

private:
                                        XModel();
                                        ~XModel();
	void                                UpdateBoneOBB(const XArray<xint32> &aBoneUpdateList);
	void                                UpdateInitModelAABB();

	XString                             m_strSkinModelFile;
	xuint32                             m_nVersion;
	XSkeleton*                          m_pSkeleton;
	XArray<XCusOBB>                     m_aBoneOBB;
	XArray<XSkin*>                      m_aSkin;
	XCusAABB                            m_InitAABB;
};


class IXModelManager : public XMemBase
{
public:
	virtual                             ~IXModelManager(){}

	virtual bool                        Init() = 0;
	virtual void                        Release() = 0;


	/*
	* 从文件中加载模型
	*
	* @notice	引用计数会加1
	*
	* @param	szNewSkinModelFile 模型文件路径
	* @param	szSkeletonFile 骨骼文件路径
	*/	
	virtual XModel*                     CreateModel(const xchar* szNewSkinModelFile, const xchar* szSkeletonFile) = 0;
	virtual XModel*                     GetModel(const xchar* szSkinModelFile, xbool bReload = xfalse) = 0;

	/*
	* 从文件中加载蒙皮
	*
	* @notice	引用计数会加1
	*
	* @param	szFileName 蒙皮文件路径
	*/
 	virtual XSkin*						GetSkin(const xchar* szFileName, xbool bReload = xfalse, const xchar* szSkeletonPath = NULL) = 0;
 	virtual XSkin*						CreateSkin(const xchar* szNewSkinFile, const xchar* szSkinDatXFile, const xchar* szSkeletonFile) = 0;

	// 引用计算会加1
	virtual XSkinData*					GetSkinData(const xchar* szSkinDatXFileName, xbool bReload = xfalse) = 0;
	virtual XSkinData*					CreateSkinData(const xchar* szSkinDatXFileName, xint32 nNumLODs = 1) = 0;

	virtual IXModelInstance*			CreateSkinModelInstance(const xchar* szSkinModelFileName) = 0;

	//	Reload
	virtual void						ReloadSkeleton(const xchar* szSkeletonFile) = 0;
	virtual void						ReloadSkinModel(const xchar* szSkinModelFile) = 0;
	virtual void						ReloadSkin(const xchar* szFileName) = 0;
	virtual void						ReloadSkinData(const xchar* szSkinDatXFileName) = 0;

	//	Check
	virtual xbool						IsSkeletonLoaded(const xchar* szSkeletonFile) = 0;
	virtual xbool						IsSkinModelLoaded(const xchar* szSkinModelFile) = 0;
	virtual xbool						IsSkinLoaded(const xchar* szFileName) = 0;
	virtual xbool						IsSkinDataLoaded(const xchar* szSkinDatXFileName) = 0;
	virtual void						UpdateUpwardFromSkinData(XSkinData* pSkinData) = 0;


};
class IXEditorModelManager : public IXModelManager
{
protected:
	virtual					~IXEditorModelManager() {}

public:
	struct XModelParamForSave
	{
		XString	strSkinModelName;
		XString	strSkeletonFile;
		bool bSkeletonRelativeToCurDir;
		XArray<XString> aSkinNames;
		XArray<bool> aSkinRelativeToCurDir;
	};

	struct XMeshInfoParamForSave
	{
		XString	strMeshName;
		bool bInvisible;
		XString	strMtlInsFile;
		bool bMtlInstRelativeToCurDir;
		bool bCloth;
		XString strClothName;
		bool bClothRelativeToCurDir;
		XString strClothMaterialName;
	};

	struct XSkinInfoParamForSave
	{
		XString strSkinName;
		XString	strSkinDataFile;
		bool bSkinDataRelativeToCurDir;
		XString strSkeletonFile;
		bool bSkeletonRelativeToCurDir;
		XArray<XArray<XMeshInfoParamForSave> > meshInfos;
		XArray<XString> strBShpFiles;
		XArray<xbool> bBShpRelativeToCurDirs;
	};

	virtual void				SaveSkinModel(const xchar* szSaveSkinModelFile, const XModelParamForSave& skinModelInfo) = 0;
	virtual void				SaveSkin(const XSkinInfoParamForSave& skinInfo) = 0;

#if (defined _DEBUG) && !(defined SERIALIZE_BINARY) 
	virtual void				SerializeSkinModel(XXMLExtendTool& outXmlArchive, const XModelParamForSave& skinModelInfo) = 0;
	virtual void				SerializeSkin(XXMLExtendTool& outXmlArchive, const XSkinInfoParamForSave& skinInfo) = 0;
#endif	
};

extern IXModelManager* g_pXModelManager;
extern IXEditorModelManager* g_pXEditorModelManager;

#endif