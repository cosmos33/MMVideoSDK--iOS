#ifndef _UIFINITETIMEACTION_H_
#define _UIFINITETIMEACTION_H_

#include "XUIAction.h"

class XUIFiniteTimeAction : public XUIAction
{
protected:
	XUIFiniteTimeAction();


public:

	virtual ~XUIFiniteTimeAction();
	virtual XUIFiniteTimeAction* Clone() const override { return NULL; }

	xfloat32 GetDuration() const;
	void SetDuration(const xfloat32& fDuration);



protected:
	xfloat32 m_fDuration;
};

#endif