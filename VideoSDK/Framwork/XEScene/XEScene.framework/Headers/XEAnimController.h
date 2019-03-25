/******************************************************************************

@File         XEAnimController.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_CONTROLLER_H
#define XE_ANIM_CONTROLLER_H
#include "XMath3D.h"
#include "XArray.h"
#include "XClassReflector.h"

class XEModelComponent;
class XEAnimMontage;
class XESequencer;
class XEAnimComponentPlayList;
class XSkelAnimController;
class XEPrimitiveComponent;
class XEAnimController 
	: public XMemBase
	, public XClass
{
public:
	enum EPlayControlState
	{
		PS_UNKNOWN = 0,
		PS_PLAY,
		PS_PAUSE,
		PS_STOP
	};
	enum EAnimationMode
	{
		AM_RUN = 1,
		AM_EDIT
	};
	class Listener
	{
	public:
		virtual			            ~Listener() {}
		virtual	void	             Ls_StepMove(xfloat32 fTime){}
		virtual void                 Ls_PlayStateChange(EPlayControlState state){}
		virtual void                 Ls_PlayOneTimeFinished(xbool bReversePlaying){}
	};
	typedef XArray<Listener*>        StepperListenerList;
	typedef XEAnimController         Super;
public:
	        XEAnimController();
	virtual ~XEAnimController();
public:
	xbool                            AddListener(Listener* pListener);
	xbool                            RemoveListener(Listener* pListener);
	void							 NavigateToHead();
	void							 NavigateToTail();
	void                             BroadcastStepMove();
	void                             BroadcastPlayState(EPlayControlState state);
	virtual void                     BroadcastPlayOneTimeFinished(xbool bReversePlaying);
	X_FORCEINLINE EAnimationMode     GetAnimRunMode(){ return m_eAnimMode; }
	X_FORCEINLINE void               SetAnimRunMode(EAnimationMode em){ m_eAnimMode = em; }
	X_FORCEINLINE EPlayControlState  GetAnimPlayState(){ return m_ePlayState; }
	X_FORCEINLINE void	             SetAnimPlayState(EPlayControlState ps){ m_ePlayState = ps; }
	X_FORCEINLINE xint32             GetCurTime(){ return m_nCurTime; }
	X_FORCEINLINE xbool              IsLoop() const{ return m_bLoop; }
	X_FORCEINLINE xbool              IsReverse() const{ return m_bReverse; }
	X_FORCEINLINE xbool              IsPlaying() const{ return PS_PLAY == m_ePlayState; }
	X_FORCEINLINE xbool              IsAutoPlay() const{ return m_bAutoPlay; }
	X_FORCEINLINE void               SetAutoPlay(xbool bAuto){ m_bAutoPlay = bAuto; }
	X_FORCEINLINE xfloat32           GetPlayRate(){ return m_fRate; }
	X_FORCEINLINE void               SetManaulStartTime(xint32 nTime){ m_nManualStartTime = nTime; }
	X_FORCEINLINE xint32             GetManualStartTime() const{ return m_nManualStartTime; }
	X_FORCEINLINE void               SetManualEndTime(xint32 nTime){ m_nManualEndTime = nTime; }
	X_FORCEINLINE xint32             GetManualEndTime() const{ return m_nManualEndTime; }
	X_FORCEINLINE void               SetManualTimeMode(xbool bManual){ m_bManualTimeMode = bManual; }
	X_FORCEINLINE xbool              IsManualTimeMode() const{ return m_bManualTimeMode; }
	X_FORCEINLINE xbool              IsCallbackSafeLocked()const{ return m_bAnimCallbackSafeLock; }
	X_CLASS_DEF(XEAnimController)
public:							    
	virtual void                     Tick(xfloat32 fInterval);//in milliseconds
	virtual xint32                   GetTimeLength() const;
	virtual void                     SetTime(xint32 nTime);//in micro seconds.
	virtual void                     Play();//goto 0, and play again.
	virtual void                     Resume();
	virtual void                     Stop();
	virtual void                     Pause();
	virtual void                     SetLoop(xbool bLoop);
	virtual void                     SetReverse(xbool bReverse);
	virtual void                     SetPlayRate(xfloat32 fRate);
public:
	static  XEAnimController*        AssginAnimControllerForModelComponent(XEModelComponent* pComponent);
	static  XEAnimComponentPlayList* AssginAnimListForModelComponent(XEModelComponent* pComponent);
	static  xbool                    LoadAnimation(const xchar* pAssetName, XEModelComponent* pComponent );//could be .seq or .montage
	static  xbool                    UnloadAnimation(XEModelComponent* pComponent);//unload any animations(removed them as well.)
	static  xbool					 LoadLayerAnimations(const xchar* pLayerName, const XArray<XString>& arrAssetNames, XEModelComponent* pComponent);
	static  xbool					 UnloadLayerAnimations(const xchar* pLayerName, XEModelComponent* pComponent);
	static  xbool                    LoadVideo(const xchar* pAssetName, XEPrimitiveComponent* pComponent);
	static  xbool                    UnloadVideo(XEPrimitiveComponent* pComponent);
	static  void					 SetCurPlayLayerName(const XString& strLayerName){ m_strCurPlayLayer = strLayerName; }
	static  const XString&			 GetCurPlayLayerName(){ return m_strCurPlayLayer; }
protected:
	static  xbool					 UpdateLayerAnimations(const xchar* pLayerName, const XArray<XString>& arrAssetNames, XEModelComponent* pComponent);
protected:
	EPlayControlState                m_ePlayState;
	EAnimationMode                   m_eAnimMode;
	xbool                            m_bLoop;
	xbool                            m_bReverse;//reverse playing...
	xint32                           m_nCurTime;
	xfloat32                         m_fRate;
	xbool                            m_bAutoPlay;//load then play, if it is auto.
	xbool                            m_bSetTimeInTickTicked;//dirty in tick of set-time?
	StepperListenerList              m_Listeners;
	static XString					 m_strCurPlayLayer;
protected:
	xint32                           m_nManualStartTime;
	xint32                           m_nManualEndTime;
	xbool                            m_bManualTimeMode;
private:
	xbool                            m_bAnimCallbackSafeLock;//forbidden to delete this in callback, if it is true!
	xbool                            m_bTicked;

};

#endif // XE_ANIM_CONTROLLER_H
