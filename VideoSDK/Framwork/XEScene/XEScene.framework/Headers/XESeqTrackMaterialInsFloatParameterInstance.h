/******************************************************************************

@File         XESeqTrackMaterialInsFloatParameterInstance.h

@Version       1.0 

@Created      2018,5, 3

@HISTORY:

******************************************************************************/
#ifndef _XE_SEQ_TRACK_MATERIAL_INS_FLOAT_PARAMETER_INSTANCE_H
#define _XE_SEQ_TRACK_MATERIAL_INS_FLOAT_PARAMETER_INSTANCE_H

#include "XESeqBase.h"
#include "XEUtility.h"

class XEActor;
class XESeqTrackMaterialInsFloatParameter;
class XESeqTrackMaterialInsFloatParameterInstance 
	: public XESeqBaseInstance
{
public:
	XESeqTrackMaterialInsFloatParameterInstance(XESeqTrackMaterialInsFloatParameter* pNodeTl);
	virtual ~XESeqTrackMaterialInsFloatParameterInstance();
public:
	virtual void                             SetTime(xint32 nMicrosecond) override;//in microsecond.
	virtual void                             Apply() override;
	XESeqTrackMaterialInsFloatParameter*     GetSeqTrackMaterialInsParameterTemplate();
protected:
	XEActor*                                 GetActorHolder();
	xbool                                    ValidActor();
	static xbool                             CheckMaterialParameter(void*  holder, const XEUtility::MaterialKey& mk, XSkin* sk, IXMaterialInstance* mi, XMaterialSupportMacro* msm, const XMaterialParamTypeValue& mptv, XMaterialParamDescInfo* mpdi);
public:
	XE_USER_NODE_CAST(XESeqTrackMaterialInsFloatParameterInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	XEActor*                           m_pActorHolder;

};

#endif // _XE_SEQ_TRACK_MATERIAL_INS_FLOAT_PARAMETER_INSTANCE_H
