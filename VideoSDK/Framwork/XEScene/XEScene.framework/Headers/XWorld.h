/******************************************************************************

 @File         XWorld.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XWorld.

 @HISTORY:      * The World is the top level object representing a map or a sandbox in which Actors and Components will exist and be rendered.

******************************************************************************/
#ifndef _X_WORLD_H_
#define _X_WORLD_H_

#include "XMemBase.h"
#include "XArray.h"
#include "XRectangle.h"
#include "XMath3D.h"

class IXPrimitiveBase;
class XCameraViewFrustum;
class IXLightBase;


class IXWorld : public XMemBase
{
public:
	virtual				~IXWorld() {};
	virtual	void		Init() = 0;
	virtual void		Release() = 0;
	virtual void		Clear() = 0;

	virtual void		BeginView() = 0;
	virtual void		EndView() = 0;

	virtual void		RegisterPrimitive(IXPrimitiveBase* pPrimitive) = 0;
	virtual void		GetVisiblePrimitives(XArray<IXPrimitiveBase*>& aryPrimitives, XCameraViewFrustum* pFrustum, XRectI* pRect) = 0;
	virtual void		RegisterLight(IXLightBase* pLight) = 0;
	virtual void		GetVisibleLights(XArray<IXLightBase*>& lights, XCameraViewFrustum* pFrustum) = 0;
	virtual void		RegisterEnvLight(IXLightBase* pLight, xuint32 nIdx) = 0;
	virtual IXLightBase*GetEnvLight(xuint32 nIdx) = 0;

	virtual void		GetCastShadowPrimitives(XArray<IXPrimitiveBase*>& aryPrimitives, XCameraViewFrustum* pFrustum) const = 0;

	static void			CreateWorld(IXWorld** ppWorld);
};

extern IXWorld* g_pXWorld;


#endif //_X_WORLD_H_