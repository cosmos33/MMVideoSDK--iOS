#ifndef _UI_CALLFUNC_H_
#define _UI_CALLFUNC_H_

#include "XUIActionInstant.h"
#include <functional>

class XUINode;
class XUICallFunc : public XUIActionInstant
{
public:
	typedef std::function<void(XUINode*)> XUIActionFunction;

	XUICallFunc* Clone() const override;

public:
	static XUICallFunc* Create(const XUIActionFunction& funcFunction);
	virtual ~XUICallFunc() {};

protected:
	XUICallFunc();

	xbool InitWithFunction(const XUIActionFunction& funcFunction);

	void ActionUpdate(const xfloat32& fProgress) override;

private:
	XUIActionFunction m_funcActionFunction;
};

#endif
