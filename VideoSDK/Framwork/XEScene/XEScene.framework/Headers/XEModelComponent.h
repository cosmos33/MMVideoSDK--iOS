/******************************************************************************

@File         XEModelComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XESKINMODELCOMPONENT_H
#define XESKINMODELCOMPONENT_H

#include "XModelInstance.h"
#include "XEPrimitiveComponent.h"
#include "XETreeNode.h"
#include "XEUtility.h"

class IXCloth;
class XESkeletonInstance;
class XEAnimMontageInstance;//will only use the instance.
class XEAnimSocketMounterInstance;//will only use the instance.
class XEAnimBlendInstance;
class XEMaterialFxInstance;//runtime effect of material.

class XEAnimController;
class XEAnimComponentPlayList;
class IXEDressup;
class XEARAdsComponentPlayList;
class XEModelComponent
	: public XEPrimitiveComponent
{
	friend class XEMeshAppliqueComponent;
public:
	         XEModelComponent();
	virtual ~XEModelComponent();
protected:
	//delay loading...
	class DelayLoadDestroyer :public XEUtility::XEDelayDestroyer
	{
	public:
		DelayLoadDestroyer() :m_pComponent(NULL){}
		virtual ~DelayLoadDestroyer(){}
		//functions that should be override.
		virtual xbool ShouldBeDeleted()override;
		virtual void  Release()override{}
	public:
		XEModelComponent* m_pComponent;
	};
public:
	virtual xbool                                               LoadAsset(const xchar* pPath);
	virtual void                                                Release() override;
	virtual void                                                Empty() override;
	virtual void                                                Render(XEViewport* pViewport) override;
	virtual void                                                Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void                                                Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*                                         Serialize(XMLElement* pEleParent) override;
	virtual XCusAABB                                            GetCusAABB(xfloat32* pfRadius = NULL) const override;
	virtual xbool                                               RayPick(XEHitResult& hr) override;
#if X_PLATFORM_WIN_DESKTOP			                            
	virtual void                                                GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif								                            
	//Cloth start---				                            
	virtual xbool                                               CreateClothAttachModel(const xchar* szClothPath, XEWorld* pWorld, xint32 nSkinIndex);
	virtual void					                            RemoveAndReleaseClothAssetFromMesh(const xchar* szMeshName);
	virtual IXCloth*				                            GetClothPrimitive(const xchar* szMeshName);
	virtual xbool					                            SaveCloths(const xchar* szClothPath = "");
	virtual void					                            AddAllClothToSceneWithModel(XEWorld* pWorld);
	void					                                    RemoveCloth(IXCloth* pCloth);
	void                                                        GetClothPrimitive(XArray<IXCloth*>& pCloths);
	//Cloth end---					                            
	virtual void					                            SetDeleted(xbool bDelete) override;
	virtual XEAnimController*                                   GetAnimController();//could be montage animation controller or model-animation controller.
	X_EES_LINE virtual const XEAnimController*                  GetAnimController() const;
	virtual const xchar*                                        GetCurPlayAnimation();
	virtual void					                            PresentPhysics(xfloat32 fDel) override;
	virtual void                                                SetHidden(xbool bHide) override;
													            
	static XModel*                                              GetXModelFromAsset(const xchar* pAssetPath);//full path, ref may add 1.
	xbool                                                       BuildSkeletonInstance();
	xbool                                                       DestroySkeletonInstance();	
	void											            SetSkeletonInstance(XESkeletonInstance* pSkeleIns);
	XEAnimComponentPlayList*                                    AssignAnimPlayList();//to assign an Animation play list controller, if it was not exist yet.
	XEAnimComponentPlayList*                                    GetAnimPlayList();
	X_EES_LINE const XEAnimComponentPlayList*                   GetAnimPlayList() const;
	virtual xbool					                            LoadPhysicalAsset(const xchar* pPath, RigidActorType eType) override;
													            
	XEARAdsComponentPlayList*                                   AssignARAdsPlayList();
	XEARAdsComponentPlayList*                                   GetARAdsPlayList();
	X_EES_LINE const XEARAdsComponentPlayList*                  GetARAdsPlayList() const;
													            
	xbool                                                       GetVertexPositionFromUV(const xchar* szMeshName, const xchar* szSkinName, XVECTOR2 uv, XVECTOR3& vOutPos);
private:									                    
	//physical start				                            
	void							                            DeserializePhysicalProperty(const XMLElement* pEleComponent);
	void							                            DeserializePhysicalShapeMaterial(const XMLElement* pEleComponent);
	void                                                        DeserializeARAdsProperty(const XMLElement* pEleComponent);
	//physical end									            
public:										                    
	X_FORCEINLINE IXModelInstance*                              GetModelInstance() const{ return m_pModelIns; }
	X_FORCEINLINE IXEDressup*						            GetDressUp() const { return m_pDressup; }
	X_FORCEINLINE const XString&                                GetAssetPath() const { return m_szAssetPath; }
	X_FORCEINLINE XESkeletonInstance*                           GetXESkeletonInstance(){ return m_pXESkeletonInstance; }
											        
	X_FORCEINLINE XEAnimMontageInstance*                        GetMontageInstance(){ return m_pAttachMontageIns; }
	X_EES_LINE X_FORCEINLINE const XEAnimMontageInstance*       GetMontageInstance() const{ return m_pAttachMontageIns; }

	X_FORCEINLINE XEAnimBlendInstance*                          GetBlendInstance(){ return m_pAttachBlendIns; }
	X_EES_LINE X_FORCEINLINE const XEAnimBlendInstance*         GetBlendInstance() const{ return m_pAttachBlendIns; }

	X_FORCEINLINE XEAnimSocketMounterInstance*                  GetMounterInstance(){ return m_pAttachMounterIns; }
	X_EES_LINE X_FORCEINLINE const XEAnimSocketMounterInstance* GetMounterInstance() const{ return m_pAttachMounterIns; }	

	X_FORCEINLINE XEMaterialFxInstance*                         GetMaterialFxInstance(){ return m_pAttachMaterialFxIns; }
	X_EES_LINE X_FORCEINLINE const XEMaterialFxInstance*        GetMaterialFxInstance() const{ return m_pAttachMaterialFxIns; }

	xbool                                                       AttachMounterAsset(const xchar* pAssetPath, xbool bReloadAsset = xtrue);
	void                                                        AttachMontageInstance(XEAnimMontageInstance* pMontageIns);
	void                                                        DetachMontageInstance();	
													            
	void                                                        AttachMounterInstance(XEAnimSocketMounterInstance* pMounterIns);
	void                                                        DetachMounterInstance();
													            
	xbool                                                       AttachBindingMaterialFxAsset(const xchar* pAssetPath);//path will be fixed.
	void                                                        AttachBindingMaterialFxInstance(XEMaterialFxInstance* pMaterialFxIns);
	void                                                        DetachBindingMaterialFxInstance();
	xbool                                                       HasMaterialFxNode(xint32 nSkinID, xint32 nMeshID, xint32 nLodID, xint32 nParamID);
													            
	void                                                        AttachBlendInstance(XEAnimBlendInstance* pBlendIns);
	void                                                        DetachBlendInstance();	
													            
protected:										                
	// Override this method for custom behavior.                
	virtual xbool                                               MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual XMATRIX4                                            GetRawWorldTransformImpl() const override;
	virtual xbool                                               ApplyWorldTransformImpl(const XMATRIX4& mat) override;	


public:
	// 为当前模型实例，创建新的模板 (fix flk 解决模型实例，无法针对材质和skin，差异化问题的解决实现, 此处所有材质相关的，都应该在材质编辑器有了之后，进行调整，或者去掉)
	xbool											            EmbedCurrentModel();
	xbool											            EmbedCutModelSkin(const xchar* szSkin, XString *pEmbedSkinName = NULL);
	xbool											            EmbedMeshMaterialIns(const xchar* szSkin, const xchar *szRawMeshName, xint32 nLod = 0, XString *pEmbedMatInsName = nullptr);
	const xchar*									            GetEmbedSkinName(const xchar* szSourceSkin);
	const xchar*									            GetEmbedMaterialInsName(const xchar* szSourceSkin, const xchar* szSourceMaterialInsName);
	xbool											            ClearEmbedRecoredSkin(const xchar *szSkin, xbool bSource = xtrue);
	xbool											            ClearEmbedRecord(xbool bClearModel = xtrue);
													            
protected:											            
	xbool											            IsUseEmbeddedModel();
	xbool											            IsUseEmbeddSkin(const xchar* szSkin);
	xbool											            IsUseEmbeddMeshMaterialIns(const xchar* szSkin, const xchar *szRawMeshName);
	xbool											            EmbedCurrentModelSkin(const xchar* szSkin, XString *pEmbedSkinName = NULL);
													            
	/*	由SourceModel，创建新的模型模板*/				            
	XModel*											            EmbedModel(XModel *pSourceModel);
	IXEDressup*										            EmbedDressup(IXEDressup *pSourceDressup);
	xbool											            ReloadModelInstance(const xchar* pPath);

	/*	由SourceSkin，创建新的蒙皮

		@ param  bSetMaterail : xture ： 创建时，同步原始的材质信息到新建蒙皮；
	*/
	XSkin*											            EmbedSkin(XSkin *pSourceSkin, xbool bSetMaterail = xtrue);

	/* 为skin中指定的rawmesh,创建新的材质实例

	   @ notice （fix flk 当之后，有材质编辑器后，材质都是编辑器创建的，此处的嵌入材质实例的逻辑，就不需要了）
	*/
	xbool											            EmbedMaterialIns(XSkin *pSourceSkin, const xchar* szRawMeshName, xint32 nLod = 0, XString *pEmbedMatInsName = nullptr);	

	/* 根据网格计算宏（*之后考虑移到底层引擎中*）*/
	XString											            ComputeMacrosByMesh(const XSkinData::XRenderMesh *pRenderMesh);

