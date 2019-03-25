/******************************************************************************

 @File         XBase3DTypes.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  base data types

 @HISTORY:

******************************************************************************/

#ifndef _XBASE3DTYPES_H_
#define _XBASE3DTYPES_H_

#include "XSys.h"
#include "XTypes.h"
#include "XMath3D.h"
#include "XMemBase.h"


#define SERIALIZE_BINARY
typedef xuint32		XCOLOR;
class XVECTOR2;
class XVECTOR3;
class XVECTOR4;
class XMATRIX4;
class XCOLORBASE
{
public:

	XCOLORBASE();
	XCOLORBASE(XCOLOR srcColor);
	XCOLORBASE(const XCOLORBASE& srcColor);
	XCOLORBASE(xfloat32 fValue);
	XCOLORBASE(xfloat32 frValue, xfloat32 fgValue, xfloat32 fbValue, xfloat32 faValue);
public:
	void 				Set(xfloat32 frValue, xfloat32 fgValue, xfloat32 fbValue, xfloat32 faValue);
	XCOLOR 				ConvertToRGBAColor() const;
	void 				Clamp();
	void				ClampFloor();
	void				ClampRoof();

	//	重载 *=  += -=  =
	const XCOLORBASE& operator *= (xfloat32 srcColor);
	const XCOLORBASE& operator *= (const XCOLORBASE& srcColor);
	const XCOLORBASE& operator += (const XCOLORBASE& srcColor);
	const XCOLORBASE& operator -= (const XCOLORBASE& srcColor);
	const XCOLORBASE& operator = (const XCOLORBASE& srcColor);
	const XCOLORBASE& operator = (XCOLOR srcColor);

	// 友元函数 重载     * + - != ==
	friend XCOLORBASE operator * (const XCOLORBASE& clr, xfloat32 fColor){ return XCOLORBASE(clr.r * fColor, clr.g * fColor, clr.b * fColor, clr.a * fColor); }
	friend XCOLORBASE operator * (xfloat32 fColor, const XCOLORBASE& clr) { return XCOLORBASE(clr.r * fColor, clr.g * fColor, clr.b * fColor, clr.a * fColor); }
	friend XCOLORBASE operator * (const XCOLORBASE& clr1, const XCOLORBASE& clr2) { return XCOLORBASE(clr1.r * clr2.r, clr1.g * clr2.g, clr1.b * clr2.b, clr1.a * clr2.a); }
	friend XCOLORBASE operator + (const XCOLORBASE& clr1, const XCOLORBASE& clr2) { return XCOLORBASE(clr1.r + clr2.r, clr1.g + clr2.g, clr1.b + clr2.b, clr1.a + clr2.a); }
	friend XCOLORBASE operator - (const XCOLORBASE& clr1, const XCOLORBASE& clr2) { return XCOLORBASE(clr1.r - clr2.r, clr1.g - clr2.g, clr1.b - clr2.b, clr1.a - clr2.a); }
	friend bool operator != (const XCOLORBASE& clr1, const XCOLORBASE& clr2) { return (clr1.r != clr2.r || clr1.g != clr2.g || clr1.b != clr2.b || clr1.a != clr2.a); }
	friend bool operator == (const XCOLORBASE& clr1, const XCOLORBASE& clr2) { return (clr1.r == clr2.r && clr1.g == clr2.g && clr1.b == clr2.b && clr1.a == clr2.a); }

public:
	xfloat32 r, g, b, a;
};

class XHSVCOLORBASE
{
public:
	XHSVCOLORBASE();
	XHSVCOLORBASE(xfloat32 fColor);
	XHSVCOLORBASE(xfloat32 fhValue, xfloat32 fsValue, xfloat32 fvValue, xfloat32 faValue);
	xfloat32	h;
	xfloat32	s;
	xfloat32	v;
	xfloat32	a;
};

struct XVIEWPORTPARAMETER
{	
	xuint32		X;
	xuint32		Y;
	xuint32		nWidth;
	xuint32		nHeight;
	xfloat32	fMinZ;
	xfloat32	fMaxZ;
};


namespace XEngine
{
	extern const XVECTOR3	g_vXAxis;
	extern const XVECTOR3	g_vYAxis;
	extern const XVECTOR3	g_vZAxis;
	extern const XVECTOR3	g_vOrigin;
	extern const XMATRIX4	g_matrixIdentity;
}

const xfloat32  XENGINE_DEGREE = 180.0f;
const xfloat32  XENGINE_PI = 3.1415926535f;
const xfloat32  XENGINE_2PI = 6.2831853072f;

#define XENGINE_FLOATISZERO(x)	((x) > -1e-7f && (x) < 1e-7f)
#define XENGINE_RADIANTODEGREE(radian) ((radian) * XENGINE_DEGREE / XENGINE_PI)
#define XENGINE_DEGREETORADIAN(degree) ((degree) * XENGINE_PI / XENGINE_DEGREE)

//r g b a 值的大小必须是一个字节。
#define XCOLORBASERGBA(r, g, b, a) ((XCOLOR) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))
#define XCOLORBASERGB(r, g, b) ((XCOLOR) (0xff000000 | ((r) << 16) | ((g) << 8) | (b)))
#define XCOLORBASE_GETALPHAVALUE(color) ((unsigned char)(((color) & 0xff000000) >> 24))
#define XCOLORBASE_GETREDVALUE(color) ((unsigned char)(((color) & 0x00ff0000) >> 16))
#define XCOLORBASE_GETGREENVALUE(color) ((unsigned char)(((color) & 0x0000ff00) >> 8))
#define XCOLORBASE_GETBLUEVALUE(color) ((unsigned char)(((color) & 0x000000ff)))


//	释放 XEngine 抽象接口
#define XENGINE_INTERFACERELEASE(p) \
{ \
	if (p) \
					{ \
	(p)->Release(); \
	(p) = NULL; \
					} \
}

//	释放 XEngine 对象
#define XENGINE_RELEASE(p) \
{ \
	if (p) \
			{ \
		(p)->Release(); \
		delete (p); \
		(p) = NULL; \
			} \
}


//	删除 对象 数组
#define XENGINE_DELETEARRAY(p) \
{ \
	if (p) \
			{ \
		delete [] p; \
		p = NULL; \
			} \
}

//	删除 对象 .
#define XENGINE_DELETE(p) \
{ \
	if (p) \
					{ \
		delete p; \
		p = NULL; \
					} \
}


struct XBaseVertex
{
	XVECTOR3		Position;
	XVECTOR4		TangentX;
	XVECTOR4		TangentZ;
	XVECTOR2		TexCoord0;
	XVECTOR2		TexCoord1;
	XCOLOR			Color;
};
struct XSkinMeshVertex : public XBaseVertex
{
	XSkinMeshVertex();
	XSkinMeshVertex(const XSkinMeshVertex&rhs);
	XSkinMeshVertex& operator = (const XSkinMeshVertex& rhs);
	xuint8			BlendIndices[4];
	XVECTOR4		BlendWeights;
};
struct XBlendShapeMeshVertex
{
	XBlendShapeMeshVertex();
	XBlendShapeMeshVertex(const XVECTOR3& otherBShpPosition, const XVECTOR3& otherBShpTangentZ, const XVECTOR3& otherBShpTangentX);
	XVECTOR3		BShpPosition;
	XVECTOR3		BShpTangentZ;
	XVECTOR3		BShpTangentX;
};

#endif	//	_XBASE3DTYPES_H_
