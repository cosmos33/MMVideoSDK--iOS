/******************************************************************************

 @File         XMaterial.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XMaterial.

 @HISTORY:

******************************************************************************/

#ifndef _X_MATERIAL_H_
#define _X_MATERIAL_H_

#include "XResource.h"
#include "XSys.h"
#include "XMath3D.h"
#include "XString.h"
#include "XPrimitiveBase.h"
#include "XBase3DTypes.h"
#include "XMemBase.h"
#include "XArray.h"
#include "XConsoleManager.h"
#include "XLightBase.h"

#define CONST_VECTOR_VALUE_COUNT 16
enum XMaterialDataType
{
    XMDT_UNKNOWN		= 0,
    XMDT_FLOAT       	= XBit(0), 
    XMDT_FLOAT2      	= XBit(1), 
    XMDT_FLOAT3      	= XBit(2), 
    XMDT_FLOAT4      	= XBit(3), 
    XMDT_FLOAT_ALL   	= XMDT_FLOAT | XMDT_FLOAT2 | XMDT_FLOAT3 | XMDT_FLOAT4,
    XMDT_MATRIX4     	= XBit(4), 
    XMDT_2DTEX   		= XBit(10),
	XMDT_NOTSUPPORT3DTEX = XBit(11),
	XMDT_CUBETEX		= XBit(12),
	XMDT_ALL_TEX = XMDT_2DTEX | XMDT_CUBETEX | XMDT_NOTSUPPORT3DTEX,
    XMDT_FLOAT4GROUP	= XBit(13),
};

enum XMaterialBlendMode
{
    XMBM_EMPTY			= 0,
    XMBM_OPAQUE			= XBit(1),
    XMBM_ALPHATEST		= XBit(2),
    XMBM_TRANSLUCENT	= XBit(3),
	XMBM_TRANSLUCENT_ALPHA_ADDITIVE = XBit(4),
	XMBM_DEPTHONLY		= XBit(5),
	XMBM_AR_BACKGROUND	= XBit(6),
	XMBM_TRANSLUCENT_OIT = XBit(7),
};

enum XBlendFactorType
{
    XBFT_EMPTY,
	XBFT_ONE,
	XBFT_ZERO,
	XBFT_SRCALPHA,
	XBFT_INVSRCALPHA,
	XBFT_SRCCOLOR,
	XBFT_INVSRCCOLOR,
};

//shading mode
enum XMaterialShadingType
{
	X_MSM_EMPTY = -1,
	X_MSM_UNLIT = 0,
	X_MSM_DEFAULT_LIT = 1,
};

enum XTexAddressType
{
    XTAT_WRAP = 0,
    XTAT_CLAMP,
    XTAT_MIRROR,
	XTAT_BORDER,
};

enum XTexFilterType
{
	XTFT_POINT = 0,
	XTFT_BILINEAR,
	XTFT_TRILINEAR,
	XTFT_ANISOTROPIC,
};


class IXTexture2D;

struct XMaterialParamTypeValue
{
	XMaterialDataType nMDType;

    struct Float4Group
    {
        xfloat32*	pFValues;
        xint32		nCount;
    };
	union
	{
		xfloat32		VectorValues[CONST_VECTOR_VALUE_COUNT];
		IXTexture2D*	p2DTex;
		IXTextureCube*	pCubeTex;
        Float4Group		Float4GroupValues;
	};

	X_FORCEINLINE XMaterialParamTypeValue()
	{
		nMDType = XMDT_UNKNOWN;
	}

	X_FORCEINLINE XMaterialParamTypeValue(const XMaterialParamTypeValue& xValue)
	{
		memcpy(this, &xValue, sizeof(*this));
	}

	X_FORCEINLINE XMaterialParamTypeValue(xfloat32 vec1Val)
	{
		nMDType = XMDT_FLOAT;
		VectorValues[0] = vec1Val;
	}

	X_FORCEINLINE XMaterialParamTypeValue(const XVECTOR2& vec2Val)
	{
		nMDType = XMDT_FLOAT2;
		VectorValues[0] = vec2Val.x;
		VectorValues[1] = vec2Val.y;
	}

	X_FORCEINLINE XMaterialParamTypeValue(const XVECTOR3& vec3Val)
	{
		nMDType = XMDT_FLOAT3;
		VectorValues[0] = vec3Val.x;
		VectorValues[1] = vec3Val.y;
		VectorValues[2] = vec3Val.z;
	}

	X_FORCEINLINE XMaterialParamTypeValue(const XVECTOR4& vec4Val)
	{
		nMDType = XMDT_FLOAT4;
		VectorValues[0] = vec4Val.x;
		VectorValues[1] = vec4Val.y;
		VectorValues[2] = vec4Val.z;
		VectorValues[3] = vec4Val.w;
	}
	
