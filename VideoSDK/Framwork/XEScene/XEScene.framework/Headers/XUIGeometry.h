#ifndef _XUIGEOMETRY_H_
#define _XUIGEOMETRY_H_

#include "XMath3D.h"

class XUIRect
{
public:
	XVECTOR2	origin;
	XVECTOR2	size;
public:
	XUIRect();
	XUIRect(xfloat32 x, xfloat32 y, xfloat32 width, xfloat32 height);
	XUIRect(const XVECTOR2& pos, const XVECTOR2& dimension);
	XUIRect(const XUIRect& other);
	XUIRect& operator= (const XUIRect& other);
	void		SetRect(xfloat32 x, xfloat32 y, xfloat32 width, xfloat32 height);
	xfloat32	GetMinX() const; 
	xfloat32	GetMidX() const;
	xfloat32	GetMaxX() const;
	xfloat32	GetMinY() const;
	xfloat32	GetMidY() const;
	xfloat32	GetMaxY() const;
	xbool		Equals(const XUIRect& rect) const;
	xbool		ContainsPoint(const XVECTOR2& point) const;
	xbool		IntersectsRect(const XUIRect& rect) const;
	void		Merge(const XUIRect& rect);
	static const XUIRect ZERO;
};

#endif
