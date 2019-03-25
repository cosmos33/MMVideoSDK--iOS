/******************************************************************************

@File         XXMLExtendTool.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/
#ifndef __X_XML_EXTENDTOOL__
#define __X_XML_EXTENDTOOL__

#include "XBase3DTypes.h"
#include "tinyxml2_XEngine.h"
#include "XSys.h"

class XXMLExtendTool
{
public:
	 XXMLExtendTool(tinyxml2_XEngine::XMLDocument* pXmlDoc, tinyxml2_XEngine::XMLElement* pRoot, xbool bLoad);
	virtual						~XXMLExtendTool(){};
	
	inline xbool				IsLoading() { return m_bLoad; }

	/*
	* 从 value 中读写基本类型
	* @param key : 子项名称 
	* @returns 
	*/
	void						WriteString(const xchar* key, const xchar* str);
	XString						ReadString(const xchar* key, const xchar* szdefault = "");

	xint32						ReadInt32(const xchar* key, xint32 ndefault = 0);
	void						WriteInt32(const xchar* key, xint32 i);

	xuint32						ReadUInt32(const xchar* key, xuint32 undefault = 0);
	void						WriteUInt32(const xchar* key, xuint32 u);

	xbool						ReadBool(const xchar* key, xbool bdefault = xfalse);
	void						WriteBool(const xchar* key, xbool b);

	xfloat32					ReadFloat32(const xchar* key, xfloat32 fdefault = 0);
	void						WriteFloat32(const xchar* key, xfloat32 f);

	XVECTOR3					ReadVector3(const xchar* key, const XVECTOR3& v3default = XVECTOR3(0.0f));
	void						WriteVector3(const xchar* key, const XVECTOR3& vec3);

	XVECTOR2					ReadVector2(const xchar* key, const XVECTOR2& vv3default = XVECTOR2(0.0f));
	void						WriteVector2(const xchar* key, const XVECTOR2& vec2);

	XVECTOR4					ReadVector4(const xchar* key, const XVECTOR4& v4default = XVECTOR4(0.0f));
	void						WriteVector4(const xchar* key, const XVECTOR4& vec4);

	XCOLORBASE					ReadClrValue(const xchar* key, const XCOLORBASE& cldefault = XCOLORBASE(1.0f));
	void						WriteClrValue(const xchar* key, const XCOLORBASE& clr);

	XQUATERNION					ReadQuaternion(const xchar* key, const XQUATERNION& qdefault = XQUATERNION(1.0f, 0, 0, 0));
	void						WriteQuaternion(const xchar* key, const XQUATERNION& qu);

	XMATRIX4					ReadMatrix4(const xchar* key, const XMATRIX4& mdefault = XMATRIX4());
	void						WriteMatrix4(const xchar* key, const XMATRIX4& mat4);	
		
	/*
	* 从 Attribute 中读写基本类型
	* @param key : 子项名称
	* @returns
	*/
	XString						ReadStringAttribute(const xchar* key, const xchar* szdefault = "");
	void						WriteStringAttribute(const xchar* key, const xchar* str);

	xint32						ReadInt32Attribute(const xchar* key, xint32 ndefault = 0);
	void						WriteInt32Attribute(const xchar* key, xint32 i);

	xuint32						ReadUInt32Attribute(const xchar* key, xuint32 undefault = 0);
	void						WriteUInt32Attribute(const xchar* key, xuint32 u);

	xbool						ReadBoolAttribute(const xchar* key, xbool bdefault = xfalse);
	void						WriteBoolAttribute(const xchar* key, xfloat32 b);

	xfloat32					ReadFloat32Attribute(const xchar* key, xfloat32 fdefault = 0);
	void						WriteFloat32Attribute(const xchar* key, xfloat32 f);

	void						WriteChildStringText(const xchar* key, const xchar* str);
	XString						ReadChildStringText(const xchar* key, const xchar* szdefault = "");


	/*
	* 从当前项的 value中 读写常用类型
	* 
	* @returns
	*/
	XString						ReadStringText();
	void						WriteStringText(const xchar* str);

	xint32						ReadInt32Text(xint32 ndefault = 0);
	void						WriteInt32Text(xint32 i);

	xuint32						ReadUInt32Text(xuint32 undefault = 0);
	void						WriteUInt32Text(xuint32 u);

	xbool						ReadBoolText(xbool bdefault = xfalse);
	void						WriteBoolText(xbool b);

	xfloat32					ReadFloat32Text(xfloat32 fdefault = 0);
	void						WriteFloat32Text(xfloat32 f);


	tinyxml2_XEngine::XMLElement*		NewElement(const xchar* name);
	tinyxml2_XEngine::XMLElement*		NewElementAsChild(const xchar* name);
	tinyxml2_XEngine::XMLElement*		GetChildElement(const xchar* name, xbool bFirst = xfalse);
	inline tinyxml2_XEngine::XMLElement*	GetXMLElementParent(){ return m_pParent;}
	inline tinyxml2_XEngine::XMLDocument*	GetXMLDocument() { return m_pXmlDoc; }

	void								SetXMLElementParent(tinyxml2_XEngine::XMLElement* pParent){m_pParent= pParent;}

    tinyxml2_XEngine::XMLElement*		BackToParentElement();
	const xchar *						ConvertErrorCodeToString(tinyxml2_XEngine::XMLError error);
protected:
	xbool								m_bLoad;
	tinyxml2_XEngine::XMLDocument*		m_pXmlDoc;
	tinyxml2_XEngine::XMLElement*		m_pParent;
};

#endif

