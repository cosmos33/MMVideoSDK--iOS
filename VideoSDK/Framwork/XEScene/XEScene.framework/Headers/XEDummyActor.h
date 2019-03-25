/******************************************************************************

@File         XEDummyActor.h

@Version       1.0

@Created      2017, 6, 6

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_DUMMYACTOR_H_
#define _XE_DUMMYACTOR_H_

#include "XEActor.h"
#include "XTypes.h"


typedef void(*SHAMERENDER)(XEViewport *pViewport, void *pParam);

class XEDummyActor : public XEActor
{
public:
	class XEAttachRender
	{
	public:
						XEAttachRender() : m_bActived(xtrue) {}
		virtual			~XEAttachRender(){}
		virtual void	Render(XEViewport *pViewport){}
		virtual void	Tick(xfloat32 fDel){}
		inline void		SetActived(xbool bActived) { m_bActived = bActived; }
		inline xbool	IsActived() { return m_bActived; }
	protected:
		xbool m_bActived;
	};
	typedef XArray<XEAttachRender*> AttachRenderList;

public:
	XE_ACTOR_CAST(XEDummyActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEDummyActor)
							XEDummyActor();
	virtual					~XEDummyActor();
	virtual void			Serialize(XFileBase *pFile) override {}
	virtual void			Tick(xfloat32 fDel, xbool bForceTick = xtrue) override;
	virtual void			Render(XEViewport* pViewport) override;	
	inline  void			SetRenderFunc(SHAMERENDER pFunc) { m_pRenderFunc = pFunc; }
	inline  void			SetParam(void *pParam) { m_pParam = pParam; }
	virtual void            Initialize(XEWorld* pWorld) override;
	virtual void            Release() override;
	virtual xbool           RayPick(XEHitResult& hr) override;

	void					Attach(XEAttachRender *pRender);
	void					Dettach(XEAttachRender *pRender);
	void					DettachAll();

	static const XString	ACTOR_TYPENAME;
	
protected:

	SHAMERENDER				m_pRenderFunc;
	void*					m_pParam;
	AttachRenderList		m_vAttachList;
};

#endif

