/******************************************************************************

@File         XELayersAnimaPlay.h

@Version       1.0

@Created      2018, 6, 7

@Description  The class ids of each class in XECore

@HISTORY:

******************************************************************************/

#ifndef _XE_LAYERS_ANIMA_PLAY_H_
#define _XE_LAYERS_ANIMA_PLAY_H_

#include "XBlendShapeAnim.h"
#include "XAnimation.h"
#include "XSkelMorphController.h"
#include "XCurve.h"
#include "XClass.h"
#include "XEUtility.h"


class XEViewport;
class XEAnimTimeAreaBase
	:public XClass
{
public:
	enum eAnimTimeAreaType{ ATA_UNKNOWN, ATA_XANIMATION, ATA_MONTAGE };
	virtual							~XEAnimTimeAreaBase(){}
	virtual const xchar*            GetClassName() const override = 0;
	virtual xfloat32				GetAnimationLength() = 0;
	X_FORCEINLINE const XString&    GetAreaName() const { return m_strAreaName; }
	X_FORCEINLINE void              SetAreaName(const xchar* szName) { m_strAreaName = szName; }
	X_FORCEINLINE const XString&    GetAreaLayerName() const { return m_strLayerName; }
	X_FORCEINLINE void			    SetAreaLayerName(const XString& strName) { m_strLayerName = strName; }
	X_FORCEINLINE xfloat32          GetStartTime() const { return m_fStart; }
	X_FORCEINLINE void              SetStartTime(xfloat32 fStartTime) { m_fStart = fStartTime; }
	X_FORCEINLINE xfloat32          GetEndTime() const { return m_fEnd; }
	X_FORCEINLINE void              SetEndTime(xfloat32 fEndTime) { m_fEnd = fEndTime; }
	X_FORCEINLINE eAnimTimeAreaType GetType()const{ return m_eType; }
protected:
									XEAnimTimeAreaBase(const xchar* szName) :m_fStart(0.f), m_fEnd(0.f), m_eType(ATA_UNKNOWN), m_strAreaName(szName){}
	XString							m_strAreaName;
	XString							m_strLayerName;
	xfloat32						m_fStart;
	xfloat32						m_fEnd;
	eAnimTimeAreaType               m_eType;
};


//x-primitive animation
class XEAnimtionTimeArea
	: public XEAnimTimeAreaBase
{
	friend class XEAnimBlendLayer;
	friend class XEAnimMontageTimeArea;
public:
	virtual							~XEAnimtionTimeArea();
	virtual xfloat32				GetAnimationLength() override;
	X_CLASS_DEF(XEAnimtionTimeArea)
    X_FORCEINLINE IXAnimationBase*  GetAssertAnima() const { return m_pAssertAnima; }
	X_FORCEINLINE XSkeletonMap*     GetSkeletonMap() { return m_pSkeletonMap; }
protected:
									XEAnimtionTimeArea(const xchar* szName, IXAnimationBase *pAsset);
	void							BuildSkeMap(XSkeleton *pSkeleton);
	IXAnimationBase*				m_pAssertAnima;
	XSkeletonMap*					m_pSkeletonMap;
};

//extend, e.g montage.
class XEAnimMontageInstance;
class XEAnimMontageTimeArea
	: public XEAnimTimeAreaBase
{
	friend class XEAnimBlendLayer;
public:
	virtual							      ~XEAnimMontageTimeArea();
	virtual xfloat32				      GetAnimationLength() override;
	X_CLASS_DEF(XEAnimMontageTimeArea)
	X_FORCEINLINE XEAnimMontageInstance*  GetMontageInstance() const { return m_pAnimMontageIns; }
	XEAnimtionTimeArea*                   GetAnimTimeAreaByName(const xchar* szName);
	void                                  BindSkeleton(XSkeleton* pSkeleton);//optional for changing the skeleton.
protected:
	                                      XEAnimMontageTimeArea(const xchar* szName, XSkeleton* pSkeleton, XEAnimMontageInstance *pAsset);
	XEAnimMontageInstance*                m_pAnimMontageIns;
	XSkeleton*                            m_pSkeleton;
	XArray<XEAnimtionTimeArea*>			  m_vPrimitiveArea;//primitive animations
private:
	class _TickRenderWorker :public XEUtility::XEDelayDestroyer
	{
	public:
		_TickRenderWorker(XEAnimMontageTimeArea* ata) :bDone(xfalse), _ata(ata){}
		virtual xbool ShouldBeDeleted() { return bDone; }
		virtual void  Release(){ _ata = NULL; bDone = xtrue; }
		virtual void  Tick(xfloat32 fDel);
		virtual void  Render(XEViewport* pViewport);
		xbool bDone;
		XEAnimMontageTimeArea* _ata;
	};
	_TickRenderWorker*                   m_pTickRenderWorker;
};

class XEModelComponent;
class XEAnimBlendLayer : public XSkelBlendShapeAnimController
{
public:
	enum  EInterBlendType
	{
		EIBT_INVAlID = 0,
		EIBT_LINEAR,
		EIBT_SIN_IN,
		EIBT_SIN_OUT,
		EIBT_SIN_IN_OUT,		
		EIBT_NUM,
	};

	XString								GetBlendTypeDesc(EInterBlendType etype);
	EInterBlendType						GetBlendTypeByDesc(const XString &strDesc);
	xint32								GetBlendTypeCount();

