/******************************************************************************

@File         XETrackBase.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_H
#define XE_TRACK_H
#include "XEKeyframe.h"

//track is a series of data containers.
class XETrackBase 
	: public XEUserNode
{
public:
	XETrackBase();
	virtual ~XETrackBase();
public:
	virtual void           Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*    Serialize(XMLElement* pEleParent)override;
	virtual void           Release() override;
	virtual xbool          GetOutValueForInVal(xint32 nMicroSecond, void* pOutVal){ return xfalse; }//output value for input value.
	virtual XEKeyframeBase*GetOutKeyframeForInVal(xint32 nMicrosecond){ return NULL; }//the same to the upper.
	virtual void           SyncSortKeyframes();
public:					  
	xbool                  RemoveKeyframe(xint32 nTimestamp, XETreeNode::Manager* pNodeMgr);
	XETrackBase*           CreateSubTrack(const XString& szTrackType, XETreeNode::Manager* pNodeMgr);
	XEKeyframeBase*        GetUpperboundKeyframe(xint32 nTimestamp);
	XEKeyframeBase*        GetLowerBoundKeyframe(xint32 nTimestamp);
	XEKeyframeBase*        GetKeyframe(xint32 nTimestamp);
	X_FORCEINLINE xbool    IsDeletable()const{ return m_bDeletable; }
	X_FORCEINLINE void     SetDeletable(xbool bSet){ m_bDeletable = bSet; }
	
	template<typename T>  
	XEKeyframeData<T>*         CreateKeyframe(XETreeNode::Manager* pNodeMgr);
	template<typename T>
	XEKeyframeCurve<T>*    CreateKeyframeCurve(XETreeNode::Manager* pNodeMgr);
	static xint32          SortKeyframes(XETreeNode* const* pLhs, XETreeNode* const* pRhs);
	static XEKeyframeBase* GetUpperboundSortKeyframe(const NodeList& sortList,xint32 nTimestamp);
	static XEKeyframeBase* GetLowerboundSortKeyframe(const NodeList& sortList, xint32 nTimestamp);
	static xbool           SetChildrenTrackDeletable(XEUserNode* pParentNode, const XString& szTrackName, xbool bDeletable = xtrue);
protected:
	xint32                 m_nStartTime;//>=0
	xint32                 m_nEndTime;//could be set if it is a section track.
	xbool                  m_bDeletable;//indicate whether could be deleted or not.(by outer)
	NodeList               m_lsSortKeyframe;
public:
	XE_USER_NODE_CAST(XETrackBase)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

template<typename T> 
XEKeyframeData<T>* XETrackBase::CreateKeyframe(XETreeNode::Manager* pNodeMgr)
{
	//add to child.
	if (NULL == pNodeMgr)
		return NULL;
	if (IXEUserNodeFactory* pFactory = XEUserNodeFactoryManager::GetInstance()->GetFactory(XEKeyframeData<T>::NODE_TYPENAME))
	{
		if (XEUserNode* pUserNode = pFactory->CreateUserNode(this))
		{
			if (XEKeyframeData<T>* pKeyframe = pUserNode->CastToUserNode<XEKeyframeData<T>>())
			{
				//key-frame is the point datas.
				if (AddChild(pNodeMgr, pKeyframe))
					return pKeyframe;//don't need to re-sort here.
				else
					X_SAFEDELETE(pKeyframe);
			}
			else
				X_SAFEDELETE(pUserNode);
		}
	}
	return NULL;
}

template<typename T>
XEKeyframeCurve<T>* XETrackBase::CreateKeyframeCurve(XETreeNode::Manager* pNodeMgr)
{
	//add to child.
	if (NULL == pNodeMgr)
		return NULL;
	if (IXEUserNodeFactory* pFactory = XEUserNodeFactoryManager::GetInstance()->GetFactory(XEKeyframeCurve<T>::NODE_TYPENAME))
	{
		if (XEUserNode* pUserNode = pFactory->CreateUserNode(this))
		{
			if (XEKeyframeCurve<T>* pKeyframe = pUserNode->CastToUserNode<XEKeyframeCurve<T>>())
			{
				//key-frame is the point datas.
				if (AddChild(pNodeMgr, pKeyframe))
					return pKeyframe;//don't need to re-sort here.
				else
					X_SAFEDELETE(pKeyframe);
			}
			else
				X_SAFEDELETE(pUserNode);
		}
	}
	return NULL;
}
#endif // XE_TRACK_H
