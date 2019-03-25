#ifndef _XANIMATABLE_H_
#define _XANIMATABLE_H_

#include "XMemBase.h"

/************************************************************************/
/* 一个基于时间的动画组件,具有基本控制功能接口								*/
/************************************************************************/
class IXAnimatable: public XMemBase
{
public:
    virtual                         ~IXAnimatable() {}
    virtual void                    Play() = 0;
    virtual void                    Pause() = 0;
    virtual void                    Resume() = 0;
    virtual xbool					IsPaused() const = 0;
    virtual xfloat32				GetStartTime() const = 0;
    virtual xfloat32				GetEndTime() const = 0;
	virtual xfloat32				GetCurrentTime() const = 0;
    virtual void                    Update(xfloat32 fTime) = 0;
};

#endif
