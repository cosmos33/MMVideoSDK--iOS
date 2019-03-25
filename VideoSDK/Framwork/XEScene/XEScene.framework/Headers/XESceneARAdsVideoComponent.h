/******************************************************************************

@File         XESceneARAdsVideoComponent.h

@Version       1.0

@Created      2018/5/30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XESCENEARADSVIDEOCOMPONENT_H
#define XESCENEARADSVIDEOCOMPONENT_H
#include "XEPrimitiveComponent.h"
#include "XEAnimController.h"

class VideoInfo
{
public:
	VideoInfo(){};
	virtual ~VideoInfo(){};

	typedef XArray<VideoInfo*> VideoInfoArray;
public:
	xbool operator == (const VideoInfo& aw) const;

	xint64 m_iVideoLength = 0;
	xfloat32 m_fVideoFrameRatio = 0.0f;
	xint32 m_iVideoFrames = 0;
	XString m_sVideoName;
};

class XEVideoMultiLayer
{
public:
	class Listener : XEAnimController::Listener
	{
	public:
		virtual			~Listener() {}
		virtual void     Ls_AddVideo(const xchar* pLayerName, XEVideoMultiLayer* pVMultiLayer){};
		virtual void     Ls_SetTime(xfloat32 fTime){};
	};
	typedef XArray<Listener*> VideoLayerListenerList;

	XEVideoMultiLayer(){};
	virtual	~XEVideoMultiLayer();

	// Layer control
	virtual xint32                  AddLayer(VideoInfo* pAsset);
	void                            AddLayer(const xchar* pPath);
	virtual xint32                  GetLayerNum() const;
	virtual VideoInfo*	            GetLayer(xint32 nIndex);
	virtual VideoInfo*	            GetLayer(const xchar* szName);
	xbool                           UpdateLayer(VideoInfo* pLayer);

	virtual xfloat32				GetStartTime() const;
	virtual xfloat32				GetEndTime() const;
	virtual void				    SetEndTime(xfloat32 fValue);
	virtual void                    SetCurrentTime(xfloat32 fValue);
	virtual xfloat32				GetCurrentTime() const;

	xbool                           AddListener(Listener* pListener);
	xbool                           RemoveListener(Listener* pListener);
	void                            BroadcastAddVideo(const xchar* pLayerName);
	void                            BroadcastSetTime(xfloat32 fValue);

protected:
	XArray<VideoInfo*>	            m_aVideoInfos;
	xfloat32						m_fStartTime = 0.f;
	xfloat32						m_fEndTime = 0.f;
	VideoLayerListenerList          m_Listeners;
};

class XESceneARAdsVideoComponent 
	:public XEPrimitiveComponent
{
public:
	struct VideoLayerData
	{
		enum{ AnimLayerDataIndexNone = -2, AnimLayerDataIndexNotSet = -1 };
		xint32               nLayerIndex;
		XString              szPath;
		xbool                bActive;//layer whether actived or not.
		VideoLayerData() :nLayerIndex(AnimLayerDataIndexNone), bActive(xfalse){}
	};	


	typedef XArray<VideoLayerData> VideoLayerArray;
public:
	XESceneARAdsVideoComponent();
	~XESceneARAdsVideoComponent();
public:
	class VideoAnimController : public XEAnimController
	{
	public:		
		class Listener : XEAnimController::Listener
		{
		public:
			virtual			~Listener() {}
			virtual void     Ls_AddVideo(const xchar* pLayerName, VideoAnimController/*XESceneARAdsVideoComponent*/* pController);
		};
		
		typedef XArray<Listener*> VideoListenerList;
		
		VideoAnimController(XESceneARAdsVideoComponent* pVideoComponent);
		virtual ~VideoAnimController();
	public:
		virtual void                        Tick(xfloat32 fInterval) override;
		virtual xint32                      GetTimeLength() const override;
		virtual void                        SetTime(xint32 nTime) override;
		void                                SetAnimEndTime(xfloat32 fEndTime);
		xfloat32                            GetVideoDuration(const xchar* pSeqName);
		void                                ActiveAllLayers();
		void                                DeactiveAllLayers();

	    xbool                               AddLayer(const xchar* szLayerName);
		xint32                              AddLayer(VideoInfo* videoInfo);
		void                                RemoveLayer(xint32 nIndex);
		void                                RemoveLayer(const xchar* szName);
		void                                RemoveAllLayers();
		xint32                              GetLayerNum() const;
		VideoInfo*	                        GetLayer(xint32 nIndex);
		VideoInfo*	                        GetLayer(const xchar* szName);
		xbool                               HasLayer(const xchar* pLayerName);
		xbool                               AddListener(Listener* pListener);
		xbool                               RemoveListener(Listener* pListener);
		void                                BroadcastAddVideo(const xchar* pLayerName);

		virtual XEVideoMultiLayer*          GetVideoMultiLayer();

	protected:
		void                                _SetVideoMultiLayer(XEVideoMultiLayer* pVideoMultiLayer);
		XEVideoMultiLayer*                  _GetVideoMultiLayer();
	protected:
		XESceneARAdsVideoComponent*         m_pVideoComponent;
		VideoInfo::VideoInfoArray           m_aVideoInfoArray;
		VideoListenerList                   m_Listeners;		
	};

