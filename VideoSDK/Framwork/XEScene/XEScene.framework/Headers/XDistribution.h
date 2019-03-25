#ifndef _XDISTRIBUTION_H_
#define _XDISTRIBUTION_H_

#include "XArray.h"
#include "XBase3DTypes.h"
#include "XCurve.h"

enum RawDisributionFloatType
{
	RDFT_CONSTANT,
	RDFT_UNIFORM,
	RDFT_CONSTANT_CURVE,
	RDFT_UNIFORM_CURVE
};

enum RawDisributionVectorType
{
	RDVT_CONSTANT,
	RDVT_UNIFORM,
	RDVT_CONSTANT_CURVE,
	RDVT_UNIFORM_CURVE,
};

/************************************************************************/
/* Float Type                                                           */
/************************************************************************/
class XFileBase;
class XDistributionFloat;
class XRawDistributionFloat
{
public:
	XRawDistributionFloat(xfloat32 f);
	virtual ~XRawDistributionFloat();
	virtual xfloat32				Evaluate(xfloat32 f) const;
	virtual RawDisributionFloatType	GetType() const;
	virtual void					SetType(RawDisributionFloatType eType);
	XDistributionFloat*				GetDistribution(){ return m_pDistribution; }
	const XDistributionFloat*		GetDistribution() const { return m_pDistribution; }
	xbool							CopyValueFrom(const XRawDistributionFloat* dis);

	xbool							Save(XFileBase* pFile);
	xbool							Load(XFileBase* pFile);

protected:
	XDistributionFloat*				m_pDistribution;
	RawDisributionFloatType			m_eType;
};

class XDistributionFloat
{
public:
	virtual ~XDistributionFloat(){}
	virtual xfloat32				Evaluate(xfloat32 f) = 0;
	virtual xbool					Save(XFileBase* pFile) = 0;
	virtual	xbool					Load(XFileBase* pFile) = 0;
};

class XDistributionFloatConstant : public XDistributionFloat
{
public:
	XDistributionFloatConstant()
		: fConstant(0.0f){}
	XDistributionFloatConstant(xfloat32 f)
		: fConstant(f){}
	virtual xfloat32	Evaluate(xfloat32 f){ return fConstant; }

	void				GetValue(xfloat32& f)const{ f = fConstant; }
	void				SetValue(xfloat32 f){ fConstant = f; }

	virtual xbool		Save(XFileBase* pFile);
	virtual xbool		Load(XFileBase* pFile);
protected:
	xfloat32 fConstant;
};

class XDistributionFloatUniform : public XDistributionFloat
{
public:
	XDistributionFloatUniform()
		: fMin(0)
		, fMax(0)
	{}
	virtual xfloat32	Evaluate(xfloat32 f);

	void				GetValue(xfloat32& min, xfloat32& max)const{ min = fMin, max = fMax; }
	void				SetValue(xfloat32 min, xfloat32 max){ fMin = min; fMax = max; }
	
	virtual xbool		Save(XFileBase* pFile);
	virtual xbool		Load(XFileBase* pFile);
protected:
	xfloat32 fMin;
	xfloat32 fMax;
};

struct XInterpCurveFloat;
class XDistributionFloatConstantCurve : public XDistributionFloat
{
public:
	XDistributionFloatConstantCurve();
	virtual ~XDistributionFloatConstantCurve();
	virtual xfloat32	Evaluate(xfloat32 f);

	virtual xint32		CreateNewKey(xfloat32 fIn, xfloat32 fOut);
	virtual void		DeleteAllKeys();
	virtual void		DeleteKey(xint32 KeyIndex);
	virtual xint32		GetKeyNum()const;
	virtual void		GetKeyValue(xint32 nKeyIndex, FInterpCurvePoint<xfloat32>& point)const;
	virtual void		SetKeyValue(xint32 nKeyIndex, const FInterpCurvePoint<xfloat32>& point);

	virtual xbool		Save(XFileBase* pFile);
	virtual xbool		Load(XFileBase* pFile);
	
	XInterpCurveFloat*	GetCurvePointer(){ return m_Curve; }
protected:
	XInterpCurveFloat*	m_Curve;
};

struct XInterpCurveVector2D;
class XDistributionFloatUniformCurve : public XDistributionFloat
{
public:
	XDistributionFloatUniformCurve();
	virtual ~XDistributionFloatUniformCurve();
	virtual xfloat32	Evaluate(xfloat32 f);

	virtual xint32		CreateNewKey(xfloat32 fIn, const XVECTOR2& fOut);
	virtual void		DeleteAllKeys();
	virtual void		DeleteKey(xint32 KeyIndex);
	virtual xint32		GetKeyNum()const;
	virtual void		GetKeyValue(xint32 nKeyIndex, FInterpCurvePoint<XVECTOR2>& point)const;
	virtual void		SetKeyValue(xint32 nKeyIndex, const FInterpCurvePoint<XVECTOR2>& point);

