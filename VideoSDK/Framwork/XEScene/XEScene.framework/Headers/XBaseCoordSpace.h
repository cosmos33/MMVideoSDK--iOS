/******************************************************************************

 @File         XBaseCoordSpace.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XBaseCoordSpace.

 @HISTORY:

******************************************************************************/

#ifndef _XBASECOORDSPACE_H_
#define _XBASECOORDSPACE_H_

#include "XBase3DTypes.h"
#include "XLinkList.h"

class XBaseCoordSpace
{
public:
								XBaseCoordSpace();
	virtual						~XBaseCoordSpace();
	//	设置世界坐标系下的绝对位置
	virtual void				SetAbsolutePosition(const XVECTOR3& vPosition);
	//	返回世界坐标系下的绝对位置
	XVECTOR3					GetAbsolutePosition() const;
	virtual void				SetAbsoluteMatrix(const XMATRIX4& matrix);
	//	返回世界坐标变换矩阵
	const XMATRIX4&				GetAbsoluteMatrix();
	virtual void				SetRelativeMatrix(const XMATRIX4& matrix);
	//	返回相对坐标变换矩阵
	const XMATRIX4&				GetRelativeMatrix();
	//	设置前方向、上方向
	virtual void				SetForwardDirAndUp(const XVECTOR3& vForwardDir, const XVECTOR3& vUp);
	//	设置位置、前方向
	virtual void				SetPositionAndForwardDirUp(const XVECTOR3& vPosition, const XVECTOR3& vForwardDir, const XVECTOR3& vUp);
	//	设置相对父坐标系的位置
	virtual void				SetRelativePosition(const XVECTOR3& vPosition);
	//	设置相对父坐标系的前方向、上方向
	virtual void				SetRelativeForwardDirAndUp(const XVECTOR3& vForwardDir, const XVECTOR3& vUp);
	//	设置相对父坐标系的位置、前方向
	virtual void				SetRelativePositionAndForwardDir(const XVECTOR3& vPosition, const XVECTOR3& vForwardDir, const XVECTOR3& vUp);
	//	返回世界坐标系下的前方向
	XVECTOR3					GetAbsoluteDir() const;
	//	返回世界坐标系下的上方向
	XVECTOR3					GetAbsoluteUp() const;
	//	返回世界坐标系下的右方向
	XVECTOR3					GetAbsoluteRight() const;
	//	在世界坐标系下移动一个Delta
	virtual void				AbsoluteMove(const XVECTOR3& vDelta);
	//	在父坐标系下移动一个Delta
	virtual void				RelativeMove(const XVECTOR3& vDelta);
	virtual void				RotateX(xfloat32 fDeltaRadian, xbool bLocalSpace=xtrue);
	virtual void				RotateY(xfloat32 fDeltaRadian, xbool bLocalSpace = xtrue);
	virtual void				RotateZ(xfloat32 fDeltaRadian, xbool bLocalSpace = xtrue);
	virtual void				RotateAxis(const XVECTOR3& vRotateAxis, xfloat32 fDeltaRadian, xbool bLocalSpace = xtrue);

	//	增加相对（子）坐标系
	xbool						AddChildCoordSpace(XBaseCoordSpace* pChildSpace);
	//	删除相对（子）坐标系
	void						RemoveChildCoordSpace(XBaseCoordSpace* pChildSpace);
	//	删除所有相对（子）坐标系
	void						RemoveAllChildrenCoordSpaces();
	//	返回相对（子）坐标系的数量
	xint32						GetChildrenCoordSpaceNum();
	//	设置相对（父）坐标系
	void						SetParentCoordSpace(XBaseCoordSpace* pParentSpace);
	//	返回相对（父）坐标系
	XBaseCoordSpace*			GetParentCoordSpace();
protected:
	virtual void				OnTransformChanged() {};
	void						UpdateRelativeMatrix();
	//设置一个矩阵到所有的矩阵
	void						ApplySetAbsoluteMatrix(const XMATRIX4& matrix);
	//设置移动偏移到所有的子矩阵
	void						ApplyMoveChildren(const XVECTOR3& vDelta);
	//设置移动偏移到所有的矩阵
	void						ApplyMove(const XVECTOR3& vDelta);
	//设置一个矩阵到所有的子矩阵
	void						ApplySetChildrenAbsoluteMatrix();
protected:
	//父坐标空间
	XBaseCoordSpace*			m_pParentSpace;
	xuptrint					m_unPositionIndex;   // fix flk xuint32改成xuptrint;
	//相对矩阵，变换到父空间
	XMATRIX4					m_matRelativeMatrix;
	//绝对矩阵，世界变换矩阵
	XMATRIX4					m_matAbsoluteMatrix;
	XLinkList<XBaseCoordSpace>	m_aChildSpace;
};
#endif	//	_XBASECOORDSPACE_H_

