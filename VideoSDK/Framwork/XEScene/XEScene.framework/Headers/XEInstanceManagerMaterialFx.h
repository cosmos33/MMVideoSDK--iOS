/******************************************************************************

@File         XEInstanceManagerMaterialFx.h

@Version       1.0

@Created      2018, 10, 23

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_MATERIAL_MANAGER_H_
#define _XE_MATERIAL_MANAGER_H_
#include "XEInstanceManagerBase.h"
#include "XESingleton.h"

class XEInstanceManagerMaterialFxRuntime;
class XEInstanceManagerMaterialFx
	: public XEInstanceManagerBase
{
public:
	XEInstanceManagerMaterialFx(){}
	~XEInstanceManagerMaterialFx(){}
public:
	virtual XEUserNode*                        CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld) override;
	virtual XEUserNode*                        GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload = xfalse) override;
	virtual void                               Reload(const xchar* szAssetFile = NULL) override;
	virtual void                               SaveImpl() const override;
	virtual void                               SaveAsImpl(const xchar* pPath) const override;
	virtual xbool                              IsNodesModifiedImpl()const override;
public:
	//for lua side
	static XEInstanceManagerMaterialFxRuntime* GetInstanceManagerMaterialFx();
};


//runtime only.
class XEInstanceManagerMaterialFxRuntime
	: public XEInstanceManagerMaterialFx
	, public XESingleton<XEInstanceManagerMaterialFxRuntime>
{
};

#if X_PLATFORM_WIN_DESKTOP
//edit for export.
class XEInstanceManagerMaterialFxEditing
	: public XEInstanceManagerMaterialFx
	, public XESingleton<XEInstanceManagerMaterialFxEditing>
{
};

#endif

#endif // _XE_MATERIAL_MANAGER_H_
