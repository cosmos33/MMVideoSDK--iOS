/******************************************************************************

 @File         XCustomGeometry.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  

 @HISTORY:

******************************************************************************/

#ifndef _XCUSTOMGEOMETRY_H_
#define _XCUSTOMGEOMETRY_H_

#include "XTypes.h"
#include "XMath3D.h"
#include "XMemBase.h"
class XCusAABB;
class XCusOBB
{
public:

						XCusOBB() {}
						XCusOBB(const XCusOBB& CusObb);
	bool 				IsPointInOBB(const XVECTOR3& vPoint) const;
	void 				CompleteExtAxis();
	void 				Clear();
	void 				BuildOBB(const XCusOBB& CusObb1, const XCusOBB CusObb2);
	void 				BuildOBB(const XVECTOR3* pVertexPosition, int nVertCount);
	void 				BuildOBB(const XCusAABB& formAABB);
	void 				GetVertices(XVECTOR3* pVertexPosition, unsigned short* pIndices, bool bWire) const;
public:
	XVECTOR3	Center;
	XVECTOR3	XAxis;
	XVECTOR3	YAxis;
	XVECTOR3	ZAxis;
	XVECTOR3	ExtX;
	XVECTOR3	ExtY;
	XVECTOR3	ExtZ;
	XVECTOR3	Extents;
};
class XCusAABB 
{
public:
	XCusAABB() {}
	XCusAABB(const XCusAABB& aabb);
	XCusAABB(const XVECTOR3& vMins, const XVECTOR3& vMaxs);
	void 				Clear();
	void 				AddVertex(const XVECTOR3& v);
	void 				Build(const XCusOBB& obb);
	void 				Merge(const XCusAABB& subAABB);
	void 				CompleteMinsMaxs();
	void 				CompleteCenterExts();
	bool 				IsPointIn(const XVECTOR3& v) const;
	bool 				IsAABBIn(const XCusAABB& aabb) const;
	bool 				IsIntersect(const XCusAABB& aabb) const;
	void 				Build(const XVECTOR3* aVertPos, int iNumVert);
	void 				GetVertices(XVECTOR3* aVertPos, unsigned short* aIndices, bool bWire) const;
public:
	XVECTOR3	Center;
	XVECTOR3	Extents;
	XVECTOR3	Mins;
	XVECTOR3	Maxs;
};


class XCusPlane 
{
public:

	XCusPlane() {}
	XCusPlane(const XCusPlane& p);
	XCusPlane(const XVECTOR3& n, float d);
	bool 				CreatePlane(const XVECTOR3& v1, const XVECTOR3& v2, const XVECTOR3& v3);
public:
	XVECTOR3			vNormal;
	float				fDist;
};
class XCusSPlane : public XCusPlane
{
public:
	enum
	{
		TYPE_BAD		= -1,
		TYPE_PX			= 0,
		TYPE_PY			= 1,
		TYPE_PZ			= 2,
		TYPE_NX			= 3,
		TYPE_NY			= 4,
		TYPE_NZ			= 5,
		TYPE_MAJORX		= 6,
		TYPE_MAJORY		= 7,
		TYPE_MAJORZ		= 8,
		TYPE_UNKNOWN	= 9,
	};

	enum
	{
		SIGN_P	= 0,
		SIGN_NX	= 1,
		SIGN_NY = 2,
		SIGN_NZ = 4,
	};

public:

	XCusSPlane() {}
	XCusSPlane(const XCusSPlane& p);
	XCusSPlane(const XVECTOR3& n, float d);
	void 				MakeType();
	void 				MakeSignBits();
	void 				MakeTypeAndSignBits();
public:
	unsigned char	byType;
	unsigned char	bySignBits;
};

class XCusCapsule
{
public:
	XCusCapsule() {}
	XCusCapsule(const XCusCapsule& src);
public:
	bool IsPointIn(const XVECTOR3& vPos);
public:
	XVECTOR3	vCenter;
	XVECTOR3	vAxisX;
	XVECTOR3	vAxisY;
	XVECTOR3	vAxisZ;
	float		fHalfLen;
	float		fRadius;
};

class XCusCone
{
public:
	XVECTOR3	vPos;
	XVECTOR3	vAxisX;
	XVECTOR3	vAxisY;
	XVECTOR3	vAxisZ;
	float		fHeight;
	float		fRadius;
};

class XCusCylinder
{
public:

	XCusCylinder() {}
	XCusCylinder(const XCusCylinder& src);
public:
	bool IsPointIn(const XVECTOR3& vPos);
public:

	XVECTOR3	vCenter;
	XVECTOR3	vAxisX;
	XVECTOR3	vAxisY;
	XVECTOR3	vAxisZ;
	float		fHalfLen;
	float		fRadius;
};

class XCusSphere
{
public:
	XVECTOR3 vPos;
	xfloat32 fRadius;
};

#endif	//	_XCUSTOMGEOMETRY_H_
