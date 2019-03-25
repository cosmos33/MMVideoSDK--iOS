/******************************************************************************

 @File         XRectangle.h

 @Version      1.0

 @Created      2017, 3, 6

 @Description  Rectangle class.

 @HISTORY:

******************************************************************************/

#ifndef _XRECTANGLE_H_
#define _XRECTANGLE_H_

#include "XPoint.h"

template <class T>
class XRectangle
{
public:
	XRectangle() {}
	XRectangle(const T& _left, const T& _top, const T& _right, const T& _bottom) { left = _left; top = _top; right = _right; bottom = _bottom; }
	XRectangle(const XRectangle& rc) { left = rc.left; top = rc.top; right = rc.right; bottom = rc.bottom; }

public:
	friend bool			operator != (const XRectangle& rc1, const XRectangle& rc2) { return rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom; }
	friend bool			operator == (const XRectangle& rc1, const XRectangle& rc2) { return rc1.left == rc2.left && rc1.top == rc2.top && rc1.right == rc2.right && rc1.bottom == rc2.bottom; }
	friend XRectangle	operator + (const XRectangle& rc1, const XRectangle& rc2) { return XRectangle(rc1.left+rc2.left, rc1.top+rc2.top, rc1.right+rc2.right, rc1.bottom+rc2.bottom); }
	friend XRectangle	operator - (const XRectangle& rc1, const XRectangle& rc2) { return XRectangle(rc1.left-rc2.left, rc1.top-rc2.top, rc1.right-rc2.right, rc1.bottom-rc2.bottom); }
	friend XRectangle	operator + (const XRectangle& rc1, const XPoint<T>& pt) { return XRectangle(rc1.left+pt.x, rc1.top+pt.y, rc1.right+pt.x, rc1.bottom+pt.y); }
	friend XRectangle	operator - (const XRectangle& rc1, const XPoint<T>& pt) { return XRectangle(rc1.left-pt.x, rc1.top-pt.y, rc1.right-pt.x, rc1.bottom-pt.y); }
	const XRectangle&	operator &= (const XRectangle& rc) { *this = *this & rc; return *this; }
	const XRectangle&	operator |= (const XRectangle& rc) { *this = *this | rc; return *this; }	
	const XRectangle&	operator = (const XRectangle& rc) { left = rc.left; top = rc.top; right = rc.right; bottom = rc.bottom; return *this; }
	const XRectangle&	operator += (const XRectangle& rc) { left += rc.left; top += rc.top; right += rc.right; bottom += rc.bottom; return *this; }
	const XRectangle&	operator -= (const XRectangle& rc) { left -= rc.left; top -= rc.top; right -= rc.right; bottom -= rc.bottom; return *this; }
	const XRectangle&	operator += (const XPoint<T>& pt) { left += pt.x; top += pt.y; right += pt.x; bottom += pt.y; return *this; }
	const XRectangle&	operator -= (const XPoint<T>& pt) { left -= pt.x; top -= pt.y; right -= pt.x; bottom -= pt.y; return *this; }
	XRectangle			operator + () const { return *this; }
	XRectangle			operator - () const { return XRectangle(-left, -top, -right, -bottom); }
	T 					Width() const { return right - left; }
	T 					Height() const { return bottom - top; }
	XPoint<T> 			Center() const { return XPoint<T>((left+right) / 2, (top+bottom) / 2); }
	void 				Set(const T& _left, const T& _top, const T& _right, const T& _bottom) { left=_left; top=_top; right=_right; bottom=_bottom; }
	xbool 				IsZero() const { return xbool(left == 0 && top == 0 && right == 0 && bottom == 0); }
	xbool 				IsEmpty() const { return xbool(Width() == 0 || Height() == 0); }
	xbool 				IsPointIn(const T& x, const T& y) const { return (x >= left && x < right && y >= top && y < bottom) ? xtrue : xfalse; }
	xbool 				IsPointIn(const XPoint<T>& pt) const { return IsPointIn(pt.x, pt.y); }
	void 				Normalize();
	void 				Offset(const T& x, const T& y) { left += x; top += y; right += x; bottom += y; }
	void 				SetUnion(const XRectangle<T>& rc1, const XRectangle<T>& rc2) { *this = rc1 | rc2; }
	void 				SetIntersect(const XRectangle<T>& rc1, const XRectangle<T>& rc2) { *this = rc1 & rc2; }
public:
	T					left;
	T					top;
	T					right;
	T					bottom;
};

typedef XRectangle<xint32>		XRectI;
typedef XRectangle<xfloat32>	XRectF;


template <class T>
XRectangle<T> operator & (const XRectangle<T>& rc1, const XRectangle<T>& rc2)
{
	if (rc1.IsEmpty() || rc2.IsEmpty())
		return XRectangle<T>(0, 0, 0, 0);

	if (rc1.left >= rc2.right || rc2.left >= rc1.right ||
		rc1.top >= rc2.bottom || rc2.top >= rc1.bottom)
		return XRectangle<T>(0, 0, 0, 0);

	return XRectangle<T>(rc1.left > rc2.left ? rc1.left : rc2.left,
				  rc1.top > rc2.top ? rc1.top : rc2.top,
				  rc1.right < rc2.right ? rc1.right : rc2.right,
				  rc1.bottom < rc2.bottom ? rc1.bottom : rc2.bottom);
}

template <class T>
XRectangle<T> operator | (const XRectangle<T>& rc1, const XRectangle<T>& rc2)
{
	if (rc1.IsEmpty())
		return rc2;

	if (rc2.IsEmpty())
		return rc1;
	
	return XRectangle<T>(rc1.left < rc2.left ? rc1.left : rc2.left,
				  rc1.top < rc2.top ? rc1.top : rc2.top,
				  rc1.right > rc2.right ? rc1.right : rc2.right,
				  rc1.bottom > rc2.bottom ? rc1.bottom : rc2.bottom);
}

template <class T>
void XRectangle<T>::Normalize()
{
	if (left > right)
		X_Swap(left, right); 
	
	if (top > bottom) 
		X_Swap(top, bottom);
}

#endif