#ifndef _UIEVENTTOUCH_H_
#define _UIEVENTTOUCH_H_

#include "XUIEvent.h"
#include "XArray.h"

class XUITouch;
class XUIEventTouch : public XUIEvent
{
public:
	static const xint32 MAX_TOUCHES = 15;
	enum class EventCode
	{
		BEGAN,
		MOVED,
		ENDED,
		CANCELLED
	};

	XUIEventTouch() : XUIEvent(Type::TOUCH){ /*m_aTouches.SetNum(MAX_TOUCHES);*/ }
	virtual ~XUIEventTouch(){ m_aTouches.Clear(); }
	
	void		AddTouch(XUITouch* pTouch){ m_aTouches.Add(pTouch); }
	EventCode	GetEventCode() const { return m_eEventCode; }
	void		SetEventCode(EventCode eventCode) { m_eEventCode = eventCode; };
	const XArray<XUITouch*>& GetTouches() const { return m_aTouches; }
	void SetTouches(const XArray<XUITouch*>& aTouches) { m_aTouches = aTouches; };
	
protected:
	EventCode			m_eEventCode;
	XArray<XUITouch*>	m_aTouches;
};

#endif
