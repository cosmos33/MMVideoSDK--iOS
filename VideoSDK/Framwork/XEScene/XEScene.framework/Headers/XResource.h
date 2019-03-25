/******************************************************************************

 @File         XResource.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XResource.

 @HISTORY:

******************************************************************************/
#ifndef _X_RESOURCE_H_
#define _X_RESOURCE_H_

#include "XSys.h"
#include "XMemBase.h"

#define X_INDEX_NONE -1

class IXResource;
class IXResourceListener : public XMemBase
{
public:
	virtual				~IXResourceListener() {}

	virtual	void		FreeRes(IXResource* pResource) = 0;
	virtual	void		UpdateRes(IXResource* pResource) = 0;
	virtual void		UpdateResImmediately(IXResource* pResource) = 0;
	virtual void		CreateAndUpdateResImmediately(IXResource* pResource) = 0;
};

class IXResourceManager : public XMemBase
{
public:
	virtual				~IXResourceManager() {}

	virtual xbool		Init() = 0;
	virtual void		Release() = 0;

	virtual	void		RegisterListener(IXResourceListener* pListener) = 0;
	virtual	void		DeregisterListener(IXResourceListener* pListner) = 0;

	virtual	void		AllocRes(IXResource* pResource) = 0;
	virtual	void		FreeRes(IXResource* pResource) = 0;
	virtual	void		UpdateRes(IXResource* pResource) = 0;
	virtual void		UpdateResImmediately(IXResource* pResource) = 0;
	virtual void		CreateAndUpdateResImmediately(IXResource* pResource) = 0;
};
extern IXResourceManager* g_pXResourceManager;


enum XResType
{
	XRES_INDEX_BUF,
	XRES_VERT_BUF,
	XRES_VERT_DESC,
	XRES_TEX_2D,
	XRES_TEX_CUBE,
	XRES_RENDER_TARGET,
	XRES_MATERIAL,
	XRES_MATERIAL_INSTANCE,
};

class IXResource : public XMemBase
{
public:
	virtual					~IXResource(){};
	virtual	XResType		Type() const = 0;
	
	virtual xint32			GetResourceIdx() const = 0;
	virtual void			SetResourceIdx(xint32 nIdx) = 0;
	virtual xbool			IsDynamic() const = 0;

	virtual void			Update() = 0;

};

class IXVertexBuffer : public IXResource
{
public:
	
	virtual				~IXVertexBuffer() {}
	virtual	xint32		GetVertNum() const = 0;
	virtual	void		GetData(void* pDestBuf) = 0;

	virtual xint32		GetSize() const = 0;
	virtual xint32		GetStride() const = 0;
	
};

class IXIndexBuffer : public IXResource
{
public:

	virtual				~IXIndexBuffer() {}

	virtual xint32		GetIdxNum() const = 0;
	virtual void		GetData(void* pDestBuf) = 0;
	virtual xint32		GetSize() const = 0;
	virtual xint32		GetStride() const = 0;
	
};

enum XVertElementType
{
	XVET_FLOAT1,
	XVET_FLOAT2,
	XVET_FLOAT3,
	XVET_FLOAT4,
	XVET_COLOR,
	XVET_UBYTE4,
};

// NOTICE: If you modified this enumeration, you must change the values of g_ppszVertexElementUsageNames array also.
enum XVertElementUsage
{
	XVEU_POSITION,
	XVEU_BLENDWEIGHT,
	XVEU_BLENDINDICES,
	XVEU_NORMAL,
	XVEU_PSIZE,
	XVEU_TEXCOORD,
	XVEU_TANGENT,
	XVEU_BINORMAL,
	XVEU_TESSFACTOR,
	XVEU_POSITIONT,
	XVEU_COLOR,
	XVEU_FOG,
	XVEU_DEPTH,
	XVEU_SAMPLE,
    XVEU_USAGE_COUNT,
};

class IXVertexElement 
{
public:
	virtual						~IXVertexElement() {}

	virtual IXVertexBuffer*		GetVertexBuffer() = 0;
	virtual xuint32				GetOffset() = 0;
	virtual	XVertElementType	GetType() = 0;
	virtual XVertElementUsage	GetUsage() = 0;
	virtual xuint32				GetUsageIdx() = 0;
};

enum XVertDescName
{
	XVDN_STATIC,
	//XVDN_RIGID,
	XVDN_SKIN,
	XVDN_GRASS_VS,
	XVDN_GRASS_SW,
	XVDN_DISTANT_BOARD,
	XVDN_IGNORE,
	XVDN_NUM
};

