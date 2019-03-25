/******************************************************************************

@File         XEInstanceManagerMounter.h

@Version       1.0

@Created      2018,4, 18

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_MOUNTER_MANAGER_H
#define _XE_MOUNTER_MANAGER_H
#include "XEInstanceManagerBase.h"
#include "XESingleton.h"

class XEInstanceManagerMounterRuntime;
class XEInstanceManagerMounter
	: public XEInstanceManagerBase
{
public:
	XEInstanceManagerMounter(){}
	~XEInstanceManagerMounter(){}
public:
	virtual XEUserNode*                     CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld) override;
	virtual XEUserNode*                     GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload = xfalse) override;
	virtual void                            Reload(const xchar* szAssetFile = NULL) override;
	virtual void                            SaveImpl() const override;
	virtual void                            SaveAsImpl(const xchar* pPath) const override;
	virtual xbool                           IsNodesModifiedImpl()const override;
public:							           
	void                                    SetMounterScopeModelAssetPath(const xchar* szAssetPath);//need to specifiy the scope model asset path.
	//for lua side
	static XEInstanceManagerMounterRuntime* GetInstanceManagerMounter();
protected:
	XString                                 m_strScopeMounterModelAssetPath;
};


//runtime only.
class XEInstanceManagerMounterRuntime
	: public XEInstanceManagerMounter
	, public XESingleton<XEInstanceManagerMounterRuntime>
{
};

#if X_PLATFORM_WIN_DESKTOP
//editing only.
class XEInstanceManagerMounterEditing
	: public XEInstanceManagerMounter
	, public XESingleton<XEInstanceManagerMounterEditing>
{
};
#endif

#endif // _XE_MOUNTER_MANAGER_H
