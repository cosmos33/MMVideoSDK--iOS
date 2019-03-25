#ifndef _UIACTIONINTERVAL_H_
#define _UIACTIONINTERVAL_H_

#include "XUIFiniteTimeAction.h"
#include "XUISpeed.h"

class XUIActionInterval : public XUIFiniteTimeAction
{
public:

	xfloat32 GetElapsed() { return m_fElapsed; }

	virtual XUIActionInterval* Clone() { return NULL; }
	virtual xbool IsDone() const override;

protected:

	friend class XUISpeed;

	XUIActionInterval();
	virtual ~XUIActionInterval() {};

	virtual void StartWithTarget(XUINode* pTarget) override;
	virtual void Step(const xfloat32& dt) override;

	xbool InitWithDuration(const xfloat32& fDuration);

protected:
	//已经执行的时间
	xfloat32 m_fElapsed;
	xbool m_bFirstTick;
	xbool m_bDone;

};
#endif