public:
	virtual void               Release() override;
	virtual void               Render(XEViewport* pViewport) override;
	virtual void               Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*        Serialize(XMLElement* pEleParent) override;

	XEAnimController*          GetVideoAnimationController();
	X_EES_LINE const XEAnimController* GetVideoAnimationController() const;

#if X_PLATFORM_WIN_DESKTOP
	virtual void               GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif
	void                       setRect(XVECTOR4 rec);
	inline XVECTOR4            getRect() const{ return XVECTOR4(m_nX,m_nY,m_nWidth,m_nHeight); };
	inline XVECTOR4            getRelativeRect() const{ return m_nViewRelativeRect; };

    const xchar*                            GetCurPlayAnimation();
	virtual XEAnimController*               AssignAnimationController();
	void                                    AddAnimVideo(const xchar* pPath, const xbool bActive = xfalse, const xbool bPlay = xfalse, xbool bExclusively = xtrue);
	void                                    ActiveLayer(const xchar* pLayerName, xbool bPlay = xtrue, xbool bExclusively = xtrue);
	void                                    ActiveAllLayers(xbool bPlay = xtrue);
	void                                    DeacitveLayer(const xchar* pLayerName);
	void                                    DeacitveAllLayers();
	xbool                                   HasActiveLayer();
	xbool                                   HasLayer(const xchar* pLayerName);
	const xchar*                            GetFirstActiveLayerName() const;
	VideoLayerData&                         GetVideoLayerData(const xchar* pLayerName);
	VideoLayerData&                         GetVideoLayerData(const xint32 nLayerIndex = 0);
	X_EES_LINE const VideoLayerData&        GetVideoLayerData(const xint32 nLayerIndex = 0) const;
	X_EES_LINE const VideoLayerArray&       GetVideoLayerArray() const { return m_aVideoLayer; };
	X_FORCEINLINE const XString&            GetAssetPath() const { return m_szAssetPath; }
	X_FORCEINLINE XEVideoMultiLayer*&       GetAnimMultiLayer(){ return m_pVideoMulLayer; }
	void                                    AddAnimVideo(VideoInfo* pVideoInfo, const xbool bActive = xfalse, const xbool bPlay = xfalse, xbool bExclusively = xtrue);
	VideoInfo*	                            GetAnimVideoInfo(const xchar* szName);

	
public:
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	XE_COMPONENT_CAST(XESceneARAdsVideoComponent)
	X_CLASS_DEF(XESceneARAdsVideoComponent)
	static const XString COMPONENT_TYPENAME;
protected:
	VideoLayerArray              m_aVideoLayer;
	XString                      m_szAssetPath;
public:
	xint32                       m_nX;
	xint32                       m_nY;
	xint32                       m_nWidth;
	xint32                       m_nHeight;
	xint32                       m_nXOffset = 0;
	xint32                       m_nYOffset = 0;
	xfloat32                     m_fScreenRatio = 1.0f;
	XCOLORBASE                   m_clr;
	xbool                        m_bSolid;
	//relative width and height
	xint32                       m_nRelativeWidth;
	xint32                       m_nRelativeHeight;
	XVECTOR4                     m_nViewRelativeRect = XVECTOR4(0,0,1,1);
	VideoAnimController*         m_pAnimController;
	XEVideoMultiLayer*           m_pVideoMulLayer;
	
};

#endif // XESCENEARADSVIDEOCOMPONENT_H
