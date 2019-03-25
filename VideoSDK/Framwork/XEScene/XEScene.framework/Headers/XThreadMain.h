/******************************************************************************

 @File         XThreadMain.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  .

 @HISTORY:

******************************************************************************/

#ifndef _X_THREADMAIN_H_
#define _X_THREADMAIN_H_

#include "XThreadComm.h"
#include "XMemBase.h"

class XThreadMain : public XMemBase
{
public:
	 virtual				~XThreadMain() {}
	virtual void 			Release() = 0;

	/* 初始化线程
	*
	* @notice	并不会创建新线程，而是当前线程上执行逻辑
	*
	* @param lpfnWorkProc	执行的逻辑函数
	* @param aEvents		用户信号量初始状态
	* @param iNumEvent		用户信号量的个数
	* @param pUserData		用户通知接口	
	* @return  xtrue : 执行成功
	*/
	virtual xbool 			Create(X_LPFNATHREADPROC lpfnWorkProc, EVENT_DESC* aEvents, xint32 iNumEvent, XThreadUserData* pUserData) = 0;

	/* 暂停线程
	*/
	virtual void 			Suspend() = 0;
	/* 重新开始线程
	*/
	virtual void 			Resume() = 0;
	/* 线程是否已暂停
	* @return  xtrue : 线程暂停
	*/
	virtual xbool 			IsSuspended() = 0;

	/* 设置线程优先级
	* @param priority 优先级值
	* @return  xtrue : 设置成功
	*/
	virtual xbool 			SetPriority(XThreadPriority priority) = 0;

	/* 设置线程，首选执行的CPU
	* @param iProcessorIndex 首选CPU号
	* @return  xtrue : 设置成功
	*/
	virtual xbool 			SetIdealProcessor(xuint32 iProcessorIndex) = 0;


	/* 标记信号量
	*
	* @param iEventIdx 信号量索引
	* @return  无
	*/
	virtual void 			TriggerEvent(xint32 iEventIdx) = 0;

	/* 重置信号量到初始值 
	*
	* @param iEventIdx 信号量索引
	* @return  无
	*/
	virtual void 			ResetEvent(xint32 iEventIdx) = 0;
	
	/* 线程执行一次逻辑
	*
	* @notice	函数内会判断用户信号量,有标记则会执行lpfnWorkProc。
	*
	* @return  0值为线程退出或暂停或无信号，其他值为lpfnWorkProc返回值
	*/
	virtual xint32 			RunOnce() = 0;
};


#endif // _X_SYSMAINTHREAD_H_
