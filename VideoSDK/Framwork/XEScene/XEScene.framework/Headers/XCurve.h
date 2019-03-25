#ifndef _XCURVE_H_
#define _XCURVE_H_

#define KINDA_SMALL_NUMBER	(1.e-4f)

#include "XFileBase.h"
#include "XGlobalFuncs.h"
#include "XArray.h"
#define CURVE_VERSION 0

enum EForceInit
{
	ForceInit,
	ForceInitToZero
};

enum EInterpCurveMode
{
	/** A straight line between two keypoint values. */
	CIM_Linear,

	/** A cubic-hermite curve between two keypoints, using Arrive/Leave tangents. These tangents will be automatically
	updated when points are moved, etc.  Tangents are unclamped and will plateau at curve start and end points. */
	CIM_CurveAuto,

	/** The out value is held constant until the next key, then will jump to that value. */
	CIM_Constant,

	/** A smooth curve just like CIM_Curve, but tangents are not automatically updated so you can have manual control over them (eg. in Curve Editor). */
	CIM_CurveUser,

	/** A curve like CIM_Curve, but the arrive and leave tangents are not forced to be the same, so you can create a 'corner' at this key. */
	CIM_CurveBreak,

	/** A cubic-hermite curve between two keypoints, using Arrive/Leave tangents. These tangents will be automatically
	updated when points are moved, etc.  Tangents are clamped and will plateau at curve start and end points. */
	CIM_CurveAutoClamped,

	/** Invalid or unknown curve type. */
	CIM_Unknown
};


/**
* Template for interpolation points.
*
* Interpolation points are used for describing the shape of interpolation curves.
*
* @see FInterpCurve
* @todo Docs: FInterpCurvePoint needs better function documentation.
*/
template< class T > class FInterpCurvePoint
{
public:

	/** Float input value that corresponds to this key (eg. time). */
	float InVal;

	/** Output value of templated type when input is equal to InVal. */
	T OutVal;

	/** Tangent of curve arrive this point. */
	T ArriveTangent;

	/** Tangent of curve leaving this point. */
	T LeaveTangent;

	/** Interpolation mode between this point and the next one. @see EInterpCurveMode */
	EInterpCurveMode InterpMode;

public:

	/**
	* Default constructor (no initialization).
	*/
	FInterpCurvePoint() { };

	/**
	* Constructor
	*
	* @param In input value that corresponds to this key
	* @param Out Output value of templated type
	* @note uses linear interpolation
	*/
	FInterpCurvePoint(const float In, const T &Out);

	/**
	* Constructor
	*
	* @param In input value that corresponds to this key
	* @param Out Output value of templated type
	* @param InArriveTangent Tangent of curve arriving at this point.
	* @param InLeaveTangent Tangent of curve leaving from this point.
	* @param InInterpMode interpolation mode to use
	*/
	FInterpCurvePoint(const float In, const T &Out, const T &InArriveTangent, const T &InLeaveTangent, const EInterpCurveMode InInterpMode);

public:

	/** @return true if the key value is using a curve interp mode, otherwise false */
	X_FORCEINLINE bool IsCurveKey() const;

public:
	/**
	* Compare equality of two Curve Points
	*/
	friend bool operator==(const FInterpCurvePoint& Point1, const FInterpCurvePoint& Point2)
	{
		return (Point1.InVal == Point2.InVal &&
			Point1.OutVal == Point2.OutVal &&
			Point1.ArriveTangent == Point2.ArriveTangent &&
			Point1.LeaveTangent == Point2.LeaveTangent &&
			Point1.InterpMode == Point2.InterpMode);
	}

	/**
	* Compare inequality of two Curve Points
	*/
	friend bool operator!=(const FInterpCurvePoint& Point1, const FInterpCurvePoint& Point2)
	{
		return !(Point1 == Point2);
	}
};


/* FInterpCurvePoint inline functions
*****************************************************************************/

template< class T >
X_FORCEINLINE FInterpCurvePoint<T>::FInterpCurvePoint(const float In, const T &Out)
	: InVal(In)
	, OutVal(Out)
{
	memset(&ArriveTangent, 0, sizeof(T));
	memset(&LeaveTangent, 0, sizeof(T));

	InterpMode = CIM_Linear;
}


