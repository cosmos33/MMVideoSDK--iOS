/******************************************************************************

 @File         XPoint.h

 @Version      1.0

 @Created      2017, 3, 6

 @Description  Point class.

 @HISTORY:

******************************************************************************/

#ifndef _XPOINT_H_
#define _XPOINT_H_

#include "XTypes.h"

template <class T>
class XPoint
{
public:
					XPoint() {}
					XPoint(const T& _x, const T& _y) { x = _x; y = _y; }
					XPoint(const XPoint& pt) { x = pt.x; y = pt.y; }

public:
	void 			Offset(const T& ox, const T& oy) { x += ox; y += oy; }
	void 			Set(const T& _x, const T& _y) { x = _x; y = _y; }

	friend bool		operator != (const XPoint& pt1, const XPoint& pt2) { return pt1.x != pt2.x || pt1.y != pt2.y; }
	friend bool		operator == (const XPoint& pt1, const XPoint& pt2) { return pt1.x == pt2.x && pt1.y == pt2.y; }
	friend XPoint	operator + (const XPoint& pt1, const XPoint& pt2) { return XPoint(pt1.x+pt2.x, pt1.y+pt2.y); }
	friend XPoint	operator - (const XPoint& pt1, const XPoint& pt2) { return XPoint(pt1.x-pt2.x, pt1.y-pt2.y); }
	XPoint			operator + () const { return *this; }
	XPoint			operator - () const { return XPoint(-x, -y); }
	const XPoint&	operator = (const XPoint& pt) { x = pt.x; y = pt.y; return *this; }
	const XPoint&	operator += (const XPoint& pt) { x += pt.x; y += pt.y; return *this; }
	const XPoint&	operator -= (const XPoint& pt) { x -= pt.x; y -= pt.y; return *this; }

public:
	T	x;
	T	y;
};

typedef XPoint<xint32>		XPointI;
typedef XPoint<xfloat32>	XPointF;

#endif	//	_XPOINT_H_
