/******************************************************************************

@File         XEAnimMonElementModelAnimationIns.h

@Version       1.0

@Created      2018,4, 27

@HISTORY:

******************************************************************************/
#ifndef _XE_ANIM_MON_ELEMENT_MODEL_ANIMATION_INS_H
#define _XE_ANIM_MON_ELEMENT_MODEL_ANIMATION_INS_H
#include "XEAnimMonElementInstance.h"
#include "XEEventReceiver.h"

class XEAnimMonElementModelAnimation;
class XEAnimMonElementModelAnimationIns
	: public XEAnimMonElementInstance
	, public XEEventReceiver
{
public:
	                                      XEAnimMonElementModelAnimationIns(XEAnimMonElementModelAnimation* pNodeTl);
	virtual                              ~XEAnimMonElementModelAnimationIns();
public:					                 
	xbool                                 ApplyAnimSequence();
	xint32                                GetAnimDuration();
	XEAnimMonElementModelAnimation*       GetAnimMonElementModelAnimationTempalte();
	virtual void                          SetTime(xint32 nMicrosecond) override;
	virtual void                          Apply() override;
	virtual xint32                        GetActualDuration() override;
	X_FORCEINLINE void                    SetBlendMode(xbool bSet){ m_bBlendMode = bSet; }
	X_FORCEINLINE xbool                   IsBlendMode()const{ return m_bBlendMode; }

#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet           GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
protected:
	virtual XEWorld*                      GetReceiverWorld();//the receiver channel world.
public:
	XE_USER_NODE_CAST(XEAnimMonElementModelAnimationIns)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME);
	XE_EVENT_CHANNEL_TYPE_DEF(RC_CHANNEL);
	static const XString  NODE_TYPENAME;
	static const XString  RC_CHANNEL;
protected:
	xbool                 m_bBlendMode;//[RUN-TIME]indicated that whether this animation will run in the blend mode, if it is true, will blend in the upper controller, usually is a blend-layer-controller.
};

#endif // _XE_ANIM_MON_ELEMENT_MODEL_ANIMATION_INS_H
