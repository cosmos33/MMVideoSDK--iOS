/******************************************************************************

@File         XEActorMoveEventDataInstance.h

@Version       1.0

@Created      2018, 12, 29 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_SPAWN_PARTICLE_EVENT_DATA_INSTANCE_H
#define XE_SPAWN_PARTICLE_EVENT_DATA_INSTANCE_H
#include "XEUserNode.h"
#include "XETransform.h"

class XESpawnParticleEventDataInstance
	:public XEUserNodeInstance
{
public:
	XESpawnParticleEventDataInstance();
	virtual ~XESpawnParticleEventDataInstance();

	virtual void						Release() override;

public:
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet			GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif

	void								SetTransform(const XETransform& tf){ m_Transform = tf; }
	XETransform&						GetTransform(){ return m_Transform; }
	const XETransform&					GetTransform() const { return m_Transform; }
	void								SetParticleAssetPath(const XString& path){ m_strAssetPath = path; }
	XString&							GetParticleAssetPath(){ return m_strAssetPath; }
	const XString&						GetParticleAssetPath()const { return m_strAssetPath; }
public:
	XE_USER_NODE_CAST(XESpawnParticleEventDataInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

protected:
	XETransform							m_Transform;
	XString								m_strAssetPath;
};
#endif //XE_SPAWN_PARTICLE_EVENT_DATA_INSTANCE_H