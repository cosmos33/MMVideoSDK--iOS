#ifndef _UI_SCALE_BY_H_
#define _UI_SCALE_BY_H_

#include "XUIScaleTo.h"

class XUIScaleBy : public XUIScaleTo
{
public:

	static XUIScaleBy* Create(const xfloat32& fDuration, const XVECTOR2& v2Scale);
	static XUIScaleBy* Create(const xfloat32& fDuration, const xfloat32& fScale);

	virtual XUIScaleBy* Clone() const override;

	virtual ~XUIScaleBy() {};
protected:


	virtual void StartWithTarget(XUINode* pTarget) override;
	

protected:

};
#endif
