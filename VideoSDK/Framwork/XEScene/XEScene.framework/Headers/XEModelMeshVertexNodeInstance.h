#ifndef XE_MODEL_MESH_VERTEX_NODE_INCLUDE_H
#define XE_MODEL_MESH_VERTEX_NODE_INCLUDE_H
#include "XEUserNode.h"

struct XBaseVertexInfo
{
	xint32		nSkinIndex;
	xint32		nRawMeshIndex;
	xint32		nVertexIndex;
	XVECTOR3	vPosition;
	XVECTOR3	vNormal;
	XVECTOR3	vTangent;
	XVECTOR3	vBinormal;
	//XVECTOR3    vScreenPos; //2D-for screen, not use it now.
	xbool		bPick; //is pick or not.

	XBaseVertexInfo()
		: nSkinIndex(-1)
		, nRawMeshIndex(-1)
		, nVertexIndex(-1)
		, vPosition(0.0f, 0.0f, 0.0f)
		, vNormal(0.0f, 0.0f, 0.0f)
		, vTangent(0.0f, 0.0f, 0.0f)
		, vBinormal(0.0f, 0.0f, 0.0f)
		//, vScreenPos(0.0f, 0.0f, 0.0f)
		, bPick(xfalse)
	{}
};

class XEModelMeshVertexNodeInstance
	:public XEUserNodeInstance
{
public:
	XEModelMeshVertexNodeInstance();
	virtual ~XEModelMeshVertexNodeInstance();

	virtual void						Release() override;

public:
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet			GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif

	void								SetVertexInfo(const XArray<XBaseVertexInfo>& aInfo){ m_aModelMeshVertexInfo = aInfo; }
	xbool								GetCurVertexInfo(XBaseVertexInfo& info);
	const XArray<XBaseVertexInfo>&		GetVertexArrayInfo();
	xint32								GetVertexArrayInfoCount();

	xint32								GetSamePosCurPickIndex(){ return m_nSamePosCurPickIndex; }
	void								SetSamePosCurPickIndex(xint32 nIndex){ m_nSamePosCurPickIndex = nIndex; }

	xbool								IsVertexPick();
	void								SetVertexPick(xbool bPick){ m_bVertexPick = bPick; }

	xbool								IsEnablePickSize(){ return m_bPickSizeEnable; }
	void								SetEnablePickSize(xbool bEnable){ m_bPickSizeEnable = bEnable; }

	xfloat32							GetVertexPickBoxSize(){ return m_fPickBoxSize; }
	void								SetVertexPickBoxSize(xfloat32 fSize){ m_fPickBoxSize = fSize; }

	xbool								IsEnableLineLength(){ return m_bLineLengthEnable; }
	void								SetEnableLineLength(xbool bEnable){ m_bLineLengthEnable = bEnable; }

	xfloat32							GetLineLength(){ return m_fLineLength; }
	void								SetLineLength(xfloat32 fLength){ m_fLineLength = fLength; }
public:
	XE_USER_NODE_CAST(XEModelMeshVertexNodeInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
private:
	XArray<XBaseVertexInfo>				m_aModelMeshVertexInfo;
	xbool								m_bVertexPick;
	xint32								m_nSamePosCurPickIndex; //combox当前索引，不是vertex的实际索引.
	xbool								m_bPickSizeEnable; //manul set pick box size or not.
	xfloat32							m_fPickBoxSize;
	xbool								m_bLineLengthEnable; //manul set line length or not.
	xfloat32							m_fLineLength;
};

#endif //XE_MODEL_MESH_VERTEX_NODE_INCLUDE_H