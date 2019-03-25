/******************************************************************************

@File         XEGame.h

@Version       1.0

@Created      2017, 6, 2

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_GAME_H_
#define _XE_GAME_H_

#include "XHashTable.h"
#include "XArray.h"
#include "XApplication.h"
#include "XPlatformWindow.h"
#include "XEngineRoot.h"
#include "XEViewport.h"

class XEWorld;
class XEGame : public IXApplication
{
public:
									   XEGame();
	virtual					           ~XEGame();
	typedef XArray<XEWorld*>           XEWorldList;
public:
	// 底层引擎初始化的时候会调用的函数
	virtual xbool			           Init(const XApplicationInitParameter* pParam) override;
	virtual void			           Release() override;
	virtual void			           FrameStep() override;
	virtual XViewport*		           GetAppViewPort() override { return m_pCurViewPort->GetXViewport(); }
public:
	static XEGame*			           GetInstance();
	void							   ReleaseAllWorld();
	inline void				           SetCurDeltaTime(xfloat32 fDel) { m_fCurDeltaTime = fDel; }
	inline void                        SetTickEnable(xbool bEnable){ m_bEnableTick = bEnable; }
	inline xfloat32			           GetCurDeltaTime() { return m_fCurDeltaTime; }	
	XEWorld*				           CreateXEWorld(XEWorld* pWorld = NULL );
	X_FORCEINLINE XEWorldList&         GetWorldList(){ return m_vWorld; }
	X_FORCEINLINE const XEWorldList&   GetWorldList() const{ return m_vWorld; }
	void					           DeleteXEWorld(XEWorld *pWorld);
	void					           SetCurViewPort(XEViewport* pViewport) { m_pCurViewPort = pViewport; }
	XEViewport*                        GetCurViewPort(){ return m_pCurViewPort; }
public:
	class TickListener
	{
		friend class XEGame;
	public:
		                               TickListener(){};
		virtual                       ~TickListener(){};
	protected:
		virtual  void                  Tick(xfloat32 fDel) = 0;
	};
	xbool                              AddTickListener(TickListener* pTickListener);
	xbool                              RemoveTickListener(TickListener* pTickListener);
protected:
	void					           Tick();
	void					           Render();
	XEViewport*				           m_pCurViewPort;
	XEWorldList				           m_vWorld;
	xfloat32				           m_fCurDeltaTime;
	xbool                              m_bEnableTick;
	XArray<TickListener*>              m_aTickListener;
};

#endif