template< class T >
X_FORCEINLINE FInterpCurvePoint<T>::FInterpCurvePoint(const float In, const T &Out, const T &InArriveTangent, const T &InLeaveTangent, const EInterpCurveMode InInterpMode)
	: InVal(In)
	, OutVal(Out)
	, ArriveTangent(InArriveTangent)
	, LeaveTangent(InLeaveTangent)
	, InterpMode(InInterpMode)
{ }


template< class T >
X_FORCEINLINE bool FInterpCurvePoint<T>::IsCurveKey() const
{
	return ((InterpMode == CIM_CurveAuto) || (InterpMode == CIM_CurveAutoClamped) || (InterpMode == CIM_CurveUser) || (InterpMode == CIM_CurveBreak));
}

/**
* Clamps a tangent formed by the specified control point values
*/
static float ClampFloatTangent(float PrevPointVal, float PrevTime, float CurPointVal, float CurTime, float NextPointVal, float NextTime)
{
	const float PrevToNextTimeDiff = X_Max(KINDA_SMALL_NUMBER, NextTime - PrevTime);
	const float PrevToCurTimeDiff = X_Max(KINDA_SMALL_NUMBER, CurTime - PrevTime);
	const float CurToNextTimeDiff = X_Max(KINDA_SMALL_NUMBER, NextTime - CurTime);

	float OutTangentVal = 0.0f;

	const float PrevToNextHeightDiff = NextPointVal - PrevPointVal;
	const float PrevToCurHeightDiff = CurPointVal - PrevPointVal;
	const float CurToNextHeightDiff = NextPointVal - CurPointVal;

	// Check to see if the current point is crest
	if ((PrevToCurHeightDiff >= 0.0f && CurToNextHeightDiff <= 0.0f) ||
		(PrevToCurHeightDiff <= 0.0f && CurToNextHeightDiff >= 0.0f))
	{
		// Neighbor points are both both on the same side, so zero out the tangent
		OutTangentVal = 0.0f;
	}
	else
	{
		// The three points form a slope

		// Constants
		const float ClampThreshold = 0.333f;

		// Compute height deltas
		const float CurToNextTangent = CurToNextHeightDiff / CurToNextTimeDiff;
		const float PrevToCurTangent = PrevToCurHeightDiff / PrevToCurTimeDiff;
		const float PrevToNextTangent = PrevToNextHeightDiff / PrevToNextTimeDiff;

		// Default to not clamping
		const float UnclampedTangent = PrevToNextTangent;
		float ClampedTangent = UnclampedTangent;

		const float LowerClampThreshold = ClampThreshold;
		const float UpperClampThreshold = 1.0f - ClampThreshold;

		// @todo: Would we get better results using percentange of TIME instead of HEIGHT?
		const float CurHeightAlpha = PrevToCurHeightDiff / PrevToNextHeightDiff;

		if (PrevToNextHeightDiff > 0.0f)
		{
			if (CurHeightAlpha < LowerClampThreshold)
			{
				// 1.0 = maximum clamping (flat), 0.0 = minimal clamping (don't touch)
				const float ClampAlpha = 1.0f - CurHeightAlpha / ClampThreshold;
				const float LowerClamp = Lerp(PrevToNextTangent, PrevToCurTangent, ClampAlpha);
				ClampedTangent = X_Min(ClampedTangent, LowerClamp);
			}

			if (CurHeightAlpha > UpperClampThreshold)
			{
				// 1.0 = maximum clamping (flat), 0.0 = minimal clamping (don't touch)
				const float ClampAlpha = (CurHeightAlpha - UpperClampThreshold) / ClampThreshold;
				const float UpperClamp = Lerp(PrevToNextTangent, CurToNextTangent, ClampAlpha);
				ClampedTangent = X_Min(ClampedTangent, UpperClamp);
			}
		}
		else
		{

			if (CurHeightAlpha < LowerClampThreshold)
			{
				// 1.0 = maximum clamping (flat), 0.0 = minimal clamping (don't touch)
				const float ClampAlpha = 1.0f - CurHeightAlpha / ClampThreshold;
				const float LowerClamp = Lerp(PrevToNextTangent, PrevToCurTangent, ClampAlpha);
				ClampedTangent = X_Max(ClampedTangent, LowerClamp);
			}

			if (CurHeightAlpha > UpperClampThreshold)
			{
				// 1.0 = maximum clamping (flat), 0.0 = minimal clamping (don't touch)
				const float ClampAlpha = (CurHeightAlpha - UpperClampThreshold) / ClampThreshold;
				const float UpperClamp = Lerp(PrevToNextTangent, CurToNextTangent, ClampAlpha);
				ClampedTangent = X_Max(ClampedTangent, UpperClamp);
			}
		}

		OutTangentVal = ClampedTangent;
	}

	return OutTangentVal;
}


