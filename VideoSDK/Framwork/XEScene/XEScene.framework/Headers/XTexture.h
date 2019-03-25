/******************************************************************************

 @File         XTexture.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XTexture.

 @HISTORY:

******************************************************************************/
#ifndef _X_TEXTURE_H_
#define _X_TEXTURE_H_

#include "XResource.h"
#include "XString.h"
#include "XMemBase.h"
#include "XStats.h"

class XFileBase;

enum XTexLoadFlag
{
	ATLF_FORCE_QUALITY_HIGH = XBit(0),
	
};

class IXTextureManager : public XMemBase
{
public:
	virtual					~IXTextureManager() {}

	virtual xbool			Init() = 0;
	virtual void			Release() = 0;

	virtual IXTexture2D*	CreateTexture2D(const XString& strFileName,
											const xuint32 nWidth,
											const xuint32 nHeight,
											const XTexFormat eFormat,
											const xuint32 nMipmapLevels,
											xbool bDynamic = xfalse) = 0;
	virtual IXTextureCube*	CreateTextureCube(	const XString& strFileName,
												const xuint32 nEdgeLength,
												const XTexFormat eFormat,
												const xuint32 nMipmapLevels,
												xbool bDynamic = xfalse) = 0;

	virtual IXRenderTarget*	CreateRenderTarget( const XString& strRTName,
												const xuint32 nWidth, 
												const xuint32 nHeight, 
												const XTexFormat eFmt) = 0;

	virtual IXTexture*		LoadTexture(const XString& strFileName, xint32 nLoadFlag = 0) = 0;
	virtual IXTexture*		LoadTexture(XFileBase* pFile, xint32 nLoadFlag = 0) = 0;

	virtual IXTexture2D*	LoadTexture2D(const XString& strFileName, xint32 nLoadFlag = 0) = 0;
	virtual IXTexture2D*	LoadTexture2D(XFileBase* pFile, xint32 nLoadFlag = 0) = 0;
	virtual IXTextureCube*	LoadTextureCube(const XString& strFileName, xint32 nLoadFlag = 0) = 0;
	virtual IXTextureCube*	LoadTextureCube(XFileBase* pFile, xint32 nLoadFlag = 0) = 0;

    virtual void			AddTextureRef(IXTexture* pTexture) = 0;
	virtual IXTexture2D*	CreateTexture2DImpl(const XString& strFileName,
												const xuint32 nWidth,
												const xuint32 nHeight,
												const XTexFormat eFormat,
												const xuint32 nMipmapLevels,
												xbool bDynamic = xfalse) = 0;
	virtual IXTextureCube*	CreateTextureCubeImpl(	const XString& strFileName,
													const xuint32 nEdgeLength,
													const XTexFormat eFormat,
													const xuint32 nMipmapLevels,
													xbool bDynamic = xfalse) = 0;

	/*
	* 重新从文件中更新纹理资源
	*
	* @notice  要求纹理类型（2D,3D,CUBE）必需一致，才能更新成功。
	*/
	virtual xbool			ReLoadTexture(IXTexture *pTexture) = 0;
	/*
	* 重新从文件中更新纹理资源
	*
	* @notice  要求纹理类型（2D,3D,CUBE）必需一致，才能更新成功。
	*
	* @return true : 重新加载成功或资源未加载返回true
	*/
	virtual xbool			ReLoadTexture(const XString& strRelativeFileName) = 0;

	/* 判断资源是否已加载
	*/
	virtual	xbool			IsTextureLoaded(const XString& strRelativeFileName) = 0;

	/* 返回默认的错误纹理
	*/
	virtual IXTexture*		GetErrorTexture() = 0;
};

extern IXTextureManager* g_pXTextureManager;


struct XTexFormatDesc
{
	XTexFormat	eFormat;
	xuint32		nBlockBytes;
	xuint32		nBlockWidth;
	xuint32		nBlockHeight;
	xuint32		nMinWidth;
	xuint32		nMinHeight;
    xbool       bHasAlpha;
};

extern const XTexFormatDesc* GetTexFormatDesc(const XTexFormat eFormat);
extern xuint32 GetTexMipmapNumBlocksX(const XTexFormatDesc* pFormatDesc, const xuint32 nWidth);
extern xuint32 GetTexMipmapNumBlocksY(const XTexFormatDesc* pFormatDesc, const xuint32 nHeight);
extern xuint32 GetTexMipmapSize(const XTexFormatDesc* pFormatDesc, const xuint32 nWidth, const xuint32 nHeight, const xuint32 nDepth);
#endif// _X_TEXTURE_H_

