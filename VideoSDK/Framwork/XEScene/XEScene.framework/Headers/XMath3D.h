/******************************************************************************

 @File         XMath3D.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description   XMath3D 

 @HISTORY:

******************************************************************************/

#ifndef _XMATH3D_H_
#define _XMATH3D_H_

#include "XSys.h"
#include "XMemBase.h"

class XVECTOR2
{
public:
	explicit XVECTOR2();
	XVECTOR2(xfloat32 fValue);
	XVECTOR2(xfloat32 fx, xfloat32 fy);
	XVECTOR2(const XVECTOR2& vRhs);
public:
	union
	{
		struct
		{
			xfloat32 x, y;
		};

		xfloat32 m[2];
	};

public:
	xfloat32 								Normalize();
	void 									Set(xfloat32 fx, xfloat32 fy);
	void 									Clear();
	bool 									IsZero() const;
	bool 									IsEquals(const XVECTOR2 & vec, xfloat32 fEpsilon) const;
	xfloat32 								Magnitude() const;
	xfloat32 								SquaredMagnitude() const;
	xfloat32 								MinMemberValue() const;
	xfloat32 								MaxMemberValue() const;
	void 									Snap();
	friend xfloat32 						DotProduct(const XVECTOR2& vec1, const XVECTOR2& vec2);
	friend xfloat32 						Normalize(const XVECTOR2& vecIn, XVECTOR2& vecOut);
	friend xfloat32							CrossProduct(const XVECTOR2& vec1, const XVECTOR2& vec2);
	friend XVECTOR2 						LerpVec(const XVECTOR2& vec1, const XVECTOR2& vec2, xfloat32 fFraction);
	const XVECTOR2& 						operator += (const XVECTOR2& vec);
	const XVECTOR2& 						operator -= (const XVECTOR2& vec);
	const XVECTOR2& 						operator *= (xfloat32 fvalue);
	const XVECTOR2& 						operator /= (xfloat32 fvalue);
	const XVECTOR2& 						operator = (const XVECTOR2& vec);
	XVECTOR2 								operator + () const;
	XVECTOR2 								operator - () const;
	friend XVECTOR2							operator + (const XVECTOR2& vec1, const XVECTOR2& vec2);
	friend XVECTOR2 						operator - (const XVECTOR2& vec1, const XVECTOR2& vec2);
	friend XVECTOR2 						operator * (const XVECTOR2& vec, xfloat32 fvalue);
	friend XVECTOR2 						operator * (xfloat32 fvalue, const XVECTOR2& vec);
	friend XVECTOR2 						operator * (const XVECTOR2& vec, int fvalue);
	friend XVECTOR2 						operator * (int fvalue, const XVECTOR2& vec);
	friend XVECTOR2 						operator * (const XVECTOR2& vec1, const XVECTOR2& vec2);
	friend XVECTOR2 						operator / (const XVECTOR2& vec, xfloat32 fvalue);
	friend XVECTOR2 						operator / (const XVECTOR2& vec, int fvalue);
	friend XVECTOR2 						operator / (const XVECTOR2& vec1, const XVECTOR2& vec2);
	friend bool 							operator == (const XVECTOR2& vec1, const XVECTOR2& vec2);
	friend bool 							operator != (const XVECTOR2& vec1, const XVECTOR2& vec2);
};

class XVECTOR3
{
public:
	XVECTOR3();
	XVECTOR3(xfloat32 m);
	XVECTOR3(xfloat32 x, xfloat32 y, xfloat32 z);
	XVECTOR3(const XVECTOR3& v);

public:
	union
	{
		struct
		{
			xfloat32 x, y, z;
		};

