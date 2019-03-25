/******************************************************************************

@File         XEUISceneActor.h

@Version       1.0

@Created      2018, 7, 5

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XEUISCENEACTOR_H
#define XEUISCENEACTOR_H
#include "XEActor.h"
#include "XEModelComponent.h"

class XUIScene;
class XEUISceneActor
	:public XEActor
{
public:
	XEUISceneActor();
	virtual ~XEUISceneActor();
public:
    XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	XE_ACTOR_CAST(XEUISceneActor)
	X_CLASS_DEF(XEUISceneActor)
	virtual void									 Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void									 Render(XEViewport* pViewport) override;
	virtual void									 Initialize(XEWorld* pWorld) override;
	static const									 XString ACTOR_TYPENAME;

	virtual xbool                                    LoadAsset(const xchar* pPath);
	virtual void                                     Empty();
	virtual void									 Deserialize(const XMLElement* pEleActor) override;
	virtual XMLElement*								 Serialize(XMLElement* pEleParent) override;


	XUIScene*										 GetScene()const { return m_pScene; }

public:

private:
	XUIScene*										 m_pScene;
	XString											 m_strScenePath;
};
#endif // XEASTATICMESHACTOR_H
