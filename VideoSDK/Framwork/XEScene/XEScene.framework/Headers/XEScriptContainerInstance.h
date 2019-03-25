/******************************************************************************

@File         XEScriptContainerInstance.h

@Version       1.0

@Created      2018,9, 6

@HISTORY:

******************************************************************************/
#ifndef _XE_SCRIPT_CONTAINER_INSTANCE_H_
#define _XE_SCRIPT_CONTAINER_INSTANCE_H_
#include "XEUserNode.h"

class XEScriptContainer;
class XEScriptContainerInstance 
	: public XEUserNodeInstance
{
public:
	XEScriptContainerInstance(XEScriptContainer* pNodeTl);
	virtual ~XEScriptContainerInstance();
public:
	virtual void                                  Release() override;
	virtual Manager*                              GetNodeManager() override { return m_pNodeManager; }
	virtual void                                  Apply() override;

	XEScriptContainer*                            GetScriptContainerTemplate();
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet                   GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy)override;
#endif
public:
	void                                          AcceptHolder(void* pHolder);
	void                                          AcceptWorld(XEWorld* pWorld);// set to node manager
	XEWorld*                                      GetWorld();// comes from node manager
	static XEScriptContainerInstance*             CreateBindingInstanceFromAsset(const xchar* pAssetPath, void* pHolder, XEWorld* pWorld);//path will be fixed. ensure detach when you try to attach.
	static xbool                                  DestroyBindingScriptInstance(XEScriptContainerInstance*& pInstanceToDestroy);//pInstanceToDetach will be set to NULL.
	X_FORCEINLINE void*                           GetHolder(){ return m_pHolder; }
	//pass callback to the children(script interpreter callback-like.)
	void                                          OnHolderEntrance();
	void                                          OnHolderRelease();
	void                                          OnHolderTick(xfloat32 fIntervalMs);//in milliseconds.
	void                                          OnHolderRender(XEViewport *pViewport);
	void										  SetScriptAssetPath(const xchar* szScriptPath){ m_strFileAssetPath = szScriptPath; };
	const XString&								  GetScriptAssetPath(){ return m_strFileAssetPath; }
public:
	XE_USER_NODE_CAST(XEScriptContainerInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	Manager*                                      m_pNodeManager;
	XString                                       m_strFileAssetPath;//script asset path
	void*                                         m_pHolder;//pass to the children.
};

#endif // _XE_SCRIPT_CONTAINER_INSTANCE_H_