	static xfloat32					    ComputeLinearFactor(xfloat32 fStart, xfloat32 fEnd, xfloat32 fCur, EInterBlendType eType);

public:
										XEAnimBlendLayer(const xchar* szName, IXAnimationBase* pAsset = NULL);
	virtual								~XEAnimBlendLayer();
	virtual void						Update(const UpdateParam& context, XAnimInstance& instData) override;
	virtual xfloat32					GetStartTime() const override;
	virtual xfloat32					GetEndTime() const override;	
	virtual void						SetAnimation(IXAnimationBase* pAnimation) override {};
	virtual void						BindSkeleton(XSkeleton* pSkeleton) override;

	X_FORCEINLINE void                  SetStartTime(xfloat32 fTime){ m_fStart = fTime; }
	X_FORCEINLINE void                  SetEndTime(xfloat32 fTime){ m_fEnd = fTime; }

	/*
	notice : pAsset must be a newly loaded by g_pXAnimationManager::LoadAnimation, Because when XEAnimBlendLayer destructed, it will be released
	*/
	// AddRef
	XEAnimtionTimeArea*					AddAnimationAsset(const xchar* szName, IXAnimationBase* pAsset);
	XEAnimMontageTimeArea*              AddMontageAsset(const xchar* szName, XEModelComponent* pModelComponent, const xchar* pAssetPath);

	/*
	notice: The animation entered when construction function, can't be remove
	*/
	xbool								RemoveAnimationAsset(const xchar* szName);


	//=> change XEAnimtionTimeArea into XEAnimTimeAreaBase 
	XEAnimTimeAreaBase*                 GetTimeAreaByName(const xchar* szName);
	X_FORCEINLINE xint32				GetTimeAreaNum() const { return m_vAnimation.Num(); }
	XEAnimTimeAreaBase*					GetTimeAreaByIndex(xint32 nIndex) { return (nIndex < m_vAnimation.Num()) ? m_vAnimation[nIndex] : NULL; }


	X_FORCEINLINE XInterpCurveFloat*	GetWeightCurve() { return &m_WeightCurve; }
	X_FORCEINLINE void					SetInterBlendType(EInterBlendType eType) { m_eInterBlendType = eType; }
	X_FORCEINLINE EInterBlendType		GetInterBlendType() const { return m_eInterBlendType; }

	void								UpdateLayerStartEndTime();

	void								AttachWeightCurve(XInterpCurveFloat* pCurve){ m_pAttachWeightCurve = pCurve; }
	void								DetachWeightCurve(){ m_pAttachWeightCurve = NULL; }
	void								SetCurAttachWeight(xfloat32 fWeight){ m_fCurAttachWeight = fWeight; }
protected:
	void								Clear();
	void								BlendInterAnimation(const UpdateParam& context, XAnimInstance& instData);
	void								SampleAnimation(const UpdateParam& context, XEAnimTimeAreaBase* pArea, XAnimInstance& instData);


	XArray<XEAnimTimeAreaBase*>			m_vAnimation;
	XInterpCurveFloat					m_WeightCurve;
	XInterpCurveFloat*					m_pAttachWeightCurve; //for sequence editor.
	EInterBlendType						m_eInterBlendType;

	xfloat32							m_fStart;
	xfloat32							m_fEnd;

	xfloat32							m_fCurAttachWeight;
};

class XELayersAnimaPlay : public XBlendShapeAnim
{
public:
	enum eExtendAnimationType{ EAT_UNKNOWN, EAT_PRIMITIVE_SEQ, EAT_MONTAGE };// to be completed with other types.
									XELayersAnimaPlay(IXModelInstance *pIns);
									XELayersAnimaPlay(XEModelComponent* pModelComponent);
	virtual							~XELayersAnimaPlay();
	virtual xint32                  AddLayer(AnimControllerType eType, const xchar* szLayerName, IXAnimationBase* pAsset) override;
	xint32                          AddLayer(eExtendAnimationType extType, const xchar* szLayerName, const xchar* szAssetPath);//extend animation format.
	void					        UpdateTimeLine();
	X_FORCEINLINE void              SetModelComponent(XEModelComponent* pComponent){ m_pModelComponent = pComponent; }
	X_FORCEINLINE XEModelComponent* GetModelComponent()const{ return m_pModelComponent; }
	X_FORCEINLINE xfloat32          GetCurrentTime()const{ return m_fCurrentTime; }
	virtual void                    RemoveLayer(xint32 nIndex) override;
	virtual void                    RemoveLayer(const xchar* szName) override;
	virtual void                    RemoveAllLayers() override;
	virtual void                    SetCurrentTime(xfloat32 fValue) override;
public:
	//optional for blending.
	xbool                           BlendAndSetTwoLayers(const xchar* layer1Name, const xchar* asset1Path, const xchar* layer2Name, const xchar* asset2Path);//in the last max 0.5s will be crossed and blend.
	xbool                           BlendAndSetTwoAreaInALayer(const xchar* layerName, const xchar* area1Name, const xchar* asset1Path, const xchar* area2Name, const xchar* asset2Path);//blend from start.
	xbool                           BlendAnimIntoCurrentTimeline(const xchar* newLayerName, const xchar* assetPath);//blend from current.
protected:
	XEModelComponent*               m_pModelComponent;//a driver for extended animations, e.g montage
	xfloat32                        m_fCurrentTime;
};


#endif


