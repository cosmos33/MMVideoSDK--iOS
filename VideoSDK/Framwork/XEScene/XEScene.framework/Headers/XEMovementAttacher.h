/******************************************************************************

@File         XEBindSocket.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef _XE_MOVEMENTATTACHER_H
#define _XE_MOVEMENTATTACHER_H
#include "XEActorComponent.h"

//handle the movement of the component.
class XEMovementAttacher
{
public:	
	class Listener
	{
	public:
		virtual			~Listener() {}
		virtual	void	 Ls_OnMoveFinished(XEActorComponent *pComponent){}
	};
	typedef XArray<XEMovementAttacher::Listener*> MovemoentAttacherListenerList;
	XEMovementAttacher();
	virtual ~XEMovementAttacher();

public:	
	// Called every frame
	void Tick(xfloat32 DeltaTime);

public:
	struct MoveableComponent {
		enum MoveState{    MS_NOT_START, MS_MOVING, MS_FINISHED};
		enum MoveDir{      MD_NEGATIVE, MD_POSITIVE};
		enum MoveStrategy{ MG_ONCE, MG_PATROL, MG_CYCLE };
		MoveableComponent() 
			: pComponent(NULL), pCurrentTrack(NULL), bRunning(xfalse), eMoveStrategy(MG_ONCE)
			, eGotoFirstPointState(MS_NOT_START), eCurDir(MD_POSITIVE)
			, fCurGotoFirstPointLen(0.f), fGotoFirstPointLen(0.f), fRunSpeed(60.f), nCurTrackPointIndex(0), fCurSegMoveLen(0.f), fCurTrackSegLen(0.f)
			, vCurGotoFirstPointDir(0.f), vCurGotoFirstPointStartLocation(0.f), qPivotRotation(0.f, 0.f, 0.f){}

		xbool operator == (const MoveableComponent& mc) const
		{
			return pComponent == mc.pComponent;
		}
		XEActorComponent* pComponent;
		XArray<XVECTOR3>* pCurrentTrack;
		xbool             bRunning;
		MoveStrategy      eMoveStrategy;//true for moving positive and negative.
		MoveDir           eCurDir;//true for positive.
		MoveState         eGotoFirstPointState;//the state for going to the first point. 0-not done, 1-doing, 2-done.
		xfloat32          fCurGotoFirstPointLen;//current movement of going to the first point.
		xfloat32          fGotoFirstPointLen;//total movements of going to the first point.
		xfloat32          fRunSpeed;//to determine the current run position.
		xint32            nCurTrackPointIndex;//current index of the track points.
		xfloat32          fCurSegMoveLen;//determine the exact position.
		xfloat32          fCurTrackSegLen;//determine whether to change the points.
		XVECTOR3          vCurGotoFirstPointDir;//current movement direction of going to the first point.
		XVECTOR3          vCurGotoFirstPointStartLocation;//
		XQUATERNION       qPivotRotation;//for turning...
	};
public:
	xbool                 AddMovementComponent(XEActorComponent* pComponent, MoveableComponent::MoveStrategy eMoveStrategy = MoveableComponent::MG_ONCE, XQUATERNION qPivot = XQUATERNION(XETransform::TF_UP, 0.f));
	xbool                 RemoveMovementComponent(XEActorComponent* pComponent);
	xbool                 DoMove(XEActorComponent* pComponent, const XString& szTrackname, const xfloat32 fAtWhatSpeed);
	xbool                 DoStop(XEActorComponent* pComponent);
	xbool                 SetMoveStrategy(XEActorComponent* pComponent, MoveableComponent::MoveStrategy eMoveStrategy = MoveableComponent::MG_PATROL);
	xbool                 SetPivotRotation(XEActorComponent* pComponent, const XQUATERNION& qQ);
	XQUATERNION           GetPivotRotation(XEActorComponent* pComponent);
	xbool                 AddMovementTrack(const XString& szTrackname, const XArray<XVECTOR3>& vTrackPoints);
	xbool                 HasMovementTrack(const XString& szTrackname);
	xbool                 RemoveMovementTrack(const XString& szTrackname);
	MoveableComponent*    GetMovableComponent(XEActorComponent* pComponent);
public:
	XHashTable<XString, XArray<XVECTOR3>> m_mapMovementTrack;
	XArray<MoveableComponent>             m_arrMovementComponents;
	MovemoentAttacherListenerList         m_arrMovementAttacherListeners;
};

#endif //_XE_MOVEMENTATTACHER_H