/** Computes Tangent for a curve segment */
template< class T, class U >
inline void AutoCalcTangent(const T& PrevP, const T& P, const T& NextP, const U& Tension, T& OutTan)
{
	OutTan = (1.f - Tension) * ((P - PrevP) + (NextP - P));
}

/** Computes a tangent for the specified control point.  General case, doesn't support clamping. */
template< class T >
inline void ComputeCurveTangent(float PrevTime, const T& PrevPoint,
	float CurTime, const T& CurPoint,
	float NextTime, const T& NextPoint,
	float Tension,
	bool bWantClamping,
	T& OutTangent)
{
	// NOTE: Clamping not supported for non-float vector types (bWantClamping is ignored)

	AutoCalcTangent(PrevPoint, CurPoint, NextPoint, Tension, OutTangent);

	const float PrevToNextTimeDiff = X_Max(KINDA_SMALL_NUMBER, NextTime - PrevTime);

	OutTangent /= PrevToNextTimeDiff;
}


/**
* Computes a tangent for the specified control point; supports clamping, but only works
* with floats or contiguous arrays of floats.
*/
template< class T >
inline void ComputeClampableFloatVectorCurveTangent(float PrevTime, const T& PrevPoint,
	float CurTime, const T& CurPoint,
	float NextTime, const T& NextPoint,
	float Tension,
	bool bWantClamping,
	T& OutTangent)
{
	// Clamp the tangents if we need to do that
	if (bWantClamping)
	{
		// NOTE: We always treat the type as an array of floats
		float* PrevPointVal = (float*)&PrevPoint;
		float* CurPointVal = (float*)&CurPoint;
		float* NextPointVal = (float*)&NextPoint;
		float* OutTangentVal = (float*)&OutTangent;
		for (xint32 CurValPos = 0; CurValPos < sizeof(T); CurValPos += sizeof(float))
		{
			// Clamp it!
			const float ClampedTangent =
				ClampFloatTangent(
				*PrevPointVal, PrevTime,
				*CurPointVal, CurTime,
				*NextPointVal, NextTime);

			// Apply tension value
			*OutTangentVal = (1.0f - Tension) * ClampedTangent;


			// Advance pointers
			++OutTangentVal;
			++PrevPointVal;
			++CurPointVal;
			++NextPointVal;
		}
	}
	else
	{
		// No clamping needed
		AutoCalcTangent(PrevPoint, CurPoint, NextPoint, Tension, OutTangent);

		const float PrevToNextTimeDiff = X_Max(KINDA_SMALL_NUMBER, NextTime - PrevTime);

		OutTangent /= PrevToNextTimeDiff;
	}
}


/** Computes a tangent for the specified control point.  Special case for float types; supports clamping. */
inline void ComputeCurveTangent(float PrevTime, const float& PrevPoint,
	float CurTime, const float& CurPoint,
	float NextTime, const float& NextPoint,
	float Tension,
	bool bWantClamping,
	float& OutTangent)
{
	ComputeClampableFloatVectorCurveTangent(
		PrevTime, PrevPoint,
		CurTime, CurPoint,
		NextTime, NextPoint,
		Tension, bWantClamping, OutTangent);
}


/** Computes a tangent for the specified control point.  Special case for FVector types; supports clamping. */
inline void ComputeCurveTangent(float PrevTime, const XVECTOR3& PrevPoint,
	float CurTime, const XVECTOR3& CurPoint,
	float NextTime, const XVECTOR3& NextPoint,
	float Tension,
	bool bWantClamping,
	XVECTOR3& OutTangent)
{
	ComputeClampableFloatVectorCurveTangent(
		PrevTime, PrevPoint,
		CurTime, CurPoint,
		NextTime, NextPoint,
		Tension, bWantClamping, OutTangent);
}

