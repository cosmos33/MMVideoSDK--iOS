/******************************************************************************

@File         XEKeyframe.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_KEYFRAME_H
#define XE_KEYFRAME_H
#include "XEFactoryUserNodeUtil.h"
#include "XCurve.h"
#include "XTypes.h"

class XEKeyframeBase :public XEUserNode
{
public:
	XEKeyframeBase() :m_pUserData(NULL){}
	virtual ~XEKeyframeBase(){}
public:
	XE_USER_NODE_CAST(XEKeyframeBase)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
public:
	X_FORCEINLINE void                 SetUserData(void* pUserData){ m_pUserData = pUserData; }
	X_FORCEINLINE void*                GetUserData() const{ return m_pUserData; }
	X_FORCEINLINE xint32               GetStartTime() const{ return m_nStartTime; }
public:
	virtual const XString              GetDataType() = 0;
	virtual void                       SetStartTime(xint32 nStartTime, xbool bSynCurve = xfalse);
	virtual void                       Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                Serialize(XMLElement* pEleParent)override;
	template<typename __typeTest>
	xbool                              MatchType();
	template<typename __castTest>
	__castTest*                        CastKeyframe();
public:
	void*                              GetCurve(xbool);//if it is a curve.
protected:
	xint32                             m_nStartTime;//in microsecond.
	void*                              m_pUserData;//e.g. the shape struct of this  key-frame,etc.
	
};

#define XE_TEMPLATE_KEYFRAME_MATCH_TYPE(T)\
template<>\
xbool XEKeyframeBase::MatchType<T>()\
{\
	return 0 == GetDataType().CompareNoCase(#T);\
}\


template<typename __castTest>
__castTest*    XEKeyframeBase::CastKeyframe()
{
	if( __castTest().GetDataType() == GetDataType())
		return static_cast<__castTest*>(this);
	return NULL;
}


template<typename __DataType>
class XEKeyframeData :public XEKeyframeBase
{
public:
	XEKeyframeData(){}
	virtual ~XEKeyframeData(){ }
public:
	virtual const XString              GetDataType() override;
public:
	X_FORCEINLINE const __DataType&    GetValue() const{ return m_Data; }
	X_FORCEINLINE __DataType&          GetValue(){ return m_Data; }
	void                               SetValue(const __DataType& data);//if need to synchronize the curve, set it to xtrue.
protected:
	__DataType                         m_Data;//__DataType.should be explain in its holders.(usually is the track.)  
public:
	XE_USER_NODE_CAST(XEKeyframeData<xfloat32>)
	XE_USER_NODE_CAST_OVERRIDE(XEKeyframeData<xint32>, 1)
	XE_USER_NODE_CAST_OVERRIDE(XEKeyframeData<xbool>, 2)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

#define XE_KEYFRAME_NODE_TYPENAME(T)\
template<>\
const XString XEKeyframeData<T>::NODE_TYPENAME = XString("KeyframeData.") + XString(#T);

#define XE_TEMPLATE_KEYFRAME_GETTYPE(T)\
template<>\
const XString XEKeyframeData<T>::GetDataType()\
{\
	return #T;\
}

template<typename __DataType>
void XEKeyframeData<__DataType>::SetValue(const __DataType& data)
{
	m_Data = data;
}

template<typename __DataType>
class XEKeyframeCurve :public XEKeyframeData<__DataType>
{
public:
	XEKeyframeCurve() : m_bCurvePointLock(xfalse), m_pCurvePointToBackUp(NULL){}
	virtual ~XEKeyframeCurve(){ }
	typedef XEKeyframeData<__DataType> Super;
public:
	virtual void                       Release()override;
	virtual const XString              GetDataType() override;
	virtual void                       SetStartTime(xint32 nStartTime, xbool bSynCurve = xfalse) override;//if need to synchronize the curve, set it to xtrue.
	virtual void                       ReverseRecover() override;//do something BEFORE detach from parent.
	virtual void                       Recover() override;//do something AFTER attach to the parent.
	virtual void                       Backup() override;//do something to backup datas.
public:
	FInterpCurve<__DataType>*          GetCurve();//in the parent.
	FInterpCurvePoint<__DataType>*     GetCurveInterpPoint();//the interpolating point in the curve, 1-1, in memory index.
	xint32                             GetCurveInterpPointIndex();//according to the timestamp, actually index in the POINT ARRAY.
public:
	X_FORCEINLINE void                 SetCurvePointLock(xbool bLock){ m_bCurvePointLock = bLock; }
	void                               SetValue(const __DataType& data, xbool bSynCurve = xfalse);//if need to synchronize the curve, set it to xtrue.
	xbool                              BackupCurvePoint();//if necessary.
	FInterpCurvePoint<__DataType>*     GetBackupCurvePoint(xbool bGenerateForcely = xtrue);
	xbool                              RemoveCurvePoint();//if necessary.
	xbool                              RecoverCurvePoint();//if necessary.
	xbool                              HasBackupCurvePoint();//check if necessary
	X_FORCEINLINE const xbool		   GetCurvePointLock(){ return m_bCurvePointLock; }
protected:
	xbool                              m_bCurvePointLock;//if lock is on, will not affect the actual curve.
	__DataType                         m_Data;//__DataType.should be explain in its holders.(usually is the track.)  
	FInterpCurvePoint<__DataType>*     m_pCurvePointToBackUp;//a copy of curve point.(will be constituted the final curve.)
public:
	XE_USER_NODE_CAST(XEKeyframeCurve<xfloat32>)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
};

template<typename __DataType>
void XEKeyframeCurve<__DataType>::ReverseRecover()
{
	//before detach 
	BackupCurvePoint();
	RemoveCurvePoint();
}

template<typename __DataType>
void XEKeyframeCurve<__DataType>::Recover()
{
	RecoverCurvePoint();
	X_SAFEDELETE(m_pCurvePointToBackUp);
}

template<typename __DataType>
void XEKeyframeCurve<__DataType>::Backup()
{
	BackupCurvePoint();
}

template<typename __DataType>
xbool XEKeyframeCurve<__DataType>::BackupCurvePoint()
{
	if (FInterpCurvePoint<__DataType>* pCurvePoint = GetCurveInterpPoint())
	{
		X_SAFEDELETE(m_pCurvePointToBackUp);
		m_pCurvePointToBackUp = new FInterpCurvePoint<__DataType>(*pCurvePoint);
		return xtrue;
	}
	return xfalse;
}


template<typename __DataType>
FInterpCurvePoint<__DataType>* XEKeyframeCurve<__DataType>::GetBackupCurvePoint(xbool bGenerateForcely /*= xtrue*/)
{
	if (NULL == m_pCurvePointToBackUp && bGenerateForcely)
	{
		m_pCurvePointToBackUp = new FInterpCurvePoint<__DataType>();
		memset(m_pCurvePointToBackUp, 0, sizeof(FInterpCurvePoint<__DataType>));
	}

	return m_pCurvePointToBackUp;
}


