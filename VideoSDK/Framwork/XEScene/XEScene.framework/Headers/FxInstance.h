#ifndef _FXINSTANCE_H_
#define _FXINSTANCE_H_

#include "XBaseCoordSpace.h"
#include "XRefCount.h"
#include "FxGlobal.h"

class FxElement;
class IFxTemplate : public XRefCount, public XMemBase
{
public:
	virtual				 ~IFxTemplate(){}

	virtual const xchar* GetName() const = 0;
	virtual xint32		 GetElementNum() const = 0;
	virtual FxElement*	 GetElement(xint32 nIndex) = 0;
	virtual FxElement*	 AddElement(const xchar* szName, FxElementType eType) = 0;
	virtual xbool		 AddElement(FxElement* pElement) = 0;
	virtual xbool		 RemoveElement(xint32 nIndex, xbool bDelete = xtrue) = 0;
	virtual xbool		 RemoveElement(FxElement* pElement, xbool bDelete = xtrue) = 0;
	virtual xbool		 MoveElement(FxElement* pElement, xint32 nMoveAmount) = 0;
	virtual xbool		 DumplicateElement(xint32 nIndex) = 0;
	virtual xbool		 DumplicateElement(FxElement* pElement) = 0;
};

class IXWorld;
class XBaseCamera;
class IFxInstance : public XBaseCoordSpace, public XMemBase
{
public:
	virtual				 ~IFxInstance(){}
	// resource			 
	virtual void		 Release() = 0;

	// update			 
	virtual void		 Tick(xfloat32 fDeltaTime) = 0;

	// play control		 
	virtual void		 Play() = 0;
	virtual void		 Pause() = 0;
	virtual xbool		 IsPaused() const = 0;
	virtual void		 Stop(xbool bClearNow = xfalse) = 0;
	virtual void		 Restart() = 0;
	virtual xbool		 IsCompleted() const = 0;

	// render			 
	virtual void		 Render(XBaseCamera* pCamera, IXWorld* pScene) = 0;

	// 					 
	virtual IFxTemplate* GetFxTemplate() = 0;
	virtual void		 OnPostEditProperty() = 0;
	virtual xint32		 GetParticleNum(xint32 nElementIndex) const = 0;
	virtual xint32		 GetParticleNum(FxElement* pElement) const = 0;
};

class IFxManager : public XMemBase
{
public:
	virtual xbool		 Init() = 0;
	virtual void		 Release() = 0;

	// 根据模板文件创建一个特效实例
	virtual IFxInstance* GetFxInstance(const xchar* szFxTemplateFile) = 0;
	// 新建一个特效实例
	virtual IFxInstance* CreateFxInstance(const xchar* szNewFxTemplateFile) = 0;
	// 将一个FxTemplate对象存到硬盘
	virtual xbool		 SaveFxTemplate(const xchar* szFxTemplateFile, IFxTemplate* pTemplate) = 0;

protected:
	virtual				 ~IFxManager() {}
};

extern IFxManager* g_pFxManager;

#endif