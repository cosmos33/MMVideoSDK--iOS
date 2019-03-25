/******************************************************************************

@File         XEMath.h

@Version       1.0

@Created      2017, 10, 12

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_MATH_H_
#define _XE_MATH_H_
#include "XTypes.h"
#include "XMath3D.h"
#include <limits>

// Aux constants.
#undef  PI
#define PI 			    (3.1415926535897932f)
#define INV_PI			(0.31830988618f)
#define HALF_PI			(1.57079632679f)

template <class T>
inline bool Equals(T lhs, T rhs) { return lhs + std::numeric_limits<T>::epsilon() >= rhs && lhs - std::numeric_limits<T>::epsilon() <= rhs; }

static const float M_EPSILON = 0.001f;
template <class T>
inline bool EqualsNotPrecison(T lhs, T rhs) { return lhs + M_EPSILON >= rhs && lhs - M_EPSILON <= rhs; }

//z is the forward vector of our camera. so the euler angle is Pitch.
namespace XEMath
{
	class LineSegment3
	{
	public:
		LineSegment3() :m_origin(0.f), m_direction(0.f){}
		LineSegment3(const XVECTOR3& origin, const XVECTOR3& direction) :m_origin(origin), m_direction(direction){}
	public:
		// get a point from a segment. t is the segment scale position(0~1)
		void GetPoint(XVECTOR3& point, xfloat32 t) const;
		// get lenght of this segment
		xfloat32 GetLength() const;
	public:
		XVECTOR3 m_origin;		//(m_origin, m_origin + m_direction)
		XVECTOR3 m_direction;	//direction with length.
	};

	xfloat32    InvSqrt(xfloat32 fNumber);
	xfloat32    FastAsin(xfloat32 Value);
	xfloat32    ClampAxis(xfloat32 radian);// returns radians in the range [0,2*PI)
	xfloat32    NormalizeAxis(xfloat32 radian);// returns radians in the range (-PI,PI]
	xfloat32    Xmod(xfloat32 X, xfloat32 Y);
	xfloat32    Atan2(xfloat32 Y, xfloat32 X);// y/x
	xfloat32    AreaOfTriangle(XVECTOR2 v1, XVECTOR2 v2, XVECTOR2 v3);//return 0 if can't be a triangle.
	void        SinCos(xfloat32* ScalarSin, xfloat32* ScalarCos, xfloat32  Value);
	void        QuaternionToEuler(const XQUATERNION& quat, xfloat32& fRoll, xfloat32& fYaw, xfloat32& fPitch);
	void        EulerToQuaternion(xfloat32 fRoll, xfloat32 fYaw, xfloat32 fPitch, XQUATERNION& quat);
	void        DirAndUpToQuaternion(const XVECTOR3& vForwardDir, const XVECTOR3& vUp, XQUATERNION& quat);
	void        QuaternionToDirAndUp(const XQUATERNION& quat, XVECTOR3& vForwardDir, XVECTOR3& vUp);
	void        LocationDirAndUpToMatrix(const XVECTOR3& vLocation, const XVECTOR3& vForwardDir, const XVECTOR3& vUp, XMATRIX4& mat4);
	void        MatrixToLocationAndDirAndUp(const XMATRIX4& mat4, XVECTOR3& vLocation, XVECTOR3& vForwardDir, XVECTOR3& vUp);
	XVECTOR3    GetScaleFromMatrix(const XMATRIX4& mat);
	XQUATERNION GetQuaternionFromMatrix(const XMATRIX4& mat);
	XMATRIX4    GetMatrixFromQuaternion(const XQUATERNION& quat);
	void        EliminateScaleFromMatrix(XMATRIX4& mat);
	void        EliminateRotateFromMatrix(XMATRIX4& mat);
	void        RotateMatrixWorld(XMATRIX4& mat, const XQUATERNION& quat);
	void        ScaleMatrixWorld(XMATRIX4& mat, const XVECTOR3& vScale);
	XVECTOR3    RotateVector(const XQUATERNION& quat, const XVECTOR3&vec);
	XVECTOR3    UnrotateVector(const XQUATERNION& quat, const XVECTOR3& vec);
	/************************************************************************/
	// To calculate the intersection point in a plane for a ray-line with specific origin point and its dir.
	// vLineOriginPoint: original point of the ray.
	// vLineDir: directional vector of the ray.
	// vPlanePoint: the specific point in the plane.
	// vPlaneDir: the specific dir of the plane.
	/************************************************************************/
	xbool	    CalculatePlaneWithLineIntersection(const XVECTOR3& vLineOriginPoint,
		const XVECTOR3& vLineDir,
		const XVECTOR3& vPlanePoint,
		const XVECTOR3& vPlaneDir, XVECTOR3& vResult);
	/************************************************************************/
	// To calculate the intersection point of two vectors. 
	// lineCrossPostion, to hold the scale position in these two lines.
	// bTestSegLineCrossOnly, to test whether these two lines are crossed or not only.
	// fTolerance, the tolerance of the calculation.
	// return, see the enum below.
	/************************************************************************/
	enum{MATH_SEG_COINCIDE, MATH_SEG_CROSS, MATH_SEG_PARALLEL};
	xint32      CalculateSegmentLineCross(
		XVECTOR3& out, 
		const LineSegment3& line1, 
		const LineSegment3& line2, 
		XVECTOR2* lineCrossPostion = NULL, 
		xbool bTestSegLineCrossOnly = xfalse,
		xfloat32 fTolerance = 0.000001f);

	//get cross point of the 4-edge shape.
	//return, XVECTOR2: the cross-points
	//line1:(l,t),(l+w,t)
	//line2:(l+w,t),(l+w,t+h)
	//line3:(l+w,t+h),(l,t+h)
	//line4:(l,t+h),(l,t)
	XArray<XVECTOR2> GetCrossPointOf2DEdge(const XVECTOR2& vLineOrigin, const XVECTOR2& vLineDir, xfloat32 l, xfloat32 t, xfloat32 w, xfloat32 h);

	/************************************************************************/
	//2D:Determine if the point is inside the convex  polygon
	//aPoints:the points in the convex polygon 
	/************************************************************************/	
	xbool	IsPointInConvexPolygon(const XArray<XVECTOR2>& aPoints,const XVECTOR2& vTarget);
	/************************************************************************/
	//Determine if the point is inside the triangle,default contains point on the edge
	//bContrainEdge:whether contains points on the edge
	/************************************************************************/
	xbool	IsPointInTriangle(const XVECTOR2& v1, const XVECTOR2& v2, const XVECTOR2& v3, const XVECTOR2& vTarget,xbool bContrainEdge = xtrue);

	/************************************************************************/
	// Barycentric Coordinates in 2D
	// p = a + m * (b - a) + n * (c - a) = (1 - m - n) * a + m * b + n * c
	// p is a point in triangle, and a,b,c is three points of triangle
	/************************************************************************/
	xbool   CalculateBarycentricCoord(XVECTOR2 vPos1,XVECTOR2 vPos2,XVECTOR2 vPos3,XVECTOR2 vP,xfloat32& nI,xfloat32& nJ,xfloat32& nK);
};

#endif


