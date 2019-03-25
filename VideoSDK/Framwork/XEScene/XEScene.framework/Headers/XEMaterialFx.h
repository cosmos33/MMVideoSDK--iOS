/******************************************************************************

@File         XEMaterialFx.h

@Version       1.0

@Created      2018,10, 23

@HISTORY:

******************************************************************************/
#ifndef _XE_MATERIAL_H_
#define _XE_MATERIAL_H_
#include "XEUserNode.h"

class XEMatFxDistributionParameter;
class XEMaterialFx 
	: public XEUserNode
{
public:
	XEMaterialFx();
	virtual ~XEMaterialFx();
	enum MaterialFxHolderType{ MAT_HT_COMPONENT };//to be extended here.
public:
	virtual void                                  Deserialize(const XMLElement* pEleRoot,XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                           Serialize(XMLElement* pEleParent)override;
	virtual void                                  Release() override;
	virtual Manager*                              GetNodeManager() override { return m_pNodeManager; }
	xbool                                         Save();
	xbool                                         SaveAs(const XString& strAssetPath);
	void                                          Initialize(const XString& strAssetPath);
	X_FORCEINLINE const XString&                  GetAssetPath(){ return m_strFileAssetPath; }
	X_FORCEINLINE void                            SetModified(xbool bSet){ m_bModify = bSet; }
	X_FORCEINLINE xbool                           IsModified()const{ return m_bModify; }
	X_FORCEINLINE xbool                           IsAutoRun()const{ return m_bAutoRun; }
	X_FORCEINLINE MaterialFxHolderType            GetMaterialFxHolderType() const{ return m_eMaterailHolderType; }
	X_FORCEINLINE void                            SetMaterialFxHolderType(MaterialFxHolderType mht) { m_eMaterailHolderType = mht; }
	X_FORCEINLINE void                            SetAutoRun(xbool bAuto){ m_bAutoRun = bAuto; }
	X_FORCEINLINE void                            UpdateAssetPath(const XString& strPath){ m_strFileAssetPath = strPath; }

public:
	//can attach to the specific Material node with the variable: pMaterialParentNode, if it is NULL, will be attached to the container as a child node.
	//FOR EDITOR ONLY
#if X_PLATFORM_WIN_DESKTOP
	XEMatFxDistributionParameter*                 CreateMateriaFxCurveParameterNode(XEUserNode* pMaterialParentNode = NULL);   
	void										  GetBindNode(XETreeNode::NodeList& nl);
#endif
public:
	XE_USER_NODE_CAST(XEMaterialFx)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	static const XString  SUFFIX;
protected:
	Manager*                                      m_pNodeManager;
	XString                                       m_strFileAssetPath;
	MaterialFxHolderType                          m_eMaterailHolderType;
	xbool                                         m_bModify;//modified?
	xbool                                         m_bAutoRun;//will run when loaded if set to true 
};

#endif // _XE_MATERIAL_H_
