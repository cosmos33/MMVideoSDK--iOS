/******************************************************************************

@File         XEAnimBlendEleModelAnimation.h

@Version       1.0

@Created      2018,9, 27

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_BLEND_ELE_MODEL_ANIMATION
#define XE_ANIM_BLEND_ELE_MODEL_ANIMATION
#include "XEAnimBlendBase.h"
#include "XELayersAnimaPlay.h"

class XEAnimBlendEleModelAnimationIns;
class XEAnimBlendEleModelAnimation
	:public XEAnimBlendBase
{
	friend class XEAnimBlendEleModelAnimationIns;
public:
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
	XEAnimBlendEleModelAnimation();
	virtual                              ~XEAnimBlendEleModelAnimation();
public:	
	void                                  DerializeMetaData(const XMLElement* pEleNode, XEAnimBlendEleModelAnimation::MetaData& metaData);
	virtual void                          Deserialize(const XMLElement* pEleElement, XETreeNode::Manager* pNodeMgr = NULL)override;
	void                                  SerializeMetaData(XMLElement* pEleNode, const XEAnimBlendEleModelAnimation::MetaData& metaData);
	virtual XMLElement*                   Serialize(XMLElement* pEleParent)override;
	//void                                  UpdateAnimBlendTime();
	void                                  SetBlendInTime(xint32 fBlendInTime);
	void                                  SetBlendOutTime(xint32 fBlendOutTime);
	xint32                                GetBlendInTime();
	xint32                                GetBlendOutTime();
	xint32                                GetStartTime();
	xint32                                GetEndTime();
	/*xbool                                 SetStartTime(xint32 nStartTime);
	void                                  SetEndTime(xint32 nEndTime);*/
	xbool                                 AddAnimation(xint32 nStartTime, XEAnimBlendEleModelAnimationIns* pIns);

public:
	xbool                                ExpandSegmentEndTime(xint32 nMetaIndex, xint32 nDeltaTime);//treated as a whole.
	xbool                                ClipSegmentStartTime(xint32 nMetaIndex, xint32 nDeltaTime, XEAnimBlendEleModelAnimationIns* pIns);//treated as a whole.
	xbool                                SetOffsetStartTime(xint32 nMetaIndex, xint32 nOffsetTime);//will be applied to all-segments, to calculate the splitting positions.
	xbool                                SetOffsetEndTime(xint32 nMetaIndex, xint32 nOffsetTime);//will be applied to all-segments, to calculate the splitting positions.
	xint32                               GetFirstSegmentEndtime(xint32 nMetaIndex, XEAnimBlendEleModelAnimationIns* pIns);
	xint32                               GetSplitStartOffsetTime(xint32 nMetaIndex, xint32 nSplitTimePos, XEAnimBlendEleModelAnimationIns* pIns);
	xbool                                SetSegmentPlayRate(xint32 nMetaIndex, xfloat32 fPlayRate);
	xbool                                MoveSegment(xint32 nMetaIndex, xint32 nDeltaTime);
	void                                 MoveSegments(XArray<xint32>& aMetaIndexes, xint32 nDeltaTime);//must be continually and head or tail must include.
	xbool                                SplitToSegments(xint32 nMetaIndex, xint32 nSplitTimePos, XEAnimBlendEleModelAnimationIns* pIns);
	xbool                                RemoveSegment(xint32 nMetaIndex);
	xbool                                CalculateSegmentAnimationSplitPos(xint32 nMetaIndex, XArray<xint32>& aTimePositions, XEAnimBlendEleModelAnimationIns* pIns);
	xbool                                SetSegmentActive(xint32 nMetaIndex, xbool bActive);
	xint32                               GetUpperboundMetaDataIndex(xint32 nTime);
	xint32                               ConvertToAnimationTime(xint32 nMetaIndex, xint32 nAtTime, XEAnimBlendEleModelAnimationIns* pIns);
	X_FORCEINLINE const MetaSegmentList& GetSegmentList() const{ return m_metaSegments; }
	XString&							 GetAnimAssetPath(){ return m_strAnimAssetPath; }

public:
	XE_USER_NODE_CAST(XEAnimBlendEleModelAnimation)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	XString         m_strAnimAssetPath;
	XString         m_strBlendLayerName;
	xint32          m_nBlendInTime;
	xint32          m_nBlendOutTime;
	xint32          m_nSortIndex;
	xbool           m_bManualBlend;
	xint32          m_nManualBlendInTime;
	xint32          m_nManualBlendOutTime;
	XEAnimBlendLayer::EInterBlendType m_eBlendType;
protected:
	MetaSegmentList                      m_metaSegments;//segments are discrete.
};

#endif // XE_ANIM_BLEND_ELE_MODEL_ANIMATION
