/******************************************************************************

@File         XEUserNode.h

@Version       1.0

@Created      2018,2, 8

@HISTORY:

******************************************************************************/
#ifndef _XE_USER_NODE_H
#define _XE_USER_NODE_H

#include "XGlobalFuncs.h"
#include "XMath3D.h"
#include "XETreeNode.h"
#include "XESingleton.h"
#include "tinyxml2_XEngine.h"
#include "XRefCount.h"
#include "XClass.h"

#if X_PLATFORM_WIN_DESKTOP
#include "XEPropertyObjectBase.h"
#include "XEFactoryPropertyObjectUtil.h"
#include "XEProperty.h"
#endif

X_EEB_BEGIN
#define COMPATIBLE_USERNODE_DEPRECATED 1
X_EEB_END

using namespace tinyxml2_XEngine;
class XEWorld;
class XEUserNodeInstance;
class XEUserNode 
	: public XETreeNode
{
public:
	XEUserNode();
	virtual ~XEUserNode(){}
	typedef XArray<XEUserNode*> UserNodeList;
public:
	virtual void                            Deserialize(const XMLElement* pEleNode, XETreeNode::Manager* pNodeMgr = NULL);
	virtual XMLElement*                     Serialize(XMLElement* pEleParent);
	virtual	const XString&                  GetTypeName() const override{ return NODE_TYPENAME; }
	virtual const XString&                  GetNodeName() const override{ return m_strNodeName; }
	virtual void                            Release() override{}
	virtual XEUserNodeInstance*             SpawnNodeInstance();//may be forbidden by instance.
	virtual void                            ReverseRecover(){}//do something BEFORE detach from parent.
	virtual void                            Recover(){}//do something AFTER attach to the parent.
	virtual void                            Backup(){}//do something to backup datas.
	xbool                                   SetNodeName(const XString& strName, xbool bSameNameLimit = xtrue);
	XEUserNode*                             FindChildNode(const XString& strName, const XString& strType);
	XEUserNode*                             FindChildNode(const XString& strName);
	xbool								    HasChild(const XString& strName, xbool bRecursion) const;
	xbool								    HasChild(const XEUserNode* pNode, xbool bRecursion) const;
	XString                                 GetTypeNameWithoutAncestorPrefix();
	const XString                           GetValidNodeName(XEUserNode* pNodeContext, xbool bBaseOnUseNodeContext = xfalse);
	X_FORCEINLINE void                      SetIncludeChildren(xbool bInclude){ m_bIncludeChildren = bInclude; }
	X_FORCEINLINE xbool                     IsIncludeChildren()const{ return m_bIncludeChildren; }
	X_FORCEINLINE const xchar*              GetBindingScriptAssetPath()const{ return m_strBindingScriptAssetPath.CStr(); }
	X_FORCEINLINE void                      SetBindingScriptAssetPath(const XString& strAssetPath){ m_strBindingScriptAssetPath = strAssetPath; }
	static void                             RemoveAncestorPrefix(XString& szTypeNameWithPrefix);
#if X_PLATFORM_WIN_DESKTOP				    
	virtual XEPropertyObjectSet             GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy);
#endif	
	template<typename T>				    
	static const XArray<XString>&           GetUserNodeSimilarTypes(xbool bRefresh = xfalse);
	static const XArray<XString>&           GetUserNodeSimilarTypes(xbool bRefresh, const XString& strType);
	template<typename T>				    
	T*                                      CastToUserNode();
	template<typename T>				    
	const T*                                CastToUserNode() const;
public:
	XString m_szFilterPath;//记录自身层级
protected:
	static const XString NODE_TYPENAME;
	XString m_strNodeName;
	XString m_strBindingScriptAssetPath;
	xbool   m_bDeserialized;//has been de-serialized?
	xbool   m_bIncludeChildren;//for serializing/de-serializing.
public:
#if COMPATIBLE_USERNODE_DEPRECATED
	XString m_strDeprecatedTypeName;