template<typename __DataType>
xbool XEKeyframeCurve<__DataType>::RemoveCurvePoint()
{
	if (FInterpCurve<__DataType>* pCurve = GetCurve())
	{
		xint32 nIndex = Super::GetIndex(Super::GetFirstParent());
		if (X_INDEX_NONE != nIndex)
		{
			pCurve->DeletePoint(nIndex);//using sequence index.
			pCurve->AutoSetTangents();
			return xtrue;
		}
	}
	return xfalse;
}

template<typename __DataType>
xbool XEKeyframeCurve<__DataType>::RecoverCurvePoint()
{
	if (NULL == m_pCurvePointToBackUp)
		return xfalse;

	//warning! be careful.
	if (FInterpCurve<__DataType>* pCurve = GetCurve())
	{
		xint32 nIndex = Super::GetIndex(Super::GetFirstParent());
		pCurve->InsertPoint(nIndex, m_pCurvePointToBackUp->InVal, m_pCurvePointToBackUp->OutVal);
		pCurve->Points[nIndex].InterpMode = m_pCurvePointToBackUp->InterpMode;
		pCurve->AutoSetTangents();
		return xtrue;
	}
	return xfalse;
}

template<typename __DataType>
xbool XEKeyframeCurve<__DataType>::HasBackupCurvePoint()
{
	return NULL != m_pCurvePointToBackUp;
}


