/******************************************************************************

 @File         XGlobalFuncs.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description

 @HISTORY:

******************************************************************************/
#ifndef _XGLOBALFUNCS_H_
#define _XGLOBALFUNCS_H_

#include "XSys.h"
#include "XBase3DTypes.h"
#include "XCustomGeometry.h"
#include "XMemBase.h"
#include "XViewport.h"



xbool			XRT_RayToAABB3(const XVECTOR3& vStart, const XVECTOR3& vDelta, const XVECTOR3& vMins, const XVECTOR3& vMaxs, XVECTOR3& vPoint, float* pfFraction, XVECTOR3& vNormal);
xint32			XRT_PlaneAABBOverlap(const XVECTOR3& vNormal, xfloat32 fDist, const XVECTOR3& vOrigin, const XVECTOR3& vExtents);
xint32 			XRT_PlaneAABBOverlap(const XCusSPlane& Plane, const XVECTOR3& _vMins, const XVECTOR3& _vMaxs);
xint32 			XRT_PlaneSphereOverlap(const XCusSPlane& Plane, const XVECTOR3& vCenter, xfloat32 fRadius);
xint32 			XRT_PlaneSphereOverlap(XVECTOR3& vNormal, xfloat32 fDist, XVECTOR3& vCenter, xfloat32 fRadius);

