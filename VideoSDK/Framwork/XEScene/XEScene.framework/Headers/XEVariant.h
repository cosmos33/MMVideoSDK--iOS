/******************************************************************************

@File         XEVariant.h

@Version       1.0

@Created      2017, 9, 27

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/


#ifndef _XE_VARIANT_H_
#define _XE_VARIANT_H_

#include "XTypes.h"
#include "XMath3D.h"
#include "XString.h"
#include "XBase3DTypes.h"
#include "tinyxml2_XEngine.h"
#include "XETransform.h"

struct XEVariant
{
	enum PType
	{
		XVT_NONE = 0,
		XVT_FLOAT1,
		XVT_FLOAT2,
		XVT_FLOAT3,
		XVT_FLOAT4,
		XVT_COLORRGB,
		XVT_COLORRGBA,
		XVT_BOOL,
		XVT_INT,
		XVT_STRING,
		XVT_TRANSFORM,
		XVT_VARIANT_WRAPPER,
		XVT_USER_DATA,
		XVT_NUM
	};

	XEVariant();
	XEVariant(PType type);
	~XEVariant();

	XEVariant(const XEVariant& value)
		: eType(XVT_NONE)
	{
		*this = value;
	}

	XEVariant& operator = (const XEVariant& rhs);	

	inline void SetFloat(xfloat32 fValue)
	{
		SetType(XVT_FLOAT1);
		fVals[0] = fValue;
	}

	inline void SetFloat2(xfloat32 fValue1, xfloat32 fValue2)
	{
		SetType(XVT_FLOAT2);
		fVals[0] = fValue1;
		fVals[1] = fValue2;
	}	

	inline void SetFloat3(xfloat32 fValue1, xfloat32 fValue2, xfloat32 fValue3)
	{
		SetType(XVT_FLOAT3);
		fVals[0] = fValue1;
		fVals[1] = fValue2;
		fVals[2] = fValue3;
	}
	inline void SetFloat4(xfloat32 fValue1, xfloat32 fValue2, xfloat32 fValue3, xfloat32 fValue4)
	{
		SetType(XVT_FLOAT4);
		fVals[0] = fValue1;
		fVals[1] = fValue2;
		fVals[2] = fValue3;
		fVals[3] = fValue4;
	}

	inline void SetColor(xfloat32 fR, xfloat32 fG, xfloat32 fB)
	{
		SetType(XVT_COLORRGB);
		fVals[0] = fR;
		fVals[1] = fG;
		fVals[2] = fB;
	}

	inline void SetColor(xfloat32 fR, xfloat32 fG, xfloat32 fB, xfloat32 fA)
	{
		SetType(XVT_COLORRGBA);
		fVals[0] = fR;
		fVals[1] = fG;
		fVals[2] = fB;
		fVals[3] = fA;
	}

	inline void SetBool(xbool bValue)
	{
		SetType(XVT_BOOL);
		bVal = bValue;
	}

	inline void SetInt(xint32 nValue_)
	{
		SetType(XVT_INT);
		nValue = nValue_;
	}

	inline void SetVariantWrapper(const XArray<XEVariant>& vw)
	{
		SetType(XVT_VARIANT_WRAPPER);
		*(reinterpret_cast<XArray<XEVariant>*>(pPtr)) = vw;
	}

	inline void SetTransform(const XETransform& tf)
	{
		SetType(XVT_TRANSFORM);
		*(reinterpret_cast<XETransform*>(pPtr)) = tf;
	}

	inline void SetString(const XString &str)
	{
		SetType(XVT_STRING);
		*(reinterpret_cast<XString*>(pPtr)) = str;
	}

	inline void SetVECTOR2(const XVECTOR2 &Value)
	{
		SetFloat2(Value.x, Value.y);
	}

	inline void SetVECTOR3(const XVECTOR3 &Value)
	{
		SetFloat3(Value.x, Value.y, Value.z);
	}

	inline void SetVECTOR4(const XVECTOR4 &Value)
	{
		SetFloat4(Value.x, Value.y, Value.z, Value.w);
	}

	inline void SetCOLORGBASE(const XCOLORBASE &Value)
	{
		SetColor(Value.r, Value.g, Value.b, Value.a);
	}

	inline void SetUserData(void* pUserData)
	{
		SetType(XVT_USER_DATA);
		pPtr = pUserData;
	}

	inline xfloat32 GetFloat() const
	{
		return XVT_FLOAT1 == eType ? fVals[0] : 0.0f;
	}

	inline void GetFloat2(xfloat32 &fVal1, xfloat32 &fVal2) const
	{
		if (XVT_FLOAT2 == eType)
		{
			fVal1 = fVals[0];
			fVal2 = fVals[1];
		}
		else
		{
			fVal1 = 0.0f;
			fVal2 = 0.0f;
		}
	}

	inline void GetFloat3(xfloat32 &fVal1, xfloat32 &fVal2, xfloat32 &fVal3) const
	{
		if (XVT_FLOAT3 == eType)
		{
			fVal1 = fVals[0];
			fVal2 = fVals[1];
			fVal3 = fVals[2];
		}
		else
		{
			fVal1 = 0.0f;
			fVal2 = 0.0f;
			fVal3 = 0.0f;
		}
	}

	inline void GetFloat4(xfloat32 &fVal1, xfloat32 &fVal2, xfloat32 &fVal3, xfloat32 &fVal4) const
	{
		if (XVT_FLOAT4 == eType)
		{
			fVal1 = fVals[0];
			fVal2 = fVals[1];
			fVal3 = fVals[2];
			fVal4 = fVals[3];
		}
		else
		{
			fVal1 = 0.0f;
			fVal2 = 0.0f;
			fVal3 = 0.0f;
			fVal4 = 0.0f;
		}
	}

	inline void GetColor(xfloat32 &fR, xfloat32 &fG, xfloat32 &fB) const
	{
		if (XVT_COLORRGB == eType)
		{
			fR = fVals[0];
			fG = fVals[1];
			fB = fVals[2];
		}
		else
		{
			fR = 0.0f;
			fG = 0.0f;
			fB = 0.0f;
		}
	}

	inline void GetColor(xfloat32 &fR, xfloat32 &fG, xfloat32 &fB, xfloat32 &fA) const
	{
		if (XVT_COLORRGBA == eType)
		{
			fR = fVals[0];
			fG = fVals[1];
			fB = fVals[2];
			fA = fVals[3];
		}
		else
		{
			fR = 0.0f;
			fG = 0.0f;
			fB = 0.0f;
			fA = 0.0f;
		}
	}

	inline xbool GetBool() const
	{
		return XVT_BOOL == eType ? bVal : xfalse;
	}

	inline xint32 GetInt() const
	{
		return XVT_INT == eType ? nValue : s_Invalid_Int;
	}

	inline void* GetUserData() const
	{
		return XVT_USER_DATA == eType ? pPtr : NULL;
	}
	
	inline const XString& GetString() const
	{
		return XVT_STRING == eType ? *reinterpret_cast<const XString*>(pPtr) : s_InValid;
	}

	inline  XETransform& GetTransform() 
	{
		static XETransform __tf;
		return XVT_TRANSFORM == eType ? *reinterpret_cast<XETransform*>(pPtr) : __tf;
	}

X_EEB_BEGIN
	inline const XETransform& GetTransform() const
	{
		const static XETransform __tf;
		return XVT_TRANSFORM == eType ? *reinterpret_cast<const XETransform*>(pPtr) : __tf;
	}

	inline const XArray<XEVariant>& GetVariantWrapper() const
	{
		const static XArray<XEVariant> __vw;
		return XVT_VARIANT_WRAPPER == eType ? *reinterpret_cast<const XArray<XEVariant>*>(pPtr) : __vw;
	}

	inline const XEVariant* GetVariantWrapperItem(xint32 nIndex) const{ return nIndex >= 0 && nIndex < GetVariantWrapperItemNum() ? &GetVariantWrapper()[nIndex] : NULL; }
X_EEB_END

	inline XArray<XEVariant>& GetVariantWrapper()//for wrapper memory operating efficiency.
	{
		static XArray<XEVariant> __vw;
		return XVT_VARIANT_WRAPPER == eType ? *reinterpret_cast<XArray<XEVariant>*>(pPtr) : __vw;
	}

	inline xint32 GetVariantWrapperItemNum() const{ return GetVariantWrapper().Num(); }

	inline XEVariant* GetVariantWrapperItem(xint32 nIndex){ return nIndex >= 0 && nIndex < GetVariantWrapperItemNum() ? &GetVariantWrapper()[nIndex] : NULL; }

	inline xbool RemoveVariantWrapperItemAt(xint32 nIndex){ if (nIndex >= 0 && nIndex < GetVariantWrapperItemNum()){ GetVariantWrapper().RemoveAt(nIndex); return xtrue; } return xfalse; }

	inline xbool AddVariantWrapperItem(const XEVariant& data){ if (eType == XVT_VARIANT_WRAPPER){ GetVariantWrapper().Add(data); return xtrue; } return xfalse; }

	inline XVECTOR2 GetVECTOR2() const
	{
		XVECTOR2 vRet;
		GetFloat2(vRet.x, vRet.y);
		return vRet;		
	}

	inline XVECTOR3 GetVECTOR3() const
	{
		XVECTOR3 vRet;
		GetFloat3(vRet.x, vRet.y, vRet.z);
		return vRet;
	}

	inline XVECTOR4 GetVECTOR4() const
	{
		XVECTOR4 vRet;
		GetFloat4(vRet.x, vRet.y, vRet.z, vRet.w);
		return vRet;
	}

	inline XCOLORBASE GetCOLORGBASE() const
	{
		XCOLORBASE vRet;
		GetColor(vRet.r, vRet.g, vRet.b, vRet.a);
		return vRet;
	}

	inline PType GetType() const { return eType; }

	void SetType(PType type);

	static XString GetTypeString(PType eType);
	static PType   GetStringType(const XString& strType);

	X_EES_LINE void Deserialize(const tinyxml2_XEngine::XMLElement* pEleVaraintNode);
	X_EES_LINE tinyxml2_XEngine::XMLElement* Serialize(tinyxml2_XEngine::XMLElement* pEleVaraintNode);

protected:
	PType	eType;
	union
	{
		xbool		bVal;
		xfloat32	fVals[4];
		xint32		nValue;
		void*		pPtr;
	};

	const static XString   s_InValid;
	const static xint32    s_Invalid_Int;
};

#endif//#ifndef _XE_VARIANT_H_


