/******************************************************************************

@File         XESeqTrackMaterialInsFloatParameter.h

@Version       1.0 

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_TRACK_MATERIAL_INS_FLOAT_PARAMETER_H
#define XE_SEQ_TRACK_MATERIAL_INS_FLOAT_PARAMETER_H
#include "XETrackVirtual.h"
#include "XETrackFloat.h"
#include "XEUtility.h"

class XESeqTrackMaterialInsFloatParameter 
	: public XETrackVirtual<XETrackFloat>
{
	friend class XESeqTrackMaterialInsFloatParameterInstance;
public:
	XESeqTrackMaterialInsFloatParameter();
	virtual ~XESeqTrackMaterialInsFloatParameter();
public:
	virtual void                                Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                         Serialize(XMLElement* pEleParent)override;
	virtual xbool                               GetOutValueForInVal(xint32 nMicrosecond, void* pOutVal) override;
	X_FORCEINLINE XEUtility::MaterialKey&       GetMaterialKey(){ return m_matKey; }//can be changed.
	X_FORCEINLINE XString&                      GetMaterialParamName(){ return m_szParameterName; }//can be changed.
public:
	static XETrackBase*                         SetupMaterialFloatParameterTrack(XETrackBase* pTrackParent, 
		XETreeNode::Manager* pNodeMgr, 
		const XEUtility::MaterialKey& mk, 
		xint32 nParameterIndex, 
		const xchar* pActorName, 
		const xchar* pParameterName = NULL);
public:
	XE_USER_NODE_CAST(XESeqTrackMaterialInsFloatParameter)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	XString                m_szActorName;//to find the model-instance(currently material is only used in models.)
	XString                m_szParameterName;//for displaying...
	XEUtility::MaterialKey m_matKey;
	xint32                 m_nMatParamterIndex;//the parameter may exist multi. However, this one is the single.
};

#endif // XE_SEQ_TRACK_MATERIAL_INS_FLOAT_PARAMETER_H
