/******************************************************************************

@File         XECameraComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XECAMERACOMPONENT_H
#define XECAMERACOMPONENT_H
#include "XEPrimitiveComponent.h"
#include "XPerspectiveCamera.h"
#include "XOrthoCamera.h"

class XEWorld;
class XECameraComponent :public XEPrimitiveComponent
{
public:
	enum  XEProjectionModel
	{
		XEPM_PERSPECTIVE = 0,
		XEPM_ORTHO
	};  
public:
	XECameraComponent();
	~XECameraComponent();
public:
	virtual void                     Release() override;
	virtual void                     Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*              Serialize(XMLElement* pEleParent) override;
	virtual void                     UpdateForSerialize() override;
	virtual void                     Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;

#if X_PLATFORM_WIN_DESKTOP
	virtual void                     GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif
public:
	XPerspectiveCamera*              SetAsPerspectiveCamera(xfloat32 fFov = XENGINE_DEGREETORADIAN(DEFAULTFOVDEGREE), xfloat32 fZNear = DEFAULTZNEAR, xfloat32 fZFar = DEFAULTZFAR, xfloat32 fRatio = DEFAULTRADIO);
	XOrthoCamera*                    SetASOrthoCamera(xfloat32 fLeft, xfloat32 fRight, xfloat32 fBottom, xfloat32 fTop, xfloat32 fZNear, xfloat32 fZFar);	
	xbool                            IsSystemCamera() const;
	xbool                            ApplyAsSystemCamera();
	xbool							 SwitchProjectModel(XEProjectionModel eModel);	
	static XBaseCamera*              GetSystemCamera(XEWorld* pWorldContext);	
public:
	X_FORCEINLINE XBaseCamera*       GetCamera(){ return m_pBaseCamera; }
	X_EES_LINE X_FORCEINLINE const XBaseCamera* GetCamera() const { return m_pBaseCamera; }
	X_FORCEINLINE xbool              IsPerspectiveCamera() const { return NULL != m_pBaseCamera ? m_pBaseCamera->IsPerspective() : xfalse; }
	X_FORCEINLINE xbool              IsOrthoCamera() const { return NULL != m_pBaseCamera ? m_pBaseCamera->IsOrthogonal() : xfalse; }
	X_FORCEINLINE xbool              IsActiveCamera() const{ return m_bActive; }
	X_FORCEINLINE void               SetActiveCamera(xbool bActive) { m_bActive = bActive; }
	xbool                            SetZNear(xfloat32 fZNear, xbool bUpdateProjMat = xtrue);
	xbool                            SetZFar(xfloat32 fZFar, xbool bUpdateProjMat = xtrue);
	xbool							 SetFov(xfloat32 fFov);
	xfloat32			             GetZFar() const;
	xfloat32			             GetZNear() const;

	X_FORCEINLINE xfloat32			 GetFov() const { return m_fFov; }
	xbool							 SetOrthoWidth(xfloat32 fOrthoWidth);
	X_FORCEINLINE xfloat32			 GetOrthoWidth() const { return m_fOrthoWidth; }

X_EEB_BEGIN//not export to the lua side.
	static xbool                     SerializeCamera(XBaseCamera* pBaseCamera, XMLElement* pElement, xbool bIncludeTranform = xfalse);
	static XBaseCamera*              DeserializeCamera(const XMLElement* pElement, xbool bIncludeTranform = xfalse);//XBaseCamera* should be deleted after your using.[NEW INSIDE], cameraType:Ortho, Perspective
X_EEB_END

protected:
	// Override this method for custom behavior.
	virtual xbool                    MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual xbool                    ApplyWorldTransformImpl(const XMATRIX4& mat) override;
public:
	XE_COMPONENT_CAST(XECameraComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XECameraComponent)
	static const XString COMPONENT_TYPENAME;
private:
	XBaseCamera*                     m_pBaseCamera;
	xbool                            m_bActive;

	//perspective camera.
	xfloat32						 m_fFov;

	//ortho camera.
	xfloat32						 m_fOrthoWidth;
};

#endif // XECAMERACOMPONENT_H
