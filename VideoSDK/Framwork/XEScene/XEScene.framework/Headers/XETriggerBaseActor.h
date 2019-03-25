/******************************************************************************

@File         XETriggerBaseActor.h

@Version       1.0

@Created      2018, 12, 17 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_TRIGGER_BASE_ACTOR_H
#define XE_TRIGGER_BASE_ACTOR_H

#include "XEActor.h"
#include "XEEventUtil.h"
#include "XEVariant.h"
#include "XETriggerUtil.h"


class XETriggerBaseActor : public XEActor
{
public:
	/*
	** For developers using in code.
	** If has no specific Event, you can derived from Listener, and overwriting Execute func.
	** Note, you should set the TriggerState value, it presents when should call the Execute func. 
	*/
	class Listener
	{
	public:
		Listener() : m_nTriggerState(0), m_bActive(xfalse), m_fCountDown(0.0f), m_fResetCountDown(0.0f), m_bTriggerRepeat(xtrue){};
		virtual ~Listener(){};
		virtual void			Execute(){}
		void					SetTriggerState(xuint32 state){ m_nTriggerState = state; }
		xuint32					GetTriggerState(){ return m_nTriggerState; }
		xfloat32				GetCountDown(){ return m_fCountDown; }
		void					SetCountDown(xfloat32 fVal){ m_fCountDown = fVal; }
		void					ResetCountDown(){ m_fCountDown = m_fResetCountDown; }
		void					SetActive(xbool bActive){ m_bActive = bActive; }
		xbool					IsActive(){ return m_bActive; }
		void					SetTriggerRepeat(xbool bRepeat){ m_bTriggerRepeat = bRepeat; }
		xbool					IsTriggerRepeat(){ return m_bTriggerRepeat; }
	private:
		xuint32					m_nTriggerState;
		xbool					m_bActive; //be ready to execute.
		xfloat32				m_fCountDown; //delay time
		xfloat32				m_fResetCountDown; //use to reset delay time.
		xbool					m_bTriggerRepeat; //repeat trigger or not.
	};
	void						AddListener(Listener *pListener);
	void						RemoveListener(Listener *pListener);

public:
	XETriggerBaseActor();
	virtual ~XETriggerBaseActor();

public:

	//XEActor Interface Begin.
	virtual void				Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void				Render(XEViewport* pViewport) override;
	virtual void				Initialize(XEWorld* pWorld) override;
	virtual void				Release() override;
	virtual void                Deserialize(const XMLElement* pEleActor) override;
	virtual XMLElement*         Serialize(XMLElement* pEleParent) override;
	//XEActor Interface End.

	//response
	virtual void				OnOverlapBegin();
	virtual void				OnOverlapStay();
	virtual void				OnOverlapEnd();

	//register event.
	virtual void				AddOverlapBeginEventData(XEEventUtil::XEEventType eEventType, const XEVariant& eventData = XEVariant(),
		const XString& strSender = "", const XString& strExecutor = "", xfloat32 fdelay = 0.0f);
	virtual void				AddOverlapStayEventData(XEEventUtil::XEEventType eEventType, const XEVariant& eventData = XEVariant(),
		const XString& strSender = "", const XString& strExecutor = "", xfloat32 fdelay = 0.0f);
	virtual void				AddOverlapEndEventData(XEEventUtil::XEEventType eEventType, const XEVariant& eventData = XEVariant(),
		const XString& strSender = "", const XString& strExecutor = "", xfloat32 fdelay = 0.0f);
	xbool						RemoveOverlapEventData(xint32 nAddIndex);

	virtual void				OnOverlapCheck(TriggerOverlapCheckType eType  = TriggerOverlapCheck_AABB);

	xint32                      GetMaxAddIndex();
	const XETriggerData&        GetTriggerData(xint32 nIndex) const;
	XETriggerData&				GetTriggerData(xint32 nIndex);

	const XArray<XETriggerData>& GetTriggerDataList() const{ return m_aTriggerEventDataArray; }

	void						ResetTriggerData();//reset bFirstExec state after stop simulated.
	
public:
#if X_PLATFORM_WIN_DESKTOP
	static xbool                BuildLuaScriptEntranceCodeFile(const XString& filePath);
#endif
protected:
	void						AddOverlapEventData(TriggerState nState, XEEventUtil::XEEventType eEventType, const XEVariant& eventData, 
		const XString& strSender = "", const XString& strExecutor = "", xfloat32 fdelay = 0.0f);
	
	void						OnOverlap(TriggerState nState);
	XEEventBase*				GenerateTriggerEvent(XETriggerData& triggerData);
	void						OnOverlapCheckAABB(); //aabb intersect or not
	void						OnOverlapCheckPos(); //move actor pos is in Trigger actor aabb or not.

	void						SerializeEventData(XMLElement* pEleTriggerItem, XEEventUtil::XEEventType eEventType, const XEVariant& eventData);
	void						SerializeTransform(XMLElement* pEleTriggerItem, const XEVariant& eventData);
	void						DeserializeEventData(const XMLElement* pEleTriggerItem, XEEventUtil::XEEventType eEventType, XEVariant& eventData);
	void						DesetializeTransform(const XMLElement* pEleTriggerItem, XEVariant& eventData);

public:
	XE_ACTOR_CAST(XETriggerBaseActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XETriggerBaseActor)
	static const XString ACTOR_TYPENAME;
	static XETriggerData DEFAULT_TRIGGER_DATA;
protected:
	XArray<XETriggerData>		m_aTriggerEventDataArray;
	XArray<Listener*>			m_aListener; 
	xbool						m_bOverLaped;
	xbool						m_bNeedResetTriggerData; //need to reset trigger bFirstExec state.
};

#endif //XE_TRIGGER_BASE_ACTOR_H