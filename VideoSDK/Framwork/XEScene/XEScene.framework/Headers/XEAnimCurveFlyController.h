/******************************************************************************

@File         XEAnimCurveFlyController.h

@Version       1.0

@Created      2018, 12, 28

@Description  The class ids of each class in X Editor, A fly controller using a curve that can apply to an actor, etc.

@HISTORY:

******************************************************************************/

#include "XCurve.h"
#include "XClassReflector.h"
#include "XEUtility.h"
#include "XEAnimController.h"

class XEWorld;
class XEActor;
class XEActorComponent;
class XBaseCamera;
class XEAnimCurveFlyController
	:public XEAnimController
{
	typedef XEAnimController Super;
public:
	// Called every frame
	XEAnimCurveFlyController() :m_fDuration(0.f), m_fElapseTime(0.f), m_eFlyAccelerationType(FAT_ATAN),m_pCurFlyTemporalObject(NULL){}
	virtual ~XEAnimCurveFlyController(){}
	enum eCanDriveObjectType{ AT_ACTOR, AT_COMPONENT, AT_CAMERA_BASE };
	enum eFlyAccelerationType{ FAT_LINEAR, FAT_ATAN };

	X_CLASS_DEF(XEAnimCurveFlyController)
	class Listener
		:public XEAnimController::Listener
	{
	public:
		Listener(){}
		virtual ~Listener(){}
		X_EES_LINE virtual void Ls_Flying(XEAnimCurveFlyController* pController, xfloat32 fCurTime, const XMATRIX4& mat4){}//you can do something with the controller, e.g, pause the flying at a pecific.
	};
private:
	class TemporalObject :public XEUtility::XEDelayDestroyer
	{
		friend class XEAnimCurveFlyController;
	protected:
		TemporalObject(XEAnimCurveFlyController* pController, eCanDriveObjectType type, void* target) :controller(pController), eType(type), done(xfalse), target(target){}
		virtual xbool ShouldBeDeleted() override{ return done; }
		virtual void  Tick(xfloat32 fDel) override;
		virtual void  Release() override{ done = xtrue; }
		XEAnimCurveFlyController* controller;
		xbool done;
		eCanDriveObjectType eType;
		union
		{
			void* target;
			XEActor* actor;
			XEActorComponent* component;
			XBaseCamera* baseCamera;  
		};
	};
public:
	virtual xint32                     GetTimeLength() const override;
	virtual void                       SetTime(xint32 nTime) override;//in micro seconds.
	virtual void                       Stop() override;
	virtual void                       BroadcastPlayOneTimeFinished(xbool bReversePlaying) override;
public:						           
	X_FORCEINLINE void                 SetFlyDuration(xfloat32 fTime){ m_fDuration = fTime; }//in seconds.
	X_FORCEINLINE xfloat32             GetFlyDuration()const{ return m_fDuration; }
	X_FORCEINLINE xfloat32             GetCurElapseTime()const{ return m_fElapseTime; }
	//curve mini-point-count: start,end.
	void                               SetFlyBegin(const XMATRIX4& mat4);
	void                               SetFlyBegin(const XVECTOR3& vLocation, const XVECTOR3& vForwardDir, const XVECTOR3&vUp);
	void                               SetFlyBegin(const XVECTOR3& vLocation, const XQUATERNION& quat);
	void                               SetFlyBegin(const XVECTOR3& vLocation, xfloat32 fRoll, xfloat32 fYaw, xfloat32 fPitch = 0.f);//z round - is forbidden by default.
	void                               SetFlyEnd(const XMATRIX4& mat4);
	void                               SetFlyEnd(const XVECTOR3& vLocation, const XVECTOR3& vForwardDir, const XVECTOR3& vUp);
	void                               SetFlyEnd(const XVECTOR3& vLocation, const XQUATERNION& quat);
	void                               SetFlyEnd(const XVECTOR3& vLocation, xfloat32 fRoll, xfloat32 fYaw, xfloat32 fPitch = 0.f);//z round - is forbidden by default.
	void                               SetupFlyPoint(const XMATRIX4& mat4, xfloat32 fPercent);//optional for adding a point to the curve. points with the explicit inValue(fPercent) will be replaced.
	xbool                              FlyToPercent(xfloat32 fPercent, XMATRIX4& matResult);//0-1
	xbool                              FlyToTimestamp(xfloat32 fTimestamp, XMATRIX4& matResult);//0-duration, in seconds.
	xfloat32                           GetCurFlyPercent()const;
	void                               Fly(XEWorld* pWorld, eCanDriveObjectType objType, void* pFlyObject, eFlyAccelerationType accelerateType = FAT_ATAN);//fly in world
private:				               
	xfloat32                           m_fDuration;//in seconds.
	xfloat32                           m_fElapseTime;//in seconds.
	eFlyAccelerationType               m_eFlyAccelerationType;
	XInterpCurveVector                 m_fFlyLocationCurve;
	FInterpCurve<XQUATERNION>          m_fFlyRotationcurve;//in quaternion.
	TemporalObject*                    m_pCurFlyTemporalObject;
};