xfloat32 		XG_InvSqrt(xfloat32 v);
xfloat32 		XG_SquareMagnitude(const XVECTOR3& v);
xfloat32 		XG_Magnitude(const XVECTOR3& v);
xfloat32 		XG_MagnitudeH(const XVECTOR3& v);
XVECTOR3 		XG_Vector423(const XVECTOR4& v);
XVECTOR2 		XG_Normalize(const XVECTOR2& v);
XVECTOR3 		XG_Normalize(const XVECTOR3& v);
unsigned char 	XG_CompressDirH(xfloat32 x, xfloat32 z);
XVECTOR3 		XG_DecompressDirH(unsigned char byDir);
void 			XG_CompressDir(const XVECTOR3& v, unsigned char& b1, unsigned char& b2);
XVECTOR3 		XG_DecompressDir(unsigned char b1, unsigned char b2);
XVECTOR3 		XG_VecMin(const XVECTOR3& v1, const XVECTOR3& v2);
XVECTOR3 		XG_VecMax(const XVECTOR3& v1, const XVECTOR3& v2);
XVECTOR3 		XG_ViewToWorld(const XVECTOR3& vIn, XMATRIX4& matView);
XMATRIX3 		XG_IdentityMatrix3();
XMATRIX3 		XG_TransformMatrix3(xfloat32 fRad, const XVECTOR2& vecPos, const XVECTOR2 &vecScale = XVECTOR2(1.0f, 1.0f));
XMATRIX3 		XG_TransformMatrix3(const XVECTOR2& vecXDir, const XVECTOR2& vecPos, const XVECTOR2 &vecScale = XVECTOR2(1.0f,1.0f));
XMATRIX4 		XG_IdentityMatrix();
XMATRIX4 		XG_ZeroMatrix();
XMATRIX4 		XG_ViewMatrix(const XVECTOR3& from, const XVECTOR3& dir, const XVECTOR3& vecUp, xfloat32 roll);
XMATRIX4 		XG_LookAtMatrix(const XVECTOR3& from, const XVECTOR3& to, const XVECTOR3& vecUp, xfloat32 roll);
XMATRIX4 		XG_TransformMatrix(const XVECTOR3& vecDir, const XVECTOR3& vecUp, const XVECTOR3& vecPos);
XMATRIX4 		XG_RotateX(xfloat32 vRad);
XMATRIX4 		XG_RotateX(const XMATRIX4& mat, xfloat32 vRad);
XMATRIX4 		XG_RotateY(xfloat32 vRad);
XMATRIX4 		XG_RotateY(const XMATRIX4& mat, xfloat32 vRad);
XMATRIX4 		XG_RotateZ(xfloat32 vRad);
XMATRIX4 		XG_RotateZ(const XMATRIX4& mat, xfloat32 vRad);
XMATRIX4 		XG_RotateAxis(const XVECTOR3& vecAxis, xfloat32 vRad);
XMATRIX4 		XG_RotateAxis(const XVECTOR3& vecPos, const XVECTOR3& vecAxis, xfloat32 vRad);
XMATRIX4		XG_RotateEuler(xfloat32 xRad, xfloat32 yRad, xfloat32 zRad); // result = RotX * RotY * RotZ
XVECTOR3 		XG_RotatePosAroundX(const XVECTOR3& vPos, xfloat32 fRad);
XVECTOR3 		XG_RotatePosAroundY(const XVECTOR3& vPos, xfloat32 fRad);
XVECTOR3 		XG_RotatePosAroundZ(const XVECTOR3& vPos, xfloat32 fRad);
XVECTOR3 		XG_RotatePosAroundAxis(const XVECTOR3& vPos, const XVECTOR3& vAxis, xfloat32 fRad);
XVECTOR3 		XG_RotatePosAroundLine(const XVECTOR3& vPos, const XVECTOR3& vOrigin, const XVECTOR3& vDir, xfloat32 fRad);
XVECTOR3 		XG_RotateVecAroundLine(const XVECTOR3& v, const XVECTOR3& vOrigin, const XVECTOR3& vDir, xfloat32 fRad);
XMATRIX4 		XG_Scaling(xfloat32 sx, xfloat32 sy, xfloat32 sz);
XMATRIX4 		XG_Scaling(const XMATRIX4& mat, xfloat32 sx, xfloat32 sy, xfloat32 sz);
XMATRIX4 		XG_ScalingRelative(const XMATRIX4& matRoot, xfloat32 sx, xfloat32 sy, xfloat32 sz);
XMATRIX4 		XG_Translate(xfloat32 x, xfloat32 y, xfloat32 z);
XMATRIX4 		XG_ScaleAlongAxis(const XVECTOR3& vAxis, xfloat32 fScale);
XMATRIX4 		XG_Transpose(const XMATRIX4& mat);
void 			XG_Transpose(const XMATRIX4& matIn, XMATRIX4* pmatOut);
void 			XG_DecomposeMatrix(const XMATRIX4& mat, XVECTOR3& scale, XQUATERNION& orient, XVECTOR3& pos);
void			XG_DecomposeStrechedMatrixDiscardScale(const XMATRIX4& mat, XQUATERNION& rotate, XVECTOR3& pos, xfloat32& sign);
xbool 			XG_GetCubeMapDirAndUp(xint32 nFaceIndex, XVECTOR3 * pDir, XVECTOR3 * pUp);
XCOLOR 			XG_ColorValueToColorRGBA(XCOLORBASE colorValue);
XCOLORBASE 		XG_ColorRGBAToColorValue(XCOLOR colorRGBA);
XMATRIX4 		XG_MirrorMatrix(const XVECTOR3 &p, const XVECTOR3 &n);
XMATRIX4 		XG_InverseTM(const XMATRIX4& mat);
void 			XG_InverseTM(const XMATRIX4& matIn, XMATRIX4* pmatOut);
XMATRIX4 		XG_InverseMatrix(const XMATRIX4& mat);
void 			XG_InverseMatrix(const XMATRIX4& matIn, XMATRIX4* pmatOut);
XMATRIX4 		XG_InverseAffineMatrix(const XMATRIX4& mat);
void 			XG_InverseAffineMatrix(const XMATRIX4& matIn, XMATRIX4* pmatOut);
XMATRIX4 		XG_OrthoMatrix(xfloat32 fWidth, xfloat32 fHeight, xfloat32 fZNear, xfloat32 fZFar);
XMATRIX4 		XG_OrthoOffCenterMatrix(xfloat32 fLeft, xfloat32 fRight, xfloat32 fBottom, xfloat32 fTop, xfloat32 fZNear, xfloat32 fZFar);
XMATRIX4 		XG_PerspectiveMatrix(xfloat32 fWidth, xfloat32 fHeight, xfloat32 fZNear, xfloat32 fZFar);
XMATRIX4 		XG_PerspectiveFovMatrix(xfloat32 fFovY, xfloat32 fAspect, xfloat32 fZNear, xfloat32 fZFar);
XMATRIX4 		XG_PerspectiveOffCenterMatrix(xfloat32 fLeft, xfloat32 fRight, xfloat32 fBottom, xfloat32 fTop, xfloat32 fZNear, xfloat32 fZFar);
XMATRIX4 		XG_OrthoMatrixRH(xfloat32 fWidth, xfloat32 fHeight, xfloat32 fZNear, xfloat32 fZFar);
XMATRIX4 		XG_OrthoOffCenterMatrixRH(xfloat32 fLeft, xfloat32 fRight, xfloat32 fBottom, xfloat32 fTop, xfloat32 fZNear, xfloat32 fZFar);
XMATRIX4 		XG_PerspectiveMatrixRH(xfloat32 fWidth, xfloat32 fHeight, xfloat32 fZNear, xfloat32 fZFar);
XMATRIX4 		XG_PerspectiveFovMatrixRH(xfloat32 fFovY, xfloat32 fAspect, xfloat32 fZNear, xfloat32 fZFar);
XMATRIX4 		XG_PerspectiveOffCenterMatrixRH(xfloat32 fLeft, xfloat32 fRight, xfloat32 fBottom, xfloat32 fTop, xfloat32 fZNear, xfloat32 fZFar);
void 			XG_ClearAABB(XVECTOR3& vMins, XVECTOR3& vMaxs);
void 			XG_AddVertexToAABB(XVECTOR3& vMins, XVECTOR3& vMaxs, XVECTOR3& vPoint);
void 			XG_ExpandAABB(XVECTOR3& vecMins, XVECTOR3& vecMaxs, const XCusOBB& obb);
void 			XG_ExpandAABB(XVECTOR3& vecMins, XVECTOR3& vecMaxs, const XCusAABB& subAABB);
void 			XG_BuildAABB(XCusAABB* pAABB, const XCusOBB& obb);
void 			XG_MergeAABB(XCusAABB* pAABB, const XCusAABB& subAABB);
void 			XG_CompleteAABB(XCusAABB* pAABB);
void 			XG_CompleteOBB(XCusOBB* pOBB);
XVECTOR3 		XG_RandDirH();
void 			XG_HSVToRGB(XHSVCOLORBASE& hsvColor, XCOLOR * pRgbColor);
void 			XG_RGBToHSV(XCOLOR rgbColor, XHSVCOLORBASE * pHsvColor);
void 			XG_RGBToHSL(xfloat32 r, xfloat32 g, xfloat32 b, xfloat32&  h, xfloat32& s, xfloat32& l);
void 			XG_DecompressColor(XCOLOR rgbColor, unsigned char * pR, unsigned char * pG, unsigned char * pB, unsigned char *pA = NULL);
XMATRIX3 		XG_Matrix3Rotate(xfloat32 fRad);
XMATRIX3 		XG_Matrix3Rotate(const XMATRIX3& mat, xfloat32 fRad);
XMATRIX3 		XG_Matrix3Translate(xfloat32 x, xfloat32 y);
XMATRIX3 		XG_Matrix3Translate(const XMATRIX3& mat, xfloat32 x, xfloat32 y);
XVECTOR3 		XG_VectorMatrix3x3(const XVECTOR3& v, const XMATRIX4& mat);
xfloat32 		XG_DistSquareToAABB(const XVECTOR3& vPos, const XCusAABB& aabb);
XCusAABB 		XG_TransformAABB(const XCusAABB& aabb, const XMATRIX4& mat);
xbool			XG_RayToTriangle(const XVECTOR3& vStart, const XVECTOR3& vDelta, const XVECTOR3& v0, const XVECTOR3& v1, const XVECTOR3& v2, XVECTOR3& vPoint, xbool bTwoSides, float* pfFraction);
//xbool 		XG_RayIntersectTriangle(const XVECTOR3& vecStart, const XVECTOR3& vecDelta, XVECTOR3 * pTriVerts, xfloat32 * pvFraction, XVECTOR3 * pVecPos);
XMATRIX4		TransformMatrix(const XQUATERNION& qRotation, const XVECTOR3& vTranslation, const XVECTOR3& vScaling);
void			XG_CastRay(XViewport* pViewport, const XVECTOR3& vecScreenPoint, XVECTOR3& vecStart, XVECTOR3& vecDir);
inline XVECTOR3	XG_NormalizedCrossProduct(const XVECTOR3& vec1, const XVECTOR3& vec2) { return XG_Normalize(CrossProduct(vec1, vec2)); }
inline xbool	XG_IsZeroLength(const XVECTOR3& vecIn) { return XG_Normalize(vecIn).IsZero(); }
xfloat32		XG_PointToLineDistance(const XVECTOR3& vecPoint, const XVECTOR3& vecLinePoint, const XVECTOR3& vecLineDirection, xfloat32* pFraction = NULL);
xfloat32		XG_LineLineDistance(const XVECTOR3& vecPoint0, const XVECTOR3& vecDir0, const XVECTOR3& vecPoint1, const XVECTOR3& vecDir1, xfloat32 pFractions[2] = NULL);
XVECTOR3		XG_LinePlaneIntersection(const XVECTOR3& vecLinePoint, const XVECTOR3& vecLineDir, const XVECTOR3& vecPlanePoint, const XVECTOR3& vecPlaneNormal);
XVECTOR3		XG_LineSphereIntersection(const XVECTOR3& vecLinePoint, const XVECTOR3& vecLineDir, const XVECTOR3& vecSphereCenter, xfloat32 fRadius);