		xfloat32 m[3];
	};

public:
	xfloat32 								Normalize();
	void 									Set(xfloat32 _x, xfloat32 _y, xfloat32 _z);
	void 									Clear();
	bool 									IsZero() const;
	bool 									IsEquals(const XVECTOR3 & v, xfloat32 epsilon) const;
	xfloat32 								Magnitude() const;
	xfloat32 								MagnitudeH() const;
	xfloat32 								SquaredMagnitude() const;
	xfloat32 								SquaredMagnitudeH() const;
	xfloat32 								MinMember() const;
	xfloat32 								MaxMember() const;
	void 									Snap();
	void 									CrossProduct(const XVECTOR3& v1, const XVECTOR3& v2);
	friend xfloat32 						DotProduct(const XVECTOR3& v1, const XVECTOR3& v2);
	friend XVECTOR3 						CrossProduct(const XVECTOR3& v1, const XVECTOR3& v2);
	friend xfloat32 						Normalize(const XVECTOR3& vIn, XVECTOR3& vOut);
	friend XVECTOR3 						LERPVec(const XVECTOR3& v1, const XVECTOR3& v2, xfloat32 fraction);
	friend XVECTOR3 						operator + (const XVECTOR3& v1, const XVECTOR3& v2);
	friend XVECTOR3 						operator - (const XVECTOR3& v1, const XVECTOR3& v2);
	friend XVECTOR3 						operator * (const XVECTOR3& v, xfloat32 f);
	friend XVECTOR3 						operator * (xfloat32 f, const XVECTOR3& v);
	friend XVECTOR3 						operator * (const XVECTOR3& v, int f);
	friend XVECTOR3 						operator * (int f, const XVECTOR3& v);
	friend XVECTOR3 						operator * (const XVECTOR3& v1, const XVECTOR3& v2);
	friend XVECTOR3 						operator / (const XVECTOR3& v, xfloat32 f);
	friend XVECTOR3 						operator / (const XVECTOR3& v, int f);
	friend XVECTOR3 						operator / (const XVECTOR3& v1, const XVECTOR3& v2);
	friend bool 							operator == (const XVECTOR3& v1, const XVECTOR3& v2);
	friend bool 							operator != (const XVECTOR3& v1, const XVECTOR3& v2);
	const XVECTOR3& 						operator += (const XVECTOR3& v);
	const XVECTOR3& 						operator -= (const XVECTOR3& v);
	const XVECTOR3& 						operator *= (xfloat32 f);
	const XVECTOR3& 						operator /= (xfloat32 f);
	const XVECTOR3& 						operator = (const XVECTOR3& v);
	XVECTOR3 								operator + () const;
	XVECTOR3 								operator - () const;
};

xfloat32 DotProduct(const XVECTOR3& v1, const XVECTOR3& v2);


class XVECTOR4
{
public:
	union
	{
		struct
		{
			xfloat32 x, y, z, w;
		};

		xfloat32 m[4];
	};

public:
										XVECTOR4();
										XVECTOR4(xfloat32 _x, xfloat32 _y, xfloat32 _z, xfloat32 _w);
										explicit XVECTOR4(xfloat32 f);
										XVECTOR4(const xfloat32 f[4]);
										XVECTOR4(const XVECTOR4& v);
										XVECTOR4(const XVECTOR3& v);
	const XVECTOR4&						operator = (const XVECTOR4& v);
	const XVECTOR4&						operator = (const XVECTOR3& v);
	void 								Set(xfloat32 _x, xfloat32 _y, xfloat32 _z, xfloat32 _w);
	void 								Clear();
	bool 								IsEquals(const XVECTOR4 & v, xfloat32 epsilon) const;
};

xfloat32 								DotProduct(const XVECTOR2& v1, const XVECTOR2& v2);
xfloat32 								DotProduct(xfloat32 v1, xfloat32 v2);


class XMATRIX3
{
public:
	enum CONSTRUCT
	{
		IDENTITY = 0,
		CLEARED,
	};

public:
								XMATRIX3();
								XMATRIX3(CONSTRUCT c);
								XMATRIX3(const xfloat32 arr[3][3]);
								XMATRIX3(const XMATRIX3& rkMatrix);
								XMATRIX3(xfloat32 fEntry00, xfloat32 fEntry01, xfloat32 fEntry02,
										xfloat32 fEntry10, xfloat32 fEntry11, xfloat32 fEntry12,
										xfloat32 fEntry20, xfloat32 fEntry21, xfloat32 fEntry22);
	XVECTOR3					GetRow(int i) const;
	XVECTOR3					GetCol(int i) const;
	void						Transpose();
	void						Clear();
	void						Identity();
	void						Translate(xfloat32 x, xfloat32 y);
	void						Rotate(xfloat32 fRad);
	void						InverseTM();
	XMATRIX3&					operator *= (const XMATRIX3& mat);
	friend XVECTOR2				operator * (const XVECTOR2& v, const XMATRIX3& mat);
	friend XVECTOR2				operator * (const XMATRIX3& mat, const XVECTOR2& v);
	friend XVECTOR3				operator * (const XVECTOR3& v, const XMATRIX3& mat);
	friend XVECTOR3				operator * (const XMATRIX3& mat, const XVECTOR3& v);
	friend XMATRIX3				operator * (const XMATRIX3& mat1, const XMATRIX3& mat2);
public:
	union
	{
		struct
		{
			xfloat32 _11, _12, _13;
			xfloat32 _21, _22, _23;
			xfloat32 _31, _32, _33;
		};

		xfloat32 m[3][3];
	};
};


class XMATRIX4
{
public:
	enum CONSTRUCT
	{
		IDENTITY = 0,
	};
	union
	{
		struct
		{
			xfloat32	_11, _12, _13, _14;
			xfloat32	_21, _22, _23, _24;
			xfloat32	_31, _32, _33, _34;
			xfloat32	_41, _42, _43, _44;
		};

