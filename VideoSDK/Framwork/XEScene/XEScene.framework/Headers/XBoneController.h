/******************************************************************************

@File         XBoneController.h

@Version       1.0

@Created      2017, 4, 14

@Description  

@HISTORY:

******************************************************************************/

#ifndef _X_BONE_CONTROLLER_H_
#define _X_BONE_CONTROLLER_H_

#include "XBase3DTypes.h"
#include "XHashTable.h"
#include "XMemBase.h"

class XBone;
class XBoneControllerBase : public XMemBase
{
public:
									XBoneControllerBase(XBone * pTargetBone);
	virtual							~XBoneControllerBase();

	/*
	* 控制器更新骨头矩阵
	*
	* @notice	在骨头更新时，会被调用
	*
	* @param	nDeltaTime	步进时间
	* @param	pTargetBone	目标骨头
	* @param	matControlled	输出计算后矩阵
	* @returns  true : 执行成功
	*/
	virtual xbool					Update(xint32 nDeltaTime, XBone * pTargetBone, XMATRIX4& matControlled) = 0;


	inline XBoneControllerBase*	    GetNextController() { return m_pNextController; }
	inline void					    SetNextController(XBoneControllerBase * pController) { m_pNextController = pController; }
	inline XBone*					GetTargetBone() { return m_pTargetBone; }
	inline const XMATRIX4&			GetControllerMatrix() { return m_matController; }

	void							SetUserData(const xchar * key, xint32 value);
    xbool							GetUserData(const xchar * key, xint32 * pValue);

protected:
	typedef XHashTable<const xchar *, xint32> USERDATATAB;

    XBone *							m_pTargetBone;
	XBoneControllerBase *			m_pNextController;
	XMATRIX4						m_matController;	
	// 用户扩展参数
	USERDATATAB*					m_pUserData;	
};

// 缩放控制器
class XBoneScaleController : public XBoneControllerBase
{
public:
								XBoneScaleController(XBone * pTargetBone);
	virtual						~XBoneScaleController();

	/*
	* 控制器更新骨头矩阵
	*
	* @notice	在骨头更新时，会被调用
	*
	* @param	nDeltaTime	步进时间
	* @param	pTargetBone	目标骨头
	* @param	matControlled	输出计算后矩阵
	* @returns  true : 执行成功
	*/
	virtual xbool				Update(xint32 nDeltaTime, XBone * pTargetBone, XMATRIX4& matControlled);
	xbool						Scale(const XVECTOR3& scale, xint32 nTransTime);

protected:
	XVECTOR3					m_scaleStart;
	XVECTOR3					m_scaleEnd;
	XVECTOR3					m_scale;	
	xint32						m_nTransTime;
	xint32						m_nCurTime;
};

class XBoneLocalScaleController : public XBoneScaleController
{
public:
								XBoneLocalScaleController(XBone * pTargetBone);
	virtual						~XBoneLocalScaleController();

	/*
	* 控制器更新骨头矩阵
	*
	* @notice	在骨头更新时，会被调用
	*
	* @param	nDeltaTime	步进时间
	* @param	pTargetBone	目标骨头
	* @param	matControlled	输出计算后矩阵
	* @returns  true : 执行成功
	*/
	virtual xbool				Update(xint32 nDeltaTime, XBone * pTargetBone, XMATRIX4& matControlled);
};

class XBoneRotController : public XBoneControllerBase
{
public:
								XBoneRotController(XBone * pTargetBone);
	virtual						~XBoneRotController();

	/*
	* 控制器更新骨头矩阵
	*
	* @notice	在骨头更新时，会被调用
	*
	* @param	nDeltaTime	步进时间
	* @param	pTargetBone	目标骨头
	* @param	matControlled	输出计算后矩阵
	* @returns  true : 执行成功
	*/
	virtual xbool				Update(xint32 nDeltaTime, XBone * pTargetBone, XMATRIX4& matControlled);
	xbool						Rotate(const XQUATERNION& qu, xint32 nTransTime);

protected:
	XQUATERNION					m_quStart;
	XQUATERNION					m_quEnd;	
	XQUATERNION					m_qu;	

	xint32						m_nTransTime;
	xint32						m_nCurTime;
};

