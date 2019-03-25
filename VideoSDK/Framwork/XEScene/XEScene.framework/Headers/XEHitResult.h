/******************************************************************************

@File         XEHitResult.h

@Version       1.0

@Created      2017, 10, 12

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_HITRESULT_H_
#define _XE_HITRESULT_H_

#include "XMemBase.h"
#include "XMath3D.h"
#include "XTypes.h"

class XEActor;
class XEActorComponent;

#define	XE_PICK_PRIORITY_MIN -0xffffff//24bits
#define XE_PICK_PRIORITY_MAX 0Xffffff

struct XECollisionChannelMeta
{
	typedef XArray<XECollisionChannelMeta> ECC_META_POOL;
	enum ECollisionChannel
	{
		ECC_ALL,//channel that pass all
		ECC_HIDDEN,
		ECC_VISIBLE,
		ECC_SYSTEM_0 = 100,//100+,binding a unique string.
		ECC_SYSTEM_1,
		ECC_SYSTEM_2,
		ECC_SYSTEM_3,
		ECC_SYSTEM_4,
		ECC_SYSTEM_5,
		ECC_SYSTEM_6,
		ECC_SYSTEM_7,
		ECC_SYSTEM_8,
		ECC_SYSTEM_9,
		ECC_SYSTEM_10,//110+,binding a unique string.
		ECC_SYSTEM_11,
		ECC_SYSTEM_12,
		ECC_SYSTEM_13,
		ECC_SYSTEM_14,
		ECC_SYSTEM_15,
		ECC_SYSTEM_16,
		ECC_SYSTEM_17,
		ECC_SYSTEM_18,
		ECC_SYSTEM_19,
		ECC_SYSTEM_20,//120+,binding a unique string.
		ECC_SYSTEM_21,
		ECC_SYSTEM_22,
		ECC_SYSTEM_23,
		ECC_SYSTEM_24,
		ECC_SYSTEM_25,
		ECC_SYSTEM_26,
		ECC_SYSTEM_27,
		ECC_SYSTEM_28,
		ECC_SYSTEM_29,
		ECC_SYSTEM_END = 199,
		ECC_CUSTOM_0 = 200,//200+,binding a unique string.
		ECC_CUSTOM_1,
		ECC_CUSTOM_2,
		ECC_CUSTOM_3,
		ECC_CUSTOM_4,
		ECC_CUSTOM_5,
		ECC_CUSTOM_6,
		ECC_CUSTOM_7,
		ECC_CUSTOM_8,
		ECC_CUSTOM_9,
		ECC_CUSTOM_END = 300
	};
	ECollisionChannel eCC;
	xchar             metaName[MAX_PATH];

	XECollisionChannelMeta()
	{
		memset(metaName, 0, MAX_PATH*sizeof(xchar));
		eCC = ECC_ALL;
	}
	explicit XECollisionChannelMeta(ECollisionChannel ecc, const xchar* mn)
	{
		memset(metaName, 0, MAX_PATH*sizeof(xchar));
		eCC = ecc;
		if (mn)
			strcpy(metaName, mn);
	}
	const xbool operator == (const XECollisionChannelMeta& ccm) const
	{
		return eCC == ccm.eCC;
	}

	xbool IsRaw() const
	{
		if (eCC < ECC_CUSTOM_0)
			return xfalse;//system

		XString szCustomName;
		szCustomName.Format("Custom channel-%d", eCC - ECC_CUSTOM_0);
		return 0 == szCustomName.CompareNoCase(metaName);
	}

	xbool IsCustom() const
	{
		return eCC >= ECC_CUSTOM_0 && eCC <= ECC_CUSTOM_END;
	}

	XString  GetOriginName() const
	{
		XString szCustomName;
		if (eCC >= ECC_CUSTOM_0)
			szCustomName.Format("Custom channel-%d", eCC - ECC_CUSTOM_0);
		else
			szCustomName = metaName;
		return szCustomName;
	}

	void ResetToRaw()
	{
		if (eCC >= ECC_CUSTOM_0)
		{
			XString szCustomName;
			szCustomName.Format("Custom channel-%d", eCC - ECC_CUSTOM_0);
			strcpy(metaName, szCustomName.CStr());
		}
	}

	static ECC_META_POOL& GetArtifactitMetas()
	{
		static ECC_META_POOL sECCMetaPoolArti;
		sECCMetaPoolArti.Clear();
		ECC_META_POOL& rawSet = GetECCMetaPool();
		for (xint32 i = 0; i < rawSet.Num(); ++i)
		{
			if (!rawSet[i].IsRaw())
				sECCMetaPoolArti.Add(rawSet[i]);
		}
		return sECCMetaPoolArti;
	}

	static ECC_META_POOL& GetCustomMetas()
	{
		static ECC_META_POOL sECCMetaPoolCustom;
		sECCMetaPoolCustom.Clear();
		ECC_META_POOL& rawSet = GetECCMetaPool();
		for (xint32 i = 0; i < rawSet.Num(); ++i)
		{
			if (rawSet[i].IsCustom() && !rawSet[i].IsRaw() )
				sECCMetaPoolCustom.Add(rawSet[i]);
		}
		return sECCMetaPoolCustom;
	}

	static ECC_META_POOL& GetECCMetaPool()
	{
		static ECC_META_POOL sECCMetaPool;
		if (0 == sECCMetaPool.Num())
		{
			sECCMetaPool.Add(XECollisionChannelMeta(ECC_ALL, "All pass"));
			sECCMetaPool.Add(XECollisionChannelMeta(ECC_HIDDEN, "Hidden object"));
			sECCMetaPool.Add(XECollisionChannelMeta(ECC_VISIBLE, "Visible object"));
			for (xint32 i = ECC_CUSTOM_0; i < ECC_CUSTOM_END; ++i)
			{
				if (i > ECC_CUSTOM_0 + 9)
					break;//as max as 10, currently.
				XString szCustomName;
				szCustomName.Format("Custom channel-%d", i - ECC_CUSTOM_0);
				sECCMetaPool.Add(XECollisionChannelMeta((ECollisionChannel)i, szCustomName));
			}		
		}
		return sECCMetaPool;
	}

	static XECollisionChannelMeta MetaGet(const xchar* mn)
	{
		ECC_META_POOL& emp = GetECCMetaPool();
		for (xint32 i = 0; i < emp.Num(); ++i)
		{
			XECollisionChannelMeta& _ccm = emp[i];
			if (0 == strcmp(mn, _ccm.metaName))
				return _ccm;
		}
		return XECollisionChannelMeta();
	}

	static XECollisionChannelMeta MetaGet(ECollisionChannel ecc)
	{
		ECC_META_POOL& emp = GetECCMetaPool();
		XECollisionChannelMeta _ccm(ecc, "");
		xint32 nIndex = emp.Find(_ccm);
		if (X_INDEX_NONE != nIndex)
			strcpy(_ccm.metaName,emp[nIndex].metaName);
		return _ccm;
	}

	static xbool MetaSet(ECollisionChannel ecc, const xchar* mn)
	{
		if (NULL == mn)
			return xfalse;

		ECC_META_POOL& emp = GetECCMetaPool();
		XECollisionChannelMeta _ccm(ecc, "");
		xint32 nIndex = emp.Find(_ccm);
		if (X_INDEX_NONE == nIndex)
			return xfalse;
		strcpy(emp[nIndex].metaName, mn);
		return xtrue;
	}

	static void MetaResetAll()
	{
		ECC_META_POOL& emp = GetECCMetaPool();
		for (xint32 i = 0; i < emp.Num(); ++i)
		{
			XECollisionChannelMeta& _ccm = emp[i];
			_ccm.ResetToRaw();
		}
	}
	static xbool IsMetaExist(const xchar* mn)
	{
		if (NULL == mn)
			return xfalse;

		ECC_META_POOL& emp = GetECCMetaPool();
		for (xint32 i = 0; i < emp.Num(); ++i)
		{
			XECollisionChannelMeta& _ccm = emp[i];
			if (0 == strcmp(mn, _ccm.metaName))
				return xtrue;
		}
		return xfalse;
	}
};


#define ECC_META_REG(e,m)       XECollisionChannelMeta::GetECCMetaPool().Add(XECollisionChannelMeta(e,m))
#define ECC_META_UNREG(e)       XECollisionChannelMeta::GetECCMetaPool().Remove(XECollisionChannelMeta(e,""))
#define ECC_META_SET(e,m)       XECollisionChannelMeta::MetaSet(e,m)
#define ECC_META_GET(eom)       XECollisionChannelMeta::MetaGet(eom)
#define ECC_META_IS_EXIST(eom)  XECollisionChannelMeta::IsMetaExist(eom)
#define ECC_META_GET_E(m)       XECollisionChannelMeta::MetaGet(m).eCC
#define ECC_META_GET_M(e)       XECollisionChannelMeta::MetaGet(e).metaName

struct XEHitResult
	:public XMemBase
{
	enum XHitResultOpt
	{
		XHR_EnableHit    = 1 << 1,//Can be hitted or not;
		XHR_WithPriority = 1 << 0 //With Priority or not;
	};
	/** Indicates if this hit was a result of blocking collision. If false, there was no hit or it was an overlap/touch instead. */
	xint32   bBlockingHit;

	/** The distance from the TraceStart to the ImpactPoint in world space. This value is 0 if there was an initial overlap (trace started inside another colliding object). */
	xfloat32 fDistance;

	/**
	* The location in world space where the moving shape would end up against the impacted object, if there is a hit. Equal to the point of impact for line tests.
	* Example: for a sphere trace test, this is the point where the center of the sphere would be located when it touched the other object.
	* For swept movement (but not queries) this may not equal the final location of the shape since hits are pulled back slightly to prevent precision issues from overlapping another surface.
	*/
	XVECTOR3 vLocation;

	/**
	* Location in world space of the actual contact of the trace shape (box, sphere, ray, etc) with the impacted object.
	* Example: for a sphere trace test, this is the point where the surface of the sphere touches the other object.
	*/
	XVECTOR3 vImpactPoint;

	/**
	* Normal of the hit in world space, for the object that was swept. Equal to ImpactNormal for line tests.
	* This is computed for capsules and spheres, otherwise it will be the same as ImpactNormal.
	* Example: for a sphere trace test, this is a normalized vector pointing in towards the center of the sphere at the point of impact.
	*/
	XVECTOR3 vNormal;

	/**
	* Normal of the hit in world space, for the object that was hit by the sweep, if any.
	* For example if a box hits a flat plane, this is a normalized vector pointing out from the plane.
	* In the case of impact with a corner or edge of a surface, usually the "most opposing" normal (opposed to the query direction) is chosen.
	*/
	XVECTOR3 vImpactNormal;

	/**
	* Start location of the trace.
	* For example if a sphere is swept against the world, this is the starting location of the center of the sphere.
	*/
	XVECTOR3 vTraceStart;

	/**
	* End location of the trace; this is NOT where the impact occurred (if any), but the furthest point in the attempted sweep.
	* For example if a sphere is swept against the world, this would be the center of the sphere if there was no blocking hit.
	*/
	XVECTOR3 vTraceEnd;

	/** Extra data about item that was hit (hit primitive specific). */
	xint32   nItem;

	/** Priority**/
	xint32 nPriority;

	/** Hit mask**/
	xint32 nHitMask;

	/** Trace AABB only**/
	xbool bAABBHitTestOnly;

	/** Actor hit by the trace. */
	XEActor* pActor;

	/** PrimitiveComponent hit by the trace. */
	XEActorComponent* pComponent;

	/*specific collision channel*/
	XECollisionChannelMeta eCollisionChannelMeta;

	XEHitResult()
	{
		Init();
	}
	explicit XEHitResult(const XVECTOR3& vStart, const XVECTOR3& vEnd)
	{
		Init(vStart, vEnd);
	}

	X_FORCEINLINE void Init()
	{
		memset(this, 0, sizeof(XEHitResult));
	}
	X_FORCEINLINE void Init(const XVECTOR3& vStart, const XVECTOR3& vEnd)
	{
		memset(this, 0, sizeof(XEHitResult));
		vTraceStart = vStart;
		vTraceEnd = vEnd;
	}
	X_FORCEINLINE static xint32 SortHitResultList(XEHitResult const* pLhs, XEHitResult const* pRhs)
	{
		if (pLhs && pRhs)
		{
			xint32 nLhsResult = 0,nRhsResult = 0;
			xint32 _3 = 1 << 3;
			xint32 _2 = 1 << 2;
			xint32 _1 = 1 << 1;
			xint32 _0 = 1;
			nLhsResult |= (pLhs->nHitMask & XHR_EnableHit)    < (pRhs->nHitMask & XHR_EnableHit)    ? _3 : 0;
			nLhsResult |= (pLhs->nHitMask & XHR_WithPriority) < (pRhs->nHitMask & XHR_WithPriority) ? _2 : 0;
			nLhsResult |= pLhs->nPriority < pRhs->nPriority ? _1 : 0;
			nLhsResult |= pLhs->fDistance > pRhs->fDistance ? _0 : 0;
			
			nRhsResult |= (pRhs->nHitMask & XHR_EnableHit)    < (pLhs->nHitMask & XHR_EnableHit)    ? _3 : 0;
			nRhsResult |= (pRhs->nHitMask & XHR_WithPriority) < (pLhs->nHitMask & XHR_WithPriority) ? _2 : 0;
			nRhsResult |= pRhs->nPriority < pLhs->nPriority ? _1 : 0;
			nRhsResult |= pRhs->fDistance > pLhs->fDistance ? _0 : 0;
			
			if (nLhsResult == nRhsResult)
				return 0;
			else if (nLhsResult < nRhsResult)
				return -1;
			else
				return 1;

		}
		return 0;
	}
};


#endif


