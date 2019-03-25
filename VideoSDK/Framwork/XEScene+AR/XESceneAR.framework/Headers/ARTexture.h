#include "xcommon/XTexture.h"
#include "xcommon/XString.h"

namespace AR {
    
// 用于渲染ARKit相机画面
class ARKitTexture : public IXTexture2D
{
public:
	ARKitTexture(const xchar* szName,
		const xuint32 nWidth,
		const xuint32 nHeight,
		const XTexFormat eFormat);
	virtual ~ARKitTexture();
	virtual	XResType			Type() const{ return XRES_TEX_2D; }
	virtual xint32				GetResourceIdx() const{ return m_nResourceIdx; }
	virtual void				SetResourceIdx(xint32 nIdx){ m_nResourceIdx = nIdx; }
	virtual xbool				IsDynamic() const{ return m_bDynamic; }
	virtual void				Update(){ g_pXResourceManager->UpdateResImmediately(this); }

    virtual void*               GetNativeResource() const{return NULL;}
    virtual void                SetNativeResource(void* p){return;}
    virtual xbool               IsExternalOES(){return xfalse;}
    
	virtual XTexFormat			Format()const;
	virtual xuint32				MipmapNum() const {return 1; }
	virtual xbool				IsSRGB() const { return 0; }
	virtual void				GenerateMipmaps(const xuint32 nMipmapLevels){}
	virtual const xchar*		GetName() const;
	virtual void				Release();
	virtual	xuint32				Width() const;
	virtual	xuint32				Height() const;
	virtual void				GetData(void* pDestBuf, xuint32 nMipmap, xuint32 nStrideY);
	virtual void				GetData(void** pp, xuint32 nMipmap);
	virtual void				Lock(const xuint32 nMipmap, XLockedRect* pLockedRect);
	virtual void				Unlock();
	virtual xuint32				GetMipmapSize(const xuint32 nMipmap);
	void						SetData(void* pData, xint32 nWidth, xint32 nHeight);
private:
	int							m_nResourceIdx;
	XTexFormat					m_format;
	xuint32						m_nWidth;
	xuint32						m_nHeight;
	xbool						m_bDynamic;
	XString						m_strName;
	void*						m_pData;
	xuint32						m_nDataSize;
};

// 用于渲染Tango SDK/ARCore 相机画面（使用OES扩展纹理）
class XARCoreTexture : public IXTexture2D
{
public:
	XARCoreTexture(const xchar* szName,
				 const xuint32 nWidth,
				 const xuint32 nHeight,
				 const XTexFormat eFormat);
	virtual ~XARCoreTexture();
	virtual	XResType			Type() const{ return XRES_TEX_2D; }
	virtual xint32				GetResourceIdx() const{ return m_nResourceIdx; }
	virtual void				SetResourceIdx(xint32 nIdx){ m_nResourceIdx = nIdx; }
	virtual xbool				IsDynamic() const{ return m_bDynamic; }
	virtual void				Update(){ g_pXResourceManager->UpdateResImmediately(this); }

	virtual XTexFormat			Format()const;
	virtual xuint32				MipmapNum() const {return 1; }
	virtual xbool				IsSRGB() const { return 0; }
	virtual void				GenerateMipmaps(const xuint32 nMipmapLevels){}
	virtual const xchar*		GetName() const;
	virtual void				Release();
	virtual	xuint32				Width() const;
	virtual	xuint32				Height() const;
	virtual void				GetData(void* pDestBuf, xuint32 nMipmap, xuint32 nStrideY);
	virtual void				GetData(void** pp, xuint32 nMipmap);
	virtual void				Lock(const xuint32 nMipmap, XLockedRect* pLockedRect);
	virtual void				Unlock();
	virtual xuint32				GetMipmapSize(const xuint32 nMipmap);

	virtual void*    			GetNativeResource() const;
	virtual void    			SetNativeResource(void* p);

	void						SetData(void* pData, xint32 nWidth, xint32 nHeight);
	xbool 						IsExternalOES(){return xtrue;}
private:
	int							m_nResourceIdx;
	XTexFormat					m_format;
	xuint32						m_nWidth;
	xuint32						m_nHeight;
	xbool						m_bDynamic;
	XString						m_strName;
	void*						m_pData;
	xuint32						m_nDataSize;
	xint32                      m_nNativeResourceIndex;
};
}
