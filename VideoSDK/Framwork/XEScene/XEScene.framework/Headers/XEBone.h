/******************************************************************************

@File         XEBone.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef _XE_BONE_H
#define _XE_BONE_H
#include "XEUserNode.h"
#include "XETransform.h"

class XBone;
class XEBindSocket;
class XESkeleton;
class XEPhysicsSkeletalBody;
class XEBone 
	:public XEUserNode
{
public:
	XEBone();
	virtual ~XEBone();
public:
	virtual void                Deserialize(const XMLElement* pEleNode);
	virtual XMLElement*         Serialize(XMLElement* pEleParent) override;
	X_FORCEINLINE void          SetBone(XBone* pBone){ m_pBone = pBone; }
	X_FORCEINLINE XBone*        GetBone(){ return m_pBone; }
	XEBindSocket*               CreateSocket(const xchar* pFromOccupidSocketName = NULL);
	XEBindSocket*               BuildDummySocket();//from skeleton.
	void                        RemoveSocket(XEBindSocket* pSocket);
	xint32                      GetBoneIndex();

	XESkeleton*                 GetXESkeleton();

	void						RemoveBody(XEPhysicsSkeletalBody* pBody);
public:
	XE_USER_NODE_CAST(XEBone)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	static const XString  DUMMY_NAME_CONTAIN;
protected:
	XBone*                      m_pBone;//template bone
	XArray<XEUserNode*>			m_aEditSkeletalBody;
};
#endif // _XE_BONE_H
