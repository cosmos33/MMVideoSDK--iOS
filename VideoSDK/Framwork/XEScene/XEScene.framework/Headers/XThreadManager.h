/******************************************************************************

 @File         XThreadManager.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XThreadManager.

 @HISTORY:

******************************************************************************/
#ifndef _X_THREADMANAGER_H_
#define _X_THREADMANAGER_H_

#include "XTypes.h"
#include "XThreadComm.h"
#include "XThreadMain.h"
#include "XThread.h"
#include "XLinkList.h"
#include "XMemBase.h"

class XThreadPool;

class XThreadManager : public XMemBase
{
public:

	/*
	* 创建跨平台的原子操作
	*
	* @param iValue 原子初始值
	* @return  XThreadAtomic 原子指针
	*/
	static XThreadAtomic*			CreateThreadAtomic(xint32 iValue);

	/*
	* 创建跨平台的互斥锁
	*
	* @return  XThreadMutex 互斥锁指针
	*/
	static XThreadMutex*			CreateThreadMutex();

	/*
	* 创建在当前线程执行的线程对象
	*
	* @notice	此线程本为当前线程上运行，并不会创建新线程，
	*
	* @param lpfnWorkProc	执行的逻辑函数
	* @param aEvents		用户信号量初始状态
	* @param iNumEvent		用户信号量的个数
	* @param pUserData		用户通知接口
	* @return  线程对象
	*/
	static XThreadMain*				CreateMainThread(X_LPFNATHREADPROC lpfnWorkProc, EVENT_DESC* aEvents, xint32 iNumEvent, XThreadUserData* pUserData);

	/* 
	* 创建线程对象
	*
	* @notice	bMainThread为假时，新建线程, 且线程默认为非暂停状态。
	*
	* @param lpfnWorkProc	执行的逻辑函数
	* @param aEvents		用户信号量初始状态
	* @param iNumEvent		用户信号量的个数
	* @param pUserData		用户通知接口
	* @param bMainThread	true : 为在当前线程上运行逻辑，并不会创建新线程， false 创建新线程运行逻辑
	* @return  xtrue : 执行成功
	*/
	static XThread*					CreateThread(X_LPFNATHREADPROC lpfnWorkProc, EVENT_DESC* aEvents, xint32 iNumEvent, XThreadUserData* pUserData, xbool bMainThread=xfalse);

	/*
	* 创建线程池
	*
	* @param   iThreadNum			线程个数
	* @param   iProcessorIndex		
	* @return  线程池对象
	*/
	static XThreadPool*				CreateThreadPool(xuint32 iThreadNum);

	/* 销毁线程 */
	static void 					ReleaseMainThread(XThreadMain* pMainThread);
	/* 销毁线程 */
	static void 					ReleaseThread(XThread* pThread);
	/* 销毁线程池 */
	static void 					ReleaseThreadPool(XThreadPool* pThreadPool);

private:
	static XLinkList<XThreadMain>	m_MainThreadList;
	static XLinkList<XThread>		m_ThreadList;
	static XLinkList<XThreadPool>	m_ThreadPoolList;
};

#endif // _X_THREADFACTORY_H_
