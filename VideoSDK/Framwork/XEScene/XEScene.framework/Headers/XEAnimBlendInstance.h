/******************************************************************************

@File         XEAnimBlendInstance.h

@Version       1.0

@Created      2018,4, 24

@HISTORY:     ONLY GENERATED INSTANCE OF MONTAGES.

******************************************************************************/
#ifndef XE_ANIM_BLEND_INSTANCE_H
#define XE_ANIM_BLEND_INSTANCE_H
#include "XEAnimBlendBaseInstance.h"

class XEModelComponent;
class XEAnimBlendController;
class XEMovementAttacher;
class XEWorld;
class XEActorComponent;
class XEAnimBlend;
class XEParticleSystemComponent;
class XESkeletonInstance;

class XEAnimBlendInstance
	: public XEAnimBlendBaseInstance
{
public:
	XEAnimBlendInstance(XEAnimBlend* pAnimBlend);
	virtual ~XEAnimBlendInstance();
public:
	virtual void                                  Tick(xfloat32 fInterval) override;
	virtual void                                  Release() override;
	virtual void                                  Apply() override;
	virtual Manager*                              GetNodeManager() override{ return m_pNodeManager; }
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet                   GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
public:
	xbool                                         AcceptSkinModel(XEModelComponent* pComponent);
	XEAnimBlend*                                  GetAnimBlendTemplate();
	X_FORCEINLINE XEAnimBlendController*          GetAnimBlendController(){ return m_pAnimBlendController; }
	X_EES_LINE X_FORCEINLINE const XEAnimBlendController* GetAnimBlendController() const{ return m_pAnimBlendController; }
	X_FORCEINLINE XEModelComponent*               GetModelComponent(){ return m_pModelTarget; }
	X_EES_LINE X_FORCEINLINE const XEModelComponent* GetModelComponent() const{ return m_pModelTarget; }
	X_FORCEINLINE XEMovementAttacher*             GetMovementAttacher(){ return m_pMovementAttacher; }
	X_EES_LINE X_FORCEINLINE const Manager*       GetNodeManager()const{ return m_pNodeManager; }

	void                                          AcceptWorld(XEWorld* pWorld);
	XEWorld*                                      GetWorld();
public:
	XE_USER_NODE_CAST(XEAnimBlendInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString                          NODE_TYPENAME;
protected:
	XEAnimBlendController*                        m_pAnimBlendController;
	XEMovementAttacher*                           m_pMovementAttacher;
	XEModelComponent*                             m_pModelTarget;//may have nothing.
	XETreeNode::Manager*                          m_pNodeManager;//node manager.
};

#endif // XE_ANIM_BLEND_INSTANCE_H
