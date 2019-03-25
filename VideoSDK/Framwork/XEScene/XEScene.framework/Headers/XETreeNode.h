/******************************************************************************

@File         XETreeNode.h

@Version       1.0

@Created      2017, 12, 27

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#pragma once

#include "XEIteratorWrapper.h"
#include "XMemBase.h"
#include "XArray.h"

// Topology shared tree-node( can be forest as well).
class XEViewport;
class XEWorld;
class XETreeNode
	:public XMemBase
{
public:
	enum AddNodeMode{ ANM_APPEND_TO_TAIL, ANM_INSERT_TO_HEAD, ANM_INSERT_TO_SPECIFIC};
	typedef XArray<XETreeNode*>		        NodeList;
	typedef IteratorWrapper<XETreeNode*>	NodeIterator;

	XETreeNode(){}
	virtual ~XETreeNode(){}
    
public:
    //linear list of the tree.
    class Manager:public XMemBase
    {
    public:
        friend class XETreeNode;
        typedef XArray<Manager*> ManagerList;
        Manager();
        virtual ~Manager();
    public:
        xbool                          AddTreeNode(XETreeNode* pNode);
        xbool                          RemoveTreeNode(XETreeNode* pNode,xbool bIncludeChild = xfalse, xbool bReleaseMemory = xtrue, xbool bReleaseNodes = xtrue);
		xbool                          RemoveSubTreeNode(XETreeNode* pRootNode,xbool bReleaseMemory = xtrue, xbool bReleaseNodes = xtrue);
		xbool                          RemoveTree(XETreeNode* pNodeContext, xbool bReleaseNodes = xtrue);
		xbool                          RemoveTreeExceptNode(XETreeNode* pNodeExcept, xbool bReleaseNodes = xtrue);
		void                           ReleaseTreedNode(XETreeNode** pNodesExcept = NULL,xint32 nNodesExceptNum = 0);
        void                           RemoveAllTreeNodes(xbool bReleaseNodes = xtrue);
        void                           SetOwnerWorld(XEWorld* pWorld);//if world is NULL, means belong to each world.
        XEWorld*                       GetOwnerWolrd();
		const XEWorld*                 GetOwnerWolrd() const;
        XETreeNode::NodeList&          GetNodeList();
		xint32                         GetNodesOfType(const XString& strNodeType, NodeList& nl, const XETreeNode* pNodeContext = NULL) const;
		XETreeNode*                    FindTreeNode(const XString& strNodeName, const XString& strNodeType, const XETreeNode* pNodeContext);
		const XETreeNode*              FindTreeNode(const XString& strNodeName, const XString& strNodeType, const XETreeNode* pNodeContext) const;

        const xbool                    HasTreeNode(const XETreeNode* pNode) const;
		virtual xbool                  NodeDelayDelete(XETreeNode* pNode) const;
    protected:
        XEWorld*                       m_pWorld;
        XETreeNode::NodeList           m_NodeList;
    };
    
public:
	xbool                              AddParent(Manager* manager, XETreeNode* parent, AddNodeMode eAppend = ANM_APPEND_TO_TAIL, int* specificIndex = NULL);
	xbool                              AddChild(Manager* manager, XETreeNode* child, AddNodeMode eAppend = ANM_APPEND_TO_TAIL, int* specificIndex = NULL);
	void                               RemoveAllChildren();
	void                               RemoveFromParent();
	xbool                              RemoveChild(XETreeNode* child);
	xbool                              RemoveParent(XETreeNode* parent);
	xbool                              HasParent() const;
	xbool                              HasChild(XETreeNode* node);
	xbool                              HasChild() const;
	xbool                              HasTreeNodeInOwnTree(const XETreeNode* node);
	xint32                             GetParentCount() const;
	xint32                             GetChildCount() const;
	xint32                             GetChildIndex(const XETreeNode* child) const;
	xint32                             GetIndex(XETreeNode* pParent) const;
	NodeIterator                       GetParentIterator() const;
	NodeIterator                       GetChildIterator() const;
	XETreeNode*                        GetRoot();
	const XETreeNode*                  GetRoot() const;
	XETreeNode*                        GetFirstParent();
	const XETreeNode*                  GetFirstParent() const;
	xint32                             TravelNode(NodeList& container, const xchar* nodetype = NULL, xbool fuzzy = xfalse, xbool recursion = xtrue);
	virtual void                       Release();
	virtual Manager*                   GetNodeManager();
public:								   
	virtual const XString&             GetNodeName()const = 0;
	virtual const XString&             GetTypeName()const = 0;

protected:
	NodeList	                       m_parent;
	NodeList	                       m_child;
};

