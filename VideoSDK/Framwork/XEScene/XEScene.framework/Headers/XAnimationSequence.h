#ifndef _XANIMATIONSEQUENCE_H_
#define _XANIMATIONSEQUENCE_H_

#include "XTypes.h"
#include "XString.h"
#include "XAnimation.h"

class XFileBase;
class XSkeleton;
class IXAnimTrack;
class IXMorphTrack;

class XAnimationSequence : public IXAnimationBase
{
public:
	virtual xint32					GetAnimationType() const override;
	virtual xfloat32				GetStartTime() const override;
	virtual xfloat32				GetTimeLength() const override;

	virtual bool					HasPoseTrack() const override { return m_pTrackSet != nullptr; }
	virtual bool					HasMorphTrack() const override { return NULL != m_pMorphTrackSet; }

	virtual PoseType				GetSampleType() const override { return PoseType::POSE_TYPE_NORMAL; }
	virtual bool   					BuildSkeletonMap(const XSkeleton* pSkeleton, XSkeletonMap& skeltonMap) const override;
	virtual void					SamplePose(const SampleParam& context, const XSkeletonMap& skeletonMap, SampleOutput& sampleOutput) override;
    virtual void					SampleBone(xint32 boneId, const SampleParam& context, const XSkeletonMap& skeletonMap, XBaseTM& out) override;

	virtual MorphTrackModelLinker*	CreateMorphModelLinker(const XModel* targetModel) const override;
	virtual void					SampleMorph(const BlendShapeSampleParam& context, const MorphTrackModelLinker& modelLinker, XSkinModelBlendShapeWeight& sampleOutput) const override;


	virtual bool					Save(XFileBase* pFile) override;
	virtual bool					Load(XFileBase* pFile, bool bReload = false) override;

	virtual const xchar*			GetFilename() const override;

	void							SetBaseSkeletonName(const xchar* szName);
	const xchar*					GetBaseSkeletonName() const;

	void							SetBaseSkeleton(const XSkeleton& pSkeleton);
	XSkeleton*						GetBaseSkeleton();

	bool							SetTrackSet(IXAnimTrack* pTrack);
	IXAnimTrack*					GetTrackSet();

	bool							SetMorphTrackSet(IXMorphTrack* pTrack);
	IXMorphTrack*					GetMorphTrackSet();

	xfloat32						GetTotalTime() const;
	void							SetStartTime(xfloat32 time);
	void							SetEndTime(xfloat32 time);

	void							SetFrameRate(xfloat32 fps);
	xfloat32						GetFrameRate() const;
protected:
	XAnimationSequence(const xchar* fileName);
	~XAnimationSequence();

	bool _LoadContentsForVersion1(XFileBase* pFile, const struct AnimSequenceHeader &header, bool bReload);
	bool _LoadContentsForVersion2(XFileBase* pFile, const struct AnimSequenceHeader &header, bool bReload);
	bool _LoadContentsForVersion3(XFileBase* pFile, const struct AnimSequenceHeader &header, bool bReload);

	void                            Clear();

	friend class XAnimationManager;
private:
	struct AnimInfo
	{
		XString         BaseSkeletonName;
		XString         SequenceName;
		xfloat32		StartTime;
		xfloat32		EndTime;
		xfloat32        FrameRate;

		AnimInfo()
			: BaseSkeletonName()
			, SequenceName()
			, StartTime(0)
			, EndTime(0)
			, FrameRate(30.0f)
		{
		}
		bool            Save(XFileBase*);
		bool            Load(XFileBase*);
	};
	AnimInfo					m_Info;
	IXAnimTrack*				m_pTrackSet = NULL;
	IXMorphTrack*				m_pMorphTrackSet = NULL;
	XSkeleton*					m_pSkeleton = NULL;
	XString						m_strFilename;
};

#endif