		xfloat32 m[4][4];
	};

public:
								XMATRIX4();
								XMATRIX4(xfloat32* v);
								XMATRIX4(const XMATRIX4& mat);
								XMATRIX4(CONSTRUCT c);
								XMATRIX4(xfloat32 fEntry00, xfloat32 fEntry01, xfloat32 fEntry02, xfloat32 fEntry03,
									xfloat32 fEntry10, xfloat32 fEntry11, xfloat32 fEntry12, xfloat32 fEntry13,
									xfloat32 fEntry20, xfloat32 fEntry21, xfloat32 fEntry22, xfloat32 fEntry23,
									xfloat32 fEntry30, xfloat32 fEntry31, xfloat32 fEntry32, xfloat32 fEntry33);
	void						Clear();
	void						Identity();
	void						Transpose();
	XMATRIX4					GetTranspose() const;
	void						Inverse();
	XMATRIX4					GetInverse() const;
	void						InverseTM();
	XMATRIX4					GetInverseTM() const;
	xfloat32					Determinant() const;
	void						Translate(xfloat32 x, xfloat32 y, xfloat32 z);
	void						RotateX(xfloat32 fRad);
	void						RotateY(xfloat32 fRad);
	void						RotateZ(xfloat32 fRad);
	void						RotateAxis(const XVECTOR3& v, xfloat32 fRad);
	void						RotateAxis(const XVECTOR3& vPos, const XVECTOR3& vAxis, xfloat32 fRad);
	void						Scale(xfloat32 sx, xfloat32 sy, xfloat32 sz);
	void						SetRotatePart(const XMATRIX3& mat);
	XMATRIX3					GetRotatePart() const;
	void						SetTransPart(const XVECTOR3& vTrans);
	XVECTOR3					GetTransPart() const;
	XVECTOR3					GetRow(int i) const;
	XVECTOR3					GetCol(int i) const;
	void						SetRow(int i, const XVECTOR3& v);
	void						SetCol(int i, const XVECTOR3& v);
	
	// 直接相乘
	XVECTOR3					MulVec(const XVECTOR3& v) const;
	// 与operator *实现同样的功能，之后版本应该把operator *的功能改为矩阵的直接相乘
	XVECTOR3					TransformCoord(const XVECTOR3& v) const;
	void						TransformCoord(const XVECTOR3& inV, XVECTOR3& outV) const;
	//	* operator
	// 特别注意 vector3 * matrix4 在引擎中被当作Vec3TransformCoord 处理
	// 并不是普通的向量与矩阵乘法
	// 未来将修正此做法
	friend XVECTOR3				operator * (const XVECTOR3& v, const XMATRIX4& mat);
	friend XVECTOR3				operator * (const XMATRIX4& mat, const XVECTOR3& v);
	friend XVECTOR4				operator * (const XVECTOR4& v, const XMATRIX4& mat);
	friend XVECTOR4				operator * (const XMATRIX4& mat, const XVECTOR4& v);
	friend XMATRIX4 			operator * (const XMATRIX4& mat1, const XMATRIX4& mat2);
	friend XMATRIX4 			operator * (const XMATRIX4& mat, xfloat32 s);
	friend XMATRIX4 			operator * (xfloat32 s, const XMATRIX4& mat);
	friend XMATRIX4 			operator / (const XMATRIX4& mat, xfloat32 s);
	XMATRIX4& 					operator *= (const XMATRIX4& mat);
	XMATRIX4& 					operator *= (xfloat32 s);
	XMATRIX4& 					operator /= (xfloat32 s);
	friend bool 				operator == (const XMATRIX4& mat1, const XMATRIX4& mat2);
	friend bool 				operator != (const XMATRIX4& mat1, const XMATRIX4& mat2);
	friend XMATRIX4 			operator + (const XMATRIX4& mat1, const XMATRIX4& mat2);
	friend XMATRIX4 			operator - (const XMATRIX4& mat1, const XMATRIX4& mat2);
	XMATRIX4& 					operator += (const XMATRIX4& mat);
	XMATRIX4& 					operator -= (const XMATRIX4& mat);
protected:
	xfloat32					Det3x3(xfloat32 a11, xfloat32 a12, xfloat32 a13, xfloat32 a21, xfloat32 a22, xfloat32 a23, xfloat32 a31, xfloat32 a32, xfloat32 a33) const;
};

class XQUATERNION
{
public:
	union
	{
		struct
		{
			xfloat32 x, y, z, w;
		};
		xfloat32 m[4];
	};
public:
							XQUATERNION();

