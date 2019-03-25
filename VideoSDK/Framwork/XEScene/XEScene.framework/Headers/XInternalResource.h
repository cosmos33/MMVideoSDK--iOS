/******************************************************************************

 @File         XInternalResource.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XInternalResource.

 @HISTORY:     缓冲不足导致反复分配内存，性能会降低。所以最好指定足够大的Buffer尺寸

******************************************************************************/
#ifndef _X_INTERNAL_RESOURCE_H_
#define _X_INTERNAL_RESOURCE_H_

#include "XResource.h"
#include "XMath3D.h"
#include "XStats.h"

class XIndexBuffer16 : public IXIndexBuffer
{
public:
								XIndexBuffer16(xbool bDynamic, xint32 nSize, xint32 nGrowSize);
								~XIndexBuffer16();
	virtual	XResType			Type() const { return XRES_INDEX_BUF;}
	virtual xint32				GetResourceIdx() const { return m_nResourceIdx;}
	virtual void				SetResourceIdx(xint32 nIdx) { m_nResourceIdx = nIdx;}
	virtual xbool				IsDynamic() const { return m_bDynamic;}
	virtual void				Update() { g_pXResourceManager->UpdateRes(this);}

	virtual xint32				GetIdxNum() const  { return m_Indices.Num();}
	virtual void				GetData(void* pDestBuf);
	virtual xint32				GetSize() const { return m_Indices.Num() * sizeof(xuint16);}
	virtual xint32				GetStride() const { return sizeof(xuint16);}

	void						SetIndexNum(xint32 nNum) { m_Indices.SetNum(nNum); }
	void						AddIndex(xuint16 nIdx);
	xuint16						GetIndex(xint32 nIdx) const { return m_Indices[nIdx]; }
	void						Flush();
	const xuint16*				GetIndices() const { return m_Indices.GetData(); }
	xuint16*					GetIndices()  { return m_Indices.GetData(); }

protected:
	XArray<xuint16>				m_Indices;
	xint32						m_nResourceIdx;
	xbool						m_bDynamic;
	
};

inline XIndexBuffer16::XIndexBuffer16(xbool bDynamic,xint32 nSize, xint32 nGrowSize)
	:m_nResourceIdx(X_INDEX_NONE),
	m_bDynamic(bDynamic),
	m_Indices(nSize, nGrowSize)
{
	g_pXResourceManager->AllocRes(this);
}

inline XIndexBuffer16::~XIndexBuffer16()
{
	g_pXResourceManager->FreeRes(this);
}

inline void XIndexBuffer16::GetData(void* pDestBuf) 
{
	memcpy(pDestBuf, (void*)m_Indices.GetData(), m_Indices.Num() * sizeof(xuint16));
}

inline void XIndexBuffer16::AddIndex(xuint16 nIdx)
{
	m_Indices.Add(nIdx);
}

inline void XIndexBuffer16::Flush() 
{
	m_Indices.Clear(!m_bDynamic);

}

class XIndexBuffer32 : public IXIndexBuffer
{
public:
								XIndexBuffer32(xbool bDynamic, xint32 nSize, xint32 nGrowSize);
	virtual						~XIndexBuffer32();

	virtual	XResType			Type() const { return XRES_INDEX_BUF;}
	virtual xint32				GetResourceIdx() const { return m_nResourceIdx;}
	virtual void				SetResourceIdx(xint32 nIdx) { m_nResourceIdx = nIdx;}
	virtual xbool				IsDynamic() const { return m_bDynamic;}
	virtual void				Update() { g_pXResourceManager->UpdateRes(this);}

	virtual xint32				GetIdxNum() const  { return m_Indices.Num();}
	virtual void				GetData(void* pDestBuf);
	virtual xint32				GetSize() const { return m_Indices.Num() * sizeof(xuint32); }
	virtual xint32				GetStride() const { return sizeof(xuint32);}

	void						SetIndexNum(xint32 nNum) { m_Indices.SetNum(nNum); }
	void						AddIndex(xuint32 nIdx);
	X_FORCEINLINE xuint32		GetIndex(xint32 nIdx) const { return m_Indices[nIdx]; }
	void						Flush();
	const xuint32*				GetIndices() const { return m_Indices.GetData(); }
	xuint32*					GetIndices()	   { return m_Indices.GetData(); }
protected:
	XArray<xuint32>				m_Indices;
	xint32						m_nResourceIdx;
	xbool						m_bDynamic;
	
};
inline XIndexBuffer32::XIndexBuffer32(xbool bDynamic, xint32 nSize, xint32 nGrowSize)
	:m_nResourceIdx(X_INDEX_NONE),
	m_bDynamic(bDynamic),
	m_Indices(nSize, nGrowSize)
{
	g_pXResourceManager->AllocRes(this);
	
}

inline XIndexBuffer32::~XIndexBuffer32()
{
	g_pXResourceManager->FreeRes(this);
}

inline void XIndexBuffer32::GetData(void* pDestBuf) 
{
	memcpy(pDestBuf, (void*)m_Indices.GetData(), m_Indices.Num() * sizeof(xuint32));
}

inline void XIndexBuffer32::AddIndex(xuint32 nIdx)
{
	m_Indices.Add(nIdx);
}

inline void XIndexBuffer32::Flush() 
{
	m_Indices.Clear(!m_bDynamic);
}

template<class T>
class XTypeVertexBuffer : public IXVertexBuffer
{
public:
	XTypeVertexBuffer(xbool bDynamic, xint32 nSize, xint32 nGrowSize);
	virtual ~XTypeVertexBuffer();

