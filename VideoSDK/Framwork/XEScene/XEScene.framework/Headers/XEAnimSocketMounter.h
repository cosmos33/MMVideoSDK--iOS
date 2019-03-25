/******************************************************************************

@File         XEAnimSocketMounter.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_SOCKET_MOUNTER_H
#define XE_ANIM_SOCKET_MOUNTER_H
#include "XEUserNode.h"
class XEBindSocket;
class XEModelComponent;
class XEAnimSocketMounter 
	: public XEUserNode
{
	friend class XEAnimSocketMounterInstance;
public:
	XEAnimSocketMounter();
	virtual ~XEAnimSocketMounter();
	typedef XArray<XString>                       BindSocketNameList;
public:
	virtual void                                  Deserialize(const XMLElement* pEleRoot,XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                           Serialize(XMLElement* pEleParent)override;
	virtual void                                  Release() override;
	virtual Manager*                              GetNodeManager() override { return m_pNodeManager; }
public:
	xbool                                         Save();
	xbool                                         SaveAs(const XString& strAssetPath);
	void                                          Initialize(const XString& strAssetPath, const XString& strMountModelPath);

	xbool                                         BindAllXESockets();
	XEBindSocket*                                 BindXESocket(const XString& socketName);
	xbool                                         BindXESocket(XEBindSocket* pXESokcet);
	xbool                                         BindXESocket(XEBindSocket* pXESokcet, xint32 nBindIndex);//bind to the specific binding socket.
	xbool                                         UnbindXESocket(XEBindSocket* pXESocketToUnbind = NULL);//if set to NULL, means unbind all.
	xbool                                         UnbindXESocket(xint32 nBindIndex);//according to the bind index.
	XEBindSocket*                                 GetBindXESocket(xint32 nBindIndex);//according to the bind index.
	X_EES_LINE const XEBindSocket*                GetBindXESocket(xint32 nBindIndex) const;//according to the bind index.
	XEBindSocket*                                 GetBindXESocket(const XString& socketName);//by name
	XEBindSocket*                                 GetOneBindableXESocket();//return a bind-able socket.
	XEBindSocket*                                 AddNewBindSocketToSkeleton(const XString& parentName, const XString& socketName);
	xbool                                         UpdateBindSocketName(const XString& oldSocketName, const XString& newSocketName);
	
	X_FORCEINLINE BindSocketNameList&             GetBindXESocketList(){ return m_arrBindSocket; }
	X_EES_LINE X_FORCEINLINE const BindSocketNameList& GetBindXESocketList()const{ return m_arrBindSocket; }
	X_FORCEINLINE const XString&                  GetSkinModelAssetPath()const{ return m_strSkinModelAssetPath; }
	X_FORCEINLINE const XString&                  GetSkeleteonAssetPath()const{ return m_strSkeletonAssetPath; }
	X_FORCEINLINE const XString&                  GetAssetPath(){ return m_strFileAssetPath; }
	X_FORCEINLINE const XString&                  GetEditSkinModelAssetPath()const{ return m_strEditorAssetPath; }
	X_FORCEINLINE void                            SetEnableRenderBone(xbool bEnable){ m_bEnableRenderBone = bEnable; }
	X_FORCEINLINE xbool                           IsEnableRenderBone()const{ return m_bEnableRenderBone; }
	X_FORCEINLINE void                            SetModified(xbool bSet){ m_bModify = bSet; }
	X_FORCEINLINE xbool                           IsModified()const{ return m_bModify; }
	X_FORCEINLINE void                            UpdateAssetPath(const XString& strPath){ m_strFileAssetPath = strPath; }
	X_FORCEINLINE Manager*                        GetNodeManager() const { return m_pNodeManager; }
public:
	XE_USER_NODE_CAST(XEAnimSocketMounter)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	static const XString  SUFFIX;
protected:
	XString                                       m_strSkinModelAssetPath;//for matching.
	XString                                       m_strSkeletonAssetPath;//for matching.
	XString                                       m_strEditorAssetPath;//for editing.
	XString                                       m_strFileAssetPath;//self file asset path.
	xbool                                         m_bEnableRenderBone;
	XETreeNode::Manager*                          m_pNodeManager;//node manager.
	BindSocketNameList                            m_arrBindSocket;//could be bind to more than one.
	//modified?
	xbool                                         m_bModify;
};

#endif // XE_ANIM_SOCKET_MOUNTER_H
