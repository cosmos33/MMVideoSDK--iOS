/******************************************************************************

@File         XESkySphereActor.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_SKYSPHERE_ACTOR_H
#define XE_SKYSPHERE_ACTOR_H
#include "XEActor.h"
//#include "X3DSky.h"

class XESkySphereActor :public XEActor
{
public:
	struct XESkySetting
	{
		XESkySetting(){};
		XESkySetting(const xchar* pszCapTexturePath, const xchar* pszSurroundFrontTexturePath, const xchar* pszSurroundBackTexturePath/*, X3DSky::XANIM_PROP& AnimProp*/);
		XString				strCapTexturePath;
		XString				strSurroundFrontTexturePath;
		XString				strSurroundBackTexturePath;
		//X3DSky::XANIM_PROP	sAnimProp;
	};
	typedef XHashTable<XString, XESkySetting> XESkySettingMap;
	XESkySphereActor();
	~XESkySphereActor(){};
public:
	virtual void        Initialize(XEWorld* pWorld) override;
	virtual void        Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void        Render(XEViewport* pViewport) override;
	virtual void        Release() override;
	virtual void        Deserialize(const XMLElement* pEleActor) override;
	virtual XMLElement* Serialize(XMLElement* pEleParent) override;
	XE_ACTOR_CAST(XESkySphereActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XESkySphereActor)
	static const XString	ACTOR_TYPENAME;
public:
	xbool               Present(XEViewport* pViewport, const xchar* pSkyName = NULL);
	void                Absent();
	X_FORCEINLINE xbool IsPresent(){ return m_bPresent; }
	xbool               AddSkySetting(const XString& skyName, const XESkySetting& cfg);
	xbool               SwitchSky(const XString& skyName);
	xbool               SwitchSkyNext();
private:			    
	xbool               TransSky(const XESkySetting* pSkySetting);
private:
	xbool              m_bPresent;//should be present first.
	xint32             m_nSkyIndex;
	XString            m_szActiveSkyName;
	//X3DSky		   m_Sky;
	XESkySettingMap	   m_mSkySettings;
};

#endif // XE_SKYSPHERE_ACTOR_H
