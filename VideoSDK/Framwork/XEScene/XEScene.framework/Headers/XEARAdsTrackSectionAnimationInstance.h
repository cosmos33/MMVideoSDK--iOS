/******************************************************************************

@File         XEARAdsTrackSectionAnimationInstance.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef _XE_ARADS_TRACK_SECTION_ANIMATION_INSTANCE_H_
#define _XE_ARADS_TRACK_SECTION_ANIMATION_INSTANCE_H_
#include "XEARAdsBase.h"

class XEModelComponent;
class XEARAdsTrackSectionAnimation;
class XEARAdsTrackSectionAnimationInstance 
	:public XEARAdsBaseInstance
{
public:
	XEARAdsTrackSectionAnimationInstance(XEARAdsTrackSectionAnimation* pNodeTl);
	virtual ~XEARAdsTrackSectionAnimationInstance();
public:
	virtual void                         SetTime(xint32 nMicrosecond) override;
	virtual void                         Apply() override;
protected:
	void                                 BuildAnimation();
	xbool                                IsCurAnimation();
	xint32                               m_nAnimLength;
public:
	xint32                               GetAnimationDuration();
	xint32                               GetAnimationDurationWithScale(xint32 nMetaIndex);
	XEModelComponent*                    GetModelComponent();
	XEARAdsTrackSectionAnimation*        GetARAdsTrackSectionAnimationTemplate();
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_ARADS_TRACK_SECTION_ANIMATION_INSTANCE_H_
