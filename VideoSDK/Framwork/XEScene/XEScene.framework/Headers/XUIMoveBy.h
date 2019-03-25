#ifndef _UI_MOVE_BY_H_
#define _UI_MOVE_BY_H_

#include "XUIActionInterval.h"

class XUIMoveBy : public XUIActionInterval
{
public:

	static XUIMoveBy* Create(const xfloat32& fDuration, const XVECTOR2& v2DeltaPosition);

	virtual XUIMoveBy* Clone() const override;
	virtual XUIMoveBy* Reverse() const override;

	virtual ~XUIMoveBy() {};
protected:
	XUIMoveBy();


	virtual void StartWithTarget(XUINode* pTarget) override;
	
	virtual void ActionUpdate(const xfloat32& fProgress) override;


protected:

	xbool InitWithDuration(const xfloat32& fDuration, const XVECTOR2& v2DeltaPosition);

protected:
	
	XVECTOR2 m_v2PositionDelta;
	XVECTOR2 m_v2StartPosition;
	XVECTOR2 m_v2PreviousPosition;


};
#endif
