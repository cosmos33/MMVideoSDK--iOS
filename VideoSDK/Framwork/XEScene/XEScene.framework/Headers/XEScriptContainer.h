/******************************************************************************

@File         XEScriptContainer.h

@Version       1.0

@Created      2018,9, 6

@HISTORY:

******************************************************************************/
#ifndef _XE_SCRIPT_CONTAINER_H_
#define _XE_SCRIPT_CONTAINER_H_
#include "XEUserNode.h"
#include "XEScript.h"

//generate a file with the extend format of ".xscript"
//script link files can be "lua", "js", "python", etc.
//currently, only "lua" files supported.

class XEScript;
class XEWorld;
class XEScriptContainerInstance;
class XEScriptContainer 
	: public XEUserNode
{
public:
	XEScriptContainer();
	virtual ~XEScriptContainer();
public:
	virtual void                                  Deserialize(const XMLElement* pEleRoot,XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                           Serialize(XMLElement* pEleParent)override;
	virtual void                                  Release() override;
	virtual Manager*                              GetNodeManager() override { return m_pNodeManager; }
	xbool                                         Save();
	xbool                                         SaveAs(const XString& strAssetPath);
	void                                          Initialize(const XString& strAssetPath);
	X_FORCEINLINE const XString&                  GetAssetPath(){ return m_strFileAssetPath; }
	X_FORCEINLINE void			                  UpdateScriptAssetPath(const xchar* szScriptPath){ m_strFileAssetPath = szScriptPath; }
	X_FORCEINLINE void                            SetModified(xbool bSet){ m_bModify = bSet; }
	X_FORCEINLINE xbool                           IsModified()const{ return m_bModify; }
	//pass callback to the children(base attribute)
	X_FORCEINLINE XEScript::ScriptHolderType      GetScriptHolderType() const{ return m_eScriptHolderType; }
	X_FORCEINLINE XEScript::ScriptType            GetScriptType() const{ return m_eScriptType; }
	X_FORCEINLINE void                            SetScriptType(XEScript::ScriptType st) { m_eScriptType = st; }
	X_FORCEINLINE void                            SetScriptHolderType(XEScript::ScriptHolderType sht) { m_eScriptHolderType = sht; }
public:
	//if bAsNewScriptFile is set to xtrue, will generate the new script file place in the pScriptAssetPath, 
	//meanwhile, will build the default code from a code-template file according to the claiming nScriptHolderType as well.
	//can attach to the specific script node with the variable: pScriptParentNode, if it is NULL, will be attached to the container as a child node.
	//FOR EDITOR ONLY
#if X_PLATFORM_WIN_DESKTOP
	XEScript*                                     CreateScript(const xchar* pScriptAssetPath, xint32 nScriptType, xint32 nScriptHolderType, xbool bAsNewScriptFile = xfalse, XEUserNode* pScriptParentNode = NULL);
#endif
	void										  GetBindNode(XETreeNode::NodeList& nl);

public:
	XE_USER_NODE_CAST(XEScriptContainer)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	static const XString  SUFFIX;

protected:
	Manager*                                      m_pNodeManager;
	XString                                       m_strFileAssetPath;//script asset path
	xbool                                         m_bModify;
	XEScript::ScriptType                          m_eScriptType;
	XEScript::ScriptHolderType                    m_eScriptHolderType;//will match along with the claim object, which may build some default codes for this script file.

};

#endif // _XE_SCRIPT_CONTAINER_H_