public:
	XE_COMPONENT_CAST(XEModelComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEModelComponent)
	static const XString COMPONENT_TYPENAME;
protected:
	IXModelInstance*                                            m_pModelIns;
	XEAnimComponentPlayList*                                    m_pAnimPlayList;
	XEARAdsComponentPlayList*                                   m_pARAdsPlayList;
	XString                                                     m_szAssetPath;
											                    
	XESkeletonInstance*                                         m_pXESkeletonInstance;
	XEAnimMontageInstance*                                      m_pAttachMontageIns;
	XEAnimSocketMounterInstance*                                m_pAttachMounterIns;
	XEAnimBlendInstance*                                        m_pAttachBlendIns;
	XEMaterialFxInstance*                                       m_pAttachMaterialFxIns;
													            
	IXEDressup*										            m_pDressup;

	
	// Embed Record Info
	xbool											            m_bUseEmbeddedModel;
	// key : old skin name; value : new skin name;	            
	XHashTable<XString, XString>					            m_mUseEmbeddedSkin;

	struct EmbedRawMeshMat
	{
		XString strRawMesh;
		XString strOldMatInsFile;
		XString strEmbedMatInsFile;
	};
	
	// key : old skin name;
	XHashTable<XString, XHashTable<XString, EmbedRawMeshMat>>   m_mUseEmbeddedRawMeshMatIns;

};

#endif // XESKINMODELCOMPONENT_H
