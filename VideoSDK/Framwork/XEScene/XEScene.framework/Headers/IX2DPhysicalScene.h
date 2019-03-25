#ifndef _IX2DPHYSICALSCENE_H_
#define _IX2DPHYSICALSCENE_H_

#include "XMath3D.h"

class IX2DRigidBody;
struct X2DRigidBodyDesc;
class IX2DPhysicalScene : public XMemBase
{
public:
	virtual ~IX2DPhysicalScene(){}
	/**
	* 获取物理场景名称
	*/
	virtual const xchar*		GetName() = 0;

	/*
	* Tick，单位为s
	*/
	virtual void				Tick(xfloat32 fTime) = 0;
	/*
	* 设置Tick时速度的迭代次数和位置的迭代次数
	* velocity: default 6
	* position: default 2
	*/
	virtual void				SetVelocityIterations(xint32 nVelocityIters) = 0;
	virtual xint32				GetVelocityIterations() const = 0;	
	virtual void				SetPositionIterations(xint32 nPositionIters) = 0;
	virtual xint32				GetPositionIterations() const = 0;
	/*
	* 设置场景重力参数
	*/
	virtual XVECTOR2			GetGravity() = 0;
	virtual void				SetGravity(const XVECTOR2& vGravity) = 0;
	/*
	* 添加一个RigidBody
	*/
	virtual IX2DRigidBody*		CreateRigidBody(const X2DRigidBodyDesc& pDesc) = 0;
	/*
	* 删除一个RigidBody
	* 内部会Delete
	*/
	virtual void				DestroyBody(IX2DRigidBody* pBody) = 0;
};

#endif
