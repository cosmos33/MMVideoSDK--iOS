/******************************************************************************

@File         XEMaterialFxInstance.h

@Version       1.0

@Created      2018,10, 23

@HISTORY:

******************************************************************************/
#ifndef _XE_MATERIAL_INSTANCE_H_
#define _XE_MATERIAL_INSTANCE_H_
#include "XEUserNode.h"

class XEMaterialFx;
class XEMaterialFxInstance 
	: public XEUserNodeInstance
{
public:
	XEMaterialFxInstance(XEMaterialFx* pNodeTl);
	virtual ~XEMaterialFxInstance();
public:
	virtual void                                  Release() override;
	virtual Manager*                              GetNodeManager() override { return m_pNodeManager; }
	virtual void                                  Apply() override;
	virtual void                                  Tick(xfloat32 fInterval) override;

	XEMaterialFx*                                 GetMaterialFxTemplate();
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet                   GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy)override;
#endif
public:
	void                                          AcceptHolder(void* pHolder);
	void                                          AcceptWorld(XEWorld* pWorld);// set to node manager
	XEWorld*                                      GetWorld();// comes from node manager
	static XEMaterialFxInstance*                  CreateBindingInstanceFromAsset(const xchar* pAssetPath, void* pHolder, XEWorld* pWorld);//path will be fixed. ensure detach when you try to attach.
	static xbool                                  DestroyBindingMaterialFxInstance(XEMaterialFxInstance*& pInstanceToDestroy);//pInstanceToDetach will be set to NULL.
	X_FORCEINLINE void*                           GetHolder(){ return m_pHolder; }
public:
	XE_USER_NODE_CAST(XEMaterialFxInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	Manager*                                      m_pNodeManager;
	void*                                         m_pHolder;//pass to the children.
};

#endif // _XE_MATERIAL_INSTANCE_H_
