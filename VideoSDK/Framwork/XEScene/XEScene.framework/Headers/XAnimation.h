#ifndef _XANIMATION_H_
#define _XANIMATION_H_

#include "XMemBase.h"
#include "XRefCount.h"

class XFileBase;
class XSkeleton;
struct XSkeletonMap;
class XSkeletonMask;
struct XAnimParam;
class XFullPose;
class XBaseTM;
class XPose;
struct MorphTrackModelLinker;
struct XSkinModelBlendShapeWeight;
class XModel;

enum AnimationType
{
	ANIM_TYPE_SEQUENCE,
	ANIM_TYPE_NUM
};

enum PoseType
{
	POSE_TYPE_NORMAL,
	POSE_TYPE_DIFF,
};

struct SampleParam
{
    SampleParam(const XFullPose& sourcePose, const XSkeletonMask& mask) 
    : SourcePose(sourcePose)
    , Bonemask(mask)
	, fCurTime(0.0f)
	, fPreTime(0.0f)
    , fPreNormalizedTime(0.0f)
    , PlayRate(1.0f)
	, AnimParam(NULL)
    {}

	const XFullPose&		SourcePose;
	const XSkeletonMask&    Bonemask;
    xfloat32				fCurTime;
    xfloat32				fPreTime;
    xfloat32				fPreNormalizedTime;
    xfloat32				PlayRate;
    XAnimParam*				AnimParam;
};

struct SampleOutput
{
	SampleOutput();
	~SampleOutput();
	XPose*		OutputPose;
	XPose*		OutputSpeed;
	xfloat32	OutNormlizedTime;
};

struct BlendShapeSampleParam
{
	xfloat32        fCurTime;
	xfloat32        fPreTime;
};

class IXAnimationBase : public XMemBase, public XRefCount
{
public:
	virtual void					Release();
	virtual bool					Save(XFileBase* pFile) = 0;
	virtual bool					Load(XFileBase* pFile, bool bReload) = 0;
	virtual const xchar*			GetFilename() const = 0;
	virtual xint32					GetAnimationType() const = 0;
	virtual PoseType				GetSampleType() const = 0;
	virtual xfloat32				GetStartTime() const = 0;
	virtual xfloat32				GetTimeLength() const = 0;

	virtual bool					HasPoseTrack() const = 0;
	virtual bool					HasMorphTrack() const = 0;

	virtual void					SamplePose(const SampleParam& param, const XSkeletonMap& skeletonMap, SampleOutput& sampleOutput) = 0;
	virtual void					SampleBone(xint32 boneName, const SampleParam& param, const XSkeletonMap& skeletonMap, XBaseTM& out) {}
	virtual void					SampleMorph(const BlendShapeSampleParam& param, const MorphTrackModelLinker& modelLinker, XSkinModelBlendShapeWeight& sampleOutput) const = 0;

	virtual bool					BuildSkeletonMap(const XSkeleton* pSkeleton, XSkeletonMap& skeltonMap) const = 0;
	virtual MorphTrackModelLinker*	CreateMorphModelLinker(const XModel* targetModel) const = 0;

protected:
									IXAnimationBase(){}
	virtual							~IXAnimationBase(){}
	friend class					XAnimationManager;
};

class IXAnimationManager
{
public:
    ~IXAnimationManager() {}

    virtual bool                Init() = 0;
    virtual void                Release() = 0;

    virtual IXAnimationBase*	LoadAnimation(const xchar* szFile) = 0;
    virtual IXAnimationBase*	ReloadAnimation(const xchar* szFile) = 0;
    virtual IXAnimationBase*	CreateAnimation(const xchar* szFile, xint32 type) = 0;
    virtual bool				ReleaseAnimation(IXAnimationBase* pAsset) = 0;
    virtual bool				SaveAnimation(IXAnimationBase* pAsset, const xchar* szName = NULL) = 0;
	virtual xbool				IsAnimationLoaded(const xchar* szFile) = 0;
};

extern IXAnimationManager* g_pXAnimationManager;

#endif