	virtual xbool		Save(XFileBase* pFile);
	virtual xbool		Load(XFileBase* pFile);
	XInterpCurveVector2D*	GetCurvePointer(){ return m_Curve; }
protected:
	XInterpCurveVector2D*	m_Curve;
};

/************************************************************************/
/* Vector Type                                                           */
/************************************************************************/

class XDistributionVector;
class XRawDistributionVector
{
public:
	XRawDistributionVector(const XVECTOR3& v);
	virtual ~XRawDistributionVector();
	virtual XVECTOR3					Evaluate(xfloat32 f) const;
	virtual RawDisributionVectorType	GetType() const;
	virtual void						SetType(RawDisributionVectorType eType);
	const XDistributionVector*			GetDistribution()const{ return m_pDistribution; }
	XDistributionVector*				GetDistribution(){ return m_pDistribution; }
	xbool								CopyValueFrom(const XRawDistributionVector* dis);

	virtual xbool						Save(XFileBase* pFile);
	virtual xbool						Load(XFileBase* pFile);
protected:
	XDistributionVector*				m_pDistribution;
	RawDisributionVectorType			m_eType;
};

class XDistributionVector
{
public:
	virtual ~XDistributionVector(){}
	virtual XVECTOR3				Evaluate(xfloat32 f) = 0;
	
	virtual xbool					Save(XFileBase* pFile) = 0;
	virtual xbool					Load(XFileBase* pFile) = 0;
};

class XDistributionVectorConstant : public XDistributionVector
{
public:
	XDistributionVectorConstant(const XVECTOR3& v)
		: vConstant(v){}
	XDistributionVectorConstant()
		: vConstant(0.0f){}
	virtual XVECTOR3				Evaluate(xfloat32 f){ return vConstant; }

	void							GetValue(XVECTOR3& v)const{ v = vConstant; }
	void							SetValue(const XVECTOR3& v){ vConstant = v; }

	virtual xbool					Save(XFileBase* pFile);
	virtual xbool					Load(XFileBase* pFile);
protected:
	XVECTOR3 vConstant;
};

class XDistributionVectorUniform : public XDistributionVector
{
public:
	XDistributionVectorUniform()
		: vMin(0.0f)
		, vMax(0.0f)
	{}
	virtual XVECTOR3				Evaluate(xfloat32 f);

	void							GetValue(XVECTOR3& min, XVECTOR3& max)const{ min = vMin; max = vMax; }
	void							SetValue(const XVECTOR3& min, const XVECTOR3& max){ vMin = min; vMax = max; }

	virtual xbool					Save(XFileBase* pFile);
	virtual xbool					Load(XFileBase* pFile);
protected:
	XVECTOR3 vMin;
	XVECTOR3 vMax;
};

struct XInterpCurveVector;
class XDistributionVectorConstantCurve : public XDistributionVector
{
public:
	XDistributionVectorConstantCurve();
	virtual ~XDistributionVectorConstantCurve();
	virtual XVECTOR3				Evaluate(xfloat32 f);

	virtual xint32					CreateNewKey(xfloat32 fIn, const XVECTOR3& fOut);
	virtual void					DeleteKey(xint32 KeyIndex);
	virtual void					DeleteAllKeys();
	virtual xint32					GetKeyNum()const;
	virtual void					GetKeyValue(xint32 nKeyIndex, FInterpCurvePoint<XVECTOR3>& point)const;
	virtual void					SetKeyValue(xint32 nKeyIndex, const FInterpCurvePoint<XVECTOR3>& point);

	virtual xbool					Save(XFileBase* pFile);
	virtual xbool					Load(XFileBase* pFile);
	XInterpCurveVector*			GetCurvePointer(){ return m_Curve; }
protected:
	XInterpCurveVector*				m_Curve;
};

class XDistributionVectorUniformCurve : public XDistributionVector
{
public:
	XDistributionVectorUniformCurve();
	virtual ~XDistributionVectorUniformCurve();
	virtual XVECTOR3				Evaluate(xfloat32 f);

	virtual xint32					CreateNewKey(xfloat32 fIn, const XVECTOR3& fOut1, const XVECTOR3& fOut2);
	virtual void					DeleteKey(xint32 KeyIndex);
	virtual void					DeleteAllKeys();
	virtual xint32					GetKeyNum()const;
	virtual void					GetKeyValue(xint32 nKeyIndex, FInterpCurvePoint<XVECTOR3>& point1, FInterpCurvePoint<XVECTOR3>& point2)const;
	virtual void					SetKeyValue(xint32 nKeyIndex, const FInterpCurvePoint<XVECTOR3>& point1, const FInterpCurvePoint<XVECTOR3>& point2);

	virtual xbool					Save(XFileBase* pFile);
	virtual xbool					Load(XFileBase* pFile);
	XInterpCurveVector*				GetCurvePointer1(){ return m_Curve1; }
	XInterpCurveVector*				GetCurvePointer2(){ return m_Curve2; }
protected:
	XInterpCurveVector*				m_Curve1;
	XInterpCurveVector*				m_Curve2;
};

#endif
