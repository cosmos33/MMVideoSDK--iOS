#ifndef _FXELEMENT_H_
#define _FXELEMENT_H_

#include "FxPropertyObject.h"
#include "FxGlobal.h"

class XBaseCamera;
class IXWorld;
class FxInstance;
class IFxTemplate;
class FxElementData;

class FxElement : public XMemBase
{
public:
	FxElement(const xchar*);
	virtual					~FxElement();

	// 是否可以完成，如：一个粒子系统有Loop次数大于0，则认为是可以完成的
	virtual xbool			CanComplete() = 0;
	// 获取最大粒子数
	virtual xint32			GetMaxParticles() = 0;
	// 复制一个完全相同的自身，不添加到Template中
	// 如果之后手动添加到了Template中，不需要delete，否则需要自己delete
	virtual FxElement*		Clone() = 0;

	xbool					IsParticleSystem();	
	void					SetEnabled(xbool bSet){ m_bEnabled = bSet; }
	xbool					IsEnabled() const { return m_bEnabled; }
	const XString&			GetName(){ return m_strName; }
	void					SetName(const XString& strName){ m_strName = strName; }
	FxElementType			GetType(){ return m_eType; }	
	IFxTemplate*			GetFxTemplate(){ return m_pFxTemplate; }

	// 禁止调用以下函数，改写为接口类后将不可见
	static FxElement*		CreateElement(const xchar* szName, FxElementType eType);
	virtual FxElementData*  CreateData() = 0;
	virtual xbool			Save(XFileBase* pFile, xint32 nVersion) = 0;
	virtual xbool			Load(XFileBase* pFile, xint32 nVersion) = 0;
	virtual FxElement*		Dumplicate() = 0;
	virtual void			Tick(xfloat32 fDeltaTime, FxInstance* pInstance) = 0;
	virtual void			PostTick(xfloat32 fDeltaTime, FxInstance* pInstance) = 0;
	virtual void			Render(XBaseCamera* pCamera, FxInstance* pInstance, IXWorld* pScene) = 0;
	virtual void			AddNecessaryModule() = 0;
	virtual void			OnLoadFinished() = 0;
	void					SetFxTemplate(IFxTemplate* pTemplate){ m_pFxTemplate = pTemplate; }
protected:
	FxElementType			m_eType;
	XString					m_strName;
	IFxTemplate*			m_pFxTemplate;
	xbool					m_bEnabled;
};

#endif
