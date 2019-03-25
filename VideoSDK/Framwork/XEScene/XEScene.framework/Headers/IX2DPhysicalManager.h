#ifndef _IX2DPHYSICALMANAGER_H_
#define _IX2DPHYSICALMANAGER_H_

#include "XMath3D.h"

class IX2DPhysicalScene;
class IX2DPhysicalManager : public XMemBase
{
public:
	virtual						~IX2DPhysicalManager() {};

	/**
	* 初始化及释放
	* 当前什么也没做
	*/
	virtual xbool				Init() = 0;
	virtual void				Release() = 0;

	/**
	* 创建一个2D物理场景
	* @note 调用者delete
	*
	* @param szSceneName 场景名称
	* @return 场景指针，创建失败返回NULL
	*/
	virtual IX2DPhysicalScene*	CreateScene(const xchar* szSceneName, const XVECTOR2& vGravity = XVECTOR2(0.0f, -9.8f)) = 0;
};

extern IX2DPhysicalManager* g_pIX2DPhysicalManager;

#endif

