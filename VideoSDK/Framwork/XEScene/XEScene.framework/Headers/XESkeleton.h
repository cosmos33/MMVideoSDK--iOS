/******************************************************************************

@File         XESkeleton.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef _XE_SKELONTON_H
#define _XE_SKELONTON_H
#include "XEFactoryUserNodeUtil.h"
#include "XEBindSocket.h"

class XBone;
class XSkeleton;
class XEBone;
class XModel;
class XESkeleton 
	:public XEUserNode
{
public:
	typedef XArray<XEBone*> RootBoneList;
	             XESkeleton();
	virtual     ~XESkeleton();
public:
	virtual Manager*               GetNodeManager() override{ return m_pNodeManager; }
	xbool                          Initialize(const xchar* pSkeletonModelPath);//will use the model path, to search the skeleton path.
	void						   UpdatePhysicsSkeltalNodeForSkeleton();
	xint32                         GetBindSockets(XEBindSocket::BindSocketList& sockets);
	xint32                         GetSocketNames(XArray<XString>& names);
	XEBindSocket*                  GetBindSocket(const XString& sokcetName);
	XEBone*                        GetBone(const XString& boneName);
	RootBoneList                   GetRootBones();
	xbool                          IsWithTheSameSkeleton(const xchar* pSkeletonModelPath);//to test whether in the same skeleton.
	static XString                 GetSkeletonPathOfModel(const xchar* pSkeletonModelPath);
	X_FORCEINLINE const XString&   GetAssetPath()const{ return m_strSkeletonModelPath; }
	X_FORCEINLINE const XString&   GetSkeletonAssetPath()const{ return m_strSkeletonPath; }
	X_FORCEINLINE XSkeleton*       GetXSkeletonTemplate(){ return m_pSkeletonTemplate; }
	X_EES_LINE X_FORCEINLINE const XSkeleton* GetXSkeletonTemplate()const{ return m_pSkeletonTemplate; }
	X_FORCEINLINE XModel*          GetXModelTemplate(){ return m_pXModel; }
	void						   SetIsModify(xbool bModify){ m_bIsModify = bModify; }
	xbool						   GetIsModify(){ return m_bIsModify; }
	X_FORCEINLINE const XString&   GetPhyAssetPath(){ return m_strPhyAssetPath; }
	X_FORCEINLINE void			   SetPhyAssetPath(const xchar* szPhyAssetPath){ m_strPhyAssetPath = szPhyAssetPath; }


protected:
	XEBone*                        BuildBones(XBone* pXBone);
public:
	virtual void                   Release() override;
protected:
	Manager*                       m_pNodeManager;
	XSkeleton*                     m_pSkeletonTemplate;
	XString                        m_strSkeletonModelPath;
	XString                        m_strSkeletonPath;
	XModel*                        m_pXModel;
	xbool						   m_bIsModify;
	XString						   m_strPhyAssetPath;
public:
	XE_USER_NODE_CAST(XESkeleton)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};
#endif // _XE_SKELONTON_H
