#ifndef _XE_BIND_USER_NODE_DATA_H_
#define _XE_BIND_USER_NODE_DATA_H_
#include "XMemBase.h"
#include "XArray.h"
#include "XMath3D.h"
#include "tinyxml2_XEngine.h"

class XEBindUserNodeData : public XMemBase
{
public:
	XEBindUserNodeData();
	~XEBindUserNodeData(){}
	void                            Empty();
	void			                SetBindUserNodeName(const XString& strBindUserNodeName){ m_strBindUserNodeName = strBindUserNodeName; }
	XString			                GetBindUserNodeName(){ return m_strBindUserNodeName; }
	void					        SetBindUserNodeType(const XString& strBindUserNodeType){ m_strBindUserNodeType = strBindUserNodeType; }
	XString					        GetBindUserNodeType(){ return m_strBindUserNodeType; }
	xbool					        GetIsBindParentUserNode(){ return m_bIsBindUserNode; }
	void					        SetIsBindParentUserNode(xbool bIsBindParentUserNode){ m_bIsBindUserNode = bIsBindParentUserNode; }
	void					        SetTransform(XMATRIX4 matTransform){ m_matTransform = matTransform; }
	XMATRIX4						GetTransform(){ return m_matTransform; }
	tinyxml2_XEngine::XMLElement*	Serialize(tinyxml2_XEngine::XMLElement* pEleParent);
	void							Deserialize(const tinyxml2_XEngine::XMLElement* pEleParent);
	void					        SetBindBoneIndex(const xint32& nBoneIndex){ m_nBindBoneIndex = nBoneIndex; }
	xint32					        GetBindBoneIndex(){ return m_nBindBoneIndex; }
protected:
private:

	XString			                m_strBindUserNodeName;
	XString			                m_strBindUserNodeType;	
	xbool				            m_bIsBindUserNode;//whether bind parent's usernode
	XMATRIX4				        m_matTransform;
	xint32			                m_nBindBoneIndex;//½öÓÃÓÚbone
};

#endif//_XE_BIND_USER_NODE_DATA_H_