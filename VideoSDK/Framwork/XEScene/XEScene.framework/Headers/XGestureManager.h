#ifndef _IXGESTUREMANAGER_H_
#define _IXGESTUREMANAGER_H_

#include "XMemBase.h"
#include "XMath3D.h"
#include "XHashTable.h"
#include <deque>
#include <functional>

// 点击
struct GestureClickParam
{
	enum class Type
	{
		NormalClick,
		LongClick,
		MultiClick
	};
	enum class State
	{
		Pressed,
		Raised
	};
	XVECTOR2 vPosition;
	Type	 eType;
	State	 eState;
	xfloat32 fParam;	//NormalClick --nouse, LongClick --seconds, MultiClick -- click times per second(not implemented)
};

// 单指移动
class GestureMoveParam
{
public:
	enum class State
	{
		Moved,
		Stopped,
	};
	XVECTOR2	vLastPosition;
	XVECTOR2	vPosition;
	State		eState;
};

// 双指同向移动
class GestureMove2Param
{
public:
	enum class State
	{
		Moved,
		Stopped,
	};
	XArray<XVECTOR2> aPositions;
	XArray<XVECTOR2> aLastPositions;
	XVECTOR2    vDir;
	State		eState;
};

// 双指不同向移动
class GesturePinchParam
{
public:
	enum class State
	{
		Moved,
		Stopped,
	};
	XArray<XVECTOR2> aPositions;
	XArray<XVECTOR2> aLastPositions;
	xfloat32    fLastScale;
	xfloat32	fNewScale;
	State		eState;
};

// 双指旋转
class GestureRotate2Param
{
public:
	enum class State
	{
		Moved,
		Stopped,
	};
	enum class Order
	{
		Clockwise,
		CounterClockwise,
		NotCircle
	};
	State eState;
	Order eOrder;
};

class XGestureManager : public XMemBase
{
public:
	typedef std::function<void(GestureClickParam*)> TriggerClickCallBack;
	typedef std::function<void(GestureMoveParam*)> TriggerMoveCallBack;
	typedef std::function<void(GestureMove2Param*)> TriggerMove2CallBack;
	typedef std::function<void(GesturePinchParam*)> TriggerPinchCallBack;
	typedef std::function<void(GestureRotate2Param*)> TriggerRotate2CallBack;
public:
	XGestureManager();
	virtual					~XGestureManager(){}

	// 参数设置
	// 连续点击的间隔时间，点击间隔在该时间内视为连续点击，否则为普通单击，默认0.2s
	virtual void			SetMultiClickInterpTime(xfloat32 fTime);
	virtual xfloat32		GetMultiClickInterpTime()const;
    
    // 长按的判定时间，默认0.2s
    virtual void            SetLongPressTime(xfloat32 fTime);
    virtual xfloat32        GetLongPressTime()const;
    
	// 事件处理
	virtual void			HandleTouchesBegin(xint32 nNumber, intptr_t ids[], xfloat32 fPosX[], xfloat32 fPosY[]);
	virtual void			HandleTouchesMove(xint32 nNumber, intptr_t ids[], xfloat32 fPosX[], xfloat32 fPosY[]);
	virtual void			HandleTouchesEnd(xint32 nNumber, intptr_t ids[], xfloat32 fPosX[], xfloat32 fPosY[]);
	virtual void			Tick(xfloat32 fTickTime);

	TriggerClickCallBack	OnTouchClickEvent_CallBack;
	TriggerMoveCallBack		OnTouchMoveEvent_CallBack;
	TriggerMove2CallBack	OnTouchMove2Event_CallBack;
	TriggerPinchCallBack	OnTouchPinchEvent_CallBack;
	TriggerRotate2CallBack  OnTouchRotate2Event_CallBack;
public:
	xbool					m_bTouching;
	xbool					m_bMoving;
	xfloat32				m_fPressedTime;

	xbool					m_TouchLongClick;
	xbool					m_TouchMultiClick;
	xbool					m_TouchWaitingForNextClick;
	xuint32					m_TouchEndTime;
	XVECTOR2				m_vLastPos;

	xbool					m_TouchPinch;
	xbool					m_TouchMoved;
	xbool					m_TouchMoved2; //双指平移

	xint32					m_TouchMoveNums;
	xint64					m_TouchMoveId;
	XVECTOR2				m_TouchPinchBegin;//distance and scale

	XHashTable<intptr_t, std::deque<XVECTOR2>>		m_tbPosDeque;
protected:
	
	void					Recognize(xint32 nNumber, intptr_t ids[], xfloat32 fPosX[], xfloat32 fPosY[]);
	XArray<intptr_t>        m_aMissMove;
	xfloat32                m_fLastScale;
	xfloat32				m_fMultiClickInterpTime;
    xfloat32                m_fLongPressTime;
};

extern XGestureManager* g_pIXGestureManager;

#endif
