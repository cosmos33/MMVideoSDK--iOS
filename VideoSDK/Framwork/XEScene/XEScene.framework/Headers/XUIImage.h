#ifndef _XUIIMAGE_H_
#define _XUIIMAGE_H_

#include "XUIWidget.h"
#include "XHashTable.h"

const xint32 EMPTY_TAG = 0xFFFFFFFF;

class XUISprite;
class IXTexture2D;

class XUITexture
{
public:
	XUITexture(){}
	~XUITexture();
	IXTexture2D*				m_pTexture;
	XUIWidget::TextureResType	m_eTexType;
	XString						m_strPath;
	xbool						m_bRelative;	
};

class XUIImage : public XUIWidget
{
public:	
	X_CLASS_DEF(XUIImage)
	static XUIImage*		Create();
	static XUIImage*		Create(xint32 nTag, const XString& strTextureName, TextureResType texType = TextureResType::XUI_LOCAL);
	XUIImage();
	virtual ~XUIImage();
	void					SetUseTexture(xbool bUse);
	xbool					IsUseTexture()const{ return m_bUseTexture; }
	xbool					LoadTexture(xint32 nTag, const XString& strTextureName, TextureResType texType = TextureResType::XUI_LOCAL);
	void					ShowTexture(xint32 nTag);
	void					RemoveTexture(xint32 nTag);
	xint32					GetTextureNum()const{ return m_tbTexture.Num(); }
	xint32					GetCurrentTag()const{ return m_nCurrentTag; }
	XString					GetTexturePath(xint32 nTag);
	xbool					IsTextureExisted(xint32 nTag);
	virtual void			Update(xfloat32 fDelta)override;
	virtual void			Draw(IXWorld* pWorld, xuint32 unParentFlags)override;
	virtual void			SetContentSize(const XVECTOR2& vContentSize)override;
	xbool					IsFollowTextureSize()const{ return m_bFollowTextureSize; }
	void					SetFollowTextureSize(xbool bFollow){ m_bFollowTextureSize = bFollow; }
	void					SetRectPercent(const XVECTOR2& vLTPercent, const XVECTOR2& vBRPercent);
	void					SetFlipX(xbool bFlip);
	xbool					IsFlipX()const;

	XVECTOR2				GetTextureOriginalSize(xint32 nTag);
	
	// sequence
	void					SetUseSequence(xbool bUse){ m_bUseSequence = bUse; }
	xbool					IsUseSequence()const{ return m_bUseSequence; }
	xbool					IsSequencePlaying()const{ return m_bPlaySequence; }
	void					PlaySequence(xbool bPlay);
	void					ResetSequence();
	void					SetUVTile(XVECTOR2 vTile){ m_vUVTile = vTile; }
	void					SetUVTile(xfloat32 fUTile, xfloat32 fVTile){ SetUVTile(XVECTOR2(fUTile, fVTile)); }
	const XVECTOR2&			GetUVTile()const{ return m_vUVTile; }
	void					SetSequenceFPS(xfloat32 fFPS){ m_fFPS = fFPS; }
	xfloat32				GetSequenceFPS()const{ return m_fFPS; }
	void					SetActualFrameNum(xint32 nNum){ m_nActualFrameNum = nNum; }
	xint32					GetActualFrameNum()const{ return m_nActualFrameNum; }
	void					SetCurrentFrame(xint32 nFrame){ m_nCurrentFrame = nFrame; }
	xint32					GetCurrentFrame()const{ return m_nCurrentFrame; }


	// Slice
	virtual void			Enable9Slice(xbool bSet);
	virtual xbool			Is9SliceEnabled()const;
	virtual void			SetSliceLeft(xfloat32 fLeft);
	virtual xfloat32		GetSliceLeft()const;
	virtual void			SetSliceRight(xfloat32 fRight);
	virtual xfloat32		GetSliceRight()const;
	virtual void			SetSliceTop(xfloat32 fTop);
	virtual xfloat32		GetSliceTop()const;
	virtual void			SetSliceBottom(xfloat32 fBottom);
	virtual xfloat32		GetSliceBottom()const;
	// serilize
	virtual xbool			SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	virtual xbool			Init() override;
	virtual xbool			Init(xint32 nTag, const XString& strTextureName, TextureResType texType = TextureResType::XUI_LOCAL);
	virtual void			UpdateColor();
	virtual XUINode*		CreateClonedInstance() override;
	virtual void			CopyProperties(XUINode* pNode)override;
	void					ShowCurrentTexture();
	void					LoadTexture(xint32 nTag, IXTexture2D* pTexture, const XString& strPath, TextureResType texType = TextureResType::XUI_LOCAL);
	void					UpdateVertexPos();
	void					UpdateVertexUV();
protected:
	xbool					m_bUseTexture;
	XUISprite*				m_pImageSprite;
	XHashTable<xint32, XUITexture*>	m_tbTexture;
	xint32					m_nCurrentTag;
	xbool					m_bFollowTextureSize;

	xbool					m_bUseSequence;
	XVECTOR2				m_vUVTile;
	xfloat32				m_fFPS;
	xint32					m_nActualFrameNum;
	xint32					m_nCurrentFrame;
	xfloat32				m_fTickTotalTime;
	xbool					m_bPlaySequence;

	XVECTOR2				m_vLTPercent;
	XVECTOR2				m_vBRPercent;
	xbool					m_bFlipX;

	xbool					m_bEnable9Slice;
	xfloat32				m_fSliceLeft;
	xfloat32				m_fSliceRight;
	xfloat32				m_fSliceTop;
	xfloat32				m_fSliceBottom;
};

#endif
