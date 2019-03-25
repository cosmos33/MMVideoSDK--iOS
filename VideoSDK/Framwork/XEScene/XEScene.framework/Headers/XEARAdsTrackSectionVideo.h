/******************************************************************************

@File         XEARAdsTrackSectionVideo.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_SECTION_VIDEO_H
#define XE_TRACK_SECTION_VIDEO_H
#include "XETrackSection.h"

class XEARAdsTrackSectionVideoInstance;
class XEARAdsTrackSectionVideo :public XETrackSection
{
	friend class XEARAdsTrackSectionVideoInstance;
public:
	XEARAdsTrackSectionVideo();
	virtual ~XEARAdsTrackSectionVideo();
public:
	struct MetaData
	{
		MetaData() : nStartTime(0), nEndTime(0), nAnimStartOffset(0), nAnimEndOffset(0), bActive(xtrue),fPlayRate(1.f), nAddIndex(0){}
		xint32        nStartTime;
		xint32        nEndTime;
		xint32        nAnimStartOffset;
		xint32        nAnimEndOffset;
		xbool         bActive;
		xint32        nAddIndex;
		xfloat32      fPlayRate;
	};
	typedef XArray<MetaData> MetaSegmentList;
public:
	virtual void                         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                  Serialize(XMLElement* pEleParent)override;
public:
	//edit mode. may mix to an instance.
	xbool                                AcceptVideo(const XString& path, XEARAdsTrackSectionVideoInstance* pIns);//could be model-sequence animations only.
	xbool                                ExpandSegmentEndTime(xint32 nMetaIndex, xint32 nDeltaTime);//treated as a whole.
	xbool                                ClipSegmentStartTime(xint32 nMetaIndex, xint32 nDeltaTime, XEARAdsTrackSectionVideoInstance* pIns);//treated as a whole.
	xbool                                SetOffsetStartTime(xint32 nMetaIndex, xint32 nOffsetTime);//will be applied to all-segments, to calculate the splitting positions.
	xbool                                SetOffsetEndTime(xint32 nMetaIndex, xint32 nOffsetTime);//will be applied to all-segments, to calculate the splitting positions.
	xint32                               GetFirstSegmentEndtime(xint32 nMetaIndex, XEARAdsTrackSectionVideoInstance* pIns);
	xint32                               GetSplitStartOffsetTime(xint32 nMetaIndex, xint32 nSplitTimePos, XEARAdsTrackSectionVideoInstance* pIns);
	xbool                                SetSegmentPlayRate(xint32 nMetaIndex,xfloat32 fPlayRate);
	xbool                                MoveSegment(xint32 nMetaIndex, xint32 nDeltaTime);
	void                                 MoveSegments(XArray<xint32>& aMetaIndexes, xint32 nDeltaTime);//must be continually and head or tail must include.
	xbool                                SplitToSegments(xint32 nMetaIndex, xint32 nSplitTimePos, XEARAdsTrackSectionVideoInstance* pIns);
	xbool                                RemoveSegment(xint32 nMetaIndex);
	xbool                                CalculateSegmentVideoSplitPos(xint32 nMetaIndex, XArray<xint32>& aTimePositions, XEARAdsTrackSectionVideoInstance* pIns);
	xbool                                SetSegmentActive(xint32 nMetaIndex, xbool bActive);
	xint32                               GetUpperboundMetaDataIndex(xint32 nTime);
	xint32                               ConvertToVideoTime(xint32 nMetaIndex, xint32 nAtTime, XEARAdsTrackSectionVideoInstance* pIns);
	X_FORCEINLINE const MetaSegmentList& GetSegmentList() const{ return m_metaSegments; }
private:
	void                                 SerializeMetaData(XMLElement* pEleNode, const MetaData& metaData);
	void                                 DerializeMetaData(const XMLElement* pEleNode, MetaData& metaData);
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	XString                              m_strVideoAssetPath;
	xint32                               m_nStartTime = 0;
	xint32                               m_nEndTime = 0;

	xint32                               m_iVideoLength = 0;
	xfloat32                             m_fVideoFrameRatio = 0.0f;
	xint32                               m_iVideoFrames = 0;
protected:				                 
	MetaSegmentList                      m_metaSegments;//segments are discrete.
};

#endif // XE_TRACK_SECTION_VIDEO_H