	X_FORCEINLINE XMaterialParamTypeValue(const XCOLORBASE& vec4Val)
	{
		nMDType = XMDT_FLOAT4;
		VectorValues[0] = vec4Val.r;
		VectorValues[1] = vec4Val.g;
		VectorValues[2] = vec4Val.b;
		VectorValues[3] = vec4Val.a;
	}


	X_FORCEINLINE XMaterialParamTypeValue(const XMATRIX4& vec16Val)
	{
		nMDType = XMDT_MATRIX4;
		memcpy(VectorValues, vec16Val.m, sizeof(xfloat32) * 16);
	}

	X_FORCEINLINE XMaterialParamTypeValue(IXTexture2D* pTexture2D)
	{
		nMDType = XMDT_2DTEX;
		p2DTex = pTexture2D;
	}

	X_FORCEINLINE XMaterialParamTypeValue(IXTextureCube* pTextureCube)
	{
		nMDType = XMDT_CUBETEX;
		pCubeTex = pTextureCube;
	}

	X_FORCEINLINE XMaterialParamTypeValue& operator=(const XMaterialParamTypeValue& xValue)
	{
		memcpy(this, &xValue, sizeof(*this));
		return *this;
	}

};

struct XMaterialParamDescInfo : public XMemBase
{
    XMaterialDataType iType;
    XString strMatParamName;
	xuint32 crcMatParamName;
    xint32  nId;
	xbool	bUser;

    XTexAddressType		nTexAddreU;
    XTexAddressType		nTexAddreV;
    XTexAddressType		nTexAddreW;
    XTexFilterType		nTexFilter;
	
	enum XWidgetType
	{
		XWT_INPUT1 = 0,
		XWT_INPUT2,
		XWT_INPUT3,
		XWT_INPUT4,
		XWT_COLOR,
		XWT_TEXTURE,
		XWT_NUM
	};
	struct XAnnotation
	{
		XString		strShowNameOnWidgetUI;
		XWidgetType nWidgetType;
		XString		strTexName;
		xfloat32	fValues[4];

		XAnnotation()
		{
			strShowNameOnWidgetUI = "";
			nWidgetType = XWT_NUM;
			strTexName = "";
			memset(fValues, 0, sizeof(fValues));
		}

		XAnnotation(const XAnnotation& other)
		{
			*this = other;
		}

		XAnnotation& operator=(const XAnnotation& other)
		{
			if (&other == this)
			{
				return *this;
			}
			strShowNameOnWidgetUI = other.strShowNameOnWidgetUI;
			nWidgetType = other.nWidgetType;
			strTexName = other.strTexName;
			memcpy(fValues, other.fValues, sizeof(fValues));
			return *this;
		}
	} annotation;
};

struct XMaterialSupportMacro
{
	enum MacroType
	{
		MT_PROGRAM,
		MT_ART,
		MT_NUM
	};
	XString			strName;
	MacroType		eType;
	XString			strDesc;
	xuint32			nGroupID;
	XMaterialSupportMacro()
		: strName("")
		, eType(MT_NUM)
		, strDesc("")
		, nGroupID(0)
	{}
};

struct XMaterialShaderDescInfo : public XMemBase
{
    XString strVertexShaderFileName;
    XString strPixelShaderFileName;
    XString strShaderMacro;
	XString strMacroInMtlFile;
    XString strVSMainEntry;
    XString strPSMainEntry;
};

class IXMaterial;
class IXMaterialInstance;

struct XMaterialDescInfo
{
    xint32						bWriteDepth;
    xint32						bTestDepth;
    xint32                      bTwoSideShow;
    XMaterialBlendMode			nMaterialBlendMode;
    XBlendFactorType			nSrcBlendFactor;
    XBlendFactorType			nDestBlendFactor;
	xfloat32					fRenderLayerSort;
    XMaterialShaderDescInfo         strShaderDesc;
    
    bool operator ==(const XMaterialDescInfo& desc) const
    {
        return bWriteDepth == desc.bWriteDepth
            && bTestDepth == desc.bTestDepth
            && bTwoSideShow == desc.bTwoSideShow
            && nMaterialBlendMode == desc.nMaterialBlendMode
            && nSrcBlendFactor == desc.nSrcBlendFactor
            && nDestBlendFactor == desc.nDestBlendFactor
			&& fRenderLayerSort == desc.fRenderLayerSort
            && strShaderDesc.strPSMainEntry == desc.strShaderDesc.strPSMainEntry
            && strShaderDesc.strVSMainEntry == desc.strShaderDesc.strVSMainEntry
            && strShaderDesc.strVertexShaderFileName == desc.strShaderDesc.strVertexShaderFileName
            && strShaderDesc.strPixelShaderFileName == desc.strShaderDesc.strPixelShaderFileName
            && strShaderDesc.strShaderMacro == desc.strShaderDesc.strShaderMacro;
    }
    XMaterialDescInfo();
};
class IXMaterial : public IXResource
{
protected:
    virtual								~IXMaterial() {}

public:
    virtual void						Release() = 0;