void CurveFloatFindIntervalBounds(const FInterpCurvePoint<float>& Start, const FInterpCurvePoint<float>& End, float& CurrentMin, float& CurrentMax);
void CurveVectorFindIntervalBounds(const FInterpCurvePoint<XVECTOR3>& Start, const FInterpCurvePoint<XVECTOR3>& End, XVECTOR3& CurrentMin, XVECTOR3& CurrentMax);


template< class T, class U >
inline void CurveFindIntervalBounds(const FInterpCurvePoint<T>& Start, const FInterpCurvePoint<T>& End, T& CurrentMin, T& CurrentMax, const U& Dummy)
{ }


template< class U >
inline void CurveFindIntervalBounds(const FInterpCurvePoint<float>& Start, const FInterpCurvePoint<float>& End, float& CurrentMin, float& CurrentMax, const U& Dummy)
{
	CurveFloatFindIntervalBounds(Start, End, CurrentMin, CurrentMax);
}


template< class U >
inline void CurveFindIntervalBounds(const FInterpCurvePoint<XVECTOR3>& Start, const FInterpCurvePoint<XVECTOR3>& End, XVECTOR3& CurrentMin, XVECTOR3& CurrentMax, const U& Dummy)
{
	CurveVectorFindIntervalBounds(Start, End, CurrentMin, CurrentMax);
}

// Native implementation of NOEXPORT FInterpCurvePoint structures
typedef FInterpCurvePoint<float> FInterpCurvePointFloat;
typedef FInterpCurvePoint<XVECTOR3> FInterpCurvePointVector;

/**
* Template for interpolation curves.
*
* @see FInterpCurvePoint
* @todo Docs: FInterpCurve needs template and function documentation
*/
template<class T>
class FInterpCurve
{
public:

	/** Holds the collection of interpolation points. */
	XArray<FInterpCurvePoint<T>> Points;
	
	// 界面上的显示顺序
	XArray<xint32> PointIndex;


	/** Specify whether the curve is looped or not */
	bool bIsLooped;

	/** Specify the offset from the last point's input key corresponding to the loop point */
	float LoopKeyOffset;

public:

	/** Default constructor. */
	FInterpCurve()
		: bIsLooped(false)
	{
	}

public:

	/**
	* Adds a new keypoint to the InterpCurve with the supplied In and Out value.
	*
	* @param InVal
	* @param OutVal
	* @return The index of the new key.
	*/
	xint32 AddPoint(const float InVal, const T &OutVal);

	void GetPoint(xint32 nKeyIndex, FInterpCurvePoint<T>& point);

	void SetKeyValue(xint32 nKeyIndex, const FInterpCurvePoint<T>& point);
	
	void InsertPoint(xint32 nKeyIndex, const float InVal, const T &OutVal);

	/**
	* Moves a keypoint to a new In value.
	*
	* This may change the index of the keypoint, so the new key index is returned.
	*
	* @param PointIndex
	* @param NewInVal
	* @return
	*/
	xint32 MovePoint(xint32 PointIndex, float NewInVal);

	void DeletePoint(xint32 nPointIndex);

	/** Clears all keypoints from InterpCurve. */
	void Reset();

	/** Set loop key for curve */
	void SetLoopKey(float InLoopKey);

	/** Clear loop key for curve */
	void ClearLoopKey();

	/**
	*	Evaluate the output for an arbitary input value.
	*	For inputs outside the range of the keys, the first/last key value is assumed.
	*/
	T Eval(const float InVal, const T& Default = T(ForceInit)) const;

	/** Automatically set the tangents on the curve based on surrounding points */
	void AutoSetTangents(float Tension = 0.0f, bool bStationaryEndpoints = true);

	/** Calculate the min/max out value that can be returned by this InterpCurve. */
	void CalcBounds(T& OutMin, T& OutMax, const T& Default = T(ForceInit)) const;

	xbool Save(XFileBase* pFile);
	xbool Load(XFileBase* pFile);

public:

	/**
	* Compare equality of two FInterpCurves
	*/
	friend bool operator==(const FInterpCurve& Curve1, const FInterpCurve& Curve2)
	{
		return (Curve1.Points == Curve2.Points &&
			Curve1.bIsLooped == Curve2.bIsLooped &&
			(!Curve1.bIsLooped || Curve1.LoopKeyOffset == Curve2.LoopKeyOffset));
	}

