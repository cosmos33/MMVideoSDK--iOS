/******************************************************************************

@File         XEUtility.h

@Version       1.0

@Created      2017, 10, 12

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_UTILITY_H_
#define _XE_UTILITY_H_
#include "XEHitResult.h"
#include "XCustomGeometry.h"
#include "XArray.h"
#include "XHashTable.h"
#include "XMaterial.h"
#include "XModel.h"
#include "XModelInstance.h"
#include "tinyxml2_XEngine.h"
#include "XPlatform.h"
#include <string>
#include "IXPhysicsRes.h"
#include "XClass.h"

class XEWorld;
class XEAnimatableModelComponent;
class XEActorComponent;
class XEModelComponent;
class XEViewport;
class XBaseCamera;
class XESceneARAdsVideoComponent;
class XEAnimCurveFlyController;

struct XEMacroRelationParamInfo
{
	XString strMacro;
	XArray<XString> vRelationParam;
	XArray<XString> vEliminateParam;
};

namespace XEUtility
{
	xbool								  GetTriangleFaceInfoByUV(IXModelInstance* pModelIns, const xchar* szMeshName, const xchar* szSkinName, XVECTOR2 uv, xint32& nOutTriIndex, XSkinMeshVertex outVertices[3],xint32 outVerIndices[3]);
	xbool                                 GetVertexPositionFromIndex(IXModelInstance* pModelIns, const xchar* szMeshName, const xchar* szSkinName, xint32 nVertexIndex, XVECTOR3& vOutPos);
	xbool                                 GetVertexIndexFromUV(IXModelInstance* pModelIns, const xchar* szMeshName, const xchar* szSkinName, XVECTOR2 uv, xint32& vOutVertexIndex);
	xbool                                 GetVertexPositionFromUV(IXModelInstance* pModelIns, const xchar* szMeshName, const xchar* szSkinName, XVECTOR2 uv, XVECTOR3& vOutPos);
	xbool                                 GetHitResultAtScreenPosition(const XVECTOR2& ScreenPosition, XEWorld* pWorld, XEHitResult& HitResult, XArray<XEActor*>* pActorsExclude = NULL);//deprecated  Do not use this function - it is deprecated in release 1.2.17. Instead, use XEWorld::RayPick instead[collision channel supported]
	xbool                                 LookAtActorWithCurrentCameraRotation(const XEActor* pActor, const xfloat32 fMultiNum = 1.f);
	xbool                                 LookAtComponentWithCurrentCameraRotation(const XEActorComponent* pComponent, const XEWorld* pWorld, const xfloat32 fMultiNum = 1.f);
	xbool                                 LookAtBoundBoxWithCurrentCameraRotation(const XCusAABB& box, const XEWorld* pWorld, const xfloat32 fMultiNum = 1.f);
	xbool                                 LookAtBoundSphereWithCurrentCameraRotation(const XCusSphere& sphere, const XEWorld* pWorld, const xfloat32 fMultiNum = 1.f);
	XArray<XString>&                      GetMaterialTemplate();
	XHashTable<XString, XEMacroRelationParamInfo>& GetMaterialShaderParamMacroRelation();
	xbool                                 IsShaderParamRelatedToMacro(const XString& strParamName, const XString& strMacroName);
	xbool								  IsShaderParamEliminateByMacro(const XString& strParamName, const XString& strMacroName);
	void                                  MakeNameLegalForLua(std::string& szName);
	XEAnimCurveFlyController*             GetCameraFlyAnimCurveController();
	XEAnimCurveFlyController*             GetActorFlyAnimCurveController();
	XEAnimCurveFlyController*             GetActorComponentFlyAnimCurveController();
#if X_PLATFORM_WIN_DESKTOP
	xbool                                 GetActorAnimationSequenceResources(const XEActor* pAnimationActor, XArray<XString>& arrSeqRes);
	xbool                                 GetComponentAnimationSequenceResources(const XEAnimatableModelComponent* pAnimatableComponent, XArray<XString>& arrSeqRes);
	xbool                                 GetClothResources(const XEAnimatableModelComponent* pAnimatableComponent, XArray<XString>& arrClothRes);
	xbool                                 GetResourcesWithSuffix(XArray<XString>& arrResource, const xchar* pDirPath, const xchar* pSuffix, xbool bRelativeToResourcePath = xtrue);//suffix is with the format of "*.xxx", if bRelativeToResourcePath is set to true, will auto append the relative to the resource path.
	xbool                                 GetComponentVideoResources(const XESceneARAdsVideoComponent* pAnimatableComponent, XArray<XString>& arrVideoRes);
	xbool                                 GetComponentARAdsResources(const XEModelComponent* pSkinModelComponent, XArray<XString>& arrARAdsRes);
	xbool                                 GetComponentMontageAnimationResources(const XEModelComponent* pSkinModelComponent, XArray<XString>& arrMontageAnimRes);
	xbool                                 GetComponentMounterResources(const XEModelComponent* pSkinModelComponent, XArray<XString>& arrMounters);
	xbool                                 GetComponentBlendAnimationResources(const XEModelComponent* pSkinModelComponent, XArray<XString>& arrBlendAnimRes);
#endif
	XQUATERNION                           GetCameraQuaternion(XBaseCamera* pCamera);
	XMATRIX4                              GetCameraWorldMatrix(XBaseCamera* pCamera);
	XArray<XVECTOR3>                      GetCircleTrackPoint(const XVECTOR3 vCenter = XVECTOR3(0.f), const xfloat32 fRadius = 1.f, const xint32 nSegment = 32);
	XArray<XVECTOR3>                      GetCrossRectTrackPoint(const XVECTOR3 vCenter = XVECTOR3(0.f), const xfloat32 fRadius = 1.f);
	XArray<XVECTOR3>                      GetSinTrackPoint(const XVECTOR3 vCenter = XVECTOR3(0.f), const xfloat32 fAmplitude = 1.f, const xfloat32 fPeriod = 1.f);
	XArray<XVECTOR2>                      GetDrawPointOfLookingLocationAtScreen(XEWorld* pWorld, const XVECTOR3& vLocation, const xint32 nInnerPixel = 128);//0 is the location projecting in the screen. others will be the intersecting points.
	xbool                                 GetViewPointOfLookingLocationAtScreen(XEWorld* pWorld, XVECTOR2& vOutPointStart, XVECTOR2& vOutPointEnd, const XVECTOR3& vLocation, const xint32 nInnerPixel = 128);//if location is can be seen, return 0,else 1. output the direction(vOutPointStart,vOutPointEnd)
	void                                  MakePathSimple(XArray<XString>& fullPaths);
	XString                               GetAssetPackageValidPath(const xchar* pFullRelativeAssetPackagePath, const xchar* pEvalAssetPath, xbool bNoRepeatPortionPath = xfalse);//evaluate the input asset path for the relative package(usually come from worlds).
	template<typename T>
	XString                               GetArrayValidName(const XArray<T*>& arrData, const xchar* pPrefix = "ArrayValidName", const xint32 nMaxIndex = 0xffff)
	{
		XString validName;
		if (NULL != pPrefix)
		{
			for (xint32 i = 1; i < nMaxIndex; i++)
			{
				validName.Format("%s_%d", pPrefix, i);
				xbool bExist = xfalse;
				for (xint32 i = 0; i < arrData.Num(); ++i)
				{
					if (T* pData = arrData[i])
					{
						if (0 == pData->GetName().CompareNoCase(validName.CStr()))
						{
							bExist = xtrue;
							break;
						}
					}
				}
				if (xfalse == bExist)
					return validName;
			}
		}
		validName.Empty();
		return validName;//empty
	}
	
	//go through material in a model instance.
	struct MaterialKey{
		xint32 skinId;
		xint32 lodId;
		xint32 meshId;
		xint32 macroId;
		xint32 parameterId;
		MaterialKey() :skinId(0),lodId(0),meshId(0),macroId(-1),parameterId(0){}
		MaterialKey(xint32 _sid, xint32 _lid, xint32 _meid, xint32 _maid, xint32 _pid) :skinId(_sid), lodId(_lid), meshId(_meid), macroId(_maid), parameterId(_pid){}
		xbool operator == (const MaterialKey& mk)const{ return skinId == mk.skinId && lodId == mk.lodId && meshId == mk.meshId && parameterId == mk.parameterId; }//NOTE:(2018/11/7)unnecessary for macroId comparing.
	};

	struct MaterialInfo{
		MaterialKey key;
		XSkin* pSkin;
		IXMaterialInstance* pIns;
		XMaterialSupportMacro*  pMacro;
		XMaterialParamDescInfo* pParamDescInfo;
		XMaterialParamTypeValue paramTypeValue;
		xbool                   bValid;
		MaterialInfo() :pSkin(NULL), pIns(NULL), pMacro(NULL), pParamDescInfo(NULL), bValid(xfalse){}
	};

X_EEB_BEGIN
	typedef xbool(*checkItemMatch)(void* holder, MaterialInfo& materialInfo);
	void                                  TravelMaterialParameter(IXModelInstance* pModelIns,void*  pHolder, checkItemMatch checkFunc);
X_EEB_END

	//apply the specific value for the parameter.
	xbool                                 ApplyMaterialParameter(IXModelInstance* pModelIns, const MaterialKey& mk, xint32 nParamIndex, xfloat32 fParamVal);
	xbool                                 ApplyMaterialParameter(IXModelInstance* pModelIns, const MaterialKey& mk, const xchar* pTexPath);
	//szMTPath/szTexPath full relative path to the engine root
	//will match to the name
	xbool                                 ApplyMaterialType(IXModelInstance* pModelIns, const xchar* szSkinName, const xchar* szMaterialInsName, const xchar* szMTPath);
	xbool								  ApplyMaterialTextureParameterValue(IXModelInstance* pModelIns, const xchar* szSkinName, const xchar* szMaterialInsName, const xchar* szParamDesc, const xchar* szTexPath);
	xbool                                 ApplyMaterialVectorParameterValue(IXModelInstance* pModelIns, const xchar* szSkinName, const xchar* szMaterialInsName, const xchar* szParamDesc, const XVECTOR4& valueSlot);//as max as xvector4
	xbool								  ApplyMaterialVectorParameterValue(IXMaterialInstance *pMaterialIns, const xchar* szParamDesc, const XVECTOR4& valueSlot);
	//get method
	const xchar*                          GetMaterailType(IXModelInstance* pModelIns, const xchar* szSkinName, const xchar* szMaterialInsName);
	const xchar*                          GetMaterailTextureParameterValue(IXModelInstance* pModelIns, const xchar* szSkinName, const xchar* szMaterialInsName, const xchar* szParamDesc);
	XVECTOR4                              GetMaterialVectorParameterValue(IXModelInstance* pModelIns, const xchar* szSkinName, const xchar* szMaterialInsName, const xchar* szParamDesc);
	MaterialInfo                          GetMaterialParamTypeValue(IXModelInstance* pModelIns, const xchar* szSkinName, const xchar* szMaterialInsName, const xchar* szParamDesc);

	xbool								  ApplyMaterailInsParamToOther(const IXMaterialInstance *pSourceMaterialIns, IXMaterialInstance *pDestMaterialIns);
	xbool								  GetRawMeshNameByMaterialInsName(IXModelInstance* pModelIns, const xchar* szSkinName, const xchar *szMaterialInsName, xint32 nLod, XArray<XString> &vRawMeshName);


	//////////////////////////////////////////////////////////////////////////
	enum ESceneType
	{
		ST_DEFAULT = 0,//default scene
		ST_FACE_TRACKER /*= 0*/,
		ST_MOBILE_AR,
		ST_ARADS,
		ST_NUM
	};

	const XString&				GetSceneNameByType(ESceneType eType);
	ESceneType					GetSceneTypeByName(const XString &str);
	const XArray<XString>&		GetAllSceneType();


	EConstraintMotion			GetConstraintMotionTypeByName(const XString& str);
	const XArray<XString>&		GetConstraintMotionNameList();

	IXSkeletalPhysicsRes::EPhysResFitVertWeight		GetPhysResFitVertWeightTypeByName(const XString& str);
	const XArray<XString>&		GetAllPhysResFitVertWeightType();
	const XArray<XString>&		GetAllShapeMaterialParams();

	class XEBinaryString
	{
	public:
		XEBinaryString();
		~XEBinaryString();
	public:
		const xchar*            BinaryToString(void * pData, xint32 nlen );
		xbool		            StringToBinary(const xchar * pString, void * pData, xint32 iDataBufSize);
		xbool		            IsChar(xchar ch);
	protected:
		xchar*      m_pBuffer;
		xuint32		m_dwBufferSize;
	};

	//delay destroyer
	class XEDelayDestroyer
	{
	public:
		XEDelayDestroyer(){}
		virtual ~XEDelayDestroyer(){}
		//functions that should be override.
		virtual xbool ShouldBeDeleted() = 0;
		virtual void  Release() = 0;
		virtual void  Tick(xfloat32 fDel){}//in milliseconds.
		virtual void  Render(XEViewport* pViewport){}
	};
	typedef XArray<XEDelayDestroyer*> DelayDestoryerList;


	//vectors.
	template<typename T, int n>
	class XEVector
	{
	public:
		XEVector(){ memset(m, 0, n * sizeof(T)); }
		T m[n];
		T* X(){ return 1 <= n ? &m[0] : NULL; }
		T* Y(){ return 2 <= n ? &m[1] : NULL;  }
		T* Z(){ return 3 <= n ? &m[2] : NULL;  }
		T* W(){ return 4 <= n ? &m[3] : NULL;  }
		const T* X()const{ return 1 <= n ? &m[0] : NULL; }
		const T* Y()const{ return 2 <= n ? &m[1] : NULL; }
		const T* Z()const{ return 3 <= n ? &m[2] : NULL; }
		const T* W()const{ return 4 <= n ? &m[3] : NULL; }
	};

