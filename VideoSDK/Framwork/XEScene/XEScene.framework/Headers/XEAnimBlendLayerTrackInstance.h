/******************************************************************************

@File         XEAnimBlendLayerTrackInstance.h

@Version       1.0

@Created      2018,9, 27

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_BLEND_LAYER_TRACK_INSTANCE_H
#define XE_ANIM_BLEND_LAYER_TRACK_INSTANCE_H
#include "XEAnimBlendBaseInstance.h"
#include "XEEventReceiver.h"

class XEAnimBlendLayerTrack;
class XEAnimBlendLayerTrackInstance :public XEAnimBlendBaseInstance, public XEEventReceiver
{
public:
	XEAnimBlendLayerTrackInstance(XEAnimBlendLayerTrack* pNodeTl);
	virtual ~XEAnimBlendLayerTrackInstance();
public:
	xbool                                 ApplyAnimSequence();
	xint32                                GetAnimDuration();
	XEAnimBlendLayerTrack*                GetAnimBlendLayerTempalte();
	//virtual void                          SetTime(xint32 nMicrosecond) override;
	virtual void                          Apply() override;
	virtual xint32                        GetActualDuration();
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet           GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
protected:
	virtual XEWorld*                      GetReceiverWorld();//the receiver channel world.
public:
	XE_USER_NODE_CAST(XEAnimBlendLayerTrackInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME);
	XE_EVENT_CHANNEL_TYPE_DEF(RC_CHANNEL);

	static const XString  NODE_TYPENAME;
	static const XString RC_CHANNEL;
};

#endif // XE_ANIM_BLEND_LAYER_TRACK_INSTANCE_H
