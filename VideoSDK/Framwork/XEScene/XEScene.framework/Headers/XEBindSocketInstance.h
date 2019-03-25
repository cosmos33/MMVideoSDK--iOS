/******************************************************************************

@File         XEBindSocketInstance.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_BIND_SOCKET_INSTANCE_H
#define XE_BIND_SOCKET_INSTANCE_H

#include "XEUserNode.h"
#include "XETransform.h"

class XEActorComponent;
class XEBoneInstance;
class XEBindSocket;

class XEBindSocketInstance 
	: public XEUserNodeInstance
{
public:
	class Listener
	{
	public:
		virtual ~Listener(){}
		virtual const XString        GetTypeName() const{ return "Unknown"; }
		virtual const XString        GetName() const{ return "Unknown"; }
		virtual void                 SetName(const XString& strName){}
		virtual void                 OnSocketUpdate(const XMATRIX4& matWorld){}
		template<typename castType>
		castType*                    CastListener()
		{
			return dynamic_cast<castType*>(this);
		}
	};
	typedef XArray<Listener*>             ListenerList;
	typedef XArray<XEBindSocketInstance*> BindSocketInstanceList;
	                                       XEBindSocketInstance(XEBindSocket* pBindSocketTl);
	virtual                               ~XEBindSocketInstance();
public:
#if X_PLATFORM_WIN_DESKTOP			       
	virtual XEPropertyObjectSet            GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif								       
	virtual void                           Release() override;
	virtual void                           Apply() override;//apply parameters from node-template.
	virtual void                           UpdateSocket(const XMATRIX4& mt4Abosolute);
	XEActorComponent*                      AttachComponent();//one socket, on previewing component only.
	void                                   DetachComponent();
	XEActorComponent*                      UpdateAttachComponent(const xchar* pAssetPath, const xchar* pAssetType, const xchar* pAssetAnimPath);//runtime only.
	const xchar*                           GetAttachAssetPath();

	void                                   AddListener(Listener* pListener);
	void                                   RemoveListener(Listener* pListener);
	Listener*                              FindListener();
	XEBoneInstance*                        GetXEBoneInstance();
	XEBindSocket*                          GetXEBindSocketTemplate();
	void                                   GetWorldMatrix(XMATRIX4& mt4);
	void                                   GetWorldMatrix(XMATRIX4& mt4, const XMATRIX4& mt4Absolute);

	X_FORCEINLINE ListenerList&            GetListeners(){ return m_arrSocketListener; }

	X_FORCEINLINE XEActorComponent*        GetAttachComponent(){ return m_pAttachComponent; }
	X_EES_LINE X_FORCEINLINE const XEActorComponent*  GetAttachComponent()const{ return m_pAttachComponent; }

	X_FORCEINLINE void                     SetTicked(xbool bTicked){ m_bTicked = bTicked; }
	X_FORCEINLINE xbool                    IsTicked()const{ return m_bTicked; }

	X_FORCEINLINE void                     SetRendered(xbool bRendered){ m_bRendered = bRendered; }
	X_FORCEINLINE xbool                    IsRendered()const{ return m_bRendered; }

public:
	XE_USER_NODE_CAST(XEBindSocketInstance)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
protected:
	ListenerList      m_arrSocketListener;

	XEActorComponent* m_pAttachComponent;//component for previewing...
	xbool             m_bTicked;//been ticked? on mounter that make sense.
	xbool             m_bRendered;//been rendered? on mounter that make sense.
};

#endif // XE_BIND_SOCKET_INSTANCE_H
