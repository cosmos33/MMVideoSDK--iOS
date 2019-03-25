/******************************************************************************

@File         XEInstanceManagerBlend.h

@Version       1.0

@Created      2018,9, 27

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_BLEND_MANAGER_H
#define _XE_BLEND_MANAGER_H
#include "XEInstanceManagerBase.h"
#include "XESingleton.h"

class XEAnimBlend;
class XEAnimBlendInstance;
class XEInstanceManagerBlendRuntime;

class XEInstanceManagerBlend
	: public XEInstanceManagerBase
{
public:
	XEInstanceManagerBlend(){}
	~XEInstanceManagerBlend(){}
public:
	virtual XEUserNode*                  CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld) override;
	virtual XEUserNode*                  GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload = xfalse) override;
	virtual void                         Reload(const xchar* szAssetFile = NULL) override;
	virtual void                         SaveImpl() const override;
	virtual void                         SaveAsImpl(const xchar* pPath) const override;
	virtual xbool                        IsNodesModifiedImpl()const override;
public:
	//for lua side
	static XEInstanceManagerBlendRuntime*GetInstanceManagerBlend();
};


//runtime only.
class XEInstanceManagerBlendRuntime
	: public XEInstanceManagerBlend
	, public XESingleton<XEInstanceManagerBlendRuntime>
{
};

#if X_PLATFORM_WIN_DESKTOP
//editing only.
class XEInstanceManagerBlendEditing
	: public XEInstanceManagerBlend
	, public XESingleton<XEInstanceManagerBlendEditing>
{
};
#endif

#endif // _XE_BLEND_MANAGER_H
