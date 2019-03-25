/******************************************************************************

 @File         XThreadComm.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XThreadComm.

 @HISTORY:

******************************************************************************/
#ifndef _X_THREADCOMM_H_
#define _X_THREADCOMM_H_

#include "XTypes.h"
#include "XMemBase.h"

/*线程回调，用户扩展结构*/
class XThreadUserData : public XMemBase
{
public:
	enum EThreadNotify
	{
		X_T_NOTIFY_TERMINATED = 0,
		X_T_NOTIFY_WORKFINISHED,
		X_T_NOTIFY_SUSPENDED,
		X_T_NOTIFY_RESUMED,
	};

	virtual								~XThreadUserData() {}
	virtual void						Notify(EThreadNotify notify) {}
};

/* 线程回调函数定义 */
typedef xint32 (*X_LPFNATHREADPROC)(xint32 iEventIdx, XThreadUserData* pUserData);

enum XThreadPriority
{
	XPRI_NORMAL,
	XPRI_ABOVENORMAL,
	XPRI_BELOWNORMAL,
};

struct EVENT_DESC
{
	 xbool bManualReset;  // 信号初始状态
};

/* 最大用户信号数 */
enum { MAX_USER_EVENT_NUM = 8 };


/* 原子对象 */
class XThreadAtomic : public XMemBase
{
public:
	virtual 							~XThreadAtomic() {}
	virtual void 						Release() = 0;

	/*
	* 获取当前原子的值
	* @return			返回当前原子的值
	*/
	virtual xint32 						GetValue() const = 0;

	/*
	* 对原子执行加操作
	* @param			iAmount 增加的值
	* @return			返回执行加操作后，原子的值
	*/
	virtual xint32 						Fetch_Add(xint32 iAmount) = 0;

	/*
	* 设置原子的值
	* @param			iAmount 将被设置的原子的值
	* @return			返回修改之前，原子的值
	*/
	virtual xint32 						Fetch_Set(xint32 iAmount) = 0;

	/*
	* 将原子当前值与iComparand进行比较，如果相等，就设置iAmount为当前原子的值。
	* @param			iAmount 将被设置的原子的值
	* @param			iComparand 对比参考值
	* @return			返回修改之前，原子的值
	*/
	virtual xint32 						Fetch_CompareSet(xint32 iAmount, xint32 iComparand) = 0;

	/*
	* 对原子执行递加操作
	*
	* @return			返回递加之后，原子的值
	*/
	virtual xint32 						Increment_Fetch() = 0;

	/*
	* 对原子执行递减操作
	*
	* @return			返回递减之后，原子的值
	*/
	virtual xint32 						Decrement_Fetch() = 0;
};


/* 互斥锁 */
class XThreadMutex : public XMemBase
{
public:
	virtual 							~XThreadMutex() {}
	virtual void 						Release() = 0;

	/*
	* 加锁操作
	* @return xture : 加锁成功
	*/
	virtual void 						Lock() = 0;

	/*
	* 解锁操作
	*/
	virtual void 						Unlock() = 0;

};


#endif // _X_SYSTHREADCOMMON_H_