	/* construct a quaternion with a rotating matrix */
							XQUATERNION(const XMATRIX4& mat);
							XQUATERNION(const XVECTOR3& vAxis, xfloat32 fAngle);
							XQUATERNION(xfloat32 fXAngle, xfloat32 fYAngle, xfloat32 fZAngle);
							XQUATERNION(xfloat32 fw, xfloat32 fx, xfloat32 fy, xfloat32 fz);
							XQUATERNION(xfloat32 fw, const XVECTOR3& fv);
	void					ConvToMatrix(XMATRIX4& mat) const;
	void					ConvFromMatrix(const XMATRIX4& mat);
	void					ConvToEulerAngle(xfloat32& fXAngle, xfloat32& fYAngle, xfloat32& fZAngle) const;
	void					ConvFromEulerAngle(xfloat32 fXAngle, xfloat32 fYAngle, xfloat32 fZAngle);
	void					ConvertToAxisAngle(XVECTOR3& vAxis, xfloat32& fAngle) const;
	void					ConvertFromAxisAngle(const XVECTOR3& vAxis, xfloat32 fAngle);
	void					Clear();
	void					Set(xfloat32 fx, xfloat32 fy, xfloat32 fz, xfloat32 fw);
	xfloat32				Norm() const;
	const XQUATERNION&		Normalize();
	const XQUATERNION&		Conjugate();
	const XQUATERNION&		Inverse();
	const XQUATERNION&		operator + () const;
	XQUATERNION				operator-() const;
	friend XQUATERNION		operator + (const XQUATERNION& q1, const XQUATERNION& q2);
	friend XQUATERNION		operator - (const XQUATERNION& q1, const XQUATERNION& q2);
	friend XQUATERNION		operator * (const XQUATERNION& q, xfloat32 fValue);
	friend XQUATERNION		operator * (xfloat32 fValue, const XQUATERNION& q);
	friend XQUATERNION		operator * (const XQUATERNION& q, int nValue);
	friend XQUATERNION		operator * (int nValue, const XQUATERNION& q);
	friend bool				operator == (const XQUATERNION& q1, const XQUATERNION& q2);
	friend bool				operator != (const XQUATERNION& q1, const XQUATERNION& q2);
	friend XQUATERNION		operator / (const XQUATERNION& q, xfloat32 fValue);
	friend XQUATERNION		operator / (const XQUATERNION& q, int nValue);
	friend XQUATERNION		operator * (const XQUATERNION& q1, const XQUATERNION& q2);
	friend XVECTOR3			operator * (const XQUATERNION& q, const XVECTOR3& v);
	friend XVECTOR3			operator ^ (const XQUATERNION& q, const XVECTOR3& v);
	friend XQUATERNION		Normalize(const XQUATERNION& q);
	friend XQUATERNION		Conjugate(const XQUATERNION& q);
	friend XQUATERNION		Inverse(const XQUATERNION& q);
	friend xfloat32			DotProduct(const XQUATERNION& q1, const XQUATERNION& q2);
	friend void				QuaternionToMatrix(const XQUATERNION& q, XMATRIX4& mat);
	friend void				MatrixToQuaternion(const XMATRIX4& mat, XQUATERNION& q);
	friend bool				QuaternionToEulerAngle(const XQUATERNION& q, xfloat32& fXAngle, xfloat32& fYAngle, xfloat32& fZAngle);
	friend void				EulerAngleToQuaternion(xfloat32 fXAngle, xfloat32 fYAngle, xfloat32 fZAngle, XQUATERNION& q);
	friend void				QuaternionToAxisAngle(const XQUATERNION& q, XVECTOR3& vAxis, xfloat32& fAngle);
	friend void				AxisAngleToQuaternion(const XVECTOR3& vAxis, xfloat32 fAngle, XQUATERNION& q);
	friend void				QuaternionToEulerAngle_Continuous(const XQUATERNION& quTarget, xfloat32 fRefX, xfloat32 fRefY, xfloat32 fRefZ, xfloat32& fOutX, xfloat32& fOutY, xfloat32& fOutZ);
	friend void				EulerToEuler_Continuous(xfloat32& fInOutX, xfloat32& fInOutY, xfloat32& fInOutZ, xfloat32 fRefX, xfloat32 fRefY, xfloat32 fRefZ);
	friend XQUATERNION		SlerpQuaternion(const XQUATERNION& q1, const XQUATERNION& q2, xfloat32 fraction);
	// 球面插值
	friend XQUATERNION		Slerp(const XQUATERNION& q1, const XQUATERNION& q2, xfloat32 fFactor);
	// 归一化插值
	friend XQUATERNION		Nlerp(const XQUATERNION& q1, const XQUATERNION& q2, xfloat32 fFactor);
	friend XQUATERNION		NlerpNoShortestPath(const XQUATERNION& q1, const XQUATERNION& q2, xfloat32 fFactor);
	friend xfloat32			QuaternionDiffAngle(const XQUATERNION& q1, const XQUATERNION& q2);
	static XQUATERNION		Identity();
	static XQUATERNION		RotationFromTo(const XVECTOR3 & vSrc, const XVECTOR3 & vTo);
};
#endif	//	_XMATH3D_H_
