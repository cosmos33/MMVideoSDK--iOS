#ifndef _UI_SPEED_H_
#define _UI_SPEED_H_

#include "XUIAction.h"

class XUIActionInterval;
class XUISpeed : public XUIAction
{
public:

	static XUISpeed* Create(XUIActionInterval* pAction, const xfloat32& fSpeed);

	virtual XUISpeed* Clone() const override;
	virtual xbool IsDone() const override;

	virtual ~XUISpeed();
protected:
	XUISpeed();


	virtual void StartWithTarget(XUINode* pTarget) override;
	

	virtual void Step(const xfloat32& dt) override;
	virtual void Stop() override;
	
protected:

	xbool InitWithAction(XUIActionInterval* pAction, const xfloat32& fSpeed);

protected:
	
	XUIActionInterval* m_pAction;
	xfloat32 m_fSpeed;

};
#endif