	virtual XResType		Type() const { return XRES_VERT_BUF;}
	virtual xint32			GetResourceIdx() const { return m_nResourceIdx;}
	virtual void			SetResourceIdx(xint32 nIdx) { m_nResourceIdx = nIdx;}
	virtual xbool			IsDynamic() const { return m_bDynamic;}
	virtual void			Update() { g_pXResourceManager->UpdateRes(this);}

	virtual	xint32			GetVertNum() const { return m_Verts.Num();}
	virtual	void			GetData(void* pDestBuf);
	virtual xint32			GetSize() const { return m_Verts.Num() * sizeof(T); }
	virtual xint32			GetStride() const { return sizeof(T);}

	void					SetVertNum(xint32 nNum) { m_Verts.SetNum(nNum); }
	xint32					AddVert(const T& vert);
	X_FORCEINLINE const T&	GetVert(xint32 nIdx) const { return m_Verts[nIdx]; }
	void					SetVert(xint32 iIndex, const T& vert);
	void					Flush();
	const T*				GetVerts() const { return m_Verts.GetData(); }
	T*						GetVerts() { return m_Verts.GetData(); }

protected:
    XArray<T>				m_Verts;
    xint32					m_nResourceIdx;
	xbool					m_bDynamic;
};

template<class T>
inline XTypeVertexBuffer<T>::XTypeVertexBuffer(xbool bDynamic, xint32 nSize, xint32 nGrowSize)
	: m_nResourceIdx(X_INDEX_NONE)
	, m_bDynamic(bDynamic)
	, m_Verts(nSize, nGrowSize)
{
	g_pXResourceManager->AllocRes(this);
}

template<class T>
inline XTypeVertexBuffer<T>::~XTypeVertexBuffer()
{
    g_pXResourceManager->FreeRes(this);
}

template<class T>
inline void XTypeVertexBuffer<T>::GetData(void* pDestBuf)
{
    memcpy(pDestBuf, (void*)m_Verts.GetData(), GetSize());
}

template<class T>
inline xint32 XTypeVertexBuffer<T>::AddVert(const T& vert)
{
	return m_Verts.Add(vert); 
}

template<class T>
inline void XTypeVertexBuffer<T>::SetVert(xint32 iIndex, const T& vert)
{
	m_Verts[iIndex] = vert;
}

template<class T>
inline void XTypeVertexBuffer<T>::Flush() 
{
	m_Verts.Clear(!m_bDynamic);
}


struct XVertPos
{
	XVECTOR3 vPos;
};

typedef XTypeVertexBuffer<XVertPos> XPositionVB;

struct XVertUV
{
	XVECTOR2 vUV;  
};

typedef XTypeVertexBuffer<XVertUV> XUVVB;

class XVertexElement : public IXVertexElement
{
public:
								XVertexElement(){}
								XVertexElement(	IXVertexBuffer* pVertBuf,
												xint32 nOffset,
												XVertElementType type,
												XVertElementUsage usage,
												xint32 nUsageIdx);

	virtual						~XVertexElement() {}

	virtual IXVertexBuffer*		GetVertexBuffer() { return m_pVertBuf;}
	virtual xuint32				GetOffset() { return m_nOffset;}
	virtual	XVertElementType	GetType() { return m_Type;}
	virtual XVertElementUsage	GetUsage() { return m_Usage;}
	virtual xuint32				GetUsageIdx() { return m_nUsageIdx;}
	
protected:
	IXVertexBuffer*				m_pVertBuf;
	xuint32						m_nOffset;
	XVertElementType			m_Type;
	XVertElementUsage			m_Usage;
	xuint32						m_nUsageIdx;
};

inline XVertexElement::XVertexElement(	IXVertexBuffer* pVertBuf,
												xint32 nOffset,
												XVertElementType type,
												XVertElementUsage usage,
												xint32 nUsageIdx)
												:m_pVertBuf(pVertBuf),
												m_nOffset(nOffset),
												m_Type(type),
												m_Usage(usage),
												m_nUsageIdx(nUsageIdx)
{

}

class XVertexDesc : public IXVertexDesc
{
public:
								XVertexDesc(XVertDescName name = XVDN_IGNORE);
	virtual						~XVertexDesc();

	virtual XResType			Type() const { return XRES_VERT_DESC;}
	virtual xint32				GetResourceIdx() const { return m_nResourceIdx;}
	virtual void				SetResourceIdx(xint32 nIdx) { m_nResourceIdx = nIdx;}
	virtual xbool				IsDynamic() const { return m_bDynamic;}
	virtual void				Update() { g_pXResourceManager->UpdateRes(this);}

	virtual xint32				GetVertElementNum() { return m_VertElements.Num();}
	virtual IXVertexElement*	GetVertElement(xint32 nIdx) { return &m_VertElements[nIdx];}
	virtual XVertDescName		GetName() { return m_Name;}

	void						AddVertElement(XVertexElement& vertElement);
	void						ClearAllElements();
								
protected:
	XArray<XVertexElement>		m_VertElements;
	XVertDescName				m_Name;
	xint32						m_nResourceIdx;
	xbool						m_bDynamic;
};

inline XVertexDesc::XVertexDesc(XVertDescName name)
	:m_nResourceIdx(X_INDEX_NONE),
	m_bDynamic(xfalse),
	m_Name(name)
{
	g_pXResourceManager->AllocRes(this);
}

inline XVertexDesc::~XVertexDesc()
{
	g_pXResourceManager->FreeRes(this);
}

inline void XVertexDesc::AddVertElement(XVertexElement& vertElement)
{ 
	m_bDynamic |= vertElement.GetVertexBuffer()->IsDynamic();
	m_VertElements.Add(vertElement);
}

inline void XVertexDesc::ClearAllElements()
{ 
	m_bDynamic = false;
	m_VertElements.Clear(true);
}

#endif //_X_INTERNAL_RESOURCE_H_