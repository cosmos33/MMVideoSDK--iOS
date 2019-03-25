/******************************************************************************

 @File         XConsoleManager.h

 @Version      1.0

 @Created      2017, 3, 6

 @Description  控制台变量系统，全局可访问，并在运行时可通过Console系统修改.

 @HISTORY:

******************************************************************************/

#ifndef _X_CONSOLEMANAGER_H_
#define _X_CONSOLEMANAGER_H_

#include "XTypes.h"
#include "XMemBase.h"
#include "XMath3D.h"

enum XConVarFlag
{
	XCONVAR_ALL				= -1,		

	XCONVAR_BOOL			= XBit(0),
	XCONVAR_INT				= XBit(1),	
	XCONVAR_FLOAT			= XBit(2),	

	XCONVAR_ENGINE			= XBit(3),
	XCONVAR_D3D9RENDERER	= XBit(4),
	XCONVAR_GLES2RENDERER	= XBit(5),	
	XCONVAR_D3D11RENDERER	= XBit(6),	
	XCONVAR_EDITOR			= XBit(7),
	XCONVAR_CLIENT			= XBit(8),
										

	XCONVAR_INIT			= XBit(9),
	XCONVAR_ROM				= XBit(10),
	XCONVAR_ARCHIVE			= XBit(11),	

										
	XCONVAR_STATIC			= XBit(12),
	XCONVAR_MODIFIED		= XBit(13)
};

//#define STATIC_CONVARS_INITED 0xFFFFFFFF 
///<--fixme flk 01 多次framework init和release时，出现野指针的BUG修改>

class XConsoleVariable : public XMemBase
{
public:
					XConsoleVariable(void);
					XConsoleVariable(const xchar* szName, const xchar* szValue, xint32 nFlags, const xchar* szDesc);
					XConsoleVariable(const xchar* szName, const xchar* szValue, xint32 nFlags, const xchar* szDesc, 
							xfloat32 fMinValue, xfloat32 fMaxValue);
					XConsoleVariable(const xchar* szName, const xchar* szValue, xint32 nFlags, const xchar* szDesc, 
							const xchar** ppValueStrings);
	virtual			~XConsoleVariable() {}

	static void		RegisterStaticConVars();
	static void		UnRegisterStaticConVars();

	const xchar*	GetName(void) const { return m_pInternalVar->m_szName; }
	xint32			GetFlags(void) const { return m_pInternalVar->m_nFlags; }
	const xchar*	GetDesc(void) const { return m_pInternalVar->m_szDesc; }
	xfloat32		GetMinValue(void) const { return m_pInternalVar->m_fMinValue; }
	xfloat32		GetMaxValue(void) const { return m_pInternalVar->m_fMaxValue; }
	const xchar**	GetValueStrings(void) const { return m_ppValueStrings; }

	xbool			IsModified(void) const { return (m_pInternalVar->m_nFlags & XCONVAR_MODIFIED)!= 0; }
	void			SetModified(void) { m_pInternalVar->m_nFlags |= XCONVAR_MODIFIED; }
	void			ClearModeified(void) { m_pInternalVar->m_nFlags &= ~XCONVAR_MODIFIED;}

	const xchar*	GetString(void) const { return m_pInternalVar->m_szValue; }
	xbool			GetBool(void) const { return (m_pInternalVar->m_nValue != 0); }
	xint32			GetInt(void) const { return m_pInternalVar->m_nValue; }
	xfloat32		GetFloat(void) const { return m_pInternalVar->m_fValue; }
	void			GetVector4(XVECTOR4* pValue) { sscanf(m_pInternalVar->m_szValue, "%f %f %f %f", &pValue->x, &pValue->y, &pValue->z, &pValue->w); }

	void			SetString(const xchar* szValue) { m_pInternalVar->InternalSetString(szValue); }
	void			SetBool(const xbool bValue) { m_pInternalVar->InternalSetBool(bValue); }
	void			SetInt(const xint32 nValue) { m_pInternalVar->InternalSetInt(nValue); }
	void			SetFloat(const xfloat32 fValue) { m_pInternalVar->InternalSetFloat(fValue); }
	void			SetVector4(const XVECTOR4* pValue) { m_pInternalVar->InternalSetVector4(pValue); }

	void			SetInternalVar(XConsoleVariable* pInternalVar) { m_pInternalVar = pInternalVar; }
protected:
	const xchar*	m_szName;
	const xchar*	m_szValue;
	const xchar*	m_szDesc;
	xint32			m_nFlags;
	xfloat32		m_fMinValue;
	xfloat32		m_fMaxValue;
	const xchar**	m_ppValueStrings;
	xint32			m_nValue;
	xfloat32		m_fValue;
	XConsoleVariable*		m_pInternalVar;
	XConsoleVariable*		m_pNext;

private:
	void			Init(const xchar* szName, const xchar* szValue, xint32 nFlags, const xchar* szDesc,
						xfloat32 fMinValue, xfloat32 fMaxValue, const xchar** ppValueStrings);

	virtual void	InternalSetString(const xchar* szNewValue) {}
	virtual void	InternalSetBool(const xbool bNewValue) {}
	virtual void	InternalSetInt(const xint32 nNewValue) {}
	virtual void	InternalSetFloat(const xfloat32 fNewValue) {}
	virtual void	InternalSetVector4(const XVECTOR4* pNewValue) {}

