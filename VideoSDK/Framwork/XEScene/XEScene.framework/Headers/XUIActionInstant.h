#ifndef _UIACTIONINSTANT_H_
#define _UIACTIONINSTANT_H_

#include "XUIFiniteTimeAction.h"

class XUIActionInstant : public XUIFiniteTimeAction
{
public:

	virtual xbool IsDone() const override;


protected:
	XUIActionInstant();
	virtual ~XUIActionInstant() {};

	virtual void StartWithTarget(XUINode* pTarget) override;
	virtual void Step(const xfloat32& dt) override;
protected:
	xbool m_bDone;

};
#endif
