/******************************************************************************

@File         XEInstanceManager.h

@Version       1.0

@Created      2018,4, 27

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_INSTANCE_MANAGER_H
#define _XE_INSTANCE_MANAGER_H
#include "XMemBase.h"
#include "XHashTable.h"
#include "XArray.h"
#include "XEUserNode.h"
#include "XEWorld.h"

//template-nodes now will be managed by the world,  deleted by world when it is destroyed.
class XEInstanceManagerBase
	:public XMemBase
{
public:
	XEInstanceManagerBase();
	virtual ~XEInstanceManagerBase();
	typedef XArray<XEUserNodeInstance*> InstanceList;
	typedef XHashTable<XEUserNode*, InstanceList> TemplateInstanceMap;
public:
	virtual XEUserNode*         CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld) = 0;//may have owner world.
	virtual XEUserNode*         GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload = xfalse) = 0;// get the template belong to the owner world.
	virtual void                Reload(const xchar* szAssetFile = NULL) = 0;//if no specific asset file, will reload all.
	virtual XEUserNodeInstance* CreateInstance(const xchar* szAssetFile, XEWorld* pOwnerWorld);
	virtual xbool               RemoveInstance(XEUserNodeInstance* pInsToRemove, xbool bReleaseMem = xtrue);
	virtual xbool               RemoveTemplate(XEUserNode* pTemplateToRemove);
	virtual void                Release();
	virtual void                SaveImpl() const{}
	virtual void                SaveAsImpl(const xchar* szPath) const{}
	virtual xbool               IsNodesModifiedImpl()const{ return xfalse; }
	static void					ReloadResource(const XArray<XString>& pathList);
	static xint32               RemoveAllTemplateInWorld(XEWorld* pWorld);//both in editor and runtime
	static void                 ReleaseAllTemplate();//both in editor and runtime
#if X_PLATFORM_WIN_DESKTOP
	//editor only.
	static void                 Save();
	static void                 SaveAs(const xchar* szPath);
	static xbool                IsNodesModified();
#endif
	
public:
	//convenient using...
	template<typename T> 
	T*     CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld);
	template<typename T>
	T*     GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload = xfalse);
	template<typename T>
	T*     CreateInstance(const xchar* szAssetFile, XEWorld* pOwnerWorld);

	InstanceList*                          GetInstanceList(XEUserNode* pTemplateNode);
	X_FORCEINLINE TemplateInstanceMap&     GetTemplateInstanceMap(){ return m_mapTemplateInstance; }
	xint32                                 RemoveTemplateInWorld(XEWorld* pWorld);

protected:
	TemplateInstanceMap      m_mapTemplateInstance;
};

template<typename T>
T* XEInstanceManagerBase::CreateTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld)
{
	if (XEUserNode* pUserNode = CreateTemplate(szAssetFile, pOwnerWorld))
		return pUserNode->CastToUserNode<T>();
	return NULL;
}

template<typename T>
T* XEInstanceManagerBase::GetTemplate(const xchar* szAssetFile, XEWorld* pOwnerWorld, xbool bReload /*= xfalse*/)
{
	if (XEUserNode* pUserNode = GetTemplate(szAssetFile, pOwnerWorld, bReload))
		return pUserNode->CastToUserNode<T>();
	return NULL;
}


template<typename T>
T* XEInstanceManagerBase::CreateInstance(const xchar* szAssetFile, XEWorld* pOwnerWorld)
{
	if (XEUserNodeInstance* pUserNodeIns = CreateInstance(szAssetFile,pOwnerWorld))
		return pUserNodeIns->CastToUserNode<T>();
	return NULL;
}

#endif // _XE_INSTANCE_MANAGER_H
