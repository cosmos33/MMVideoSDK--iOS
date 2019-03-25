/******************************************************************************

@File         XESeqAnimController.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_ANIM_CONTROLLER_H
#define XE_SEQ_ANIM_CONTROLLER_H
#include "XMath3D.h"
#include "XEAnimController.h"

//in a uniform time unit- microsecond.
//animation controller of the sequence.

class XESequencerInstance;
class XEUserNodeInstance;
class XEKeyframeBase;
class XESeqAnimController 
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
	                                   XESeqAnimController();
	virtual                           ~XESeqAnimController();
public:							     
								     
	void                               BroadcastKeyframeTrigger(const XEKeyframeBase* pKeyframe);
	X_FORCEINLINE void                 SetSequencer(XESequencerInstance* pSequencerIns){ m_pSequencerIns = pSequencerIns; }
	X_FORCEINLINE XESequencerInstance* GetSequencer(){ return m_pSequencerIns; }
public:
	virtual void                       Tick(xfloat32 fInterval) override;
	virtual xint32                     GetTimeLength() const override;
	virtual void                       SetTime(xint32 nTime) override;
	void                               GetNodeTimeLength(XEUserNodeInstance* pNodeIns, xint32& nTimeLen) const;
private:						       
	XESequencerInstance*               m_pSequencerIns;
};

#endif // XE_SEQ_ANIM_CONTROLLER_H
