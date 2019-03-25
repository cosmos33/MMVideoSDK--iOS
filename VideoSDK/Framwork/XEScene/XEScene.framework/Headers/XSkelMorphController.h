#ifndef _XSKELMORPHCONTROLLER_H_
#define _XSKELMORPHCONTROLLER_H_

#include "XSkelAnimController.h"

class IXAnimationBase;
class XModel;
struct MorphTrackModelLinker;

class XSkelBlendShapeAnimController : public XSkelAnimController
{
public:
									XSkelBlendShapeAnimController(const xchar* szName, IXAnimationBase* pAsset);
	virtual							~XSkelBlendShapeAnimController();

									X_CLASS_DEF(XSkelBlendShapeAnimController);   // fix flk for lua
	virtual void                    Update(const UpdateParam& context, XAnimInstance& instData) override;
	virtual xuint32                 Type() const override { return SKEL_BLENDSHAPE_ANIMCONTROLLER; }
	virtual void					BindSkinModel(const XModel* pSkinModel);

	virtual void					SampleSkeBlendShapeData(const UpdateParam& context, const XSkeletonMap* pSkeletonMap, IXAnimationBase* pAnimation, XAnimInstance& instData);

protected:
	MorphTrackModelLinker*			m_pMorphLinker;
	const XModel*					m_pModel;
};


#endif


