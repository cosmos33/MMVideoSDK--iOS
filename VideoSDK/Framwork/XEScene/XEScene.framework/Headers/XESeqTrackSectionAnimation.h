/******************************************************************************

@File         XESeqTrackSectionAnimation.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_TRACK_SECTION_ANIMATION_H
#define XE_TRACK_SECTION_ANIMATION_H
#include "XETrackSection.h"
#include "XESeqSingleAnimation.h"

class XESeqTrackSectionAnimationInstance;
class XEAnimBlendLayer;
class XESeqBindingActor;
class XELayersAnimaPlay;

class XESeqTrackSectionAnimation 
	: public XETrackSection
	, public XESeqSingleAnimation
{
	friend class XESeqTrackSectionAnimationInstance;
public:
	XESeqTrackSectionAnimation();
	virtual ~XESeqTrackSectionAnimation();

public:
	struct MetaBlendData
	{
		XString strAssetPath;
		MetaSegmentList metaDataList;
	};
	typedef XArray<MetaBlendData>  MetaBlendDataList;

public:
	virtual void                         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                  Serialize(XMLElement* pEleParent)override;
public:
	virtual xbool						 AcceptAnimation(const XString& path, XESeqTrackSectionAnimationInstance* pIns);
	virtual void						 UpdateCurActiveMetaData(xfloat32 fCurTime);
	virtual void						 UpdateCurActiveMetaData();
	virtual xbool						 ExpandSegmentEndTime(xint32 nMetaIndex, xint32 nDeltaTime);//treated as a whole.
	virtual xbool						 ClipSegmentStartTime(xint32 nMetaIndex, xint32 nDeltaTime, XESeqTrackSectionAnimationInstance* pIns);//treated as a whole.
	virtual xbool						 MoveSegment(xint32 nMetaIndex, xint32 nDeltaTime);
	virtual xbool                        SetOffsetStartTime(xint32 nMetaIndex, xint32 nOffsetTime);//will be applied to all-segments, to calculate the splitting positions.
	virtual xbool                        SetOffsetEndTime(xint32 nMetaIndex, xint32 nOffsetTime);//will be applied to all-segments, to calculate the splitting positions.
	virtual xbool                        SetSegmentPlayRate(xint32 nMetaIndex, xfloat32 fPlayRate);
	virtual xbool                        SetSegmentActive(xint32 nMetaIndex, xbool bActive);
	virtual xbool                        SplitToSegments(xint32 nMetaIndex, xint32 nSplitTimePos, XESeqTrackSectionAnimationInstance* pIns);
	virtual xbool                        RemoveSegment(xint32 nMetaIndex);
	
	virtual void						 SetCurActiveIndex(xint32 nIndex){ m_nCurActiveIndex = nIndex; }
	virtual xint32						 GetCurActiveIndex(){ return m_nCurActiveIndex; }

	virtual void						 CreateSubWeightTrack(XETreeNode::Manager* pNodeMgr); //Weight track.
	virtual XETrackBase*				 GetTrackWeight(){ return m_pTrackWeight; }

	//virtual void						 SetAnimBlendLayer(XEAnimBlendLayer* pLayer){ m_pAnimBlendLayer = pLayer; }
	XEAnimBlendLayer*					 GetAnimBlendLayer();

	XESeqBindingActor*					 GetBindingActor();

	void								 AddMetaSegmentData(XESeqTrackSectionAnimation* pAnim);
	void								 RemoveMetaSegmentData(const XString& strPath);
	void								 RemoveMetaSegmentData(xint32 nIndex);
	const MetaBlendDataList&			 GetMetaBlendDataList(){ return m_vMetaBlendData; }
	xint32								 GetMetaBlendDataListNum(){ return m_vMetaBlendData.Num(); }
	void								 ReleaseBlendDataList();
	xfloat32							 GetMinStartTime(); // the min of m_vMetaBlendData
	xfloat32							 GetMaxEndTime();// the max of m_vMetaBlendData
	void								 UpdateAreaStartEndTime(xfloat32 fMinStartTime);

	void								 SetAnimPlayer(XELayersAnimaPlay* pPlayer);
	XELayersAnimaPlay*					 GetAnimPlayer();

	void								 SetAllSeqLayerMinStartTime(xfloat32 fMin){ m_fMinStartTime = fMin; };
	xfloat32							 GetAllSeqLayerMinStartTime(){ return m_fMinStartTime; }

	//void								 SetIsMontageTrack(xbool bMontage){ m_bIsMontageTrack = bMontage; }
	xbool								 GetIsMontageTrack();

	xbool								 IsContainPlayTime(xfloat32 fCurTime);

	static void							 UpdateLayersStartEndTime(XESeqTrackSectionAnimation* pNodel);
protected:
	void								 SerializeMetaData(XMLElement* pEleNode, const MetaData& metaData);
	void								 DerializeMetaData(const XMLElement* pEleNode, MetaData& metaData);
	void								 DerializeVersion_1_0(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL);
	void								 DerializeVersion_2_0(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL);

	void								 UpdateCurActiveIndex();
	virtual void						 UpdateCurMetaData();
	void								 AddBlendData(const MetaBlendData& data);
public:
	XE_USER_NODE_CAST(XESeqTrackSectionAnimation)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	XString		          m_strLayerPathName; //layer name.
protected:				                 
	XETrackBase*						 m_pTrackWeight;
	//XEAnimBlendLayer*					 m_pAnimBlendLayer; 

	MetaBlendDataList					 m_vMetaBlendData;
	xint32								 m_nCurActiveIndex; //cur active array index.
	XELayersAnimaPlay*					 m_pAnimPlayer;
	xfloat32							 m_fMinStartTime;//all seq layer.
	//xbool								 m_bIsMontageTrack;//montage or seq track.
	XString								 m_strTrackVersion;
	static xuint32                       m_nLayerAutoAssignedID;//compatible with old version
};

#endif // XE_TRACK_SECTION_ANIMATION_H
