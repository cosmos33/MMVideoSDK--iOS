//
//  XESMessageAction.h
//  XEScene
//
//  Created by momo783 on 01/04/2018.
//

#ifndef XESMESSAGEACTION_H_
#define XESMESSAGEACTION_H_

#include "message/down/XESMessageDown.h"

XESCENE_NAMESPACE_BEGIN

class MessageDownAction : public MessageDown {
    
public:
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    // 动作间隔
    xfloat32 m_fDuration;
    xint32   m_Tag;// 动作ID
    xbool    m_bSpeedControl;
    
    Points  *m_Points;
    xbool   m_bRepeat;
    xint32  m_nRepeatTimes;
    
    xfloat32 m_fValue;
    XVECTOR3 m_fVectorValue;
    
protected:
    
    MessageDownAction();
    virtual ~MessageDownAction() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageDownActionControl : public MessageDown {
    
public:
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    // 目标动作ID
    xint32   m_ForTag;
    
    xfloat32 m_fValue;
    
protected:
    
    MessageDownActionControl();
    virtual ~MessageDownActionControl() override {};
    virtual void Release() override {};
    
    friend class Message;
};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGEACTION_H_ */
