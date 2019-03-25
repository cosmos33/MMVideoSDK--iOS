#ifndef _XTRACKSET_H_
#define _XTRACKSET_H_

#include "XMemBase.h"
#include "XMath3D.h"

class XFileBase;
class XSkeleton;
class XPose;
struct XSkeletonMap;
struct SampleParam;

enum AnimTrackType
{
	ATT_FRAME_TRACK,
	ATT_DENSE_TRACK,
	ATT_TRACK_NUM,
	ATT_NO_TRACK = -1,
};

class IXAnimTrack : public XMemBase
{
public:
    virtual ~IXAnimTrack() {}

    virtual AnimTrackType           Type() const = 0;
    virtual bool                    Save(XFileBase* file) const = 0;
    virtual bool                    Load(XFileBase* file) = 0;
    virtual bool                    BindSkeleton(const XSkeleton* pSkeleton) = 0;
    virtual bool                    BuildSkeletonMap(const XSkeleton* pSkeleton, XSkeletonMap& skeltonMap) const = 0;
    virtual bool                    SetSkeletonMapCache(XSkeletonMap* skeltonMap) = 0;
	virtual bool					SampleTranslation(xint32 boneId, xfloat32 t, XVECTOR3& trans) const = 0;
	virtual bool					SampleScale(xint32 boneId, xfloat32 t, XVECTOR3& scale) const = 0;
	virtual bool					SampleLocalScale(xint32 boneId, xfloat32 t, XVECTOR3& scale) const = 0;
	virtual bool					SampleRotationEuler(xint32 boneId, xfloat32 t, XVECTOR3& rot) const = 0;
	virtual bool					SampleRotationQuat(xint32 boneId, xfloat32 t, XQUATERNION& rotOut) const = 0;
	virtual void					SamplePose(const SampleParam& context, XPose& OutputPose) const = 0;
	virtual void                    SamplePoseAndSpeed(const SampleParam& context, XPose& OutputPose, XPose& OutputSpeed) const = 0;
    virtual void                    RemoveRedundantKeys() = 0;
	virtual IXAnimTrack*            Clone() = 0;
};

#endif
