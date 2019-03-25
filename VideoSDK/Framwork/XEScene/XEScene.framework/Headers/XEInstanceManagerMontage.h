/******************************************************************************

@File         XEInstanceManagerMontage.h

@Version       1.0

@Created      2018,4, 18

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_MONTAGE_MANAGER_H
#define _XE_MONTAGE_MANAGER_H
#include "XEInstanceManagerBase.h"
#include "XESingleton.h"

class XEAnimMontage;
class XEAnimMontageInstance;
class XEInstanceManagerMontageRuntime;
class XEInstanceManagerMontage
	: public XEInstanceManagerBase
{
public:
	XEInstanceManagerMontage(){}
	~XEInstanceManagerMontage(){}
public:
	virtual XEUserNode*                     CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld) override;
	virtual XEUserNode*                     GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload = xfalse) override;
	virtual void                            Reload(const xchar* szAssetFile = NULL) override;
	virtual void                            SaveImpl() const override;
	virtual void                            SaveAsImpl(const xchar* pPath) const override;
	virtual xbool                           IsNodesModifiedImpl()const override;
public:
	//for lua side
	static XEInstanceManagerMontageRuntime* GetInstanceManagerMontage();
};


//runtime only.
class XEInstanceManagerMontageRuntime
	: public XEInstanceManagerMontage
	, public XESingleton<XEInstanceManagerMontageRuntime>
{
};

#if X_PLATFORM_WIN_DESKTOP
//editing only.
class XEInstanceManagerMontageEditing
	: public XEInstanceManagerMontage
	, public XESingleton<XEInstanceManagerMontageEditing>
{
};
#endif

#endif // _XE_MONTAGE_MANAGER_H