	/**
	* Compare inequality of two FInterpCurves
	*/
	friend bool operator!=(const FInterpCurve& Curve1, const FInterpCurve& Curve2)
	{
		return !(Curve1 == Curve2);
	}

	/**
	* Finds the lower index of the two points whose input values bound the supplied input value.
	*/
	xint32 GetPointIndexForInputValue(const float InValue) const;
};

template<class T>
void FInterpCurve<T>::InsertPoint(xint32 nKeyIndex, const float InVal, const T &OutVal)
{
	xint32 i = 0; for (i = 0; i < Points.Num() && Points[i].InVal < InVal; i++);
	Points.Insert(i, FInterpCurvePoint< T >(InVal, OutVal));

	for (xint32 j = 0; j < PointIndex.Num(); ++j)
	{
		if (PointIndex[j] >= i)
		{
			++PointIndex[j];
		}
	}
	PointIndex.Insert(nKeyIndex, i);
}

template<class T>
void FInterpCurve<T>::SetKeyValue(xint32 nKeyIndex, const FInterpCurvePoint<T>& point)
{
	ASSERT(nKeyIndex >= 0 && nKeyIndex < Points.Num());
	xint32 nIndex = PointIndex[nKeyIndex];

	FInterpCurvePoint<T>* pPoint = &Points[nIndex];
	if (X_Equals(pPoint->InVal, point.InVal, X_EPSILON_FLT32))
	{
		Points[nIndex] = point;
	}
	else
	{
		DeletePoint(nKeyIndex);
		InsertPoint(nKeyIndex, point.InVal, point.OutVal);
		AutoSetTangents(0.0f);
	}
}

template<class T>
void FInterpCurve<T>::GetPoint(xint32 nKeyIndex, FInterpCurvePoint<T>& point)
{
	xint32 nIndex = PointIndex[nKeyIndex];
	point = Points[nIndex];
}

template<class T>
xbool FInterpCurve<T>::Load(XFileBase* pFile)
{
	xint32 nCurveVersion;
	pFile->ReadInt32(nCurveVersion);
	xint32 nPointNum;
	pFile->ReadInt32(nPointNum);
	Points.SetNum(nPointNum);
	PointIndex.SetNum(nPointNum);
	for (xint32 i = 0; i < nPointNum; ++i)
	{
		pFile->ReadInt32(PointIndex[i]);
		pFile->ReadFloat32(Points[i].InVal);
		xuint32 unTemp;
		pFile->Read(&Points[i].OutVal, sizeof(T), &unTemp);
		pFile->Read(&Points[i].ArriveTangent, sizeof(T), &unTemp);
		pFile->Read(&Points[i].LeaveTangent, sizeof(T), &unTemp);
		xint32 nInterpMode;
		pFile->ReadInt32(nInterpMode);
		Points[i].InterpMode = EInterpCurveMode(nInterpMode);
	}
	pFile->ReadBool(bIsLooped);
	pFile->ReadFloat32(LoopKeyOffset);
	return xtrue;
}

template<class T>
xbool FInterpCurve<T>::Save(XFileBase* pFile)
{
	pFile->WriteInt32(CURVE_VERSION);
	pFile->WriteInt32(Points.Num());
	for (xint32 i = 0; i < Points.Num(); ++i)
	{
		pFile->WriteInt32(PointIndex[i]);
		pFile->WriteFloat32(Points[i].InVal);
		xuint32 unTemp;
		pFile->Write(&Points[i].OutVal, sizeof(T), &unTemp);
		pFile->Write(&Points[i].ArriveTangent, sizeof(T), &unTemp);
		pFile->Write(&Points[i].LeaveTangent, sizeof(T), &unTemp);
		pFile->WriteInt32(xint32(Points[i].InterpMode));
	}
	pFile->WriteBool(bIsLooped);
	pFile->WriteFloat32(LoopKeyOffset);
	return xtrue;
}

template<class T>
void FInterpCurve<T>::DeletePoint(xint32 nPointIndex)
{
	xint32 nDeleteIndex = PointIndex[nPointIndex];
	Points.RemoveAt(nDeleteIndex);
	for (xint32 i = 0; i < PointIndex.Num(); ++i)
	{
		if (PointIndex[i] >= nDeleteIndex)
		{
			--PointIndex[i];
		}
	}
	PointIndex.RemoveAt(nPointIndex);
}

/* FInterpCurve inline functions
*****************************************************************************/

