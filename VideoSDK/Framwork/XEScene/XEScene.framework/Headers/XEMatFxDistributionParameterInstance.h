/******************************************************************************

@File         XEMatFxDistributionParameterInstance.h

@Version       1.0 

@Created      2018,5, 3

@HISTORY:

******************************************************************************/
#ifndef _XE_MAT_DISTRIBUTION_PARAMETER_INSTANCE_H
#define _XE_MAT_DISTRIBUTION_PARAMETER_INSTANCE_H

#include "XEUserNode.h"
#include "XEUtility.h"
#include "XCurve.h"
#include "XDistribution.h"
#include "FxProperty.h"
#include "XEVariant.h"
#include <stack>

class XEActor;
class XEMatFxDistributionParameter;
class XEMatFxDistributionParameterInstance 
	: public XEUserNodeInstance
{
public:
	XEMatFxDistributionParameterInstance(XEMatFxDistributionParameter* pNodeTl);
	virtual ~XEMatFxDistributionParameterInstance();
	enum MatFxState{ MFX_STATE_READY, MFX_STATE_PLAYING, MFX_STATE_PLAYED };
public:
	virtual void                                           Tick(xfloat32 fInterval) override;//in milliseconds.
	virtual void                                           Apply() override;
	virtual void                                           Release() override;
#if X_PLATFORM_WIN_DESKTOP
	virtual void                                           MarkApplyFromUndoCacheData(){ m_eApplyCacheMark = ACMT_UNDO; } //for apply-inner used.
	virtual void                                           MarkApplyFromRedoCacheData(){ m_eApplyCacheMark = ACMT_REDO; } //for apply-inner used.
	xbool                                                  LoadDistributionFromStackCache();
	void                                                   CacheCurrentCurve(xint32 nCachType);
	void                                                   ClearCacheCurves();
#endif
	void                                                   ClearDistribution();
	XEMatFxDistributionParameter*                          GetMatCurveParameterTemplate();
	X_FORCEINLINE void*                                    GetDistribution(){ return m_pDistribution; }
	void                                                   SetDistribution(void* pDistribution);
	//can be one of this(match to the correct type will return None-NULL)
	XRawDistributionFloat*                                 GetRawDistributionFloat();
	XRawDistributionVector*                                GetRawDistributionVector();

	//float group
	XDistributionFloatConstant*                            GetDistributionFloatConstant();
	XDistributionFloatUniform*                             GetDistributionFloatUniform();
	XDistributionFloatConstantCurve*                       GetDistributionFloatConstantCurve();
	XDistributionFloatUniformCurve*                        GetDistributionFloatUniformCurve();

	//vector group
	XDistributionVectorConstant*                           GetDistributionVectorConstant();
	XDistributionVectorUniform*                            GetDistributionVectorUniform();
	XDistributionVectorConstantCurve*                      GetDistributionVectorConstantCurve();
	XDistributionVectorUniformCurve*                       GetDistributionVectorUniformCurve();

	xbool                                                  LoadDistributionFromFile();
	xbool                                                  HasPoints();
	xbool                                                  IsColor(XVECTOR4* pColorGet = NULL);
	void                                                   ResetState();
	X_FORCEINLINE MatFxState                               GetState()const { return m_eMatFxState; }
	XEVariant                                              Eval(xfloat32 fInVal);//fInval is in the range of [0,1]

#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet                            GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy)override;
	xbool                                                  SaveDistributionToFile(const xchar* pFilePath);
	xbool                                                  RemoveCurveFile();
	xbool                                                  AddPoint(xfloat32 nInVal = 0.f);//to add a point
	xbool                                                  RemovePoint(xint32 nPointIndex = -1);//-1 will remove the tail.
	xbool                                                  RemoveAllPoints();
#endif										               
public:
	XEActor*                                               GetActorHolder();
	IXMaterialInstance*                                    GetMaterialInstance();           
	XEActorComponent*                                      GetMaterialActorComponent();
	xbool                                                  ValidActor();
public:
	XE_USER_NODE_CAST(XEMatFxDistributionParameterInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	static xbool checkItemMatch(void*, XEUtility::MaterialInfo&);
	MatFxState                                             m_eMatFxState;
	xfloat32                                               m_fMatFxRunAccTime;//time for accumulating.(ms)
	xfloat32                                               m_fMatFxRunPeriodAccTime;//time for a period accumulating.(ms)
	XEActor*                                               m_pActorHolder;//in actor only currently.
	IXMaterialInstance*                                    m_pMaterialInstance;
	xbool                                                  m_bBreathingForward;//forward or back. xfalse for back.
	union
	{
		void*                                              m_pDistribution;
		XRawDistributionFloat*                             m_pDistributionFloat;
		XRawDistributionVector*                            m_pDistributionVector;
	};
protected:
#if X_PLATFORM_WIN_DESKTOP
	//for windows only.[redo/undo for curve]
	enum ApplyCacheMarkType{ ACMT_NONE, ACMT_UNDO, ACMT_REDO};
	struct sDistributionCache
	{
		enum{ RDC_FLOAT, RDC_VECTOR };
		union
		{
			XRawDistributionFloat*                         pDistributionFloat;
			XRawDistributionVector*                        pDistributionVector;
		};
		xint32                                             nDistributionType;
	};
	std::stack<sDistributionCache>                         m_distributionCacheUndo;
	std::stack<sDistributionCache>                         m_distributionCacheRedo;
	ApplyCacheMarkType                                     m_eApplyCacheMark;
#endif
};

#endif // _XE_MAT_DISTRIBUTION_PARAMETER_INSTANCE_H
