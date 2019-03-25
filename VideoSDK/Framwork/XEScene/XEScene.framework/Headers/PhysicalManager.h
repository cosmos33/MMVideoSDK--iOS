#ifndef _PHYSICAL_MANAGER_H_
#define _PHYSICAL_MANAGER_H_

#include "XMath3D.h"
#include "XArray.h"
#include "XPhysicalInterface.h"
#include "IXRigidBody.h"
#include "IXPhysicsRes.h"
#include "IXSkeletalPhysicsInstance.h"

class IXCloth;
class XBaseCoordSpace;
class IXPhysicsScene;

class IXPhysicalManager : public IXPhysicalManagerBase
{
public:
	virtual					~IXPhysicalManager() {};

	/**
	* 初始化及释放
	*/
	virtual xbool			Init() = 0;
	virtual void			Release() = 0;
	
	/**
	* 创建一个物理场景
	* @note 有最大场景数的限制
	*		调用者delete
	*
	* @param szSceneName 场景名称
	* @return 场景指针，创建失败返回NULL
	*/
	virtual IXPhysicsScene*	CreateScene(const xchar* szSceneName) = 0;

	/*---------------------------*/
	/*------Cloth Interface------*/
	/*---------------------------*/

	/**
	* 从一个模型实例的某个Mesh上获取布料实例
	*
	* @param pInstance 模型实例的指针
	* @param szMeshName mesh的名称
	* @return 布料实例的指针, 如果没有绑定布料返回空指针
	*/
	virtual IXCloth*		GetCloth(IXModelInstance* pInstance, const xchar* szMeshName) = 0;
	
	/**
	* 从一个模型实例获取所有的布料实例
	*
	* @param pInstance 模型实例的指针
	* @param aCloth Cloth数组
	* @return 
	*/
	virtual void			GetCloth(IXModelInstance* pInstance, XArray<IXCloth*>& aCloth) = 0;

	/**
	* 获取所有带布料的mesh名称
	*
	* @param pInstance 模型实例的指针
	* @param out aMeshName 绑定布料的mesh名称数组
	* @return 
	*/
	virtual void			GetMeshNameWithCloth(IXModelInstance* pInstance, XArray<XString>& aMeshName) const = 0;

	/**
	* 从硬盘上加载一个布料实例
	* @note 资源创建后，如果调用AddCloth添加到模型成功，则无需手动释放，否则需要调用者Release
	* 
	* @param szPath 布料的路径
	* @return 布料实例的指针, 如果失败返回空指针
	*/
	virtual IXCloth*		CreateCloth(const xchar* szPath) = 0;

	/**
	* 自动将布料实例与模型绑定，根据材质名进行匹配
	*
	* @param pInstance 模型实例指针
	* @param pCloth 布料实例指针
	*/
	virtual xbool			AddCloth(IXModelInstance* pInstance, xint32 nSkinIndex, IXCloth* pCloth) = 0;
	
	/**
	* 移除模型实例某个mesh的所有布料
	* @note 现在移除后会直接Release布料资源,以后可能会修改
	*
	* @param pInstance 模型实例指针
	*/
	virtual void			RemoveCloth(IXModelInstance* pInstance) = 0;


	// 停用
	/**
	* 将布料实例与模型的某个mesh绑定
	*
	* @param pInstance 模型实例指针
	* @param szMeshName 模型mesh名称
	* @param pCloth 布料实例指针
	* @return 失败情况：mesh已绑定/cloth已绑定/meshName未找到/骨骼名称不匹配等.
	*/
	virtual xbool			AddCloth(IXModelInstance* pInstance, xint32 nSkinIndex, const xchar* szMeshName, IXCloth* pCloth) = 0;

	/**
	* 移除模型实例某个mesh的布料
	* @note 现在移除后会直接Release布料资源,以后可能会修改
	*
	* @param pInstance 模型实例指针
	* @param szMeshName 模型mesh名称
	*/
	virtual void			RemoveCloth(IXModelInstance* pInstance, const xchar* szMeshName) = 0;
	// 停用


	/**
	* 将模型实例当前的布料信息设置到Skin上
	* @note 保存使用,调用Skin的Save前调用,否则将不保存该模型的布料信息
	* 
	* @param pInstance 模型实例指针
	*/
	virtual void			SetClothInfoToSkin(IXModelInstance* pInstance) = 0;
	
	/**
	* 保存布料文件
	* @note 当前可以保存的只有材质信息
	*
	* @param pInstance 模型实例指针
	*/
	virtual xbool			SaveCloth(const xchar* szFile, IXCloth* pCloth) = 0;

	/*-------------------------------*/
	/*------RigidBody Interface------*/
	/*-------------------------------*/

	/**
	* 创建一个刚体
	* @note 调用者delete
	*
	* @param eType 刚体类型
	* @param pBindObject 一个BaseCoordSpace类,当前有模型和特效
	*/
	virtual IXRigidBody*	CreateRigidBody(RigidActorType eType, XBaseCoordSpace* pBindObject) = 0;
	
	/**
	* 从硬盘上加载一个物理资源(碰撞体)
	* @note 调用者Release
	*
	* @param szPath phy的路径
	* @param bReload 是否重加载
	* @return 物理资源的指针, 如果失败返回空指针
	*/
	virtual IXPhysicsRes*	LoadPhysicsRes(const xchar* sz, xbool bReload = xfalse) = 0;	

	/**
	* 从骨骼物理资源创建骨骼物理实例
	*
	* @param szSkeletalPhysicsRes 骨骼物理资源的路径
	* @return 骨骼物理实例的指针, 如果失败返回空指针
	*/
	virtual IXSkeletalPhysicsInstance* CreateSkeletalPhysicsInstance(const xchar* szSkeletalPhysicsRes, IXModelInstance* pModelInstance, IXPhysicsScene* pOwningScene) = 0;

	/**
	* 全局风效
	*/
	virtual void			SetWindSpeed(xfloat32 fWindSpeed) = 0;
	virtual xfloat32		GetWindSpeed() const = 0;
	virtual void			SetWindDir(const XVECTOR3& vDir) = 0;
	virtual const XVECTOR3&	GetWindDir() const = 0;

	/**
	* 以下函数仅限引擎内部调用
	*/
	virtual IXCloth*		LoadClothText(const xchar* szPath) = 0;
	virtual IXPhysicsRes*	CreatePhysicsRes(PhysicsResourceType eType, const xchar* szName = NULL) = 0;
	virtual xbool			SavePhysicsRes(const xchar* szFile, IXPhysicsRes* pRes) = 0;
};

extern IXPhysicalManager* g_pIXPhysicalManager;

#endif