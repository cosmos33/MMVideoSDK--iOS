#ifndef _UI_ROTATE_BY_H_
#define _UI_ROTATE_BY_H_

#include "XUIRotateTo.h"

class XUIRotateBy : public XUIRotateTo
{
public:

	static XUIRotateBy* Create(const xfloat32& fDuration, const xfloat32& fRotate);

	virtual XUIRotateBy* Clone() const override;
	virtual XUIRotateBy* Reverse() const override;

	virtual ~XUIRotateBy() {};
protected:


	virtual void StartWithTarget(XUINode* pTarget) override;
	

protected:


};
#endif