template< class T >
xint32 FInterpCurve<T>::AddPoint(const float InVal, const T &OutVal)
{
	xint32 i = 0; for (i = 0; i<Points.Num() && Points[i].InVal < InVal; i++);
	Points.Insert(i, FInterpCurvePoint< T >(InVal, OutVal));

	for (xint32 j = 0; j < PointIndex.Num(); ++j)
	{
		if (PointIndex[j] >= i)
		{
			++PointIndex[j];
		}
	}
	PointIndex.Add(i);
	return i;
}

// 
// template< class T >
// xint32 FInterpCurve<T>::MovePoint(xint32 nIndex, float NewInVal)
// {
// 	if (nIndex < 0 || nIndex >= Points.Num())
// 		return nIndex;
// 
// 	const T OutVal = Points[nIndex].OutVal;
// 	const EInterpCurveMode Mode = Points[nIndex].InterpMode;
// 	const T ArriveTan = Points[nIndex].ArriveTangent;
// 	const T LeaveTan = Points[nIndex].LeaveTangent;
// 
// 	Points.RemoveAt(nIndex);	
// 
// 	xint32 i = 0; for (i = 0; i < Points.Num() && Points[i].InVal < NewInVal; i++);
// 	Points.Insert(i, FInterpCurvePoint< T >(NewInVal, OutVal));
// 
// 	for (xint32 j = 0; j < PointIndex.Num(); ++j)
// 	{
// 		if (PointIndex[j] > nIndex)
// 		{
// 			--PointIndex[j];
// 		}
// 		else if (PointIndex[j] == nIndex)
// 		{
// 			PointIndex[j] = i;
// 		}
// 	}
// 
// 	//const xint32 NewPointIndex = AddPoint(NewInVal, OutVal);
// 	Points[i].InterpMode = Mode;
// 	Points[i].ArriveTangent = ArriveTan;
// 	Points[i].LeaveTangent = LeaveTan;
// 
// 	return i;
// }

// fix flk 修改，同时修正pointindex
template< class T >
xint32 FInterpCurve<T>::MovePoint(xint32 nIndex, float NewInVal)
{
	 if (nIndex < 0 || nIndex >= Points.Num())
		  return nIndex;

	 xint32 nPointIndexIndex = -1;
	 for (xint32 j = 0; j < PointIndex.Num(); ++j)
	 {
		  if (PointIndex[j] == nIndex)
		  {
			   nPointIndexIndex = j;
			   break;
		  }
	 }
	 if (-1 == nPointIndexIndex)
		  return nIndex;

	 const T OutVal = Points[nIndex].OutVal;
	 const EInterpCurveMode Mode = Points[nIndex].InterpMode;
	 const T ArriveTan = Points[nIndex].ArriveTangent;
	 const T LeaveTan = Points[nIndex].LeaveTangent;

	 Points.RemoveAt(nIndex);
	 for (xint32 i = 0; i < PointIndex.Num(); ++i)
	 {
		  if (PointIndex[i] >= nIndex)
		  {
			   --PointIndex[i];
		  }
	 }

	 //const xint32 NewPointIndex = AddPoint(NewInVal, OutVal);
	 xint32 i = 0; for (i = 0; i < Points.Num() && Points[i].InVal < NewInVal; i++);
	 Points.Insert(i, FInterpCurvePoint< T >(NewInVal, OutVal));
	 xint32 NewPointIndex = i;

	 for (xint32 j = 0; j < PointIndex.Num(); ++j)
	 {
		  if (PointIndex[j] >= NewPointIndex)
		  {
			   ++PointIndex[j];
		  }
	 }

	 Points[NewPointIndex].InterpMode = Mode;
	 Points[NewPointIndex].ArriveTangent = ArriveTan;
	 Points[NewPointIndex].LeaveTangent = LeaveTan;

	 PointIndex[nPointIndexIndex] = NewPointIndex;

	 return NewPointIndex;
}


template< class T >
void FInterpCurve<T>::Reset()
{
	Points.Clear();
	PointIndex.Clear();
}


