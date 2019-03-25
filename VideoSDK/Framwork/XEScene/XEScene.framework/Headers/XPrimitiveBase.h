/******************************************************************************

 @File         XPrimitiveBase.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XPrimitiveBase.

 @HISTORY:

******************************************************************************/
#ifndef _X_PRIMITIVE_H_
#define _X_PRIMITIVE_H_

#include "XSys.h"
#include "XCustomGeometry.h"
#include "XMath3D.h"
#include "XRectangle.h"
#include "XMemBase.h"
#include "XBase3DTypes.h"


class IXMeshRenderBase;
class XBaseCamera;
class XViewport;
class XCameraViewFrustum;
class IXVertexDesc;
class IXIndexBuffer;
class IXMaterialInstance;
class IXRenderTarget;
class IXWorld;
class IXLightBase;


struct XPriRenderParam
{
	XBaseCamera*	pCamera;
	XViewport*		pViewport;
	XMATRIX4		matViewProj;
	XMATRIX4		matToClipSpace;
	XMATRIX4		matScreenToTranslatedWorld;
	XVECTOR4		vDiviceZToWorldZ;
	IXLightBase*	pLight;
	IXLightBase*	pEnvLights[2];
	xuint32			nLayerMask;
};

enum XPrimitiveLayerMask
{
	XPLM_ERR						= -1,
	XPLM_SKY						= XBit(0),
	XPLM_OPAQUE						= XBit(1),
	XPLM_ALPHATEST					= XBit(2),
	XPLM_DEPTH_ONLY					= XBit(3),
	XPLM_TRANSLUCENT_ZWRITE			= XBit(4),
	XPLM_TRANSLUCENT				= XBit(5),
	XPLM_TRANSLUCENT_ALPHA_ADDITIVE = XBit(6),	//ZNoWrite, Alpha = Src*1 + Des * 1
	XPLM_TRANSLUCENT_ZDISABLE		= XBit(7),
	XPLM_TRANSLUCENT_2D_ZTEST		= XBit(8),
	XPLM_TRANSLUCENT_2D				= XBit(9),// fx
	XPLM_CANVAS_3D_ZENABLE_ITEM		= XBit(10),
	XPLM_CANVAS_3D_ZDISABLE_ITEM	= XBit(11),
	XPLM_POSTPROCESS				= XBit(12),
	XPLM_CANVAS_2D_ITEM				= XBit(13),
	XPLM_BACKGROUND					= XBit(14),
	XPLM_UI							= XBit(15),
	XPLM_AR_BACKGROUND				= XBit(16),
	XPLM_TRANSLUCENT_OIT			= XBit(17),

	XPLM_CAST_SHADOW				= XBit(18),
	XPLM_UNLIT						= XBit(19),
};

struct XSubViewParam
{
	IXWorld*			pAScene;
	XViewport*			pAViewport;
	IXRenderTarget*		pSubRT;
	XCOLOR				clearColor;
};

class IXPrimitiveBase : public XMemBase
{
public:
	virtual							~IXPrimitiveBase() {};
	virtual void					Render(IXMeshRenderBase* pPriRender,const XPriRenderParam& priRenderParam) = 0;
	virtual void					RenderDepth(IXMeshRenderBase* pPriRender,const XPriRenderParam& priRenderParam) = 0;
	virtual xuint32					GetPrimitiveLayerMask() const = 0;
	virtual const XCusAABB&			GetAABB() const = 0;
	virtual xbool					IsVisible(XCameraViewFrustum* pFrustum, XRectI* pRect) = 0;
	virtual void					BeginView() = 0;
	virtual void					EndView() = 0;
};

#endif //_X_PRIMITIVE_H_