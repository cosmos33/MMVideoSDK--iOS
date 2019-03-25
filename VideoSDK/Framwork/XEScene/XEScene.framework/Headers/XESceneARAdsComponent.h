/******************************************************************************

@File         XESceneARAdsCompoent.h

@Version       1.0

@Created      2018/5/30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XESCENEARAdsCOMPONENT_H
#define XESCENEARAdsCOMPONENT_H

#include "XEActorComponent.h"
#include "XEUtility.h"

class XEARAdsInstance;
class XESceneARAdsComponent :public XEActorComponent
{
public:
	XESceneARAdsComponent();
	~XESceneARAdsComponent(){}
protected:
	class DelayLoadDestroyer :public XEUtility::XEDelayDestroyer
	{
	public:
		DelayLoadDestroyer() :m_pComponent(NULL){}
		virtual ~DelayLoadDestroyer(){}
		//functions that should be override.
		virtual xbool ShouldBeDeleted()override;
		virtual void  Release()override{}
	public:
		XESceneARAdsComponent* m_pComponent;
	};
public:
	virtual void                                Release() override;
	virtual void                                Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void                                Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*                         Serialize(XMLElement* pEleParent) override;
#if X_PLATFORM_WIN_DESKTOP			            
	virtual void                                GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif								            
	xbool                                       LoadAsset(const xchar* pPath);
	void                                        Unload();
public:						     
	X_FORCEINLINE XEARAdsInstance*			    GetARAdsInstance(){ return m_pARAdsIns; }
	X_EES_LINE X_FORCEINLINE const XEARAdsInstance* GetARAdsInstance() const { return m_pARAdsIns; }
	X_FORCEINLINE const XString&		        GetAssetPath() const { return m_szAssetPath; }
protected:
	// Override this method for custom behavior.
	virtual xbool                               MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual XMATRIX4                            GetRawWorldTransformImpl() const override;
	virtual xbool                               ApplyWorldTransformImpl(const XMATRIX4& mat) override;
public:
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	XE_COMPONENT_CAST(XESceneARAdsComponent)
	X_CLASS_DEF(XESceneARAdsComponent)
	static const XString COMPONENT_TYPENAME;
protected:
	XEARAdsInstance*                            m_pARAdsIns;
	XString                                     m_szAssetPath;
};

#endif // XESCENEARAdsCOMPONENT_H