    virtual XMaterialBlendMode			GetMaterialBlendMode() const = 0;
	virtual XBlendFactorType			GetSrcBlendFactorType() const = 0;
	virtual XBlendFactorType			GetDestBlendFactorType() const = 0;
    virtual xbool						IsEnableDepthTest() const = 0;
    virtual xbool						IsEnableDepthWrite() const = 0;
    virtual xbool						IsEnableTwoSidedShow() const = 0;
	virtual xbool						IsEnableCastShadow() const = 0;
	virtual XMaterialShadingType		GetShadingType() const = 0;
	virtual xfloat32					GetRenderLayerSortValue() const = 0;
    virtual xint32						GetMatParamCount() const = 0;
    virtual XMaterialParamDescInfo*		GetMatParamDescInfoByParamName(const xchar* szName) const = 0;
    virtual XMaterialParamDescInfo*		GetMatParamDescInfoByParamId(xint32 id) const = 0;
    virtual xint32						GetMatParamIdByParamName(const xchar* szName) const = 0;
    virtual XMaterialShaderDescInfo*	GetMatShaderDescInfo() = 0;
	virtual const XString&				GetMaterialFileName() const = 0;
	virtual const XMaterialDescInfo&	GetMaterialDescInfo() const = 0;
	virtual xint32						GetSupportMacroCount() const = 0;
	virtual XMaterialSupportMacro*		GetSupportMacroById(xint32 id) const = 0;
};

class IXMaterialInstance : public IXResource
{
protected:
    virtual										~IXMaterialInstance() {}

public:
    virtual void								Release() = 0;
    virtual IXMaterial*							GetMaterialPtr() const = 0;
	virtual const xchar*						GetMaterialInsFile()const = 0;
    virtual xint32								GetParameterCount() const = 0;
    virtual const XMaterialParamDescInfo*		GetParameterDescInfoByParamName(const xchar* szName) const = 0;
    virtual const XMaterialParamDescInfo*		GetParameterDescInfoByParamId(xint32 id) const = 0;
	virtual const xint32						GetParameterIdByParamName(const xchar* szName) const = 0;
    virtual const XMaterialParamTypeValue&		GetParameterByParamId(xint32 iId) const = 0;
    virtual const XMaterialParamTypeValue&		GetParameterByParamName(const xchar* szName) const = 0;
    virtual void								SetParameterByParamName(const xchar* szName, const XMaterialParamTypeValue& val) = 0;
    virtual void								SetParameterByParamId(xint32 id, const XMaterialParamTypeValue& val) = 0;
	virtual void								SetTextureParameterByParamName(const xchar* szName, IXTexture* pTexture) = 0;
	virtual void								SetTextureParameterByParamId(xint32 id, IXTexture* pTexture) = 0;
	virtual xbool								IsMacroEnabled(xint32 id) = 0;
	virtual void								EnabledMacro(xint32 id, xbool bEnable) = 0;
	virtual xbool								ChangeMtl(const xchar* szMaterialFile) = 0;
	virtual xbool								ApplyAndUpdateMaterial(const IXMaterialInstance* pSrcMtlIns) = 0;

	virtual xbool								IsCastShadow() const = 0;
};

class IXMaterialManager : public XMemBase
{
protected:
    virtual                     ~IXMaterialManager() {};
public:
    virtual xbool			    Init() = 0;
    virtual void			    Release() = 0;
	virtual IXMaterial*			GetMaterial(const xchar* szMaterialFile, const xchar* szReplaceShaderMacro = NULL) = 0;

	// 获取一个内存中或硬盘上的材质
	virtual IXMaterialInstance* GetMaterialInstance(const char* szMaterialFileName, const xchar* szReplaceShaderMacro = NULL, xbool bReLoad = xfalse) = 0;
	// 创建一个内存中的材质实例
	// 材质名称和宏连接起来的字符串不能相同
	virtual IXMaterialInstance*	CreateMaterialInstance(const xchar* szNewMaterialInsFile, const xchar* szMaterialFile, const xchar* szReplaceShaderMacro = NULL) = 0;
	// 临时添加，禁止调用
	virtual void				SaveMaterialBinary(const xchar* szMatFile, IXMaterial* pMaterial) = 0;

