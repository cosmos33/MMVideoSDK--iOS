#ifndef _PHYSICAL_INTERFACE_H_
#define _PHYSICAL_INTERFACE_H_

#include "XTypes.h"
class IXModelInstance;
class IXPhysicalManagerBase
{
public:
	virtual xbool	LoadCloth(const xchar* szClothPath, IXModelInstance* pInstance, const xchar* szMeshName) = 0;
	virtual void	OnModelReleased(IXModelInstance* pInstance) = 0;
};

void SetPhysicalManager(IXPhysicalManagerBase* pManager);
extern IXPhysicalManagerBase*	g_pPhysicalManagerBase;

#endif
