#ifndef _X_BRUSH_H_
#define _X_BRUSH_H_

#include "XPrimitiveBase.h"
#include "XObject.h"
#include "XArray.h"
#include "XInternalResource.h"

class IXMaterialInstance;
class IXBrushPrimitive : public IXPrimitiveBase, public IXObject
{
public:
	typedef XArray<XVECTOR3>	XBrushShape;
	typedef XArray<XBrushShape> XBrushShapeGroup;

	// ShapeGroup中各顶点纹理坐标在U方向上的平铺方式(0-1)
	enum TEXCOORDMODE
	{
		TM_VERTEX,		// 在两个顶点平铺一次
		TM_SHAPE,		// 一个Shape平铺一次
		TM_SHAPEGROUP	// 一个ShapeGroup平铺一次
	};

	/**
	* 为画刷添加一个路径点
	*
	* @param vPoint 路径点的位置
	*/
	virtual void					AddPathPoint(const XVECTOR3& vPoint) = 0;

	/**
	* 获取路径点个数
	*
	* @return 路径点的个数
	*/
	virtual xint32					GetPathPointsNum() const = 0;

	/**
	* 根据索引获取路径点位置
	*
	* @param nIndex 路径点的索引
	* @param vPos	输出路径点的位置
	* @return 路径点不存在返回xfalse, 存在返回xtrue
	*/
	virtual xbool					GetPathPoint(xint32 nIndex, XVECTOR3& vPos) const = 0;

	/**
	* 获取当前路径
	*
	* @return 包含所有路径点的数组
	*/
	virtual const XArray<XVECTOR3>&	GetPath() const = 0;

	/**
	* 获取ShapeGroup
	*
	* @return ShapeGroup
	*/
	virtual const XBrushShapeGroup&	GetShapeGroup() const = 0;

	/**
	* 获取画刷的材质实例
	*
	* @return 画刷材质实例指针
	*/
	virtual IXMaterialInstance*		GetMaterialInstance() = 0;
};

class IXBrushManager : public XMemBase
{
public:	
	/**
	* 创建画刷的初始参数
	*
	* @param brushGroup		画刷形状组
	* @param szMtlPath		画刷材质路径
	* @param eTexcoordMode	画刷纹理模式
	*/
	struct BrushInitParam
	{
		BrushInitParam() : eTexcoordMode(IXBrushPrimitive::TM_SHAPEGROUP){}

		IXBrushPrimitive::XBrushShapeGroup	brushGroup;
		const xchar*						szMtlPath;
		IXBrushPrimitive::TEXCOORDMODE		eTexcoordMode;
	};

	/**
	* 创建一个画刷
	*
	* @param param	创建画刷的初始参数
	* @return		画刷指针, 如果创建失败, 返回NULL
	*/
	virtual IXBrushPrimitive*	CreateBrush(const BrushInitParam& param) = 0;

	/**
	* 设置/获取路径点之间的最小间隔
	*
	* @default	0.1
	*/
	virtual void				SetPathPointMinDistance(xfloat32 fDistance) = 0;
	virtual xfloat32			GetPathPointMinDistance() const = 0;
	
	/**
	* 设置/获取纹理的重复距离
	* 
	* @default	1.0
	* @min		0.1
	*/
	virtual void				SetTexcoordLoopDistance(xfloat32 fDistance) = 0;
	virtual xfloat32			GetTexcoordLoopDistance() const = 0;				
};

extern IXBrushManager* g_pBrushManager;



#endif
