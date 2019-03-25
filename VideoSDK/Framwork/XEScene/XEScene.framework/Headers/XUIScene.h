#ifndef _XUISCENE_H_
#define _XUISCENE_H_

#include "XUIWidget.h"
#include "XUIAssist.h"

class XUIScene : public XUIWidget
{	
public:
	X_CLASS_DEF(XUIScene)
	void						Activate();
	void						DeActivate();
	virtual const XMATRIX4&		GetLocalToParentTransform() override;
	void						Render(IXWorld* pWorld);
	virtual XUIScene*			GetScene() override;

	// 控制显示
	xbool						IsModal()const{ return m_bModal; }
	virtual void				Show(xbool bModal = xfalse);
	virtual void				Hide();
	virtual xbool				IsShow()const{ return m_bVisible; }

	// 设计分辨率
	void						SetDesignResolution(const XVECTOR2& vDesignRes, XUIResolutionPolicy rp);
	const XVECTOR2&				GetDesignResolution()const;
	XUIResolutionPolicy			GetResolutionPolicy()const{ return m_eResolutionPolicy; }
	void						UpdateDesignResolutionSize();

	// 是否受到Manager的SetRect影响
	void						AdaptNotch(xbool bSet);
	xbool						IsAdaptNotch()const;

	const XMATRIX4&				GetWorldToScreenMatrix()const{ return m_matWorldToScreen; }
	const XMATRIX4&				GetScaleMatrix()const{ return m_matScale; }
	const XVECTOR2&				GetScale()const{ return m_vScale; }
	virtual xbool				SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	static XUIScene*			Create();
	virtual xbool				Init() override;
	XUIScene();
	virtual	~XUIScene();	
protected:
	XVECTOR2					m_vDesignResolution;
	XUIResolutionPolicy			m_eResolutionPolicy;
	XMATRIX4					m_matWorldToScreen;
	XMATRIX4					m_matScale;			// Design Space to Screen Space
	xbool						m_bShow;
	xbool						m_bModal;
	XVECTOR2					m_vScale;
	xbool						m_bAdaptNotch;
	friend class XUIManager;
};

#endif