class XBonePosController : public XBoneControllerBase
{
public:
								XBonePosController(XBone * pTargetBone);
	virtual						~XBonePosController();

	/*
	* 控制器更新骨头矩阵
	*
	* @notice	在骨头更新时，会被调用
	*
	* @param	nDeltaTime	步进时间
	* @param	pTargetBone	目标骨头
	* @param	matControlled	输出计算后矩阵
	* @returns  true : 执行成功
	*/
	virtual xbool				Update(xint32 nDeltaTime, XBone * pTargetBone, XMATRIX4& matControlled);
	xbool						Move(const XVECTOR3& vecPos, xint32 nTransTime);

protected:
	XVECTOR3					m_vecPosStart;
	XVECTOR3					m_vecPosEnd;
	XVECTOR3					m_vecPos;	

	xint32						m_nTransTime;	
	xint32						m_nCurTime;
};


class XBoneMatrixController : public XBoneControllerBase
{
public:
								XBoneMatrixController(XBone * pTargetBone);
	virtual						~XBoneMatrixController();
	/*
	* 控制器更新骨头矩阵
	*
	* @notice	在骨头更新时，会被调用
	*
	* @param	nDeltaTime	步进时间
	* @param	pTargetBone	目标骨头
	* @param	matControlled	输出计算后矩阵
	* @returns  true : 执行成功
	*/
	virtual xbool				Update(xint32 nDeltaTime, XBone * pTargetBone, XMATRIX4& matControlled);
	xbool						CombineMatrix(const XMATRIX4& mat, xint32 nTransTime);
	xbool						CombineMatrixList(const XMATRIX4 * mats, xfloat32 * weights, xint32 nNumMat, xint32 nTransTime);


protected:
	xbool						CombineMatrixElements(const XVECTOR3& vecScale, const XQUATERNION& quOrient, const XVECTOR3& vecPos, xint32 nTransTime);
	
	XVECTOR3					m_vecPosStart;
	XVECTOR3					m_vecPosEnd;	
	XVECTOR3					m_vecPos;		

	XQUATERNION					m_quStart;	
	XQUATERNION					m_quEnd;		
	XQUATERNION					m_qu;

	XVECTOR3					m_scaleStart;
	XVECTOR3					m_scaleEnd;	
	XVECTOR3					m_scale;
	
	xint32						m_nTransTime;
	xint32						m_nCurTime;
};


class XBoneWorldRotController : public XBoneControllerBase
{
public:
									XBoneWorldRotController(XBone * pTargetBone);
	 virtual						~XBoneWorldRotController();

	 /*
	 * 控制器更新骨头矩阵
	 *
	 * @notice	在骨头更新时，会被调用
	 *
	 * @param	nDeltaTime	步进时间
	 * @param	pTargetBone	目标骨头
	 * @param	matControlled	输出计算后矩阵
	 * @returns  true : 执行成功
	 */
	 virtual xbool				    Update(xint32 nDeltaTime, XBone * pTargetBone, XMATRIX4& matControlled) override;
	 void						    SetRotRadian(const XVECTOR3 &vEuler) { m_vEuler = vEuler; }

protected:
	 XVECTOR3						m_vEuler;
};


class XBoneWorldMatController : public XBoneControllerBase
{
public:
								    XBoneWorldMatController(XBone * pTargetBone);
	 virtual						~XBoneWorldMatController();


	 /*
	 * 控制器更新骨头矩阵
	 *
	 * @notice	在骨头更新时，会被调用
	 *
	 * @param	nDeltaTime	步进时间
	 * @param	pTargetBone	目标骨头
	 * @param	matControlled	输出计算后矩阵
	 * @returns  true : 执行成功
	 */
	 virtual xbool				    Update(xint32 nDeltaTime, XBone * pTargetBone, XMATRIX4& matControlled) override;
	 inline void					SetRotRadian(const XVECTOR3 &vEuler) { m_vEuler = vEuler; }
	 inline void					SetTranslate(const XVECTOR3 &vPosition) { m_vPosition = vPosition; }
	 inline void					SetScale(const XVECTOR3 &vScale) { m_vScale = vScale; }

protected:
	 XVECTOR3						m_vEuler;
	 XVECTOR3						m_vPosition;
	 XVECTOR3						m_vScale;
};


#endif//_X_BONE_CONTROLLER_H_
