/******************************************************************************

@File         XEDressup.h

@Version       1.0

@Created      2018, 5, 16

@Description  The processing logics of dress up sub-editor

@HISTORY:

******************************************************************************/
#pragma once

#include "XString.h"
#include "XArray.h"
#include "XRefCount.h"

static const char* DRESSUP_FILE_SUFFIX = "dressup";

//////////////////////////////////////////////////////////////////////////
//
//	IDressup Interface
//
//////////////////////////////////////////////////////////////////////////
class XModel;
class IXEDressup : public XRefCount
{
public:
	struct AddedSkin
	{
		XString		strSkinfile;
		XString		strRefSkeletonPath;
	};

	virtual							~IXEDressup() {}

	virtual void					Release() = 0;
	virtual bool					Save() = 0;

	virtual bool					AddSkin(const char* szSkinFile, const xchar* szSkeletonPath = NULL) = 0;
	virtual void					RemoveSkin(const char* szSkinFile) = 0;
	virtual bool					ReplaceSkin(const char* szSrcSkinFile, const char* szDestSkinFile, const xchar* szSkeletonPath = NULL) = 0;

	virtual const char*				GetTemplateSkinModelFile() const = 0;
	virtual const XArray<AddedSkin>& GetAddedSkins() const = 0;
	virtual const XArray<XString>&	GetRemovedSkins() const = 0;

	virtual const char*				GetDressupFile() const = 0;
	virtual const XModel*			GetSkinModel() const = 0;
	virtual       XModel*			GetSkinModel() = 0;
};

//////////////////////////////////////////////////////////////////////////
//
//	IDressupManager Interface
//
//////////////////////////////////////////////////////////////////////////
class IXEDressupManager
{
public:
	struct DressupParamForSave
	{
		XString							strTemplateSkinModel;
		XArray<IXEDressup::AddedSkin>	aAddedSkins;
		XArray<XString>					aRemovedSkins;
	};

	virtual						~IXEDressupManager() {}

	virtual bool				Init() = 0;
	virtual void				Release() = 0;

	virtual IXEDressup*			CreateDressup(const char* szDressupFile, const char* szSkinModelFile) = 0;
	virtual IXEDressup*			GetDressup(const char* szDressupFile, bool bReload = false) = 0;
	virtual IXEDressup*			CloneDressup(const IXEDressup* pSrcDressup, const char* szDestDressupFile) = 0;
	virtual void				ReleaseDressup(IXEDressup* pDressup) = 0;
	virtual bool				SaveDressup(const char* szDressupFile, const DressupParamForSave& paramForSave) = 0;
	virtual void				ReloadDressup(const char* szDressupFile) = 0;
};

extern IXEDressupManager* g_pDressupManager;