/******************************************************************************

@File         XEAnimBlendEleModelAnimationIns.h

@Version       1.0

@Created      2018,9, 27

@HISTORY:

******************************************************************************/
#ifndef _XE_ANIM_BLEND_ELE_MODEL_ANIMATION_INS_H
#define _XE_ANIM_BLEND_ELE_MODEL_ANIMATION_INS_H
#include "XEAnimBlendBaseInstance.h"
#include "XEEventReceiver.h"

class XEAnimBlendEleModelAnimation;
class XEAnimBlendEleModelAnimationIns
	: public XEAnimBlendBaseInstance
	, public XEEventReceiver
{
public:
	XEAnimBlendEleModelAnimationIns(XEAnimBlendEleModelAnimation* pNodeTl);
	virtual                              ~XEAnimBlendEleModelAnimationIns();
public:					                 
	xbool                                 ApplyAnimSequence();
	xint32                                GetAnimDuration();
	XEAnimBlendEleModelAnimation*         GetAnimBlendEleModelAnimationTempalte();
	void                                  SetAnimBlendTime(const xchar* pLayerName, const xchar* pPath, xfloat32 fStartTime, xfloat32 fEndTime);
	void                                  UpdateAnimBlendTime();
	virtual void                          SetTime(xint32 nMicrosecond) override;
	virtual void                          Apply() override;
	virtual xint32                        GetActualDuration() /*override*/;
	template< class T >
    T Clamp(const T X, const T Min, const T Max)
	{
		return X < Min ? Min : X < Max ? X : Max;
	}
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet           GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
protected:
	virtual XEWorld*                      GetReceiverWorld() override;//the receiver channel world.
public:
	XE_USER_NODE_CAST(XEAnimBlendEleModelAnimationIns)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME);
	XE_EVENT_CHANNEL_TYPE_DEF(RC_CHANNEL);
	static const XString  NODE_TYPENAME;
	static const XString RC_CHANNEL;
};

#endif // _XE_ANIM_BLEND_ELE_MODEL_ANIMATION_INS_H