	static XConsoleVariable* m_pStaticVar;
	static bool		m_bConversInited;
};


class IXConVarSys
{
public:
	virtual						~IXConVarSys() {}
	virtual void				Init(void) = 0;
	virtual void				Release(void) = 0;
	virtual xbool				IsInited(void) const = 0;

	virtual void				Register(XConsoleVariable* pConVar) = 0;
	virtual void				UnRegisterAll() = 0;
	virtual XConsoleVariable*	Find(const xchar* szName) = 0;
	virtual const xchar*		GetConVarString(const xchar* szName) = 0;
	virtual xbool				GetConVarBool(const xchar* szName) = 0;
	virtual xint32				GetConVarInt(const xchar* szName) = 0;
	virtual xfloat32			GetConVarFloat(const xchar* szName) = 0;
	virtual void				SetConVarString(const xchar* szName, const xchar* szValue, xint32 nFlags = 0) = 0;
	virtual void				SetConVarBool(const xchar* szName, const xbool bValue, xint32 nFlags = 0) = 0;
	virtual void				SetConVarInt(const xchar* szName, const xint32 nValue, xint32 nFlags = 0) = 0;
	virtual void				SetConVarFloat(const xchar* szName, const xfloat32 fValue, xint32 nFlags = 0) = 0;

	virtual void				SetModifiedFlags(xint32 nFlags) = 0;
	virtual xint32				GetModifiedFlags(void) const = 0;
	virtual void				ClearModifiedFlags(int nFlags) = 0;
};

extern IXConVarSys* g_pXConVarSys;
enum XSceneRenderMode
{
	XSRM_FORWARD_RENDER = 0,
};

extern XConsoleVariable	g_CVarRenderSceneToTexture;
extern XConsoleVariable g_CVarRTTWidth;
extern XConsoleVariable g_CVarRTTHeight;

extern XConsoleVariable g_CVarCaptureScreen;
extern XConsoleVariable g_CVarCaptureScreenFileName;

extern XConsoleVariable	g_CVarEnableSSAA;
extern XConsoleVariable g_CVarEnableBicubicFilter;
extern XConsoleVariable	g_CVarSSAAScale;

extern XConsoleVariable g_CVarEnablePostProcess;
extern XConsoleVariable g_CVarEnableFXAA;
extern XConsoleVariable g_CVarFXAAPreset;
extern XConsoleVariable g_CVarEnableBloom;
extern XConsoleVariable g_CVarBloomColorThreshold;
extern XConsoleVariable g_CVarBloomSamplerScale;

extern XConsoleVariable g_CVarEnableFog;
extern XConsoleVariable g_CVarFogStart;
extern XConsoleVariable g_CVarFogEnd;
extern XConsoleVariable g_CVarFogDensity;
extern XConsoleVariable g_CVarFogColorUpper;
extern XConsoleVariable g_CVarFogColorLower;
extern XConsoleVariable g_CVarFogHeightStart;
extern XConsoleVariable g_CVarFogHeightEnd;
extern XConsoleVariable g_CVarFogHeightDensity;
extern XConsoleVariable g_CVarFogDensityUpper;
extern XConsoleVariable g_CVarFogDensityLower;
extern XConsoleVariable g_CVarFogHorizontalDensity;
extern XConsoleVariable g_CVarFogHorizontalPower;
extern XConsoleVariable g_CVarFogWorldPosHeightOffset;

extern XConsoleVariable g_CVarDebugDrawPhysics;

extern XConsoleVariable g_CVarEnableARBackgroundEffect;
extern XConsoleVariable g_CVarARBackgroundHueAdjust;
extern XConsoleVariable g_CVarARBackgroundSaturationAdjust;
extern XConsoleVariable g_CVarARBackgroundLightnessAdjust;

extern XConsoleVariable g_CVarEnableOIT;
extern XConsoleVariable g_CVarOITLayerNum;

extern XConsoleVariable g_CVarEnableShadow;
extern XConsoleVariable g_CVarShadowMapResolution;
extern XConsoleVariable g_CVarShadowDistance;
extern XConsoleVariable g_CVarShadowDepthBias;
extern XConsoleVariable g_CVarShadowSoftness;
extern XConsoleVariable g_CVarShadowCSMCascadeNum;
extern XConsoleVariable g_CVarShadowCascadeDistributionExponent;
extern XConsoleVariable g_CVarShadowSoftTransitionScale;

extern XConsoleVariable g_CVarEnableSSAO;
extern XConsoleVariable g_CVarSSAOSampleRadius;


// 形变动画的法线计算方法
enum XBlendShapeNormalMethod
{
	XMM_OIRIGINAL = 0,
	XMM_NLERP = 1,
	XMM_RECALCULATE = 2,
	XMM_NUM,
};
extern XConsoleVariable g_CVarBlendShapeNormalMethod;


#if defined(X_PLATFORM_WIN_DESKTOP)
/*Check VAO in windows EGL (windows平台引擎启动前设置， xture : 检测设备是否支持VAO， xfalse : 不检测设备VAO，直接设置不支持)
*
* @notice 因为此参数在Framework::init中需要使用，而XConVar只有在Framework初始化后才可以设置，所以改为全局的bool值
*/
extern xbool  g_bXEngineCheckDeviceVAO_of_WinEGL;
#endif

#endif //_X_ENGINE_CON_VARS_H_