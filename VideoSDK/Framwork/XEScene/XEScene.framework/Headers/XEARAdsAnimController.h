/******************************************************************************

@File         XEARAdsAnimController.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef XE_ARADS_ANIM_CONTROLLER_H
#define XE_ARADS_ANIM_CONTROLLER_H

#include "XMath3D.h"
#include "XEAnimController.h"

//in a uniform time unit- microsecond.
//animation controller of the ARAds.

class XEARAdsInstance;
class XEUserNodeInstance;
class XEKeyframeBase;
class XEARAdsAnimController
	:public XEAnimController
{
public:
	class Listener
		: public XEAnimController::Listener
	{
	public:
		virtual			              ~Listener() {}
		virtual void                   Ls_KeyframeTrigger(xfloat32 nMillisecond, const XEKeyframeBase* pKeyframe){}
	};
	                                  XEARAdsAnimController();
	virtual                           ~XEARAdsAnimController();
public:							     
								     
	void                               BroadcastKeyframeTrigger(const XEKeyframeBase* pKeyframe);
	X_FORCEINLINE void                 SetARAds(XEARAdsInstance* pARAdsIns){ m_pARAdsIns = pARAdsIns; }
	X_FORCEINLINE XEARAdsInstance*     GetARAds(){ return m_pARAdsIns; }
public:
	virtual void                       Tick(xfloat32 fInterval) override;
	virtual xint32                     GetTimeLength() const override;
	virtual void                       SetTime(xint32 nTime) override;
	void                               GetNodeTimeLength(XEUserNodeInstance* pNodeIns, xint32& nTimeLen) const;
private:						       
	XEARAdsInstance*                   m_pARAdsIns;
};

#endif // XE_ARADS_ANIM_CONTROLLER_H
