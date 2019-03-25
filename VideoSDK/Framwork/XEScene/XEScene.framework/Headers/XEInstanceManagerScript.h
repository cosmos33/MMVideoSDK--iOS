/******************************************************************************

@File         XEInstanceManagerScript.h

@Version       1.0

@Created      2018,4, 18

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_SCRIPT_MANAGER_H_
#define _XE_SCRIPT_MANAGER_H_
#include "XEInstanceManagerBase.h"
#include "XESingleton.h"

class XEInstanceManagerScriptRuntime;
class XEInstanceManagerScript
	: public XEInstanceManagerBase
{
public:
	XEInstanceManagerScript(){}
	~XEInstanceManagerScript(){}
public:
	virtual XEUserNode*                    CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld) override;
	virtual XEUserNode*                    GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload = xfalse) override;
	virtual void                           Reload(const xchar* szAssetFile = NULL) override;
	virtual void                           SaveImpl() const override;
	virtual void                           SaveAsImpl(const xchar* pPath) const override;
	virtual xbool                          IsNodesModifiedImpl()const override;
public:
	//for lua side
	static XEInstanceManagerScriptRuntime* GetInstanceManagerScript();
};


//runtime only.
class XEInstanceManagerScriptRuntime
	: public XEInstanceManagerScript
	, public XESingleton<XEInstanceManagerScriptRuntime>
{
};

#if X_PLATFORM_WIN_DESKTOP
//editing only.
class XEInstanceManagerScriptEditing
	: public XEInstanceManagerScript
	, public XESingleton<XEInstanceManagerScriptEditing>
{
};
#endif

#endif // _XE_SCRIPT_MANAGER_H_
