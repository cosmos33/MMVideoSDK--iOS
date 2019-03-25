/******************************************************************************

@File         XEAnimBlendController.h

@Version       1.0

@Created      2018,9, 30

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_BLEND_CONTROLLER_H
#define XE_ANIM_BLEND_CONTROLLER_H
#include "XMath3D.h"
#include "XEAnimController.h"

//in a uniform time unit- microsecond.

class XEAnimBlendInstance;
//class XEAnimMonNotifyInstance;
class XEUserNodeInstance;

class XEAnimBlendController 
	:public XEAnimController
{
public:
	class Listener
		: public XEAnimController::Listener
	{
	public:
		virtual			~Listener() {}
		//virtual void     Ls_NotifyTrigger(xfloat32 fMillisecond, const XEAnimMonNotifyInstance* pNotifyIns){}
	};
	XEAnimBlendController();
	virtual                                ~XEAnimBlendController();
public:	
	X_FORCEINLINE void                      SetAnimBlendInstance(XEAnimBlendInstance* pAnimBlendIns){ m_pAnimBlendIns = pAnimBlendIns; }
	X_FORCEINLINE XEAnimBlendInstance*      GetAnimBlendInstance(){ return m_pAnimBlendIns; }
	X_CLASS_DEF(XEAnimBlendController)
public:
	virtual void                            Tick(xfloat32 fInterval) override;
	virtual xint32                          GetTimeLength() const override;
	virtual void                            SetTime(xint32 nTime) override;
	void                                    GetNodeTimeLength(XEUserNodeInstance* pNodeIns, xint32& nTimeLen) const;
protected:
	virtual void                            BroadcastPlayOneTimeFinished(xbool bReversePlaying) override;
private:
	XEAnimBlendInstance*                    m_pAnimBlendIns;
};

#endif // XE_ANIM_BLEND_CONTROLLER_H
