/******************************************************************************

@File         XEMatFxCurveParameter.h

@Version       1.0 

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef _XE_MAT_DISTRIBUTION_PARAMETER_H
#define _XE_MAT_DISTRIBUTION_PARAMETER_H
#include "XCurve.h"
#include "XEUtility.h"
#include "XEUserNode.h"

//designed for applying a distribution(float/curve) for the parameters in the material instance.
//warning: type should be confirm before you add any points.
//curve will be generated in its instance.

//distribution can be a number or a curve(curve can be a single/vector3 float).

class XEMaterialFx;
class XEMatFxDistributionParameter 
	: public XEUserNode
{
	friend class XEMatFxDistributionParameterInstance;
public:
	enum MatFxLockAxesType{NONE,XY,XZ,YZ,XYZ};
	enum MatFxDistributionGroup{ DISTRIBUTION_GROUP_FLOAT, DISTRIBUTION_GROUP_VECTOR, DISTRIBUTION_GROUP_FLOAT_CONTAIN_CURVE, DISTRIBUTION_GROUP_VECTOR_CONTAIN_CURVE };
	enum MatFxPointDistribution
	{ 
		DISTRIBUTION_FLOAT_CONSTANT, DISTRIBUTION_FLOAT_CONSTANT_CURVE, DISTRIBUTION_FLOAT_UNIFORM, DISTRIBUTION_FLOAT_UNIFORM_CURVE,
		DISTRIBUTION_VECTOR_CONSTANT, DISTRIBUTION_VECTOR_CONSTANT_CURVE, DISTRIBUTION_VECTOR_UNIFORM, DISTRIBUTION_VECTOR_UNIFORM_CURVE
	};
	XEMatFxDistributionParameter();
	virtual ~XEMatFxDistributionParameter();
public:
	virtual void                                  Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                           Serialize(XMLElement* pEleParent)override;
	virtual void                                  Release() override;
public:		
	X_FORCEINLINE void                            SetEnable(xbool bEnable){ m_bEnable = bEnable; }
	X_FORCEINLINE xbool                           IsEnable()const{ return m_bEnable; }

	X_FORCEINLINE void                            SetDelayTime(xfloat32 fTime){ m_fDelayTime = fTime; }//in milliseconds. in a period.
	X_FORCEINLINE xfloat32                        GetDelayTime()const{ return m_fDelayTime; }

	X_FORCEINLINE void                            SetPointDistribution(MatFxPointDistribution mpd){ m_eDistributionType = mpd; }
	X_FORCEINLINE const MatFxPointDistribution    GetPointDistribution()const{ return m_eDistributionType; }

	void                                          SetPointDistributionGroup(MatFxDistributionGroup mdg);
	X_FORCEINLINE MatFxDistributionGroup          GetPointDistributionGroup() const{ return m_eDistributionGroup; }

	X_FORCEINLINE void                            SetDistributionFilePath(const xchar* pFilePath){ if (pFilePath) m_strDistributionFilePath = pFilePath; }
	X_FORCEINLINE const xchar*                    GetDistributionFilePath()const{ return m_strDistributionFilePath.CStr(); }

	X_FORCEINLINE void                            SetLockAxesType(xint32 nCurveIndex, MatFxLockAxesType clat){ if( 0 <= nCurveIndex && 1 >= nCurveIndex) m_eLockAxesType[nCurveIndex] = clat; }
	X_FORCEINLINE const MatFxLockAxesType         GetLockAxesType(xint32 nCurveIndex)const{ return (0 <= nCurveIndex && 1 >= nCurveIndex) ? m_eLockAxesType[nCurveIndex] : NONE; }

	X_FORCEINLINE void                            SetCurveLoop(xbool bLoop){ m_bLoop = bLoop; }
	X_FORCEINLINE xbool                           IsCurveLoop()const{ return m_bLoop; }

	X_FORCEINLINE void                            SetCurveBreating(xbool bBreathing){ m_bBreathing = bBreathing; }
	X_FORCEINLINE xbool                           IsCurveBreathing()const{ return m_bBreathing; }

	X_FORCEINLINE void                            SetCurveLoopOffset(xfloat32 fOffset){ m_fKeyOffset = fOffset; }
	X_FORCEINLINE xfloat32                        GetCurveLoopOffset()const{ return m_fKeyOffset; }

	X_FORCEINLINE void                            SetFxDurationTime(xfloat32 fDuration){ m_fDurationTime = fDuration; }
	X_FORCEINLINE xfloat32                        GetFxDurationTime()const{ return m_fDurationTime; }

	X_FORCEINLINE XString                         GetMatParamName()const{ return m_szParameterName; }
	X_FORCEINLINE void                            SetMatparamName(const xchar* pName){ if (pName) m_szParameterName = pName; }

	X_FORCEINLINE XString                         GetActorName()const{ return m_szActorName; }
	X_FORCEINLINE void                            SetActorName(const xchar* pName){ if (pName) m_szActorName = pName; }

	X_FORCEINLINE xint32                          GetComponentIndex()const{ return m_nComponentIndex; }
	X_FORCEINLINE void                            SetComponentIndex(xint32 nComponentIndex){ m_nComponentIndex = nComponentIndex; }

	X_FORCEINLINE xint32                          GetMatParamSubIndex()const{ return m_nParamSubIndex; }
	X_FORCEINLINE void                            SetMatParamSubIndex(xint32 nSubIndex){ m_nParamSubIndex = nSubIndex; }

	X_FORCEINLINE XEUtility::MaterialKey&         GetMatParamKey(){ return m_matKey; }

	xbool                                         SetMatParam(const xchar* pActorName, xint32 nComponentIndex, const xchar* pParamName, const XEUtility::MaterialKey& mk, XEWorld* pWorld, xint32 nParamSubIndex = -1);//will be determined all.

	XEMaterialFx*                                 GetMaterialFx();//parent root.
public:
	xbool                                         IsCurve();
	xbool                                         IsDistributionFloat();
	xbool                                         IsDistributionVector();
	xbool                                         IsUniform();
	xint32                                        GetDistributionTypeInGroup(XArray<MatFxPointDistribution>& enumArray, XArray<XString>* pDescArray = NULL);
	MatFxPointDistribution                        GetDistributionTypeByDesc(const xchar* pDesc);
	XString                                       GetDistributionDescByType(MatFxPointDistribution mfpd);
public:
	XE_USER_NODE_CAST(XEMatFxDistributionParameter)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

protected:
	MatFxDistributionGroup       m_eDistributionGroup;
	MatFxPointDistribution       m_eDistributionType;
	xfloat32                     m_fDelayTime;//fx delay time to take effect.(ms)
	xfloat32                     m_fDurationTime;//fx duration.(ms)
	xbool                        m_bEnable;//enable or not.
	xbool                        m_bLoop;//can be loop(curve+time)
	xbool                        m_bBreathing;//effect for simulating breathing(curves will go forward and back, like a sin/cos wave. )
	xfloat32                     m_fKeyOffset;
	MatFxLockAxesType            m_eLockAxesType[2];//xy,xz,yz,xyz( w can't be locked(a different meaning), second is for a uniform curve.)
	XString                      m_strDistributionFilePath;

protected:
	XString                      m_szActorName;//to find the model-instance(currently material is only used in models.)
	xint32                       m_nComponentIndex;
	xint32                       m_nParamSubIndex;//for some special variables, such as "Color with the Alpha(RGBA)", -1 for invalid(will use all.)
	XString                      m_szParameterName;//for displaying...
	XEUtility::MaterialKey       m_matKey;
};

#endif // _XE_MAT_DISTRIBUTION_PARAMETER_H
