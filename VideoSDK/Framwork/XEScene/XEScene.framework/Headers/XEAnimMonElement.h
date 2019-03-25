/******************************************************************************

@File         XEAnimMonElement.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_MON_ELEMENT_H
#define XE_ANIM_MON_ELEMENT_H
#include "XEAnimMonBase.h"
//in microseconds.
class XEAnimMonElement :public XEAnimMonBase
{
public:
	struct MetaData
	{
		MetaData() :  nStartTime(0), nEndTime(0), nClipStartTime(0), nClipEndTime(0), nSortIndex(0), pNext(NULL), pPre(NULL), pUserData(NULL){}
		xint32        nStartTime;
		xint32        nEndTime;
		xint32        nClipStartTime;
		xint32        nClipEndTime;
		xint32        nSortIndex;
		mutable void* pUserData;//can be changed. even in a const environment.
		MetaData*     pNext;
		MetaData*     pPre;
	};
	typedef XArray<MetaData> MetaSegmentList;
	XEAnimMonElement();
	virtual ~XEAnimMonElement();
public:
	XE_USER_NODE_CAST(XEAnimMonElement)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	MetaSegmentList m_metaSegments;
	xint32          m_nSelectMetaDataSortIndex;
public:
	//all time is in microseconds.
	xbool                                GenerateMetaSegmentAuto(xint32 nPreMetaIndex, xint32 nEndTime, xbool bGenerateFromPreEntire = xtrue);//will generate proper segment(s)
	xint32                               GenerateMetaSegmentAutoPreview(xint32 nPreMetaIndex, xint32 nEndTime, MetaSegmentList& previewList, xbool bGenerateFromPreEntire = xtrue);//preview of generating segment(s).
	void                                 DragMetaSegments(xint32 nMetaIndexDrag, xint32 nMetaIndexBefore);
	void                                 RemoveMetaSegment(xint32 nMetaIndex);
	xint32                               GetUpperboundMetaDataIndex(xint32 nTime);
	xbool                                SetStartTime(xint32 nStartTime);
	void                                 SetEndTime(xint32 nEndTime);
	xint32                               GetClipStartTime();
	xint32                               GetClipEndTime();
	xint32                               GetStartTime();
	xint32                               GetEndTime();
	const MetaData*                      GetMetaData(xint32 nSortIndex) const;
	xbool                                ExpandSegClipStartTime(xint32 nMetaIndex, xint32 nExpandDeltaTime, xbool bAsClipMode = xtrue);//keep as the clip-start-time.
	xbool                                ExpandSegClipEndTime(xint32 nMetaIndex, xint32 nExpandDeltaTime, xbool bAsClipMode = xtrue);//keep as the clip-start-time.
	xint32                               CalcuInvalidZone(XArray<xint32>& zoneList);//2 in pairs.
	xint32								 CalcuInvalidZone(XArray<xint32>& zoneList, xint32 nStartTime, xint32 nEndTime);
	xbool                                IsInInvalidZone(xint32 nTime);
	X_FORCEINLINE void                   SelectMetaDataIndex(xint32 nSortIndex){ m_nSelectMetaDataSortIndex = nSortIndex; }
	X_FORCEINLINE xint32                 GetSelectMetaDataIndex()const{ return m_nSelectMetaDataSortIndex; }
	X_FORCEINLINE const MetaSegmentList& GetSegmentList() const{ return m_metaSegments; }
	virtual xint32                       GetDuration();
	virtual void                         Deserialize(const XMLElement* pEleElement, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                  Serialize(XMLElement* pEleParent)override;
protected:
	void                                 RebuildDoubleLinkList(MetaSegmentList* pList = NULL);
	void                                 ReAssignSortIndex();
	xbool                                SetSegStartTime(xint32 nMetaIndex, xint32 nStartTime);
	void                                 SetSegEndTime(xint32 nMetaIndex, xint32 nEndTime);
	void                                 SetSegClipStartTime(xint32 nMetaIndex, xint32 nClipStartTime);
	void                                 SetSegClipEndTime(xint32 nMetaIndex, xint32 nClipEndTime);
	xbool                                SetSegStartTime(MetaData& metaData, xint32 nStartTime);
	void                                 SetSegEndTime(MetaData& metaData, xint32 nEndTime);
	void                                 SetSegClipStartTime(MetaData& metaData, xint32 nClipStartTime);
	void                                 SetSegClipEndTime(MetaData& metaData, xint32 nClipEndTime);
};

#endif // XE_ANIM_MON_ELEMENT_H
