/******************************************************************************

@File         XEBoneInstance.h

@Version       1.0

@Created      2018,4, 26

@HISTORY:

******************************************************************************/
#ifndef _XE_BONE_INSTANCE_H
#define _XE_BONE_INSTANCE_H
#include "XEUserNode.h"
#include "XETransform.h"

class XBone;//the primitive object in x-engine.
class XEBone;
class XEBoneInstance 
	:public XEUserNodeInstance
{
public:
	XEBoneInstance(XEBone* pNodeTl);
	virtual ~XEBoneInstance();
public:
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
	void                        UpdateSocket();	
public:
	X_FORCEINLINE void          SetBone(XBone* pBone){ m_pBone = pBone; }
	X_FORCEINLINE XBone*        GetBone(){ return m_pBone; }
	xint32                      GetBoneIndex();
	XEBone*                     GetBoneTemplate();
	xbool                       GetRelativeTransform(XETransform& tf) const;
	xbool                       GetAbsoluteTransform(XETransform& tf) const;
	xbool                       SetRelativeTransform(const XETransform& tf);
public:
	XE_USER_NODE_CAST(XEBoneInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	XBone*                     m_pBone;
};
#endif // _XE_BONE_INSTANCE_H