#define XE_KEYFRAMECURVE_NODE_TYPENAME(T)\
template<>\
const XString XEKeyframeCurve<T>::NODE_TYPENAME = XString("KeyframeData.") + XString(#T) + ".Curve";


template<typename __DataType>
void XEKeyframeCurve<__DataType>::Release()
{
	if (!m_bCurvePointLock)
	{
		//the point in the actual curve need to be deleted.
		RecoverCurvePoint();//ensure the key-data is here.
		xint32 nPointIndex = Super::GetIndex(Super::GetFirstParent());
		if (X_INDEX_NONE != nPointIndex)
		{
			if (FInterpCurve<__DataType>* pCurve = GetCurve())
			{
				if ( pCurve->Points.Num() > nPointIndex)
					pCurve->DeletePoint(nPointIndex);
				else
				{
					//failed to delete point.
				}
			}
				
		}
	}

	X_SAFEDELETE(m_pCurvePointToBackUp);
}

template<typename __DataType>
FInterpCurve<__DataType>* XEKeyframeCurve<__DataType>::GetCurve()
{
	return (FInterpCurve<__DataType>*)XEKeyframeBase::GetCurve(xbool());
}

template<typename __DataType>
FInterpCurvePoint<__DataType>* XEKeyframeCurve<__DataType>::GetCurveInterpPoint()
{
	xint32 nIndex = Super::GetIndex(Super::GetFirstParent());
	if (X_INDEX_NONE != nIndex)
	{
		if (FInterpCurve<__DataType>* pCurve = GetCurve())
		{
			if ( pCurve->Points.Num() > nIndex && pCurve->PointIndex.Num() > nIndex )
				return &pCurve->Points[pCurve->PointIndex[nIndex]];
		}
	}
	return NULL;
}

template<typename __DataType>
xint32 XEKeyframeCurve<__DataType>::GetCurveInterpPointIndex()
{
	xint32 nIndex = Super::GetIndex(Super::GetFirstParent());
	if (X_INDEX_NONE != nIndex)
	{
		if (FInterpCurve<__DataType>* pCurve = GetCurve())
		{
			if (pCurve->Points.Num() > nIndex && pCurve->PointIndex.Num() > nIndex)
				return pCurve->PointIndex[nIndex];
		}
	}
	return X_INDEX_NONE;
}

template<typename __DataType>
void XEKeyframeCurve<__DataType>::SetStartTime(xint32 nStartTime, xbool bSynCurve /*= xfalse*/)
{
	if (xtrue == bSynCurve)
	{
		if (FInterpCurve<__DataType>* pCurve = GetCurve())
		{
			if (GetCurveInterpPoint())
			{
                pCurve->MovePoint(pCurve->PointIndex[Super::GetIndex(Super::GetFirstParent())], (xfloat32)nStartTime / (xfloat32)1.e6f);
			}
		}
	}
    
	Super::SetStartTime(nStartTime);
}


template<typename __DataType>
void XEKeyframeCurve<__DataType>::SetValue(const __DataType& data, xbool bSynCurve)
{
	if (xtrue == bSynCurve)
	{
		if (FInterpCurve<__DataType>* pCurve = GetCurve())
		{
			if (0 == pCurve->Points.Num() || NULL == GetCurveInterpPoint())
			{
				//points need to be added in the curve.
				pCurve->AddPoint((xfloat32)Super::m_nStartTime / (xfloat32)1.e6f, data);
				if (FInterpCurvePoint<__DataType>* pPoint = GetCurveInterpPoint())
					pPoint->InterpMode = CIM_CurveAuto;
				pCurve->AutoSetTangents();
			}
			else
			{
				//points need to be modified in the curve.
				if (FInterpCurvePoint<__DataType>* pPoint = GetCurveInterpPoint())
				{
					pPoint->OutVal = data;
					if (fabsf(pPoint->InVal *1.e6f - Super::m_nStartTime) > 1.e-6f)
					{
						//need to refresh.
						pPoint->InVal = (xfloat32)Super::m_nStartTime / (xfloat32)1.e6f;
						pCurve->AutoSetTangents();
					}
				}
			}
		}
	}
	Super::SetValue(data);
}

#define XE_TEMPLATE_KEYFRAMECURVE_GETTYPE(T)\
template<>\
const XString XEKeyframeCurve<T>::GetDataType()\
{\
	return #T;\
}


#endif // XE_KEYFRAME_H
