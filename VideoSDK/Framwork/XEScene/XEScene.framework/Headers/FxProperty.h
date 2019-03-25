#ifndef _FXPROPERTY_H_
#define _FXPROPERTY_H_

#include "XString.h"
#include "XMath3D.h"
#include "XBase3DTypes.h"
#include "XDistribution.h"
#include "XHashTable.h"

typedef void(*FxPropertyCallBack)(void*);

struct FxEnumTable
{
	xint32						m_nValue;
	XHashTable<xint32, XString>	m_Table;
};
class XFileBase;
class FxProperty : public XMemBase
{
public:
	enum Type
	{
		FPT_INVALID,
		FPT_BOOL,
		FPT_INT32,
		FPT_FLOAT,
		FPT_VECTOR2,
		FPT_VECTOR3,
		FPT_VECTOR4,
		FPT_COLORVALUE,
		FPT_PATH,
		FPT_STRING,
		FPT_ENUMTABLE,
		FPT_DISTRIBUTIONFLOAT,
		FPT_DISTRIBUTIONVECTOR,
		FPT_DISTRIBUTIONCOLOR,	// 与VECTOR实现相同，只是在界面显示上有区分
	};
	FxProperty(const xchar* szName, Type eType, void* pData);
	~FxProperty();

	xbool Save(XFileBase* pFile);
	xbool Load(XFileBase* pFile);

	Type GetType() const { return m_eType; }
	const xchar* GetName() const { return m_strName.CStr(); }

	void SetValue(bool b);
	void SetValue(xint32 n);
	void SetValue(xfloat32 f);
	void SetValue(const XVECTOR2& vec2);
	void SetValue(const XVECTOR3& vec3);
	void SetValue(const XVECTOR4& vec4);
	void SetValue(const XCOLORBASE& color);
	void SetValue(const XString& str);

	void SetCallBack(FxPropertyCallBack callback, void* pClass);
	xbool CopyValueFrom(const FxProperty& property);
	
	void SetVersion(xint32 nVersion){ m_nVersion = nVersion; }
	xint32 GetVersion()const{ return m_nVersion; }

	operator bool()	const					{ return *(bool*)m_pData; }
	operator xint32() const					{ return *(xint32*)m_pData; }
	operator xfloat32()	const				{ return *(xfloat32*)m_pData; }
	operator XVECTOR2()	const				{ return *(XVECTOR2*)m_pData; }
	operator XVECTOR3()	const				{ return *(XVECTOR3*)m_pData; }
	operator XVECTOR4()	const				{ return *(XVECTOR4*)m_pData; }
	operator XCOLORBASE()const				{ return *(XCOLORBASE*)m_pData; }
	operator XString()	const				{ return *(XString*)m_pData; }
	operator FxEnumTable*()	const			{ return (FxEnumTable*)m_pData; }
	operator XRawDistributionFloat*() const	{ return (XRawDistributionFloat*)m_pData; }
	operator XRawDistributionVector*() const{ return (XRawDistributionVector*)m_pData; }

private:
	void				CallBack();
	Type				m_eType;
	XString				m_strName;
	void*				m_pData;
	FxPropertyCallBack	m_pCallBack;
	void*				m_pCallBackClass;
	xint32				m_nVersion;

	XString				m_pOrignalPath;	// 暂时只有Path属性使用 @fixme 不好的设计
};

#endif