X_EEB_BEGIN
	extern const xfloat32            c_StanderCameraDis;
	extern const xfloat32            c_StanderDirScale;
	extern const xfloat32            c_StanderFadeDis;
	extern const xfloat32            c_StanderOrthSize;
	extern const xint32              c_MaxParticleSystemFadingTime;//ms.
	extern const xchar*	             c_PhyBodySuffix;
	extern const xchar*	             c_PhyConstraintSuffix;
	extern const xchar*              c_SupportPhysicsSkeletonSceneMinVersion;
	extern const xchar*              c_szMacro_DEFAULTENABLE;
X_EEB_END

	//XEActorSerializeFlag
	struct XEActorPropertySerializeFlag
	{
	public:
		XEActorPropertySerializeFlag(xbool bCopyInProcessTemp = xfalse)
			: bIsCopyProcess(bCopyInProcessTemp)
		{ }

		//actor serialize before start
		void				 SetIsCopyProcess(xbool bCopyInProcessTemp){ bIsCopyProcess = bCopyInProcessTemp; }
		void	             SetCopyActorName(const XString& strCurCopyActorName){ strCopyActorName = strCurCopyActorName; }
		void				 AddChildActorNames(const XArray<XString>& aChildActorNameTemp);
		void				 SetCopyActorFilterPath(const XString& strCurCopyActorFilterTemp){ strCopyActorFilterPath = strCurCopyActorFilterTemp; }
		void				 SetParentActorName(const xchar* szParentActorName){ strParentActor = szParentActorName; }
		//actor serialize before end

		//actor serializing
		xbool			     IsCopyProcess(){ return bIsCopyProcess; }
		XString	             GetCopyActorName(){ return strCopyActorName; }
		xbool				 IsExistChildActor(const XString& strChildActorName);
		XString				 GetCopyActorFilter(){ return strCopyActorFilterPath; }
		XString				 GetParentActorName(){ return strParentActor; }
		//actor serializing

		//actor serialize after start
		void                 Reset();
		//actor serialize after start

		tinyxml2_XEngine::XMLElement*          Serialize(tinyxml2_XEngine::XMLElement* pEleParent);
		void								   Deserialize(const tinyxml2_XEngine::XMLElement* pEleParent);

	private:
		xbool				 bIsCopyProcess;//no Serialize
		XString	             strCopyActorName;//根据此Actor拷贝的Actor Name
		XString				 strCopyActorFilterPath;//save
		XString				 strParentActor;//save
		XArray<XString>		 aChildActorNames;//no Serialize
	};

	xbool					 IsExistActorInActorList(const XEActor* pActor, const XArray<XEActor*>& aActorList);

	struct XESceneData
	{
		ESceneType				eSceneType;//such as face tracker, mobile ar ...
		XString					strSceneVersion;//version
		XESceneData() :eSceneType(ST_DEFAULT) //change to default. yanglj.
			, strSceneVersion(XEUtility::c_SupportPhysicsSkeletonSceneMinVersion){}
		XESceneData(ESceneType eType, XString strVersion) :eSceneType(eType), strSceneVersion(strVersion){}
		xbool operator == (const XESceneData& sd)const{ return eSceneType == sd.eSceneType && strSceneVersion == sd.strSceneVersion; }
	};

	//load skeletal phy res from file
	IXPhysicsRes*			 LoadPhysicsResFromPhy(const xchar* szPhyPath, xbool bReload = xfalse);
	IXPhysicsRes*			 CreatePhysicsRes(PhysicsResourceType eType, const xchar* szName, const xchar* szMdlPath, const IXSkeletalPhysicsRes::XPhysResCreateParams& Params);
};

typedef XEUtility::XEVector<xint32, 2> XEVector2i;
typedef XEUtility::XEVector<std::string, 2> XEVector2s;

#define ASSERT_ERROR(V,I) ASSERT(0&&V&&I)
#endif
