#ifndef _UI_ROTATE_TO_H_
#define _UI_ROTATE_TO_H_

#include "XUIActionInterval.h"

class XUIRotateTo : public XUIActionInterval
{
public:

	static XUIRotateTo* Create(const xfloat32& fDuration, const xfloat32& fRotate);

	virtual XUIRotateTo* Clone() const override;
	virtual XUIRotateTo* Reverse() const override;

	virtual ~XUIRotateTo() {};
protected:
	XUIRotateTo();


	virtual void StartWithTarget(XUINode* pTarget) override;
	
	virtual void ActionUpdate(const xfloat32& fProgress) override;


protected:

	xbool InitWithDuration(const xfloat32& fDuration, const xfloat32& fRotate);

protected:
	
	xfloat32 m_fStartRotate;
	xfloat32 m_fEndRotate;
	xfloat32 m_fDelta;


};
#endif
