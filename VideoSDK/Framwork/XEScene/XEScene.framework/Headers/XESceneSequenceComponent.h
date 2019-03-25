/******************************************************************************

@File         XESceneSequenceCompoent.h

@Version       1.0

@Created      2018, 3, 8

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XESCENESEQUENCECOMPONENT_H
#define XESCENESEQUENCECOMPONENT_H
#include "XEActorComponent.h"
#include "XEUtility.h"
#include "XESeqBindingActorCameraInstance.h"

class XESequencerInstance;
class XESceneSequenceComponent :public XEActorComponent
{
public:
	XESceneSequenceComponent();
	~XESceneSequenceComponent(){}
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
		XESceneSequenceComponent* m_pComponent;
	};
public:
	virtual void                                        Release() override;
	virtual void                                        Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void                                        Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*                                 Serialize(XMLElement* pEleParent) override;
#if X_PLATFORM_WIN_DESKTOP			                    
	virtual void                                        GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy, XEPropertyObjectSet& po) override;
#endif								                    
	xbool                                               LoadAsset(const xchar* pPath);
	void                                                Unload();
	xbool                                               ChangeBindingActor(const xchar* szOldActorName, XEActor* pNewActor, const xchar* szSpecificNodeName = NULL, const xchar* szSpecificNodeType = XESeqBindingActorInstance::NODE_TYPENAME, xbool bNodeTypeFuzzyFind = xfalse);//to find the binding actor INSTANCE-nodes with the specific node-type and actor name, and replace with the new actor. [CAN INDICATE A SPECIFC NODE NAME AS WELL.]
public:
	X_FORCEINLINE XESequencerInstance*			        GetSequenceInstance(){ return m_pSequencerIns; }
	X_EES_LINE X_FORCEINLINE const XESequencerInstance*	GetSequenceInstance() const { return m_pSequencerIns; }
	X_FORCEINLINE const XString&		                GetAssetPath() const { return m_szAssetPath; }
protected:
	// Override this method for custom behavior.
	virtual xbool                                       MoveComponentImpl(const XVECTOR3& vNewWorldLocation, const XQUATERNION& qNewWorldQuaternion) override;
	virtual XMATRIX4                                    GetRawWorldTransformImpl() const override;
	virtual xbool                                       ApplyWorldTransformImpl(const XMATRIX4& mat) override;
public:
	XE_COMPONENT_CAST(XESceneSequenceComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XESceneSequenceComponent)
	static const XString COMPONENT_TYPENAME;
protected:
	XESequencerInstance*                                m_pSequencerIns;
	XString                                             m_szAssetPath;
};

#endif // XESCENESEQUENCECOMPONENT_H
