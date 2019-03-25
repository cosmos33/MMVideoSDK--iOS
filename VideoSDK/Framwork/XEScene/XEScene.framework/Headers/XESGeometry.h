//
//  XESGeometry.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESGEOMETRY_H_
#define XESGEOMETRY_H_

#include "core/XESObject.h"

XESCENE_NAMESPACE_BEGIN

class Size {
    
public:
    float width;
    float height;
public:
    operator XVECTOR2() const
    {
        return XVECTOR2(width, height);
    }
    
public:
    
    Size();
    Size(float width, float height);
    Size(const Size& other);
    explicit Size(const XVECTOR2& point);
    
    Size& operator= (const Size& other);
    Size& operator= (const XVECTOR2& point);
    
    Size  operator+(const Size& right) const;
    Size  operator-(const Size& right) const;
    Size  operator*(float a) const;
    Size  operator/(float a) const;
    
    void  SetSize(float width, float height);
    bool  Equals(const Size& target) const;
    static const Size ZERO;
};

class Rect
{
public:
    Size  size;
    XVECTOR2 origin;
public:
    Rect();
    Rect(float x, float y, float width, float height);
    Rect(const XVECTOR2& pos, const Size& dimension);
    Rect(const Rect& other);

    
    Rect& operator= (const Rect& other);
    
    void SetRect(float x, float y, float width, float height);
    
    float GetMinX() const; /// return the leftmost x-value of current rect
    float GetMidX() const; /// return the midpoint x-value of current rect
    float GetMaxX() const; /// return the rightmost x-value of current rect
    float GetMinY() const; /// return the bottommost y-value of current rect
    float GetMidY() const; /// return the midpoint y-value of current rect
    float GetMaxY() const; /// return the topmost y-value of current rect
    
    bool Equals(const Rect& rect) const;
    bool containsPoint(const XVECTOR2& point) const;
    bool intersectsRect(const Rect& rect) const;
    bool intersectsCircle(const XVECTOR2& center, float radius) const;
    
    Rect unionWithRect(const Rect & rect) const;
    
    void merge(const Rect& rect);
    static const Rect ZERO;
};

XESCENE_NAMESPACE_END

#endif /* XESGEOMETRY_H_ */