xbool 			X_Equals(xfloat32 a, xfloat32 b, xfloat32 eps);
xbool 			X_Equals(xfloat64 a, xfloat64 b, xfloat64 eps);
xbool			X_IsPowerOfTwo(xuint32 x);
xuint32			X_CeilPowerOfTwo(xuint32 x);
xuint32			X_FloorPowerOfTwo(xuint32 x);

template <class T>
inline void X_Swap(T& lhs, T& rhs)
{
	T tmp;
	tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}
template <class T>
const T&		X_Min(const T& x, const T& y){ return y < x ? y : x; }
template <class T>
const T&		X_Max(const T& x, const T& y){ return y < x ? x : y; }
template <class T>
const T&		X_Min(const T& x, const T& y, const T& z){ return X_Min(X_Min(x, y), z); }
template <class T>
const T&		X_Max(const T& x, const T& y, const T& z){ return X_Max(X_Max(x, y), z); }
template <class T>
T X_ClampRet(const T& x, const T& min, const T& max)
{
	return x < min ? min : x < max ? x : max;
}
template <class T>
void X_Clamp(T& x, const T& min, const T& max)
{
	if (x < min) x = min;
	if (x > max) x = max;
}
template <class T>
void X_ClampRoof(T& x, const T& max)
{
	if (x > max) x = max;
}
template <class T>
void X_ClampFloor(T& x, const T& min)
{
	if (x < min) x = min;
}
template <typename T>
T Lerp(const T& lvalue, const T& rvalue, xfloat32 fFactor)
{
	return lvalue + (rvalue - lvalue) * fFactor;
}
template <typename T>
T Fraction(T fLeft, T fRight, T fValue)
{
	return (fValue - fLeft) / (fRight - fLeft);
}

void		X_Srand_Time();
void		X_Srand_(xuint32 seed);
xint32		X_Rand_(void);
xfloat32	X_Random_0_to_1();
xint32		X_RandInt(xint32 lower, xint32 upper);
xfloat32	X_RandFloat(xfloat32 lower, xfloat32 upper);

#endif	//	_XGLOBALFUNCS_H_
