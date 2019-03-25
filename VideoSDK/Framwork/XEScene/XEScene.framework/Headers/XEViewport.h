/******************************************************************************

@File         XEViewport.h

@Version       1.0

@Created      2017, 6, 2

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_VIEWPROT_H_
#define _XE_VIEWPROT_H_

#include "XMemBase.h"
#include "XString.h"
#include "XViewport.h"
#include "XBaseCamera.h"
#include "XPlatformWindow.h"
#include "XHashTable.h"
#include "XESingleton.h"
#include "XClass.h"

class XEWorld;

#define FPS_HISTORY_NUM 3
//orbit/pan camera simulator.
class XEViewport;
class OrbitPanView;
typedef xbool(*funcLockLookAt)(OrbitPanView*);
class OrbitPanView
{
public:
	OrbitPanView(XEViewport* pVp) 
		: m_pXEViewport(pVp)
		, m_vLookAt(0.f)
		, m_fMouseSensitivity(0.2f)
		, m_fLookAtDistance(4.f)
		, m_matPointLookAtFixView(XMATRIX4::IDENTITY)
		, m_vRotateDelta(0.f)
		, m_vPointLookAtEuler(0.f)
		, m_lpFuncLockLookAt(NULL){}
	~OrbitPanView(){}
public:
	inline void            SetLookAt(const XVECTOR3& vLookAt){ m_vLookAt = vLookAt; }
	inline void            SetLockLookAtFunc(funcLockLookAt func){ m_lpFuncLockLookAt = func; }
	inline funcLockLookAt  GetLockLookAtFunc()const{ return m_lpFuncLockLookAt; }
	inline void            SetMouseSensitivity(xfloat32 fVal = .2f){ m_fMouseSensitivity = fVal; }
	inline void            SetLookAtDistance(xfloat32 fVal = 4.f){ m_fLookAtDistance = fVal; }
	inline xfloat32        GetMouseSensitivity()const{ return m_fMouseSensitivity; }
	inline xfloat32        GetLookAtDistance()const{ return m_fLookAtDistance; }
	inline const XVECTOR3& GetLookAt()const{ return m_vLookAt; }
	void                   UpdateView(xbool bUsingCallbackFunc = xtrue);//update manually, if bUsingCallbackFunc is set to true, the look-at point will depend on this callback function.
	void                   RatateAround(xint32 nDeltaX, xint32 nDeltaY);//the mouse delta values.
	void                   SetYawLimit(xfloat32 fMinEulerRadian, xfloat32 fMaxEulerRadian, xbool bEnable = xtrue);
	void                   SetRollLimit(xfloat32 fMinEulerRadian, xfloat32 fMaxEulerRadian, xbool bEnable = xtrue);
private:
	XVECTOR3               m_vLookAt;//can be locked to a target,or a position.(interested point)
	XEViewport*            m_pXEViewport;
	xfloat32               m_fMouseSensitivity;
	xfloat32               m_fLookAtDistance;
	XMATRIX4               m_matPointLookAtFixView;
	XVECTOR2               m_vRotateDelta;
	XVECTOR3               m_vPointLookAtEuler;
	funcLockLookAt         m_lpFuncLockLookAt;
	struct cameraRotateLimitation
	{
		xfloat32 fMinEulerRadian;
		xfloat32 fMaxEulerRadian;
		xbool    bEnable;
		cameraRotateLimitation() :fMinEulerRadian(0.f), fMaxEulerRadian(0.f), bEnable(xfalse){}
	};
	cameraRotateLimitation m_rotateLimitRoll;//rotate around x.
	cameraRotateLimitation m_rotateLimitYaw;//rotate around y.
};

class XEViewport 
	: public XMemBase
{
	friend class XEGame;
public:

	enum XVPType
	{
		XVP_PERS = 0,
		XVP_TOP,
		XVP_LEFT,
		XVP_FRONT,
		XVP_NUM,
	};
	enum XVPFpsRenderPos
	{
		XVP_LEFTTOP = 0,
		XVP_LEFTBOTTOM,
		XVP_RIGHTTOP,
		XVP_RIGHTBOTTOM
	};
	static const xchar* GetVPTypeName(XVPType eType);

	enum XVPARenOpt
	{
		XVPA_RendCoord = 1<<0,		// Coordinate;
		XVPA_RendFps = 1<<1,		// fps
		XVPA_CameraPos = 1<<2,		// Camerapos
		XVPA_PreviewMode = 1 << 3,	// play world
		XVPA_StateGroup = 1 << 4,	// Engine state group
#ifdef _DEBUG
		XVPA_DefaultRenOpt = XVPA_RendCoord | XVPA_RendFps | XVPA_CameraPos,
#else 
		XVPA_DefaultRenOpt = XVPA_RendCoord | XVPA_RendFps,
#endif
	};

public:
								XEViewport(XEViewport::XVPType eType, IXPlatformWindow* pWindow, const XString &strName);
	virtual						~XEViewport();	
	void						Render();
	void						Resize();
	inline const XString&		GetName() const { return m_strName; }		
	inline XViewport*			GetXViewport() { ASSERT(NULL != m_pXViewport); return m_pXViewport; }
	inline xbool				IsActive() { return m_bActive; }
	inline void					SetActive(xbool bActive) { m_bActive = bActive; }
	inline XVPType				GetType() const { return m_eType; }
	inline xint32				GetAddRenderOption() { return m_nAddRendOption; }
	inline void					SetAddRenderOption(xuint32 nOption) { m_nAddRendOption = nOption; }
	
	void					    AttachWorld(XEWorld *pWorld);
	XEWorld*				    GetAttachWorld() { return m_pAttachWorld; }
	inline XBaseCamera*			GetWorkCamera() { return GetAttachCamera(); }//same to the attached camera.
	X_EES_LINE inline const XBaseCamera* GetWorkCamera() const { return GetAttachCamera(); }//same to the attached camera.
	inline XBaseCamera*			GetAttachCamera() { return m_pAttachCamera; }
	X_EES_LINE inline const XBaseCamera* GetAttachCamera()const { return m_pAttachCamera; }
	inline IXPlatformWindow*    GetPresentWindow(){ return m_pPresentWindow; }
	inline void                 SetPresentWindow(IXPlatformWindow* pWindow){ m_pPresentWindow = pWindow; }

	void					    AttachCamera(XBaseCamera *pAttachCamera);
	void						SetOwnerCameraParam(XBaseCamera *pCamera);
	void					    AttachToOwnerCamera();

	void						SetCameraPosTextColor(xfloat32 r = 1.0f, xfloat32 g = 1.0f, xfloat32 b = 0.8f, xfloat32 a = 1.0f);
	inline void					SetCameraPosTextColor(const XCOLORBASE& color){ m_CameraTextColor = color; }
	void						SetFpsTextColor(xfloat32 r = 1.0f, xfloat32 g = 1.0f, xfloat32 b = 1.0f, xfloat32 a = 1.0f);
	inline void					SetFpsTextColor(const XCOLORBASE& color){ m_FpsTextColor = color; }
	inline void					SetFpsRenderPos(const XVPFpsRenderPos FpsRenderpos){ m_FpsRenderpos = FpsRenderpos; }

	xint32						GetRenderY();

	OrbitPanView*               GetOribitPanView();
	XBaseCamera*				GetSceneCamera(){ return m_pOwnerCamera; }

protected:		

	void						Init();
	void						Release();
	void						RenderAdditional();
	void						RenderCoordinate();
	void						RenderFps();
	void						RenderCameraPos();
	void						RenderPreviewModeString();
	void						RenderStatesGroup();
	void						UpdateFpsHistory();
	void						RenderOrderWhenFpsPosInTop();
	void						RenderOrderWhenFpsPosInBottom();

	xfloat32					m_fCameraFOV;
	xfloat32					m_fCameraNear;
	xfloat32					m_fCameraFar;
	xbool						m_bActive;
	xint32						m_nAddRendOption;   // XVPARenOpt

	XString						m_strName;
	XVPType						m_eType;

	IXPlatformWindow*			m_pPresentWindow;	
	XBaseCamera*				m_pOwnerCamera;
	XBaseCamera*				m_pAttachCamera;
	XViewport*					m_pXViewport;
	
	XEWorld*					m_pAttachWorld;

	xfloat32					m_fFPSHistoryTime[FPS_HISTORY_NUM];
	xint32						m_nCurHistoryIndex;

	OrbitPanView*               m_pOribitPanView;
	XCOLORBASE					m_FpsTextColor;
	XCOLORBASE					m_CameraTextColor;

	XVPFpsRenderPos				m_FpsRenderpos;
};

typedef XHashTable<XString, XEViewport*> XEViewportMap;

class XEViewportManager : public XESingleton<XEViewportManager>
{
	friend class XEGame;	
	friend class XEEngine;
public:
								XEViewportManager();
	virtual						~XEViewportManager();

	XEViewport*				    CreateXEViewport(XEViewport::XVPType eType, const XString &strName, IXPlatformWindow* pWindow);
	void					    DeleteXEViewport(const XString &strName);
	XEViewport*				    GetXEViewport(const XString &strName);
	XEViewport*                 GetXEViewport(const XEWorld* pWorld);//get the viewport looking at the world.
	XEViewport*					GetXEViewport(const IXPlatformWindow *pWin);
	XArray<XEViewport*>			GetRefXEViewport(const XBaseCamera *pCamera);

protected:
	inline XEViewportMap&		GetViewportMap() { return m_mXEViewport; }

	XEViewportMap			    m_mXEViewport;

};


#endif