#endif
};

template<typename T>
const XArray<XString>& XEUserNode::GetUserNodeSimilarTypes(xbool bRefresh )
{
	return GetUserNodeSimilarTypes(bRefresh, T::NODE_TYPENAME);
}

template<typename T>
T* XEUserNode::CastToUserNode()
{
	//only match the prefix.
	if (0 == GetTypeName().Find(T::NODE_TYPENAME))
		return static_cast<T*>(this);
	return NULL;
}

template<typename T>
const T* XEUserNode::CastToUserNode() const
{
	//only match the prefix.
	if (0 == GetTypeName().Find(T::NODE_TYPENAME))
		return static_cast<const T*>(this);
	return NULL;
}

#define XE_USER_NODE_TYPE_DEF(T) virtual const XString& GetTypeName()const override{return T;}
#define XE_USER_NODE_CAST(T) static T* Cast(XEUserNode* N){ return N?N->CastToUserNode<T>():NULL;} static XEUserNode* ReverseCast(T* N){ return N;}
#define XE_USER_NODE_CAST_OVERRIDE(T,I) static T* Cast##I(XEUserNode* N){ return N?N->CastToUserNode<T>():NULL;} static XEUserNode* ReverseCast##I(T* N){ return N;}
#define XE_USER_NODE_TYPE_STRING(T) #T

//tree for node instance.

class XEScriptContainerInstance;
class XEUserNodeInstance
	: public XEUserNode
	, public XRefCount//please use the reference carefully
{
public:
	XEUserNodeInstance(XEUserNode* pNodeTl);
	virtual ~XEUserNodeInstance(){}
public:
	XE_USER_NODE_CAST(XEUserNodeInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME);
	virtual void                            Tick(xfloat32 fInterval);
	virtual void                            Render(XEViewport* pViewport);
	virtual void                            Release() override;
	virtual void                            SetTime(xint32 nMicrosecond);//in microsecond.
	virtual void                            OnSocketUpdate(const XMATRIX4& matWorld){}//connect and bind to socket.								    
	virtual xint32                          SpawnChildrenNodeInstance(Manager* pNodeMgr);//to generate instance nodes for its children.
	virtual void                            Apply();//apply parameters from node-template.
#if X_PLATFORM_WIN_DESKTOP
	virtual void                            MarkApplyFromUndoCacheData(){} //for apply-inner used.
	virtual void                            MarkApplyFromRedoCacheData(){} //for apply-inner used.
#endif
	X_FORCEINLINE XEUserNode*               GetNodeTemplate(){ return m_pNodeTemplate; }
	X_FORCEINLINE const XEUserNode*         GetNodeTemplate()const{ return m_pNodeTemplate; }
	X_FORCEINLINE XEScriptContainerInstance*GetScriptContainerInstance(){ return m_pScriptContainerInstance; }
	X_FORCEINLINE void                      SetBindingScriptEnable(xbool bEnable){ m_bEnableBindingScript = bEnable; }
	X_FORCEINLINE xbool                     IsBindingScriptEnable()const{ return m_bEnableBindingScript; }
public:
	xbool                                   AttachBindingScriptAsset(const xchar* pAssetPath);//path will be fixed.
	void                                    DetachBindingScriptInstance();
private:
	virtual void                            Deserialize(const XMLElement* pEleNode, XETreeNode::Manager* pNodeMgr = NULL) override{ return; }//forbid!
	virtual XMLElement*                     Serialize(XMLElement* pEleParent) override{ return NULL; }//forbid!
	virtual XEUserNodeInstance*             SpawnNodeInstance() override{ return NULL; }//forbid!
protected:
	XEUserNode*                             m_pNodeTemplate;
	XEScriptContainerInstance*              m_pScriptContainerInstance;//script holder. itself is also a usernodeinstance.
	xbool                                   m_bEnableBindingScript;//enable for editing or not.
public:
	static const XString                    NODE_TYPENAME;
};

#endif // _XE_USER_NODE_H