template <class T>
void FInterpCurve<T>::SetLoopKey(float InLoopKey)
{
	// Can't set a loop key if there are no points
	if (Points.Num() == 0)
	{
		bIsLooped = false;
		return;
	}

	const float LastInKey = Points[Points.Num() - 1].InVal;
	if (InLoopKey > LastInKey)
	{
		// Calculate loop key offset from the input key of the final point
		bIsLooped = true;
		LoopKeyOffset = InLoopKey - LastInKey;
	}
	else
	{
		// Specified a loop key lower than the final point; turn off looping.
		bIsLooped = false;
	}
}


template <class T>
void FInterpCurve<T>::ClearLoopKey()
{
	bIsLooped = false;
}


template< class T >
xint32 FInterpCurve<T>::GetPointIndexForInputValue(const float InValue) const
{
	const xint32 NumPoints = Points.Num();
	const xint32 LastPoint = NumPoints - 1;

	ASSERT(NumPoints > 0);

	if (InValue < Points[0].InVal)
	{
		return -1;
	}

	if (InValue >= Points[LastPoint].InVal)
	{
		return LastPoint;
	}

	xint32 MinIndex = 0;
	xint32 MaxIndex = NumPoints;

	while (MaxIndex - MinIndex > 1)
	{
		xint32 MidIndex = (MinIndex + MaxIndex) / 2;

		if (Points[MidIndex].InVal <= InValue)
		{
			MinIndex = MidIndex;
		}
		else
		{
			MaxIndex = MidIndex;
		}
	}

	return MinIndex;
}

template< class T, class U >
static T CubicInterp(const T& P0, const T& T0, const T& P1, const T& T1, const U& A)
{
	const float A2 = A  * A;
	const float A3 = A2 * A;

	return (T)(((2 * A3) - (3 * A2) + 1) * P0) + ((A3 - (2 * A2) + A) * T0) + ((A3 - A2) * T1) + (((-2 * A3) + (3 * A2)) * P1);
}

template< class T >
T FInterpCurve<T>::Eval(const float InVal, const T& Default) const
{
	const xint32 NumPoints = Points.Num();
	const xint32 LastPoint = NumPoints - 1;

	// If no point in curve, return the Default value we passed in.
	if (NumPoints == 0)
	{
		return Default;
	}

	// Binary search to find index of lower bound of input value
	const xint32 Index = GetPointIndexForInputValue(InVal);

	// If before the first point, return its value
	if (Index == -1)
	{
		return Points[0].OutVal;
	}

	// If on or beyond the last point, return its value.
	if (Index == LastPoint)
	{
		if (!bIsLooped)
		{
			return Points[LastPoint].OutVal;
		}
		else if (InVal >= Points[LastPoint].InVal + LoopKeyOffset)
		{
			// Looped spline: last point is the same as the first point
			return Points[0].OutVal;
		}
	}

	// Somewhere within curve range - interpolate.
	ASSERT(Index >= 0 && ((bIsLooped && Index < NumPoints) || (!bIsLooped && Index < LastPoint)));
	const bool bLoopSegment = (bIsLooped && Index == LastPoint);
	const xint32 NextIndex = bLoopSegment ? 0 : (Index + 1);

	const auto& PrevPoint = Points[Index];
	const auto& NextPoint = Points[NextIndex];

	const float Diff = bLoopSegment ? LoopKeyOffset : (NextPoint.InVal - PrevPoint.InVal);

	if (Diff > 0.0f && PrevPoint.InterpMode != CIM_Constant)
	{
		const float Alpha = (InVal - PrevPoint.InVal) / Diff;
		ASSERT(Alpha >= 0.0f && Alpha <= 1.0f);

		if (PrevPoint.InterpMode == CIM_Linear)
		{
			return Lerp(PrevPoint.OutVal, NextPoint.OutVal, Alpha);
		}
		else
		{
			return CubicInterp(PrevPoint.OutVal, PrevPoint.LeaveTangent * Diff, NextPoint.OutVal, NextPoint.ArriveTangent * Diff, Alpha);
		}
	}
	else
	{
		return Points[Index].OutVal;
	}
}

