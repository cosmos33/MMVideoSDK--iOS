#ifndef _UI_COLOR_TO_H_
#define _UI_COLOR_TO_H_

#include "XUIActionInterval.h"

class XUIWidget;
class XUIColorTo : public XUIActionInterval
{
public:

	static XUIColorTo* Create(const xfloat32& fDuration, const XCOLORBASE& cEndColor);

	virtual XUIColorTo* Clone() const override;
	virtual XUIColorTo* Reverse() const override;

	virtual ~XUIColorTo() {};
protected:
	XUIColorTo();

	virtual void StartWithTarget(XUINode* pTarget) override;

	virtual void ActionUpdate(const xfloat32& fProgress) override;

protected:

	xbool InitWithDuration(const xfloat32& fDuration, const XCOLORBASE& cEndColor);

protected:
	
	XCOLORBASE m_cStartColor;
	XCOLORBASE m_cEndColor;
	XCOLORBASE m_cDelta;


};
#endif
