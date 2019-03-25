/******************************************************************************

@File         XEAnimMontageInstance.h

@Version       1.0

@Created      2018,4, 24

@HISTORY:     ONLY GENERATED INSTANCE OF MONTAGES.

******************************************************************************/
#ifndef XE_ANIM_MONTAGE_INSTANCE_H
#define XE_ANIM_MONTAGE_INSTANCE_H
#include "XEAnimMonBaseInstance.h"

class XEModelComponent;
class XEAnimMonController;
class XEMovementAttacher;
class XEWorld;
class XEActorComponent;
class XEAnimMontage;
class XEParticleSystemComponent;
class XESkeletonInstance;
class XEAnimMonElementInstance;

class XEAnimMontageInstance
	: public XEAnimMonBaseInstance
{
public:
	XEAnimMontageInstance(XEAnimMontage* pAnimMontage);
	virtual ~XEAnimMontageInstance();
public:
	virtual void                                  Tick(xfloat32 fInterval) override;
	virtual void                                  Release() override;
	virtual void                                  Apply() override;
	virtual Manager*                              GetNodeManager() override{ return m_pNodeManager; }
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet                   GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
public:
	xbool                                         AcceptSkinModel(XEModelComponent* pComponent, xbool bAttachToComponent = xtrue);
	XEAnimMontage*                                GetAnimMontageTemplate();
	void                                          AcceptWorld(XEWorld* pWorld);//set to node manager
	XEWorld*                                      GetWorld();//comes from node manager
	X_FORCEINLINE XEAnimMonController*            GetAnimMonController(){ return m_pAnimMonController; }
	X_EES_LINE X_FORCEINLINE const XEAnimMonController* GetAnimMonController() const{ return m_pAnimMonController; }
	X_FORCEINLINE XEModelComponent*               GetModelComponent(){ return m_pModelTarget; }
	X_EES_LINE X_FORCEINLINE const XEModelComponent* GetModelComponent() const{ return m_pModelTarget; }
	X_FORCEINLINE XEMovementAttacher*             GetMovementAttacher(){ return m_pMovementAttacher; }
	X_EES_LINE X_FORCEINLINE const Manager*       GetNodeManager()const{ return m_pNodeManager; }
public:
	void										  GetBindNodeIns(XETreeNode::NodeList& nl);
	XEAnimMonElementInstance*                     GetAnimMonElementInsUpper(xint32 nTime);//the most >= nearest.
public:
	XE_USER_NODE_CAST(XEAnimMontageInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString                          NODE_TYPENAME;
protected:
	XEAnimMonController*                          m_pAnimMonController;
	XEMovementAttacher*                           m_pMovementAttacher;
	XEModelComponent*                             m_pModelTarget;//may have nothing.
	XETreeNode::Manager*                          m_pNodeManager;//node manager.
};

#endif // XE_ANIM_MONTAGE_INSTANCE_H
