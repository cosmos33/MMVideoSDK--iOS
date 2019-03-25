/******************************************************************************

@File         XEAnimMonNotifyInstance.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_MON_NOTIFY_INSTANCE_H
#define XE_ANIM_MON_NOTIFY_INSTANCE_H
#include "XEAnimMonBaseInstance.h"

class XEAnimMonNotify;
class XEAnimMontageInstance;
class XEAnimMonNotifyInstance 
	:public XEAnimMonBaseInstance
{
public:
	enum NotifyState
	{
		NS_UNKOWN,
		NS_LIVE_EXPLAINED,
		NS_SILENT_EXPLAINED
	};
	XEAnimMonNotifyInstance(XEAnimMonNotify* pNodeTl);
	virtual ~XEAnimMonNotifyInstance();
public:
	static XArray<XString>&           GetNotifyStateString();
public:
	X_FORCEINLINE xint32              GetNotifyStatus(){ return m_eNotifyState; }
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet       GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif
	virtual void                      ExplainLiveNotify(void* pParam = NULL){}
	virtual void                      ExplainSilentNotify(){}
	virtual void                      SetTime(xint32 nMicrosecond) override;//in microsecond.
	XEAnimMontageInstance*            GetAnimMontageInstance();
	XEAnimMonNotify*                  GetAnimMonNotifyTemplate();
public:
	XE_USER_NODE_CAST(XEAnimMonNotifyInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString              NODE_TYPENAME;
protected:
	NotifyState                       m_eNotifyState;
};

#endif // XE_ANIM_MON_NOTIFY_INSTANCE_H
