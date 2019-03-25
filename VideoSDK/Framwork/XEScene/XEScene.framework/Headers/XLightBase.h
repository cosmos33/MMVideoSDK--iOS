/******************************************************************************

 @File         XLightBase.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XLight.

 @HISTORY:

******************************************************************************/
#ifndef _X_LIGHT_H_
#define _X_LIGHT_H_

#include "XTypes.h"
#include "XBase3DTypes.h"
#include "XBase3DTypes.h"
#include "XMemBase.h"
#include "XCustomGeometry.h"

class XVECTOR3;
class XMATRIX4;
class XCusAABB;
class XBaseCamera;
class IXPrimitiveBase;
class IXLightBase;

enum XLightType
{
	XLT_DIRECTION = 0,
	XLT_POINT,
	XLT_SPOT,
	XLT_ENV,
	XLT_NUM
};

struct XPointLightDesc
{
	XCOLORBASE clrColorVal;
	xfloat32 fLuminance;
	XVECTOR3 vPos;
	xfloat32 fRadius;
	xfloat32 fFallOffExponent;
	XPointLightDesc() : clrColorVal(1.0f), fLuminance(1.0f), vPos(0.0f), fRadius(10.0f), fFallOffExponent(2.0f){}
	XPointLightDesc(const XCOLORBASE &_clrColorVal, xfloat32 _fLuminance, const XVECTOR3 &_vPos,
		xfloat32 _fRadius = 30.0f, xfloat32 _fFallOffExponent = 2.0f)
		: clrColorVal(_clrColorVal), fLuminance(_fLuminance), vPos(_vPos), fRadius(_fRadius), fFallOffExponent(_fFallOffExponent){}
};

struct XSpotLightDesc
{
	XCOLORBASE clrColorVal;
	xfloat32 fLuminance;
	XVECTOR3 vPos;
	XVECTOR3 vDir;
	xfloat32 fRadius;
	xfloat32 fFallOffExponent;
	xfloat32 fConeInnerAngle;
	xfloat32 fConeOuterAngle;

	XSpotLightDesc() : clrColorVal(1.0f), fLuminance(3.0f), vPos(0.0f), vDir(0.0f, 0.0f, 1.0f), fRadius(10.0f), 
		fFallOffExponent(2.0f), fConeInnerAngle(30.0f), fConeOuterAngle(45.0f){}

	XSpotLightDesc(const XCOLORBASE &_clrColorVal, xfloat32 _fLuminance, const XVECTOR3 &_vPos, const XVECTOR3 &_vDir, 
		xfloat32 _fRadius = 30.0f, xfloat32 _fFallOffExponent = 2.0f, xfloat32 _fConeInnerAngle = 30.0f, xfloat32 _fConeOuterAngle = 40.0f) 
		: clrColorVal(_clrColorVal), fLuminance(_fLuminance), vPos(_vPos), vDir(_vDir), fRadius(_fRadius),
		fFallOffExponent(_fFallOffExponent), fConeInnerAngle(_fConeInnerAngle), fConeOuterAngle(_fConeOuterAngle){}
};


class IXLightManager : public XMemBase
{
public:
	~IXLightManager(){}

	virtual xbool			Init() = 0;
	virtual void			Release() = 0;

	virtual IXLightBase*	CreateDirectionLight(const XVECTOR3& vDir, const XCOLORBASE& clrColorVal, xfloat32 fLuminance) = 0;
	virtual IXLightBase*	CreateEnvironmentLight(	const XCOLORBASE& clrColorVal, xfloat32 fLuminance) = 0;
	virtual IXLightBase*	CreatePointLight(const XPointLightDesc &desc) = 0;
	virtual IXLightBase*	CreateSpotLight(const XSpotLightDesc &desc) = 0;

	virtual void			ReleaseLight(IXLightBase* pLight) = 0;
};

extern IXLightManager* g_pXLightMgr;

class IXLightBase : public XMemBase
{
public:
	virtual							~IXLightBase(){}

	virtual XLightType				GetType() const = 0;
	virtual const XCusAABB&			GetAABB() const = 0;
	virtual xfloat32          		GetRadius() const = 0;
	virtual XCOLOR					GetColor() const = 0;
	virtual const XCOLORBASE&		GetColorValue() const = 0;
	virtual xfloat32				GetLuminance() const = 0;

	virtual void					SetColorValue(const XCOLORBASE& clrColorVal) = 0;
	virtual void					SetLuminance(xfloat32 fLuminance) = 0;

	virtual xbool					IsEnable() const = 0;
	virtual void					Enable(xbool enabled) = 0;

	virtual xbool					IsCastShadow() const = 0;
	virtual void					EnableCastShadow(xbool bEnabled) = 0;

	virtual void					Release() = 0;
	virtual void					GetBeLightedPrimitives(const XArray<IXPrimitiveBase*>& primitives, XArray<IXPrimitiveBase*>& lightedPrimitives) = 0;

};
class IXDirectionLight : public IXLightBase
{
public:
	virtual							~IXDirectionLight(){}
	virtual const XVECTOR3&			GetDir() const = 0;
	virtual void					SetDir(const XVECTOR3& vDir) = 0;

};
class IXEnvironmentLight : public IXLightBase
{
public:
	virtual							~IXEnvironmentLight(){}
};

class IXPointLight : public IXLightBase
{
public:
	virtual							~IXPointLight(){}
	virtual const XVECTOR3&			GetPos() const = 0;
	virtual void					SetPos(const XVECTOR3 &vPos) = 0;
	virtual void          			SetRadius(xfloat32 fRadius) = 0;
	virtual xfloat32				GetFallOffExponent() const = 0;
	virtual void					SetFallOffExponent(xfloat32 fFallOffExponent) = 0;
};

class IXSpotLight : public IXPointLight
{
public:
	virtual							~IXSpotLight(){}
	virtual const XVECTOR3&			GetDir() const = 0;
	virtual void					SetDir(const XVECTOR3 &vDir) = 0;
	virtual xfloat32				GetConeInnerAngle() const = 0;
	virtual void					SetConeInnerAngle(xfloat32 fAngle) = 0;
	virtual xfloat32				GetConeOuterAngle() const = 0;
	virtual void					SetConeOuterAngle(xfloat32 fAngle) = 0;
};


#endif //_X_LIGHT_H_