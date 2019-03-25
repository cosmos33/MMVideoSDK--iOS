#ifndef _XUIIMAGE_ARRAY_H_
#define _XUIIMAGE_ARRAY_H_

#include "XUIWidget.h"

class IXTexture2D;
class XUISpriteArray;
class XUIImageArray : public XUIWidget
{
public:
	struct XUIImageElement
	{
		XVECTOR2	m_vPosition;
		XVECTOR2	m_vSize;
		xfloat32	m_fRotation;
		xfloat32	m_fTime;
		XCOLORBASE	m_Color;
		void*		m_pUserData;
	};
	typedef std::function<void(XUINode*, void*)> XUIImageKilledEventCallback;

	// normal interface
	static XUIImageArray*		Create();
	static XUIImageArray*		Create(const XString& strTextureName, TextureResType texType = TextureResType::XUI_LOCAL);
	XUIImageArray();
	virtual ~XUIImageArray();	
	xbool						LoadTexture(const XString& strTexture, TextureResType texType = TextureResType::XUI_LOCAL);
	XString						GetTexturePath()const{ return m_strTexture; }
	virtual void				Update(xfloat32 fDelta)override;
	virtual void				Draw(IXWorld* pWorld, xuint32 unParentFlags)override;
	// unique interface
	void						SetNum(xint32 nNum);
	xint32						GetNum()const;
	xint32						GetActiveNum()const{ return m_nActiveNum; }
	void						SetLife(xfloat32 fLife); // < 0 means arrays last forever
	xfloat32					GetLife()const{ return m_fLife; }
	void						SetFadeRatio(xfloat32 fRatio);
	xfloat32					GetFadeRatio()const{ return m_fFadeRatio; }

	// vPos means world space, not parent space, maybe fix later, maybe not
	void						AddImage(const XVECTOR2& vPos, const XVECTOR2& vSize, xfloat32 fRotation, void* pUserData = NULL);
	void						RemoveImage(void* pUserData);
	void						UpdateImage(void* pData, const XVECTOR2& vPos, const XVECTOR2& vSize, xfloat32 fRotation, const XCOLORBASE& color = XCOLORBASE(1.0f));
	void						UpdateImage(void* pData, const XVECTOR2& vPos, xfloat32 fRotation, const XCOLORBASE& color = XCOLORBASE(1.0f));
	XUIImageElement*			GetImage(void* pData);
	void						SetImageKilledEventListener(const XUIImageKilledEventCallback& callback);

	// sequence
	// sequence
	void						SetUseSequence(xbool bUse){ m_bUseSequence = bUse; }
	xbool						IsUseSequence()const{ return m_bUseSequence; }
	void						SetUVTile(XVECTOR2 vTile){ m_vUVTile = vTile; }
	void						SetUVTile(xfloat32 fUTile, xfloat32 fVTile){ SetUVTile(XVECTOR2(fUTile, fVTile)); }
	const XVECTOR2&				GetUVTile()const{ return m_vUVTile; }
	void						SetSequenceFPS(xfloat32 fFPS){ m_fFPS = fFPS; }
	xfloat32					GetSequenceFPS()const{ return m_fFPS; }
	void						SetActualFrameNum(xint32 nNum){ m_nActualFrameNum = nNum; }
	xint32						GetActualFrameNum()const{ return m_nActualFrameNum; }

protected:
	virtual xbool				Init() override;
	virtual xbool				Init(const XString& strTextureName, TextureResType texType = TextureResType::XUI_LOCAL);
	virtual XUINode*			CreateClonedInstance() override;
	virtual void				CopyProperties(XUINode* pNode) override;
protected:
	XUISpriteArray*				m_pImageSprite;
	XArray<XUIImageElement>		m_aImages;
	XHashTable<void*, XUIImageElement*> m_tbImages;
	XArray<xint32>				m_aIndex;
	xint32						m_nActiveNum;
	XString						m_strTexture;
	IXTexture2D*				m_pTexture;
	xfloat32					m_fLife;
	xfloat32					m_fFadeRatio;
	XUIImageKilledEventCallback	m_KilledCallback;
	xbool						m_bUseFade;

	// sequence
	xbool						m_bUseSequence;
	XVECTOR2					m_vUVTile;
	xfloat32					m_fFPS;
	xint32						m_nActualFrameNum;
};

#endif
