/******************************************************************************

 @File         XCanvasBase.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XCanvasBase.

 @HISTORY:

******************************************************************************/
#ifndef _X_CANVAS_H_
#define _X_CANVAS_H_
#include "XObject.h"
#include "XBase3DTypes.h"
#include "XCustomGeometry.h"

class IXWorld;
class IXTexture;

class IXCanvasBase : public IXObject
{
public:
	virtual					~IXCanvasBase(){}
	
	virtual void			RegisterToScene(IXWorld* pScene) = 0;
	virtual IXPrimitiveBase*GetPrimitive() = 0;
	
	virtual xbool			Init() = 0;
	virtual void			Release() = 0;


	virtual void			DrawString(xint32 x, xint32 y, const xchar* szString, const XCOLORBASE& clr) = 0;
	virtual	void			DrawQuad(xint32 x, xint32 y, xint32 nWidth, xint32 nHeight, const XCOLORBASE& clr, xbool bSolid = xfalse, XMATRIX3 *pMat = NULL) = 0;
	virtual void			Render2DLine(xint32 xBegin, xint32 yBegin, xint32 xEnd, xint32 yEnd, const XCOLORBASE& clr, XMATRIX3 *pMat = NULL) = 0;

	/*
		绘制圆弧线或扇形线
		@param: bClockWise : 面向屏幕 xtrue: 顺时针 xflase : 逆时针
		@notice : 屏幕坐标，Y轴向下， X轴向左
	*/	
	virtual void			Render2DCircle(const XVECTOR2& vPos, xfloat32 fRadius, const XVECTOR2& vStartNormalizedDir,
		const XVECTOR2& vEndNormalizedDir, const XCOLORBASE& color, xbool bClockWise = xtrue, xbool bSolid = xfalse, XMATRIX3 *pMat = NULL) = 0;

	virtual void			RenderLine( const XVECTOR3& vBegin, const XVECTOR3& vEnd, const XCOLORBASE& clr, xbool bZEnabled = xtrue) = 0;
	virtual void			RenderLines(const XVECTOR3* aVerts, xint32 nNumVert, xint32* aIndices, xint32 nNumIndex, const XCOLORBASE& clr, 
										const XCOLORBASE* aColors = NULL, xint32 nNumColor = 0, xbool bZEnabled = xtrue) = 0;
	virtual void			RenderAABB( const XCusAABB& aabb, const XCOLORBASE& clr, xbool bSolid = xfalse, xbool bLight = xtrue, xbool bZEnabled = xtrue) = 0;
	virtual void			RenderSphere( const XVECTOR3 vPos, float fRadius, const XCOLORBASE& clr, xbool bSolid = xfalse, xbool bLight = xtrue, xbool bZEnabled = xtrue, const XMATRIX4* pMat = NULL) = 0;
	virtual void			RenderOBB( const XCusOBB& obb, const XCOLORBASE& clr, xbool bSolid = xfalse, xbool bLight = xtrue, xbool bZEnabled = xtrue, const XMATRIX4* pMat = NULL) = 0;
	virtual void			RenderBox( const XVECTOR3& vPos, const XVECTOR3& vDir, const XVECTOR3& vUp, 
										const XVECTOR3& vRight, const XVECTOR3& vExts, const XCOLORBASE& clr, xbool bSolid = xfalse, xbool bLight = xtrue, xbool bZEnabled = xtrue, const XMATRIX4* pMat = NULL) = 0;
	virtual void			RenderCone(const XCusCone& cone, const XCOLORBASE& clr, xbool bSolid = xfalse, xbool bLight = xtrue, xbool bZEnabled = xtrue, const XMATRIX4* pMat = NULL) = 0;
	virtual void			RenderCustomGeometry(const XVECTOR3* aVerts, xint32 nNumVert, xint32* aIndices, xint32 nNumIndex, const XCOLORBASE& clr, const XCOLORBASE* aColors = NULL, xint32 nNumColor = 0, 
												XVECTOR3* aNormals = NULL, xint32 nNumNormal = 0, xbool bLight = xtrue, xbool bZEnabled = xtrue) = 0;
	virtual void			RenderCustomGeometry(const XVECTOR3* aVerts, const XCOLORBASE* aColors, 
													const XVECTOR2* aTexcoords, xint32 nNumVert, 
													xint32* aIndices, xint32 nNumIndex,
													IXTexture* pTex, xbool bZEnabled = xtrue) = 0;
	virtual void			RenderCircle(const XVECTOR3& vPos, xfloat32 fRadius, const XVECTOR3& vStartNormalizedDir, const XVECTOR3& vEndNormalizedDir,
										const XVECTOR3& vNormalizedRotationAxis, const XCOLORBASE& color, xbool bSolid, xbool bZEnabled = xtrue, const XMATRIX4* pWorldMat = NULL) = 0;
}; 

extern IXCanvasBase* g_pXCanvasBase;

#endif//_X_CANVAS_H_