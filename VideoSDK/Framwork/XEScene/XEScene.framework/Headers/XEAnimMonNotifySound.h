/******************************************************************************

@File         XEAnimMonNotify.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_MON_NOTIFY_SOUND_H
#define XE_ANIM_MON_NOTIFY_SOUND_H
#include "XEAnimMonNotify.h"
#include "XETransform.h"

class XEBindSocket;
class XEAnimMonNotifySound
	:public XEAnimMonNotify
{
	friend class  XEAnimMonNotifySoundIns;
public:
	XEAnimMonNotifySound();
	virtual ~XEAnimMonNotifySound();

	virtual void                             Release() override;
	virtual xbool                            IsTheLast(xint32 nUpperboundTime) override;
	virtual void                             Deserialize(const XMLElement* pEleNotify, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                      Serialize(XMLElement* pEleParent)override;
	virtual xbool                            Verify(AnimMonBaseList* pUnsuggestedList = NULL) override;

public:
	X_FORCEINLINE xbool                      IsSpawnMode(){ return m_bSpawnMode; }
	X_FORCEINLINE xbool                      IsDestroyImmediately(){ return m_bDestroyImmediately; }
	X_FORCEINLINE XETransform&               GetRelativeTransform(){ return m_relativeTransform; }
	X_FORCEINLINE XString&                   GetSoundAssetPath(){ return m_strSoundTemplateAssetPath; }
	X_FORCEINLINE void                       SetSoundAssetPath(const XString& szPath){ m_strSoundTemplateAssetPath = szPath; }
	X_FORCEINLINE void                       SetDestroyImmediately(xbool bSet){ m_bDestroyImmediately = bSet; }
	X_FORCEINLINE void                       SetSpawnMode(xbool bSpawnMode = xtrue){ m_bSpawnMode = bSpawnMode; }

	xbool                                    BindXESocket(const XString& socketName);
	XEBindSocket*                            GetBindSocket();
	X_EES_LINE const XEBindSocket*           GetBindSocket() const;
	const XString&                           GetBindSocketName()const;

	void                                     UnbindXESocket();

public:
	XE_USER_NODE_CAST(XEAnimMonNotifySound)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;

protected:
	xbool                                    m_bSpawnMode;
	XETransform                              m_relativeTransform;
	xbool                                    m_bDestroyImmediately;
	XString                                  m_strSoundTemplateAssetPath;
	XString                                  m_strBindSocketName;
};

#endif // XE_ANIM_MON_NOTIFY_SOUND_H
