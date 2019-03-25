#ifndef _UI_SCALE_TO_H_
#define _UI_SCALE_TO_H_

#include "XUIActionInterval.h"

class XUIScaleTo : public XUIActionInterval
{
public:

	static XUIScaleTo* Create(const xfloat32& fDuration, const XVECTOR2& v2Scale);
	static XUIScaleTo* Create(const xfloat32& fDuration, const xfloat32& fScale);

	virtual XUIScaleTo* Clone() const override;
	virtual XUIScaleTo* Reverse() const override;

	virtual ~XUIScaleTo() {};
protected:
	XUIScaleTo();


	virtual void StartWithTarget(XUINode* pTarget) override;
	
	virtual void ActionUpdate(const xfloat32& fProgress) override;


protected:

	xbool InitWithDuration(const xfloat32& fDuration, const XVECTOR2& v2Scale);

protected:
	
	XVECTOR2 m_v2StartScale;
	XVECTOR2 m_v2EndScale;
	XVECTOR2 m_v2Delta;


};
#endif
