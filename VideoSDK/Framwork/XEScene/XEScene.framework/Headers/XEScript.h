/******************************************************************************

@File         XEScript.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef _XE_SCRIPT_H_
#define _XE_SCRIPT_H_
#include "XEUserNode.h"

//see @ XEScriptContainer

class XEScriptContainer;
class XEScript 
	: public XEUserNode
{
	friend class XEScriptContainer;
public:
	enum ScriptType{ES_LUA, ES_PYTHON, ES_JS };
	enum ScriptHolderType{ ESH_GLOBAL, ESH_WORLD, ESH_ACTOR, ESH_COMPONENT, ESH_USERNODE };
	XEScript();
	virtual ~XEScript();
public:
	virtual void                                  Deserialize(const XMLElement* pEleRoot,XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                           Serialize(XMLElement* pEleParent)override;
	virtual void                                  Release() override;
public:
	const xchar*                                  ReLoadCode();//reload code from file.
	const xchar*                                  GetCodeBuffer();
	void                                          SetCodeBuffer(const xchar* pCodeBuffer);
	XEScriptContainer*                            GetScriptContainer();//script may located in the script container.(AS ROOT)
	X_FORCEINLINE xbool                           IsAutoRun()const{ return m_bAutoRun; }
	X_FORCEINLINE ScriptHolderType                GetScriptHolderType() const{ return m_eScriptHolderType; }
	X_FORCEINLINE ScriptType                      GetScriptType() const{ return m_eScriptType; }
	X_FORCEINLINE const xchar*                    GetScriptAssetPath() const{ return m_strScriptAssetPath.CStr(); }
	X_FORCEINLINE void                            SetScriptType(ScriptType st) { m_eScriptType = st; }
	X_FORCEINLINE void                            SetScriptHolderType(ScriptHolderType sht) { m_eScriptHolderType = sht; }
	X_FORCEINLINE void                            SetScriptAssetPath(const xchar* pAssetPath){ if( pAssetPath ) m_strScriptAssetPath = pAssetPath; }
	X_FORCEINLINE void                            SetAutoRun(xbool bAuto){ m_bAutoRun = bAuto; }
public:
#if X_PLATFORM_WIN_DESKTOP
	xbool                                         BuildEntranceCodeFile();
	xbool                                         SaveToCodeFile();
#endif
protected:
	void                                          ReleaseCodeBuffer();
public:
	XE_USER_NODE_CAST(XEScript)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	ScriptType                                    m_eScriptType;
	ScriptHolderType                              m_eScriptHolderType;//will match along with the claim object, which may build some default codes for this script file.
	xbool                                         m_bModify;//modified?
	xbool                                         m_bAutoRun;//will run when loaded if set to true 
	XString                                       m_strScriptAssetPath;
	xchar*                                        m_szCodeBuffer;
};

#endif // _XE_SCRIPT_H_
