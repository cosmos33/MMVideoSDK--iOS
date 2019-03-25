/******************************************************************************
@File         XPinchFaceControl.h

@Version       1.0

@Created      2017, 8, 1

@Description

@HISTORY:
******************************************************************************/


#ifndef _XPINCHEDFACE_CONTROL_H_
#define _XPINCHEDFACE_CONTROL_H_

#include "XHashTable.h"
#include "XModelInstance.h"
#include "XBoneController.h"
#include "XXMLExtendTool.h"


struct XPFCtrlBone
{
	
	XPFCtrlBone() : strBoneName(""), vAxisRatio(0.0f) {}

	XString			strBoneName;
	XVECTOR3		vAxisRatio;
};

struct XPFCtrlElement
{
	enum XPFCtrlType { XPFC_Trans = 0, XPFC_Scale, XPFC_Rotate, XPFC_Num };
	XPFCtrlElement() : strName(""), strDesc(""), eType(XPFC_Trans) {}

	XString					strName;
	XString					strDesc;
	XPFCtrlType				eType;
	XArray<XPFCtrlBone>		vCtrlBone;
};

typedef XHashTable<XString, XPFCtrlElement> PFCtrlEleHashMap;
// class XPinchFaceSetting
// {
// public:
// 														XPinchFaceSetting();
// 	virtual												~XPinchFaceSetting();
// 	xbool												Load(const XString &strFilePath);
// 
// 	inline const PFCtrlEleHashMap&						GetCtrlElement() const { return m_mControlElement; }
// 
// protected:
// 
// 	void												Clear();
// 	xbool												LoadVersion0(tinyxml2_XEngine::XMLElement* pRootNode);
// 	void												SplitString(const xchar *pChar, const xchar Key, XArray<XString> &vRet);
// 
// 	PFCtrlEleHashMap									m_mControlElement;
// };



//  XPinchFaceControl

struct XPinchParam
{
	XPinchParam() : strName(""), fValue(0.0f){}
	XString strName;
	xfloat32 fValue;  // 单位 厘米、角度值
};


class XPinchFaceControl
{
public:
									XPinchFaceControl(IXModelInstance *pIns);
	virtual							~XPinchFaceControl();

	void							SetPinchParams(const XArray<XPinchParam> &vParam);
	xbool							SetPinchParam(const XPinchParam &Param);
	xbool							GetPinchParamValue(const XString &strName, XPinchParam &Param);
//	void							LoadSettingFile(const XString &strFileName);
//	inline const XPinchFaceSetting&	GetPinchFaceSetting() { return m_Setting; }
	void							SetPinchFaceCtrElem(const PFCtrlEleHashMap &ctrEleMap);
	inline const PFCtrlEleHashMap&	GetPinchFaceCtrElem() { return m_mPinchFCtrlEleMap; }
	xbool							IsPinchElementEffective(const XString& strPinchEleName);

protected:
	void							GenerateBoneIndexBySetting();	
	void							ReleaseController();	
	void							ComputePinchValueBySameController(const XBoneWorldMatController *pController, XPFCtrlElement::XPFCtrlType eType, XVECTOR3 &vRet);

// 	XString							m_strSettingFile;
// 	XPinchFaceSetting				m_Setting;
	PFCtrlEleHashMap				m_mPinchFCtrlEleMap;

	IXModelInstance					*m_pSkinModelIns;

	struct BoneIndex
	{
		BoneIndex() :strBoneName(""), pController(NULL){}
		XString strBoneName;
		XPFCtrlBone BoneCtr;
		XBoneWorldMatController *pController;
	};

	struct CtrEle
	{
		CtrEle(): strName(""), eType(XPFCtrlElement::XPFC_Trans), fParamValue(0.0f) {}

		XString strName;
		XPFCtrlElement::XPFCtrlType	eType;
		xfloat32 fParamValue;	// 单位厘米
		XArray<BoneIndex> vBone;
	};

	typedef XHashTable<XString, XBoneWorldMatController*> BoneControllerMap;
	typedef XHashTable<XString, CtrEle> ControllerElementMap;
	BoneControllerMap					m_mBoneCtrlMap;
	ControllerElementMap				m_mControlElement;
};


#endif




