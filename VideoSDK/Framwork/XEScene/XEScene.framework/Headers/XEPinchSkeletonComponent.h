/******************************************************************************

@File         XEPinchSkeletonComponent.h

@Version       1.0

@Created      2018, 8, 21

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_PINCH_SKELETON_COMPONENT_H
#define _XE_PINCH_SKELETON_COMPONENT_H
#include "XModelInstance.h"
#include "XPinchFaceControl.h"
#include "XEPrimitiveComponent.h"
#include "XEUtility.h"
#define XPFSET_VERSION_0 0
#define PINCH_CFG_SUFFIX "xpc"

class XPinchFaceControl;
class XEPinchSkeletonComponent :
	public XEPrimitiveComponent
{
public:
	XEPinchSkeletonComponent();
	virtual ~XEPinchSkeletonComponent();
	virtual void                                              Render(XEViewport* pViewport) override;
	virtual void                                              Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void                                              Empty() override;
	virtual void                                              Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*                                       Serialize(XMLElement* pEleParent) override;
public:
	//pinchParamMinMax
	struct PinchParamCurMinMaxStep
	{
		PinchParamCurMinMaxStep() :fMin(-1.f), fMax(1.f), fStep(.01f), fCur(0.f){}
		xbool operator == (const PinchParamCurMinMaxStep& cmms)const{ return 0 == szPinchElementName.CompareNoCase(cmms.szPinchElementName.CStr()); }
		XString  szPinchElementName;
		xfloat32 fMin;
		xfloat32 fMax;
		xfloat32 fStep;
		xfloat32 fCur;
	};

public:											              
	xbool                                                     BindFromParent();//set config path before your binding!
	xbool                                                     Bind(IXModelInstance* pModelIns);//set config path before your binding!
	xbool                                                     Unbind();
	xbool                                                     LoadPinchParamConfig(const xchar* pSkePinchCfgPath);
	xbool                                                     ApplyPinchParamFromCfg(const xchar* pSkePinchParamInsCfgPath);//load parameter-instance from file.
	xbool                                                     ResetPinchParams(const xchar* pPinchNodeName = NULL);//if pinch node name is null ,will reset all.
	xbool                                                     SetPinchParam(const XPinchParam& pinchParam);
	xbool                                                     SetPinchParams(const XArray<XPinchParam>& pinchParams);	
	xbool                                                     GetPinchParam(const xchar* pParamName, XPinchParam &pinchParam);
	XArray<XPinchParam>										  GetPinchParamsByArray() const;
	xbool                                                     VerifyPinchNode(const xchar* pPinchNodeName);//to verify the pinch node. return xtrue if it was effective.
	xbool                                                     UpdateValueFromExistence(const xchar* pPinchNodeName = NULL);//if pinch node name is null ,will update all from existence.
	xbool                                                     SyncValueToPinchControl();	

	PinchParamCurMinMaxStep*                                  GetPinchParamCMMS(const xchar* pPinchNodeName);
	X_FORCEINLINE XArray<PinchParamCurMinMaxStep>&            GetPinchParamCMMSArray(){ return m_aPinchParamCMMS; }
	X_FORCEINLINE void                                        SetPinchParamConfigPath(const xchar* pPath){ if(pPath) m_strPinchParamCfgPath = pPath; }
	X_FORCEINLINE const xchar*                                GetPinchParamConfigPath()const{ return m_strPinchParamCfgPath.CStr(); }
	X_FORCEINLINE XPinchFaceControl*                          GetPinchControl() const{ return m_pPinchCtrol; }
	X_FORCEINLINE IXModelInstance*                            GetModelInstance() const{ return m_pModelIns; }
protected:
	virtual void                                              OnParentEmpty(const XEActorComponent* pParentComponent) override;//need to do something necessary while parent is set to empty.
public:								            
#if X_PLATFORM_WIN_DESKTOP			            
	virtual void                                              GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
	xbool                                                     SavePinchParamInstance();
#endif
public:
	XE_COMPONENT_CAST(XEPinchSkeletonComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEPinchSkeletonComponent)
	static const XString COMPONENT_TYPENAME;
protected:
	class DelayLoadBody
		:public XEUtility::XEDelayDestroyer
	{
		friend class XEPinchSkeletonComponent;
		DelayLoadBody(XEPinchSkeletonComponent* holder) :holder_(holder){}
		virtual xbool ShouldBeDeleted() override;
		virtual void  Release() override{}
		XEPinchSkeletonComponent* holder_;
	};
protected:
	XPinchFaceControl*                         m_pPinchCtrol;
	IXModelInstance*                           m_pModelIns;
	XString                                    m_strPinchParamCfgPath;
	XArray<PinchParamCurMinMaxStep>            m_aPinchParamCMMS;
};

#endif // _XE_PINCH_SKELETON_COMPONENT_H