class IXVertexDesc : public IXResource
{
public:
	virtual						~IXVertexDesc() {}
	virtual xint32				GetVertElementNum() = 0;
	virtual IXVertexElement*	GetVertElement(xint32 nIdx) = 0;
	virtual XVertDescName		GetName() = 0;
};


//---------------------------------------------------------------------------------------
// IXTexture

// NOTICE!! If you need to change this enumeration, you must also change the values in the tables of g_pATexFormatDescs, g_pAGLTexFormatDescs, and g_AD3D9TexFormatDescs.
enum XTexFormat
{
	XTF_UNKNOWN,

	XTF_R8G8B8,
	XTF_R8G8B8A8,

	XTF_PVRTC1_RGB_2BPP,
	XTF_PVRTC1_RGBA_2BPP,
	XTF_PVRTC1_RGB_4BPP,
	XTF_PVRTC1_RGBA_4BPP,

	XTF_LUMINANCE,			// for arkit
	XTF_LUMINANCE_ALPHA,

    XTF_DXT1,
    XTF_DXT3,
    XTF_DXT5,

    XTF_ETC1_RGB,
    XTF_ETC1_RGBA,

    XTF_ATC_RGB,
    XTF_ATC_RGBA_EXPLICIT,
    XTF_ATC_RGBA_INTERPOLATED,

	ATF_COUNT,
};

struct XLockedRect
{
	xbyte*		pData;
	xuint32		nRowPitch;
	xuint32		nSize;
};

struct XLockedBox
{
	xbyte*		pData;
	xuint32		nRowPitch;
	xuint32		nSlicePitch;
	xuint32		nSize;
};

class IXTexture : public IXResource
{
public:
	virtual XTexFormat			Format() const = 0;
	virtual xuint32				MipmapNum() const = 0;
	virtual xbool				IsSRGB() const = 0;
	virtual void				GenerateMipmaps(const xuint32 nMipmapLevels) = 0;

	virtual const xchar*		GetName() const = 0;

	/**
	* 返回底层平台相关的资源指针，便于某些依赖底层的插件直接访问资源
	* 谨慎使用，如果不明白作用，就不要调用
	*/
	virtual void*				GetNativeResource() const = 0;
	// 任何情况下都不要调用
	virtual void				SetNativeResource(void* p) = 0;

	//just for Engine
	virtual void				Release() = 0;

protected:
	friend class XTextureManager;
	virtual						~IXTexture() {}
	
};

class IXTexture2D : public IXTexture
{
public:
	virtual	xuint32				Width() const = 0;
	virtual	xuint32				Height() const = 0;
	virtual void				GetData(void* pDestBuf, xuint32 nMipmap, xuint32 nStrideY) = 0;
	virtual void				GetData(void** pp, xuint32 nMipmap) = 0;
	virtual void				Lock(const xuint32 nMipmap, XLockedRect* pLockedRect) = 0;
	virtual void				Unlock() = 0;
	virtual xuint32				GetMipmapSize(const xuint32 nMipmap) = 0;
	virtual xbool				IsExternalOES() = 0;	// for android external oes texture only
	virtual xbool				ResetTexture2DBuffer(const xuint32 nWidth, const xuint32 nHeight,
								   const XTexFormat eFormat, const xuint32 nMipmapLevels, xbool bDynamic = xfalse){ return xfalse; }
protected:
	friend class XTextureManager;
	virtual						~IXTexture2D() {}

};

class IXTextureCube : public IXTexture
{
public:
	virtual	xuint32				EdgeLength() const = 0;
	virtual void				GetData(void* pDestBuf, xuint32 nFace, xuint32 nMipmap, xuint32 nStrideY) = 0;
	virtual void				Lock(const xuint32 nFace, const xuint32 nMipmap, XLockedRect* pLockedRect) = 0;
	virtual void				Unlock() = 0;
	virtual xuint32				GetMipmapSize(const xuint32 nFace, const xuint32 nMipmap) = 0;
	virtual xbool				ResetTextureCubeBuffer(const xuint32 nEdgeLength, const XTexFormat eFormat,
								   const xuint32 nMipmapLevels, xbool bDynamic = xfalse) { return xfalse; }

protected:
	friend class XTextureManager;
	virtual						~IXTextureCube() {}
};

class IXRenderTarget : public IXTexture2D
{
protected:
	friend class XTextureManager;
	virtual						~IXRenderTarget() {}
};

#endif //_X_RESOURCE_H_