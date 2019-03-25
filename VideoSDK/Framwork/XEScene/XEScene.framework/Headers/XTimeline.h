#ifndef _XTIMELINE_H_
#define _XTIMELINE_H_

#include "XTypes.h"

enum TimelineAdvanceRet
{
    TL_ADV_RET_NORMAL,
    TL_ADV_RET_FINISH,
    TL_ADV_RET_LOOP
};

enum AnimationWrapMode
{
	ANIM_WRAP_ONCE,
	ANIM_WRAP_LOOP,
	ANIM_WRAP_PINGPONG,
	ANIM_WRAP_CLAMPFOREVER,
	ANIM_WRAP_NUM
};

class XTimeline
{
public:
							XTimeline();
	virtual                 ~XTimeline();

	xfloat32				GetCurrentTime() const;
	void					SetCurrentTime(xfloat32 fCurTime);	
	xfloat32				GetLoopBegin() const;
	void					SetLoopBegin(xfloat32 fLoopBegin);
	xfloat32				GetLoopEnd() const;
	void					SetLoopEnd(xfloat32 fLoopEnd);
	xbool					IsLooped() const;
	void					SetLooped(xbool fIsLooped);
	AnimationWrapMode		GetWrapMode() const;
	void					SetWrapMode(AnimationWrapMode WrapMode);

	TimelineAdvanceRet		Advance(xfloat32 deltaTime);
private:
	AnimationWrapMode		m_eWrapMode;
	xfloat32				m_fLoopBegin;
	xfloat32				m_fLoopEnd;
	xfloat32				m_fTime;
	xbool					m_bLoop;
};

#endif
