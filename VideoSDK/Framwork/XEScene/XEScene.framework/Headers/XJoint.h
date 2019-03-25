/******************************************************************************

@File         XJoint.h

@Version       1.0

@Created      2017, 4, 14

@Description  用于连接两根骨头， Joint本身是一个控制器

@HISTORY:

******************************************************************************/
#ifndef _X_JOINT_H_
#define _X_JOINT_H_

#include "XBase3DTypes.h"
#include "XMemBase.h"

class XBone;
class XFileBase;
class XSkeleton;
class XController;

enum XCJOINTTYPE
{
	XCJT_UNKNOWN = 0,
	XCJT_JOINT,
	XCJT_ANIMJOIN,
};

/*
* XJoint中有位移和旋转变化信息
* XControlledJoint 是一个有控制限制XJoint派生。
* XAnimJoint 是一个由track控制的 XJoint派生.
*/

class XJoint : public XMemBase
{
public:
	enum
	{
		JOINT_UNKNOWN = -1,
		JOINT_ANIM = 0,
		JOINT_CONTROL,
		JOINT_SPRING,
		JOINT_AXISSPRING,
	};
	
    /*
    * JOINTDATA 用于加载和保存。
    */
	struct JOINTDATA
	{
		xint32					nParentBone;
		xint32					nChildBone;
		xint32					nSiblingJoint;
	};


public:
								XJoint();
								~XJoint();

	static XJoint*				NewJoint(xuint32 uType, xbool bClassID);

	virtual xbool				Init(XSkeleton* pSkeleton);
	virtual void				Release();
	virtual XJoint*				Duplicate(XSkeleton* pDstSkeleton) { return NULL; }

	/*
	* 按nDeltaTime时间，更新joint
	*
	* @param   nDeltaTime		逝去的时间
	* @returns  true : 执行成功
	*/
	virtual xbool				Update(xint32 nDeltaTime);
	virtual XMATRIX4			GetMatrix() = 0;
	virtual xbool				Load(XFileBase* pFile);
	virtual xbool				Save(XFileBase* pFile);

	inline xuint32				GetFileNameID() { return m_uFileNameID; }
	inline xuint32				GetClassID() { return m_uClassID; }
	inline xint32				GetJointType() { return m_nJointType; }
	virtual void				SetName(const xchar* szName);
	const xchar*				GetName() const { return m_strName; }
	inline xint32				GetParentBone() { return m_nParentBone; }
	inline xint32				GetChildBone() { return m_nChildBone; }
	inline xint32				GetSiblingJoint() { return m_nSiblingJoint; }
	XBone*						GetParentBonePtr();
	XBone*						GetChildBonePtr();
	XJoint*						GetSiblingJointPtr();
	
	inline XSkeleton*			GetSkeleton() { return m_pSkeleton; }
	inline void					SetSkeleton(XSkeleton* pSkeleton) { m_pSkeleton = pSkeleton; }
	
	inline void					SetBones(xint32 nParentBone, xint32 nChildBone)
	{
		m_nParentBone	= nParentBone;
		m_nChildBone	= nChildBone;
	}
	
	inline void					SetSiblingJoint(xint32 iJoint) { m_nSiblingJoint = iJoint; }	

protected:
     xuint32					m_uClassID;
     XString					m_strName;
	 /*
	 * m_uFileNameID 是由joint 的文件名生成的ID
	 */
     xuint32					m_uFileNameID;
	 /*
	 * m_pSkeleton 关联的骨架
	 */
     XSkeleton*					m_pSkeleton;

     xint32						m_nJointType;
     xint32						m_nParentBone;
     xint32						m_nChildBone;
	 /*
	 * 与当前Xjoints 关联骨头相同的Xjoints索引
	 */
     xint32						m_nSiblingJoint;
};



/*
* XAnimJoint 是以track数据来控制骨头的 XJoint派生
*/
class XAnimJoint : public XJoint
{
public:
							XAnimJoint();
	virtual					~XAnimJoint();

	virtual XJoint*			Duplicate(XSkeleton* pDstSkeleton);

	virtual xbool			Update(xint32 nDeltaTime);
	virtual XMATRIX4		GetMatrix();

	virtual xbool			Load(XFileBase* pFile);
	virtual xbool			Save(XFileBase* pFile);
};

#endif//_X_JOINT_H_