#ifndef _XBLENDSHAPEANIM_H_
#define _XBLENDSHAPEANIM_H_

#include "XAnimMultiLayer.h"
#include "XBlendShapeTarget.h"

class IXModelInstance;
struct XSkinModelBlendShapeWeight;

class XBlendShapeAnim : public XAnimMultiLayer
{
public:
									XBlendShapeAnim(IXModelInstance *pIns);
									~XBlendShapeAnim();	
	
	virtual void					UpdateToCurTime(const UpdateParam &ctx) override;
	virtual xint32                  AddLayer(AnimControllerType eType, const xchar* szLayerName, IXAnimationBase* pAsset) override;
protected:

	virtual	void					MergeUserMorphAndBone(){}
	xbool							BindSkinModelInstance(IXModelInstance *pIns);
	void							UpdateSkeMorphLayers(const UpdateParam& ctx);
	void							UpdateMorphWeight();
protected:
	IXModelInstance*				m_pSkinModelIns;
	XSkinModelBlendShapeWeight		m_MorphWeights;
};

void MergeToMorphWeightIfNeeded(const XAnimInstance& instData, XSkinModelBlendShapeWeight& morphWeights);

#endif


