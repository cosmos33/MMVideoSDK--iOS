/******************************************************************************

 @File         XThread.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XThread.

 @HISTORY:

******************************************************************************/
#ifndef _X_THREAD_H_
#define _X_THREAD_H_

#include "XThreadComm.h"
#include "XMemBase.h"

class XThread : public XMemBase
{
public:
	virtual					~XThread() {}
	virtual void 			Release() = 0;

	/* 初始化线程
	*
	* @notice	bMainThread为假时，新建线程，且线程默认为非暂停状态。
	*
	* @param lpfnWorkProc	执行的逻辑函数
	* @param aEvents		用户信号量初始状态
	* @param iNumEvent		用户信号量的个数
	* @param pUserData		用户通知接口
	* @param bMainThread	true : 为在当前线程上运行逻辑，并不会创建新线程， false 创建新线程运行逻辑
	* @return  xtrue : 执行成功
	*/
	virtual xbool 			Create(X_LPFNATHREADPROC lpfnWorkProc, EVENT_DESC* aEvents, xint32 iNumEvent, XThreadUserData* pUserData, xbool bMainThread=xfalse) = 0;

	/* 
	* 在主线程上运行逻辑，
	*
	* @notice	只有Create时 bMainThread为真，才可以执行此函数
	* @return  -1 ： 执行错误（bMainThread为假）， 0 ：线程正在执行， 
	*/
	virtual xint32 			RunMainThread() = 0;

	/* 结束线程
	*/
	virtual void 			Terminate() = 0;
	/* 暂停线程
	*/
	virtual void 			Suspend() = 0;
	/* 重新开始线程
	*/
	virtual void 			Resume() = 0;

	/*
	* 线程是否开启
	* 
	* @return  xtrue ： 线程正在运行
	*/
	virtual xbool 			IsRunning() = 0;
	/*
	* 线程是否暂停
	*
	* @return  xtrue ： 线程处于暂停状态
	*/
	virtual xbool 			IsSuspended()  = 0;

	/*
	* 设置线程优先级
	*
	* @param priority 优先级值
	* @return  xtrue : 设置成功
	*/
	virtual xbool 			SetPriority(XThreadPriority priority) = 0;
	/*
	* 设置线程，首选执行的CPU
	*
	* @param iProcessorIndex 首选CPU号
	* @return  xtrue : 设置成功
	*/
	virtual xbool 			SetIdealProcessor(xuint32 iProcessorIndex) = 0;

	/*
	* 标记信号量
	*
	* @param iEventIdx 信号量索引
	* @return  无
	*/
	virtual void 			TriggerEvent(xint32 iEventIdx) = 0;
	/*
	*  重置信号量到初始值 
	*
	* @param iEventIdx 信号量索引
	* @return  无
	*/
	virtual void 			ResetEvent(xint32 iEventIdx) = 0;

};


#endif // _X_SYSTHREAD_H_
