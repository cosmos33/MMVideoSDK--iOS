#ifndef _IX2DSHAPE_H_
#define _IX2DSHAPE_H_

#include "XMath3D.h"

class IX2DShape : public XMemBase
{
public:
	enum Type
	{
		X_CIRCLE = 0,
		X_EDGE = 1,
		X_POLYGON = 2,
		X_NUM = 3
	};
	virtual ~IX2DShape() {}
	virtual Type		GetType() const = 0;
};

class IX2DCircleShape : public IX2DShape
{
public:
	virtual void		SetRadius(xfloat32 fRadius) = 0;
	virtual xfloat32	GetRadius()const = 0;
};

class IX2DEdgeShape : public IX2DShape
{

};

class IX2DPolygonShape : public IX2DShape
{
public:
	virtual void		SetAsBox(xfloat32 hx, xfloat32 hy) = 0;
	virtual void		SetAsBox(xfloat32 hx, xfloat32 hy, const XVECTOR2& vCenter, xfloat32 fAngle) = 0;
};

class X2DShapeFactory : public XMemBase
{
public:
	static IX2DShape*		CreateShape(IX2DShape::Type eType);
};

#endif