	/* 是否重新加载材质实例 */
	virtual void				ReloadMaterialInstance(const xchar* szMaterialInsFile) = 0;
	/* 判断材质实例是否已加载 */
	virtual xbool				IsMaterialInstanceLoaded(const xchar* szMtlInsFile) = 0;

	struct XMaterialInsParameterForSave
	{
		XMaterialDataType		nMatInsDataType;
		XString					strMaterialInsParameterName;
		XString					strTexFile;
		xbool					bRelativeToCurrentDirection;
		XVECTOR4				vecValues;
	};
	virtual void				SaveMaterialInstance(const xchar* szSaveMatInsFile, const xchar* szMatFile, const xchar* szShaderMacro, const XArray<XMaterialInsParameterForSave>& aParams) = 0;
};


extern IXMaterialManager* g_pXMaterialMgr;

inline xuint32 GetLayerMask(IXMaterialInstance* pMaterialIns)
{
	if (!pMaterialIns || !pMaterialIns->GetMaterialPtr())
	{
		return 0;
	}

	IXMaterial* pMaterial = pMaterialIns->GetMaterialPtr();

	xuint32 unMaterialLayer = 0;

	switch (pMaterial->GetMaterialBlendMode())
	{
	case XMBM_DEPTHONLY:
	{
		unMaterialLayer = XPLM_DEPTH_ONLY;
		break;
	}
	case XMBM_OPAQUE:
	{
		unMaterialLayer = XPLM_OPAQUE;
		break;
	}
	case XMBM_ALPHATEST:
	{
		unMaterialLayer = XPLM_ALPHATEST;
		break;
	}
	case XMBM_TRANSLUCENT:
	{
		if (pMaterial->IsEnableDepthWrite())
		{
			unMaterialLayer = XPLM_TRANSLUCENT_ZWRITE;
		}
		else
		{
			unMaterialLayer = XPLM_TRANSLUCENT;
		}
		break;
	}
	case XMBM_TRANSLUCENT_ALPHA_ADDITIVE:
	{
		unMaterialLayer = XPLM_TRANSLUCENT_ALPHA_ADDITIVE;
		break;
	}
	case XMBM_AR_BACKGROUND:
	{
		unMaterialLayer = XPLM_AR_BACKGROUND;
		break;
	}
	case XMBM_TRANSLUCENT_OIT:
	{
		if (g_CVarEnableOIT.GetBool())
		{
			unMaterialLayer = XPLM_TRANSLUCENT_OIT;
		}
		else
		{
			if (pMaterial->IsEnableDepthWrite())
			{
				unMaterialLayer = XPLM_TRANSLUCENT_ZWRITE;
			}
			else
			{
				unMaterialLayer = XPLM_TRANSLUCENT;
			}
		}
		break;
	}
	default:
		break;
	}

	if (pMaterialIns->IsCastShadow()
		&& pMaterial->IsEnableCastShadow())
	{
		unMaterialLayer |= XPLM_CAST_SHADOW;
	}

	switch (pMaterial->GetShadingType())
	{
	case X_MSM_UNLIT:
		unMaterialLayer |= XPLM_UNLIT;
		break;
	default:
		break;
	}

	return unMaterialLayer;
}

inline xbool IsMaterialMatchPrimitiveLayerMask(IXMaterialInstance* pMaterialIns, xuint32 unLayer)
{
	xuint32 unMaterialLayer = GetLayerMask(pMaterialIns);

	if ((unMaterialLayer & unLayer) == 0)
	{
		return xfalse;
	}
	else
	{
		return xtrue;
	}
}

inline xuint32 GetMaterialAlphaTypeToPrimitiveLayerMask(XMaterialBlendMode t)
{
    switch (t)
    {
	case XMBM_DEPTHONLY:
		return XPLM_DEPTH_ONLY;
    case XMBM_OPAQUE:
        return XPLM_OPAQUE;
    case XMBM_ALPHATEST:
        return XPLM_ALPHATEST;
		//  如果材质是半透明，那么需要兼容半透明的所有层，防止不渲染
    case XMBM_TRANSLUCENT:
	case XMBM_TRANSLUCENT_ALPHA_ADDITIVE:
	case XMBM_TRANSLUCENT_OIT:
		return XPLM_TRANSLUCENT | XPLM_TRANSLUCENT_ZWRITE | XPLM_TRANSLUCENT_ALPHA_ADDITIVE | XPLM_TRANSLUCENT_ZDISABLE | XPLM_TRANSLUCENT_OIT;
	case XMBM_AR_BACKGROUND:
		return XPLM_AR_BACKGROUND;
    default:
        return 0;
    }
    return 0;
}

#endif//_X_MATERIAL_H_
