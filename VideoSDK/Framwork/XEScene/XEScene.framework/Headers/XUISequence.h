#ifndef _UI_SEQUENCE_H_
#define _UI_SEQUENCE_H_

#include "XArray.h"
#include "XUIActionInterval.h"

class XUIFiniteTimeAction;
class XUISequence : public XUIActionInterval
{
public:

	static XUISequence* Create(const XArray<XUIFiniteTimeAction*>& vActions);
	virtual XUISequence* Clone() const override;

	virtual xbool IsDone() const override;

	virtual ~XUISequence();
protected:

	XUISequence();


	virtual void StartWithTarget(XUINode* pTarget) override;
	virtual void Stop() override;
	

	virtual void Step(const xfloat32& dt) override;
//	virtual void ActionUpdate(const xfloat32& fProgress) override;


protected:

	xbool InitWithArray(const XArray<XUIFiniteTimeAction*>& vActions);

protected:

	XArray<XUIFiniteTimeAction*> m_vActions;

};
#endif
