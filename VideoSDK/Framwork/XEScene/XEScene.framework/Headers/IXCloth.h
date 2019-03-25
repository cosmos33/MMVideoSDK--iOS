#ifndef _IXCLOTH_H_
#define _IXCLOTH_H_

#include "XBase3DTypes.h"

enum XClothStretchType
{    
	XCST_INVALID,
	XCST_VERTICAL,    
	XCST_HORIZONTAL,  
	XCST_BENDING,     
	XCST_SHEARING   
};

struct XClothStretchConfig
{
	XClothStretchConfig()
		: fStiffness(1.0f), fStiffnessScale(1.0f), fLimit(1.0f), fCompressionLimit(1.0f){}
	xfloat32	fStiffness;
	xfloat32	fStiffnessScale;
	xfloat32	fLimit;
	xfloat32	fCompressionLimit;
};

struct XClothTetherConfig
{
	XClothTetherConfig()
		: fStiffness(1.0f), fStretchLimit(1.0f){}
	xfloat32	fStiffness;
	xfloat32	fStretchLimit;
};

struct XClothMaterial
{
	xfloat32				fStiffnessFrequency;
	xfloat32				fDamping;
	xfloat32				fDrag;
	xfloat32				fFriction;
	xfloat32				fMassScale;
	xfloat32				fSolverFrequency;
	xfloat32				fInertiaScale;
	xfloat32				fSelfCollisionThickness;
	xfloat32				fSelfCollisionStiffness;
	XClothStretchConfig		VerticleStretchConfig;
	XClothStretchConfig		HorizontalStretchConfig;
	XClothStretchConfig		BendingStretchConfig;
	XClothStretchConfig		ShearingStretchConfig;
	XClothTetherConfig		TetherConfig;
};

class IXModelInstance;
class IXCloth : public XMemBase
{
public:
	virtual ~IXCloth(){}
	virtual void				Release() = 0;
	virtual const xchar*		GetName() = 0;

	virtual xbool				IsRender() = 0;
	virtual void				SetRender(xbool bSet) = 0;
	virtual xbool				IsSimulate() = 0;
	virtual void				SetSimulate(xbool bSet) = 0;
	/**
	* 材质参数读取与设置
	*/
	virtual XClothMaterial		GetClothMaterial() = 0;
	virtual void				SetClothMaterial(const XClothMaterial& Material) = 0;
	virtual xfloat32			GetStiffnessFrequency() = 0;
	virtual void				SetStiffnessFrequency(xfloat32 fStiffnessFrequency) = 0;
	virtual XClothStretchConfig	GetStretchConfig(XClothStretchType eType) = 0;
	virtual void				SetStretchConfig(XClothStretchType eType, const XClothStretchConfig& param) = 0;	
	virtual XClothTetherConfig	GetTetherConfig() = 0;
	virtual void				SetTetherConfig(const XClothTetherConfig& config) = 0;
	virtual xfloat32			GetDamping() = 0;
	virtual void				SetDamping(xfloat32 fDamping) = 0;
	virtual xfloat32			GetDrag() = 0;
	virtual void				SetDrag(xfloat32 fDrag) = 0;
	virtual xfloat32			GetFriction() = 0;
	virtual void				SetFriction(xfloat32 fFriction) = 0;
	virtual xfloat32			GetMassScale() = 0;
	virtual void				SetMassScale(xfloat32 fMassScale) = 0;
	virtual xfloat32			GetSolverFrequency() = 0;
	virtual void				SetSolverFrequency(xfloat32 fSolverFrequency) = 0;
	virtual xfloat32			GetInertiaScale() = 0;
	virtual void				SetInertiaScale(xfloat32 fInertiaScale) = 0;
	virtual xfloat32			GetSelfCollisionThickness() = 0;
	virtual void				SetSelfCollisionThickness(xfloat32 fSelfCollisionThickness) = 0;
	virtual xfloat32			GetSelfCollisionStiffness() = 0;
	virtual void				SetSelfCollisionStiffness(xfloat32 fSelfCollisionStiffness) = 0;
	virtual xfloat32			GetExtraScale()const = 0;
	virtual void				SetExtraScale(xfloat32 fExtraScale) = 0;
	// render assist
	virtual void				SetRenderCollision(xbool bRender, const XCOLORBASE& clr = XCOLORBASE(1.0f)) = 0;
	virtual void				SetRenderNormal(xbool bRender, const XCOLORBASE& clr = XCOLORBASE(1.0f)) = 0;
	virtual void				SetRenderTangent(xbool bRender, const XCOLORBASE& clr = XCOLORBASE(1.0f)) = 0;
	virtual void				SetRenderMaxDistance(xbool bRender, const XCOLORBASE& clr = XCOLORBASE(1.0f)) = 0;
};

#endif
