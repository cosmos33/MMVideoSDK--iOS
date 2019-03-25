/******************************************************************************

@File         XESeqTrackSectionAnimationInstance.h

@Version       1.0

@Created      2018,5, 3

@HISTORY:

******************************************************************************/
#ifndef _XE_TRACK_SECTION_ANIMATION_INSTANCE_H_
#define _XE_TRACK_SECTION_ANIMATION_INSTANCE_H_
#include "XESeqBase.h"
#include "XEAnimatableModelComponent.h"

class XEModelComponent;
class XESeqTrackSectionAnimation;
class XEAnimBlendLayer;
class XELayersAnimaPlay;
class XAnimationSequence;
class XEAnimtionTimeArea;
class XESeqTrackSectionAnimationInstance 
	:public XESeqBaseInstance
{
public:
	XESeqTrackSectionAnimationInstance(XESeqTrackSectionAnimation* pNodeTl);
	virtual ~XESeqTrackSectionAnimationInstance();
public:
	virtual void                         SetTime(xint32 nMicrosecond) override;
	virtual void                         Apply() override;
	virtual void						 Release() override;
protected:
	void								 BuildAnimation();
	xbool								 IsCurAnimation();
	xbool								 IsCurMontage();
	void								 SetTimeMontage(XESeqTrackSectionAnimation* pNodeTl, xint32 nMicrosecond);
	void								 SetTimeSeq(XESeqTrackSectionAnimation* pNodeTl, xint32 nMicrosecond);
	xint32								 GetMontageAssetDuration();
	xint32								 GetSeqAssetDuration();
	xint32								 GetAnimationLenth(const XString& strSeqName); //sequence duration.

	void								 UpdateAreaTime(XEAnimtionTimeArea* pArea, xint32 nDeltaTime);//update areas start time and end time at cur layer.
	xbool								 IsContainPlayTime(xfloat32 fCurTime);
	static void							 GetDrawGrayAreaArray(XEUserNode* pNode, xbool bMontageFind, XArray<XVECTOR2>& arrGrayBlend, XArray<XVECTOR2>& arrGrayMontage);
	static void							 GetBlendDrawGrayAreaArray(xfloat32 fMinStartTime, xfloat32 fMaxEndTime, XArray<XVECTOR2>& arrGrayBlend, XArray<XVECTOR2>& arrGrayMontage);
	
public:
	virtual xint32						 GetAnimationDuration();
	xint32								 GetAnimationDurationWithScale(xint32 nMetaIndex);
	XEModelComponent*					 GetModelComponent();
	XESeqTrackSectionAnimation*			 GetSeqTrackSectionAnimationTemplate();
	xbool                                VerifyModelActor(XEActor* pActor);

	xbool								 AttachWeightCurveToLayer();
	xbool								 DetachWeightCurveToLayer();
	void								 SetCurAttachWeightVal(xint32 nMicrosecond, xbool bReset = xfalse);

	xint32								 GetLayerCurInterBlendType();
	void								 SetLayerInterBlendType(xint32 type);
	xint32								 GetLayerInterBlendTypeNames(XArray<XString>& arNameList);
	xint32								 GetLayerInterBlendTypeByDesc(const XString &strDesc);

	void								 AssignLayersAnimaPlayer(); //assign XELayersAnimaPlay.
	XELayersAnimaPlay*					 GetLayersAnimaPlayer();
	void								 RemoveLayer(const XString& strPath);

public:
	static void							 SpiltAnimationToNewLayer(XESeqTrackSectionAnimationInstance* pDragIns, XESeqTrackSectionAnimationInstance* pDropIns); //a new layer.
	static xbool						 SpiltAnimationToOtherLayer(XESeqTrackSectionAnimationInstance* pDragIns, XESeqTrackSectionAnimationInstance* pDropIns);//a already layer.
	static XAnimationSequence*			 LoadAnimation(const XString& strName);
	static xfloat32						 GetWeightFactor(xfloat32 fStart, xfloat32 fEnd, xfloat32 fCur, xint32 type);
	static void							 GetDrawGrayAreas(XESeqTrackSectionAnimationInstance* pIns, XArray<XVECTOR2>& arrGrayBlend, XArray<XVECTOR2>& arrGrayMontage);

public:
	XE_USER_NODE_CAST(XESeqTrackSectionAnimationInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	xint32								 m_nAnimLength;
};

#endif // _XE_TRACK_SECTION_ANIMATION_INSTANCE_H_
