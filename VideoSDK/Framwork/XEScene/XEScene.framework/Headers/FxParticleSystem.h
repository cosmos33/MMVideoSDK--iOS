#ifndef _FXPARTILCESYSTEM_H_
#define _FXPARTILCESYSTEM_H_

#include "FxElement.h"
#include "XArray.h"

class FxModule;
class FxModuleSpawn;
class XPerspectiveCamera;
class XFileBase;
class FxInstance;
class FxParticleSystemData;
class FxModuleRequired;
class FxParticle;
class FxModuleEventReceiver;
class FxModuleEventGenerator;

class FxParticleSystem : public FxElement
{
public:
							FxParticleSystem(const xchar* szName);
	virtual					~FxParticleSystem();

	virtual xbool			Save(XFileBase* pFile, xint32 nVersion);
	virtual xbool			Load(XFileBase* pFile, xint32 nVersion);
	virtual FxParticleSystem* Clone();
	virtual FxParticleSystem* Dumplicate();
	virtual void			Tick(xfloat32 fDeltaTime, FxInstance* pInstance) override;
	virtual void			PostTick(xfloat32 fDeltaTime, FxInstance* pInstance) override;
	virtual xbool			CanComplete() override;
	virtual xint32			GetMaxParticles() override;

	xint32					GetModuleNum();
	FxModule*				GetModule(xint32 nIndex);
	FxModule*				AddModule(FxModuleType eType);
	virtual xbool			RemoveModule(xint32 nIndex);
	xbool					MoveModule(xint32 nOldIndex, xint32 nNewIndex);
	FxModuleRequired*		GetRequiredModule(){ return m_pRequiredModule; }	
	virtual void			ForceSpawn(xint32 nSpawnNum, const XVECTOR3& vInitPos, const XVECTOR3& vInitVelocity, xfloat32 fDeltaTime, FxInstance* pInstance, FxParticleSystemData* pData);

protected:
	virtual FxModule*		CreateModule(FxModuleType eType);
	void					EmitterTimeSetup(xfloat32 fDeltaTime, FxInstance* pInstance, FxParticleSystemData* pData);
	void					Allocate(FxParticleSystemData* pData);
	virtual void			KillParticles(FxInstance* pInstance, xfloat32 fDeltaTime, FxParticleSystemData* pData);
	//void					KillParticle(xint32 nIndex, FxParticleSystemData* pData);
	void					UpdateParticles(FxInstance* pInstance, FxParticleSystem* pPS, xfloat32 fDeltaTime, FxParticleSystemData* pData);
	void					SelfUpdateParticles(xfloat32 fDeltaTime, FxParticleSystemData* pData);
	virtual void			Spawn(FxInstance* pInstance, xfloat32 fDeltaTime, FxParticleSystemData* pData);
	virtual void			SpawnParticles(xint32 nSpawnNum, const XVECTOR3& vInitPos, const XVECTOR3& vInitVelocity, xfloat32 fDeltaTime, FxInstance* pInstance, FxParticleSystemData* pData);
	
	void					HandleParticleEvents(FxInstance* pInstance, FxParticleSystem* pPS, xfloat32 fDeltaTime, FxParticleSystemData* pData);
	
	void					ResetParticleParameterToBase(FxParticle* pParticle);
	void					ResetPayload(FxParticleSystemData* pData, xint32 nIndex);
	void					SetupEmitterTime(FxParticleSystemData* pData);
	void					ForceRemoveAllModule();

	FxModuleRequired*		m_pRequiredModule;
	FxModuleSpawn*			m_pSpawnModule;
	XArray<FxModule*>	m_aModules;
	XArray<FxModule*>	m_aSpawnModules;
	XArray<FxModule*>	m_aUpdateModules;
	XArray<FxModuleEventGenerator*>	m_aEventGenerators;
	XArray<FxModuleEventReceiver*>	m_aEventReceiveModules;
};

#endif
