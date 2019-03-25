/******************************************************************************

@File         XEInstanceManagerARAds.h

@Version       1.0

@Created      2018/5/30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_ARADS_MANAGER_H
#define _XE_ARADS_MANAGER_H

#include "XEInstanceManagerBase.h"
#include "XESingleton.h"

class XEInstanceManagerARAdsRuntime;
class XEInstanceManagerARAds
	: public XEInstanceManagerBase
{
public:
	XEInstanceManagerARAds(){}
	~XEInstanceManagerARAds(){}
public:
	virtual XEUserNode*                  CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld = NULL) override;
	virtual XEUserNode*                  GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload = xfalse) override;
	virtual void                         Reload(const xchar* szAssetFile = NULL) override;
	virtual void                         SaveImpl() const override;
	virtual void                         SaveAsImpl(const xchar* pPath) const override;
	virtual xbool                        IsNodesModifiedImpl()const override;
public:
	//for lua side
	static XEInstanceManagerARAdsRuntime*GetInstanceManagerARAds();
};


//runtime only.
class XEInstanceManagerARAdsRuntime
	: public XEInstanceManagerARAds
	, public XESingleton<XEInstanceManagerARAdsRuntime>
{
};

#if X_PLATFORM_WIN_DESKTOP
//editing only.
class XEInstanceManagerARAdsEditing
	: public XEInstanceManagerARAds
	, public XESingleton<XEInstanceManagerARAdsEditing>
{
};
#endif

#endif // _XE_ARADS_MANAGER_H