template< class T >
void FInterpCurve<T>::AutoSetTangents(float Tension, bool bStationaryEndpoints)
{
	const xint32 NumPoints = Points.Num();
	const xint32 LastPoint = NumPoints - 1;

	// Iterate over all points in this InterpCurve
	for (xint32 PointIndex = 0; PointIndex < NumPoints; PointIndex++)
	{
		const xint32 PrevIndex = (PointIndex == 0) ? (bIsLooped ? LastPoint : 0) : (PointIndex - 1);
		const xint32 NextIndex = (PointIndex == LastPoint) ? (bIsLooped ? 0 : LastPoint) : (PointIndex + 1);

		auto& ThisPoint = Points[PointIndex];
		const auto& PrevPoint = Points[PrevIndex];
		const auto& NextPoint = Points[NextIndex];

		if (ThisPoint.InterpMode == CIM_CurveAuto || ThisPoint.InterpMode == CIM_CurveAutoClamped)
		{
			if (bStationaryEndpoints && (PointIndex == 0 || (PointIndex == LastPoint && !bIsLooped)))
			{
				// Start and end points get zero tangents if bStationaryEndpoints is true
				ThisPoint.ArriveTangent = T(ForceInit);
				ThisPoint.LeaveTangent = T(ForceInit);
			}
			else if (PrevPoint.IsCurveKey())
			{
				const bool bWantClamping = (ThisPoint.InterpMode == CIM_CurveAutoClamped);
				T Tangent;

				const float PrevTime = (bIsLooped && PointIndex == 0) ? (ThisPoint.InVal - LoopKeyOffset) : PrevPoint.InVal;
				const float NextTime = (bIsLooped && PointIndex == LastPoint) ? (ThisPoint.InVal + LoopKeyOffset) : NextPoint.InVal;

				ComputeCurveTangent(
					PrevTime,			// Previous time
					PrevPoint.OutVal,	// Previous point
					ThisPoint.InVal,	// Current time
					ThisPoint.OutVal,	// Current point
					NextTime,			// Next time
					NextPoint.OutVal,	// Next point
					Tension,			// Tension
					bWantClamping,		// Want clamping?
					Tangent);			// Out

				ThisPoint.ArriveTangent = Tangent;
				ThisPoint.LeaveTangent = Tangent;
			}
			else
			{
				// Following on from a line or constant; set curve tangent equal to that so there are no discontinuities
				ThisPoint.ArriveTangent = PrevPoint.ArriveTangent;
				ThisPoint.LeaveTangent = PrevPoint.LeaveTangent;
			}
		}
		else if (ThisPoint.InterpMode == CIM_Linear)
		{
			T Tangent = NextPoint.OutVal - ThisPoint.OutVal;
			ThisPoint.ArriveTangent = Tangent;
			ThisPoint.LeaveTangent = Tangent;
		}
		else if (ThisPoint.InterpMode == CIM_Constant)
		{
			ThisPoint.ArriveTangent = T(ForceInit);
			ThisPoint.LeaveTangent = T(ForceInit);
		}
	}
}


template< class T >
void FInterpCurve<T>::CalcBounds(T& OutMin, T& OutMax, const T& Default) const
{
	const xint32 NumPoints = Points.Num();

	if (NumPoints == 0)
	{
		OutMin = Default;
		OutMax = Default;
	}
	else if (NumPoints == 1)
	{
		OutMin = Points[0].OutVal;
		OutMax = Points[0].OutVal;
	}
	else
	{
		OutMin = Points[0].OutVal;
		OutMax = Points[0].OutVal;

		const xint32 NumSegments = bIsLooped ? NumPoints : (NumPoints - 1);

		for (xint32 Index = 0; Index < NumSegments; Index++)
		{
			const xint32 NextIndex = (Index == NumPoints - 1) ? 0 : (Index + 1);
			CurveFindIntervalBounds(Points[Index], Points[NextIndex], OutMin, OutMax, 0.0f);
		}
	}
}



///* Common type definitions
//*****************************************************************************/
//
#define DEFINE_INTERPCURVE_WRAPPER_STRUCT(Name, ElementType) \
	struct Name : FInterpCurve<ElementType> \
	{ \
	private: \
		typedef FInterpCurve<ElementType> Super; \
	 \
	public: \
		Name() \
			: Super() \
		{ \
		} \
		 \
		Name(const Super& Other) \
			: Super( Other ) \
		{ \
		} \
	}; 
	

DEFINE_INTERPCURVE_WRAPPER_STRUCT(XInterpCurveFloat, xfloat32)
DEFINE_INTERPCURVE_WRAPPER_STRUCT(XInterpCurveVector2D, XVECTOR2)
DEFINE_INTERPCURVE_WRAPPER_STRUCT(XInterpCurveVector, XVECTOR3)
#endif
