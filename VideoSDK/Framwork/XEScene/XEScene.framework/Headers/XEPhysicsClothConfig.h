/******************************************************************************

@File         XEPhysicsClothConfig.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_PHYSICIS_OBJECT_H
#define XE_PHYSICIS_OBJECT_H

#include "XEUserNode.h"
#include "XArray.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class XEAnimatableModelComponent;
class XEActorComponent;
class IXCloth;
class XEWorld;

typedef void (*CallBackMessageBox)(const xchar* szInfo);

//as a usernode instance.
class XEPhysicsClothConfig
	:public XEUserNodeInstance
{
public:
	XEPhysicsClothConfig();
	virtual ~XEPhysicsClothConfig();

	struct XEClothParam
	{
		XString							strCurrentName;
		XArray<XEClothParam>		aSubParamNames;

		XEClothParam(){}
		XEClothParam(const xchar* szName) :strCurrentName(szName){}
	};
public:
	virtual void				Release()override;
	virtual void				Tick(xfloat32 fInterval)override;
	virtual void				Render(XEViewport* pViewport)override;
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif

public:
	xbool						AcceptPreviewAnimatableModel(const XString& strPath);
	XEAnimatableModelComponent*	GetPreviewAnimatableModelComponent(){ return m_pSessionAsset; }
	X_FORCEINLINE void          SetPhysicsSceneName(const XString& szName){ m_strPhysicsSceneName = szName; }
	X_FORCEINLINE const XString&GetPhysicsSceneName()const{ return m_strPhysicsSceneName; }
	X_FORCEINLINE void          SetWorld(XEWorld* pWorld){ m_pWorld = pWorld; }
	X_FORCEINLINE XEWorld*      GetWorld(){ return m_pWorld; }

	//wind
	XVECTOR3					GetWindDir();
	xfloat32					GetWindSpeed();
	void						SetWindDir(XVECTOR3& vDir);
	void						SetWindSpeed(xfloat32& fSpeed);

	//cloth
	// 创建布料并绑定mesh
	IXCloth*					GetClothPrimitive(const xchar* szMeshName);
	xbool						CreateClothAttachModel(const xchar* szClothPath, const xint32& nSkinIndex);
	void						RemoveAndReleaseClothAssetFromMesh(const xchar* szMeshName);//移除某个Mesh的布料，解绑和删除
	void						GetClothPrimitive(XArray<IXCloth*>& pCloths);

	XArray<XEClothParam>&		GetAllClothParamName(){ return m_aParamName; }

	xbool						Serialize();
	void						SetModify(xbool bModify){ m_bModify = bModify; }
	xbool						GetIsModify(){ return m_bModify; }

	void						SetCallBackMessageBox(CallBackMessageBox callback){ m_CallBackMessageBox = callback; }
	CallBackMessageBox			GetCallBackMessageBox(){ return m_CallBackMessageBox; }

	void						GetMeshNameWithCloth(XArray<XString>& aMeshName);
	xbool						IsModeBindCloth(const xchar* szClothPath);

	const XString&				GetActorName(){ return m_strActorName; }
private:
	void						ExtractClothParamNames();
	void     					AppendString(std::vector<std::string>& vStrs, std::string& result);
public:
	XE_USER_NODE_CAST(XEPhysicsClothConfig)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	static const XString  PARAM_NAMES[20];
private:
	XEAnimatableModelComponent*	m_pSessionAsset;
	XArray<XEClothParam>	    m_aParamName;
	XArray<XString>			    m_aMeshName;
	xbool						m_bModify;
	XString						m_strPhysicsSceneName;
	CallBackMessageBox			m_CallBackMessageBox;
	XEWorld*					m_pWorld;
	XString						m_strActorName;
};

#endif // XE_PHYSICIS_OBJECT_H
