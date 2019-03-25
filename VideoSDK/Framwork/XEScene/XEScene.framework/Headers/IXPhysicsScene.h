#ifndef _IXPHYSICSSCENE_H_
#define _IXPHYSICSSCENE_H_

#include "XArray.h"
#include "XMath3D.h"

class IXCloth;
class IXRigidBody;
class IXWorld;
class IXSkeletalPhysicsInstance;

/****************************************/
/* 物理场景事件监听类						*/
/********************** *****************/
class IXPhysicalSceneEventListener : public XMemBase
{
public:
	/**
	* 当刚体碰撞时回调
	*
	* @param 碰撞的两个Actor
	*/
	virtual void OnContact(IXRigidBody* pBody0, IXRigidBody* pBody1) = 0;
};

/********************************************************/
/* 物理场景类											*/
/* 不负责管理添加到本场景中的资源,包括布料、刚体、监听器等	*/
/********************** *********************************/
class IXPhysicsScene : public XMemBase
{
public:
	virtual ~IXPhysicsScene(){}

	/**
	* 获取物理场景名称
	*/
	virtual const xchar*		GetName() = 0;
	
	/**
	* 将布料添加到场景中
	*
	* @param  pCloth 布料指针
	* @return 失败情况：布料已添加到其他场景
	*/
	virtual xbool				AddCloth(IXCloth* pCloth) = 0;
	
	/**
	* 将一组布料添加到场景中
	* @note	依次添加各布料，如果有一个失败，继续执行之后的布料
	* @param  aCloth 布料数组
	* @return 任意一个布料添加失败返回xfalse
	*/
	virtual xbool				AddCloth(const XArray<IXCloth*>& aCloth) = 0;
	
	/**
	* 将布料从场景中移除
	*
	* @param  pCloth 布料指针
	*/
	virtual void				RemoveCloth(IXCloth* pCloth) = 0;

	/**
	* 将一个刚体添加到场景中
	* 
	* @param  pRigidBody 刚体指针
	* @return 失败情况：刚体已添加到其他场景
	*/
	virtual xbool				AddRigidBody(IXRigidBody* pRigidBody) = 0;
	
	/**
	* 将刚体从场景中移除
	*
	* @param  pRigidBody 刚体指针
	*/
	virtual void				RemoveRigidBody(IXRigidBody* pRigidBody) = 0;

	/*
	* Tick
	*/
	virtual void				Tick(xfloat32 fTime) = 0;
	/*
	* Render场景中的布料
	*/
	virtual void				Render(IXWorld* pScene) = 0;

	/*
	* 为场景添加监听器
	*/
	virtual void				AddEventListener(IXPhysicalSceneEventListener* pListener) = 0;
	/*
	* 移除监听器
	*/
	virtual void				RemoveEventListener(IXPhysicalSceneEventListener* pListener) = 0;

	/*
	* 设置场景重力参数
	*/
	virtual XVECTOR3			GetGravity() = 0;
	virtual void				SetGravity(const XVECTOR3& vGravity) = 0;
};

#endif
