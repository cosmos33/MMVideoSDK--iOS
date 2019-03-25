#ifndef _UIEVENT_H_
#define _UIEVENT_H_

#include "XMemBase.h"
#include "XRefCount.h"
#include "XUINode.h"

class XUIEvent : public XMemBase
{
public:
	enum Type
	{
		TOUCH,
		KEYBOARD,
		ACCELERATION,
		MOUSE,
		FOCUS,
		GAME_CONTROLLER,
		CUSTOM
	};
	XUIEvent(Type eType);
	virtual ~XUIEvent(){}
	void		Release();
	Type		GetType() const { return m_eType; }
	void		StopPropagation() { m_bStopped = xtrue; }
	xbool		IsStopped() const { return m_bStopped; }
	XUINode*	GetCurrentNode() { return m_pNode; }
protected:
	void		SetCurrentNode(XUINode* pNode){ m_pNode = pNode; }
	Type		m_eType;
	xbool		m_bStopped;
	XUINode*	m_pNode;
	friend class XUIEventDispatcher;
};
#endif
