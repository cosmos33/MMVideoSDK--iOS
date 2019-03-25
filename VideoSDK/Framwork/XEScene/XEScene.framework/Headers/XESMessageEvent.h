//
//  XESMessageEvent.h
//  XEScene
//
//  Created by momo783 on 01/04/2018.
//

#ifndef XESMESSAGEEVENT_H_
#define XESMESSAGEEVENT_H_

#include "message/down/XESMessageDown.h"

XESCENE_NAMESPACE_BEGIN

class MessageDownEvent : public MessageDown {
    
public:
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    xbool m_bEnable;
    xint32 m_skipTimes;
    
    XString m_EvSubType;
    
    xfloat32 m_fInterval;
    
protected:
    
    MessageDownEvent();
    virtual ~MessageDownEvent() override {};
    virtual void Release() override {};
    
    friend class Message;
};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGEEVENT_H_ */
