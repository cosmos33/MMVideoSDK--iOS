#ifndef _IXRIGIDACTOR_H_
#define _IXRIGIDACTOR_H_

#include "XMath3D.h"

class IXPhysicsRes;
class XBaseCoordSpace;
enum RigidActorType
{
	// 静态，只会影响其他刚体，自身不会被影响
	RAT_STATIC,
	// 动态，影响其他刚体，自身也会被影响
	RAT_DYNAMIC,
	// future, 动力学，动态的一种特殊类型，不被重力和其他附加力影响，不与其他静态Actor和KINEMATIC Actor碰撞
	// RAT_KINEMATIC,
};

/****************************************/
/* 刚体形状表面材质						*/
/********************** *****************/
struct XShapeMaterial
{
	XShapeMaterial(xfloat32 sf, xfloat32 df, xfloat32 r)
		: fStaticFriction(sf)
		, fDynamicFriction(df)
		, fRestitution(r){}
	/**
	* 静摩擦系数
	*
	* @range [0, X_MAX_FLT32]
	*/
	xfloat32	fStaticFriction;

	/**
	* 动摩擦系数
	*
	* @range [0, X_MAX_FLT32]
	*/
	xfloat32	fDynamicFriction;

	/**
	* 弹性系数
	* 越大弹性越好
	* @range [0, 1]
	*/
	xfloat32	fRestitution;
};

/****************************************/
/* 刚体类								*/
/********************** *****************/
class IXRigidBody : public XMemBase
{
public:
	virtual						~IXRigidBody(){}
	
	/**
	* 为刚体绑定一个物理资源
	* @note 如果成功，则物理资源的引用计数加1
	*
	* @param pRes 物理资源
	* @param bReplace 是否替换,如果为xtrue,则会替换原有资源,如果为xfalse,未绑定则绑定,已绑定则不绑定
	* @return 成功返回xtrue,失败返回xfalse
	*/
	virtual xbool				BindPhysicsRes(IXPhysicsRes* pRes, xbool bReplace = xfalse) = 0;

	/*
	* Get
	*/
	virtual XBaseCoordSpace*	GetBaseCoordSpace() = 0;

	/*
	* 开启物理模拟属性
	*/
	virtual xbool				IsSimulate() const = 0;
	virtual void				SetSimulate(xbool bSet) = 0;

	/*
	* 类型属性
	*/
	virtual RigidActorType 		GetType() const = 0;
	virtual void				SetType(RigidActorType eType) = 0;
	
	/*
	* 刚体形状表面材质属性
	*/
	virtual XShapeMaterial		GetMaterial() const = 0;
	virtual void				SetMaterial(const XShapeMaterial& mat) = 0;

	/*
	* 开启碰撞事件属性
	* @note 如果开启，则在该物体与其他物体碰撞时调用IXPhysicalSceneEventListener::OnContact
	*/
	virtual xbool				IsNotifyContact() const = 0;
	virtual void				SetNotifyContact(xbool bSet) = 0;

	/*
	* 是否被重力影响
	*/
	virtual xbool				IsGravityEnabled() const = 0;
	virtual void				SetGravityEnabled(xbool bSet) = 0;


	// 以下函数仅当Type为Dynamic时有效
	
	/*
	* 开启CCD属性
	* @note 高速物体应开启CCD来避免隧穿效应
	*/
	virtual xbool				IsCCDEnabled() const = 0;
	virtual void				SetCCDEnabled(xbool bSet) = 0;
	
	/*
	* 设置物体质量，单位kg
	* @note 0代表无穷质量
	* @range [0, X_MAX_FLT32]
	*/
	virtual xfloat32			GetMass() const = 0;
	virtual void				SetMass(xfloat32 f) = 0;

	/**
	* 刚体速度和角速度属性
	* @note 如果未开启模拟,无效
	*/
	virtual XVECTOR3			GetLinearVelocity() const = 0;
	virtual void				SetLinearVelocity(const XVECTOR3& vVelocity) = 0;	
	virtual XVECTOR3			GetAngularVelocity() const = 0;
	virtual void				SetAngularVelocity(const XVECTOR3& vAngle) = 0;

	/*
	* 速度阻尼系数和角速度阻尼系数
	*
	* @range [0, X_MAX_FLT32]
	*/
	virtual xfloat32			GetLinearDamping() const = 0;
	virtual void				SetLinearDamping(xfloat32 fLinearDamping) = 0;
	virtual xfloat32			GetAngularDamping() const = 0;
	virtual void				SetAngularDamping(xfloat32 fAngularDamping) = 0;
};

#endif
