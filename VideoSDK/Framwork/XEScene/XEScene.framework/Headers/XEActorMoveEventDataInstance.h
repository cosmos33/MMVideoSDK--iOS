/******************************************************************************

@File         XEActorMoveEventDataInstance.h

@Version       1.0

@Created      2018, 12, 28 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_ACOTR_MOVE_EVENT_DATA_INSTANCE_H
#define XE_ACOTR_MOVE_EVENT_DATA_INSTANCE_H
#include "XEUserNode.h"
#include "XETransform.h"

class XEActorMoveEventDataInstance
	:public XEUserNodeInstance
{
public:
	XEActorMoveEventDataInstance();
	virtual ~XEActorMoveEventDataInstance();

	virtual void						Release() override;

public:
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet			GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif

	void								SetTransform(const XETransform& tf){ m_Transform = tf; }
	XETransform&						GetTransform(){ return m_Transform; }
	const XETransform&					GetTransform() const { return m_Transform; }
public:
	XE_USER_NODE_CAST(XEActorMoveEventDataInstance)
		XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
		static const XString  NODE_TYPENAME;

protected:
	XETransform							m_Transform;
};
#endif //XE_ACOTR_MOVE_EVENT_DATA_INSTANCE_H