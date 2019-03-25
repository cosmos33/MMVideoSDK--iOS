/******************************************************************************

@File         XESeqBindingCameraCutsInstance.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef _XE_SEQ_BINDING_CAMERA_CUTS_INSTANCE_H_
#define _XE_SEQ_BINDING_CAMERA_CUTS_INSTANCE_H_
#include "XESeqBase.h"

class XEActor;
class XESeqBindingCameraCuts;
class XESeqBindingCameraCutsInstance 
	:public XESeqBaseInstance
{
public:
	XESeqBindingCameraCutsInstance(XESeqBindingCameraCuts* pNodeTl);
	virtual ~XESeqBindingCameraCutsInstance();
	struct MetaDataIns
	{
		MetaDataIns() :pActor(NULL), bActive(xfalse){}
		XEActor* pActor;
		xbool    bActive;
	};
	typedef XArray<MetaDataIns>             MetaSegmentInsList;
public:
	virtual void                         SetTime(xint32 nMicrosecond) override;//in microsecond.
	virtual void                         Release() override;
	virtual void                         Apply() override;
	xbool                                VerifyCameraActor(XEActor* pCameraActor);
	XESeqBindingCameraCuts*              GetSeqBindingCameraCutsTemplate();
	void                                 ExclusiveBindingNodes(XEActor* pInCutsActor);
	xbool                                HasBindCamera(XEActor* pHolderActor);
public:
	XE_USER_NODE_CAST(XESeqBindingCameraCutsInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	MetaSegmentInsList                   m_metaSegmentIns;
};

#endif // _XE_SEQ_BINDING_CAMERA_CUTS_INSTANCE_H_
