/******************************************************************************

@File         XEBindSocket.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_BIND_SOCKET_H
#define XE_BIND_SOCKET_H
#include "XEUserNode.h"
#include "XETransform.h"

class XEBone;
class XEBindSocket 
	: public XEUserNode
{
	friend class XEBindSocketInstance;
public:
	typedef XArray<XEBindSocket*>          BindSocketList;
	                                       XEBindSocket();
	virtual                               ~XEBindSocket();
public:
	virtual void                           Deserialize(const XMLElement* pEleNode, XETreeNode::Manager* pNodeMgr = NULL) override;
	virtual XMLElement*                    Serialize(XMLElement* pEleParent) override;								       
	virtual void                           Release() override;
	XEBone*                                GetXEBone();

	X_FORCEINLINE const XString&           GetPreviewingAssetPath() const{ return m_strPreviewingAssetPath; }
	X_FORCEINLINE const XString&           GetPreviewingAssetType() const{ return m_strPreviewingAssetType; }
	X_FORCEINLINE const XString&           GetPreviewingSeqAssetPath()const{ return m_strPreviewingSeqAssetPath; }
	X_FORCEINLINE const xbool&             GetPreviewingSeqAuto()const{ return m_bSeqAuto; }
	X_FORCEINLINE const xbool&             GetPreviewingSeqLoop()const{ return m_bSeqLoop; }
	X_FORCEINLINE const xbool&             GetPreviewingSeqInTurnsPlay()const{ return m_bSeqInTurnsPlay; }
	X_FORCEINLINE const xfloat32&          GetPreviewingSeqPlayRate()const{ return m_fSeqPlayRate; }

	X_FORCEINLINE void                     SetPreviewingAssetPath(const XString& strPath){ m_strPreviewingAssetPath = strPath; }
	X_FORCEINLINE void                     SetPreviewingAssetType(const XString& strType){ m_strPreviewingAssetType = strType; }
	X_FORCEINLINE void                     SetPreviewingSeqAssetPath(const XString& strPath){ m_strPreviewingSeqAssetPath = strPath; }
	X_FORCEINLINE void                     SetPreviewingSeqAuto(const xbool& bAuto){ m_bSeqAuto = bAuto; }
	X_FORCEINLINE void                     SetPreviewingSeqLoop(const xbool& bLoop){ m_bSeqLoop = bLoop; }
	X_FORCEINLINE void                     SetPreviewingSeqInTurnsPlay(const xbool& bInTurnsPlay){ m_bSeqInTurnsPlay = bInTurnsPlay; }
	X_FORCEINLINE void                     SetPreviewingSeqPlayRate(const xfloat32& fPlayRate){m_fSeqPlayRate = fPlayRate; }

	X_FORCEINLINE XETransform&             GetRelativeTransform(){ return m_relativeTransform; }
	X_FORCEINLINE void                     SetEnablePreviewing(xbool bEnable){ m_bEnablePreview = bEnable; }
	X_FORCEINLINE xbool                    IsEnablePreviewing(){ return m_bEnablePreview; }
	X_FORCEINLINE xbool                    IsOccupied(){ return m_bSocketOccupied; }
	X_FORCEINLINE void                     SetOccupied(xbool bOccupied){ m_bSocketOccupied = bOccupied; }

public:
	XE_USER_NODE_CAST(XEBindSocket)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	XETransform                            m_relativeTransform;//relative transform of this socket.
	xbool                                  m_bEnablePreview;//for property setting
	xbool                                  m_bSocketOccupied;//has been occupied?

	XString                                m_strPreviewingAssetPath;//asset of the components for the socket that binded.
	XString                                m_strPreviewingAssetType;//type of the asset.
	//animations.
	XString                                m_strPreviewingSeqAssetPath;//seq for animatable model.
	xbool                                  m_bSeqAuto;
	xbool                                  m_bSeqLoop;
	xfloat32                               m_fSeqPlayRate;
	xbool                                  m_bSeqInTurnsPlay;

};

#endif // XE_BIND_SOCKET_H
