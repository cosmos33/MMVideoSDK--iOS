#ifndef _FXPROPERTYOBJECT_H_
#define _FXPROPERTYOBJECT_H_

#include "XMemBase.h"
#include "FxProperty.h"
#include "XArray.h"
#include "XString.h"
#include "XName.h"

class XFileBase;
class FxPropertyObject : public XMemBase
{
public:
	virtual ~FxPropertyObject();
	virtual void			AddProperty(FxProperty* pProperty, const xchar* szCategory);
	virtual FxProperty*		GetProperty(const xchar* szPropertyName);

	virtual xint32			GetCategoryNum();
	virtual const xchar*	GetCategoryName(xint32 nCategory);
	virtual XArray<FxProperty*>* GetProperties(xint32 nCategory);
	virtual xbool			CopyValueFrom(const FxPropertyObject* pPropertyObject);

	virtual xbool			Save(XFileBase* pFile, xint32 nVersion);
	virtual xbool			Load(XFileBase* pFile, xint32 nVersion);

protected:
	FxProperty*				GetProperty(xint32 nIndex) const;
	xint32					GetPropertyNum() const;

protected:
	XArray<FxProperty*>						m_aProperty;
	XHashTable<XName, FxProperty*>				m_tbProperty;
	XArray<XName>							m_aCategory;
	XHashTable<XName, XArray<FxProperty*>>	m_tbCategory;
};

#endif
