#ifndef _FXMODULE_H_
#define _FXMODULE_H_

#include "FxPropertyObject.h"
#include "FxGlobal.h"

class XFileBase;
class FxParticleSystem;
class FxParticle;
class FxParticleSystemData;
class FxInstance;
class FxModulePayload;

class FxModule : public FxPropertyObject
{
public:
								FxModule();
	virtual						~FxModule();

	static	FxModule*			CreateModule(FxModuleType eType);
	static	FxModulePayload*	CreateModulePayload(FxModuleType eType);

	virtual xbool				Save(XFileBase* pFile, xint32 nVersion);
	virtual xbool				Load(XFileBase* pFile, xint32 nVersion);

	virtual void				Spawn(FxInstance* pInstance, FxParticleSystem* pPS, xfloat32 fSpawnTime, FxParticle* pParticle, FxParticleSystemData* pData){}
	virtual void				Update(FxInstance* pInstance, FxParticleSystem* pPS, xfloat32 fDeltaTime, FxParticleSystemData* pData){}
	
	void						SetEnabled(xbool bSet){ m_bEnabled = bSet; }
	xbool						IsEnabled() const { return m_bEnabled; }
	FxModuleType				GetType() const { return m_eModuleType; }
	xbool						CanSpawn() const { return m_bSpawn; }
	xbool						CanUpdate() const { return m_bUpdate; }
	xbool						CanEdit()const { return m_bEditable; }

protected:
	FxModuleType				m_eModuleType;
	xbool						m_bSpawn;
	xbool						m_bUpdate;
	xbool						m_bEnabled;
	xbool						m_bEditable;
};

#endif
