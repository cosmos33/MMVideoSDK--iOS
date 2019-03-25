/******************************************************************************

@File         XECameraActor.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_CAMERAACTOR_H
#define XE_CAMERAACTOR_H
#include "XEActor.h"
#include "XECameraComponent.h"
#include "XECanvas3DTextureComponent.h"

class XEViewport;
class XECameraActor 
	:public XEActor
{
public:
	XECameraActor();
	~XECameraActor(){};
public:
	static xbool RestoreActiveCameraInViewport(XEViewport* pViewportWithWorld);
public:
	virtual void Initialize(XEWorld* pWorld) override;
	xbool        MarkAsActiveCamera();//exclusively from other cameras.
	xbool        ApplyAsSystemCamera();//both take effect whether active or not. 
	virtual void RenderDummyShape(XEViewport* pViewport) override; 
	virtual void Release() override;

	virtual void RenderDrawDebug(XEViewport* pViewport)override;
	virtual void Tick(xfloat32 fDel, xbool bForceTick = xtrue)override;

public:
	XE_ACTOR_CAST(XECameraActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XECameraActor)
	static const XString	   ACTOR_TYPENAME;
private:
	void		 CalculateFrustumVertices();
protected:
	XECanvas3DTextureComponent m_Canvas3DTexture;
	XArray<XVECTOR3>		   m_aFrustumVertices;
};

#endif // XE_CAMERAACTOR_H
