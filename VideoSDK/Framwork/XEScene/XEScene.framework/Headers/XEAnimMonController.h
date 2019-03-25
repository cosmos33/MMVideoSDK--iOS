/******************************************************************************

@File         XEAnimController.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_MON_CONTROLLER_H
#define XE_ANIM_MON_CONTROLLER_H
#include "XMath3D.h"
#include "XEAnimController.h"

//in a uniform time unit- microsecond.

class XEAnimMontageInstance;
class XEAnimMonNotifyInstance;
class XEUserNodeInstance;

class XEAnimMonController 
	:public XEAnimController
{
public:
	class Listener
		: public XEAnimController::Listener
	{
	public:
		virtual			~Listener() {}
		virtual void     Ls_NotifyTrigger(xfloat32 fMillisecond, const XEAnimMonNotifyInstance* pNotifyIns){}
	};
	                                        XEAnimMonController();
	virtual                                ~XEAnimMonController();
public:
	void                                    BroadcastNotifyTrigger(const XEAnimMonNotifyInstance* pNotifyIns) const;
	X_FORCEINLINE void                      SetAnimMontageInstance(XEAnimMontageInstance* pAnimMontageIns){ m_pAnimMontageIns = pAnimMontageIns; }
	X_FORCEINLINE XEAnimMontageInstance*    GetAnimMontageInstance(){ return m_pAnimMontageIns; }
	X_CLASS_DEF(XEAnimMonController)
public:
	virtual void                            Tick(xfloat32 fInterval) override;//in milliseconds.
	virtual xint32                          GetTimeLength() const override;//in microseconds.
	virtual void                            SetTime(xint32 nTime) override;//in microseconds.
	void                                    GetNodeTimeLength(XEUserNodeInstance* pNodeIns, xint32& nTimeLen) const;
protected:
	virtual void                            BroadcastPlayOneTimeFinished(xbool bReversePlaying) override;
private:
	XEAnimMontageInstance*                  m_pAnimMontageIns;
};

#endif // XE_ANIM_MON_CONTROLLER_H
