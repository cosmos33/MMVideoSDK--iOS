/******************************************************************************

@File         XEAuxiliaryLineActor.h

@Version       1.0

@Created      2018, 7, 3

@Description  The class ids of UI Designer

@HISTORY:

******************************************************************************/

#ifndef _XE_AUXILIARYLINEACTOR_H_
#define _XE_AUXILIARYLINEACTOR_H_

#include "XEActor.h"
#include "XMath3D.h"
#include "XTypes.h"

class XEAuxiliaryLineActor : public XEActor
{
	enum EAuxiliaryLine_Alignment
	{
		EALA_horizontal,
		EALA_vertical
	};
public:
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	XE_ACTOR_CAST(XEAuxiliaryLineActor)
	X_CLASS_DEF(XEAuxiliaryLineActor)
	static const XString	    ACTOR_TYPENAME;
	XEAuxiliaryLineActor();
	virtual					    ~XEAuxiliaryLineActor();
	virtual void			    Serialize(XFileBase *pFile) override {}
	virtual void                Deserialize(const XMLElement* pEleActor) override;
	virtual XMLElement*         Serialize(XMLElement* pEleParent) override;
	virtual void			    Tick(xfloat32 fDel, xbool bForceTick = xtrue) override {}
	virtual void			    Render(XEViewport* pViewport) override;
	virtual void                Initialize(XEWorld* pWorld) override;
	virtual xbool               RayPick(XEHitResult& hr) override;
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif // X_PLATFORM_WIN_DESKTOP

protected:
	void						DrawAuxiliaryLine(const XVECTOR2& s, const XVECTOR2& e, const EAuxiliaryLine_Alignment& _align);


	XCOLORBASE					m_auxiliaryColor;
};

#endif



