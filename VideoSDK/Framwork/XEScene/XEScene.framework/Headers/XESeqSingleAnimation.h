#pragma once
#include "XTypes.h"
#include "XArray.h"

class XESeqTrackSectionAnimationInstance;

class XESeqSingleAnimation
{
public:
	XESeqSingleAnimation();
	~XESeqSingleAnimation();

	public:
	//not similar to the montage meta-data at all.
	//these metadatas specific the discrete-animation-segments with the same origin-animation binded to the track.
	struct MetaData
	{
	 	MetaData() : nStartTime(0), nEndTime(0), nAnimStartOffset(0), nAnimEndOffset(0), bActive(xtrue), fPlayRate(1.f), nAddIndex(0){}
	 	xint32        nStartTime;//as a whole.
	 	xint32        nEndTime;//as a whole.
	 	xint32        nAnimStartOffset;//specific the start offset of this animation
	 	xint32        nAnimEndOffset;//specific the end offset of this animation
	 	xbool         bActive;//whether active this segment or not.
	 	xint32        nAddIndex;//no-use.
	 	xfloat32      fPlayRate;//specific the play rate of each animation-segment.
	};
	typedef XArray<MetaData> MetaSegmentList;
	 
public:
	//edit mode. may mix to an instance.
	virtual xbool								 AcceptAnimation(const XString& path, XESeqTrackSectionAnimationInstance* pIns);//could be model-sequence animations only.
	virtual xbool								 ExpandSegmentEndTime(xint32 nMetaIndex, xint32 nDeltaTime);//treated as a whole.
	virtual xbool								 ClipSegmentStartTime(xint32 nMetaIndex, xint32 nDeltaTime, XESeqTrackSectionAnimationInstance* pIns);//treated as a whole.
	virtual xbool                                SetOffsetStartTime(xint32 nMetaIndex, xint32 nOffsetTime);//will be applied to all-segments, to calculate the splitting positions.
	virtual xbool                                SetOffsetEndTime(xint32 nMetaIndex, xint32 nOffsetTime);//will be applied to all-segments, to calculate the splitting positions.
	virtual xint32                               GetFirstSegmentEndtime(xint32 nMetaIndex, XESeqTrackSectionAnimationInstance* pIns);
	virtual xint32                               GetSplitStartOffsetTime(xint32 nMetaIndex, xint32 nSplitTimePos, XESeqTrackSectionAnimationInstance* pIns);
	virtual xbool                                SetSegmentPlayRate(xint32 nMetaIndex, xfloat32 fPlayRate);
	virtual xbool								 MoveSegment(xint32 nMetaIndex, xint32 nDeltaTime);
	virtual void                                 MoveSegments(XArray<xint32>& aMetaIndexes, xint32 nDeltaTime);//must be continually and head or tail must include.
	virtual xbool                                SplitToSegments(xint32 nMetaIndex, xint32 nSplitTimePos, XESeqTrackSectionAnimationInstance* pIns);
	virtual xbool                                RemoveSegment(xint32 nMetaIndex);
	virtual xbool                                CalculateSegmentAnimationSplitPos(xint32 nMetaIndex, XArray<xint32>& aTimePositions, XESeqTrackSectionAnimationInstance* pIns);
	virtual xbool                                SetSegmentActive(xint32 nMetaIndex, xbool bActive);
	virtual xint32                               GetUpperboundMetaDataIndex(xint32 nTime);
	virtual xint32                               GetUpperboundMetaDataIndex(const MetaSegmentList& metaList, xint32 nTime);
	virtual xint32                               GetFirstUpperboundMetaDataIndex(const MetaSegmentList& metaList); //after sort, first data index.
	virtual xint32                               GetLastUpperboundMetaDataIndex(const MetaSegmentList& metaList); //after sort, end data index.
	virtual xint32                               ConvertToAnimationTime(xint32 nMetaIndex, xint32 nAtTime, XESeqTrackSectionAnimationInstance* pIns);
	virtual const MetaSegmentList&               GetSegmentList() const{ return m_metaSegments; }
	 
public:
	XString										 m_strAnimAssetPath;
protected:
	MetaSegmentList                              m_metaSegments;//segments are discrete.
};

