/******************************************************************************

@File         XESeqBindingActorInstance.h

@Version       1.0

@Created      2018,5, 3

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_TRACK_EVENT_INSTANCE_H
#define XE_SEQ_TRACK_EVENT_INSTANCE_H

#include "XESeqBase.h"
#include "XEScriptInterpreter.h"

class XESeqTrackEvent;
class XEEventBase;
class XEKeyframeBase;
class XESeqTrackEventInstance 
	: public XESeqBaseInstance
{
public:
	XESeqTrackEventInstance(XESeqTrackEvent* pNodeTl);
	virtual ~XESeqTrackEventInstance();
public:
	virtual void                                  SetTime(xint32 nMicrosecond) override;//in microsecond.
	virtual void                                  Apply() override;
	virtual void                                  Release() override;
	XESeqTrackEvent*                              GetSeqTrackEventTemplate();
	X_FORCEINLINE XEEventBase*                    GetCustomEvent(){ return m_pCustomEvent; }
	X_FORCEINLINE void                            ResetCurKeyframe(){ m_pCurKeyframeBase = NULL; }
public:
	XE_USER_NODE_CAST(XESeqTrackEventInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
private:
	XEKeyframeBase*                               m_pCurKeyframeBase;
	XEEventBase*                                  m_pCustomEvent;//manage here. will not be managed by the event manager.
};

#endif // XE_SEQ_TRACK_EVENT_INSTANCE_H
