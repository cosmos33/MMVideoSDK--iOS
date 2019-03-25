/******************************************************************************

@File         XEARAdsTrackSectionVideoInstance.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef _XE_TRACK_SECTION_VIDEO_INSTANCE_H_
#define _XE_TRACK_SECTION_VIDEO_INSTANCE_H_
#include "XEARAdsBase.h"

class XEPrimitiveComponent;
class XEARAdsTrackSectionVideo;
class XEARAdsTrackSectionVideoInstance
	:public XEARAdsBaseInstance
{
public:
	XEARAdsTrackSectionVideoInstance(XEARAdsTrackSectionVideo* pNodeTl);
	virtual ~XEARAdsTrackSectionVideoInstance();
public:
	virtual void                         SetTime(xint32 nMicrosecond) override;
	virtual void                         Apply() override;
protected:
	void                                 BuildVideo();
	xbool                                IsCurVideo();
	xint32                               m_nAnimLength;
public:
	xint32                               GetVideoDuration();
	void                                 SetVideoDuration(xint32 timeLength);
	xint32                               GetVideoDurationWithScale(xint32 nMetaIndex);
	XEPrimitiveComponent*                GetModelComponent();
	XEARAdsTrackSectionVideo*            GetARAdsTrackSectionVideoTemplate();
public:
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#endif // _XE_TRACK_SECTION_VIDEO_INSTANCE_H_
