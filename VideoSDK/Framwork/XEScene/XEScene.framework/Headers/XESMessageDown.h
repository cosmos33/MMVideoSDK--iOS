//
//  XESMessageDown.h
//  Pods
//
//  Created by momo783 on 02/28/2018.
//
//

#ifndef XESMESSAGEHIDE_H_
#define XESMESSAGEHIDE_H_

#include "message/XESMessage.h"
#include "core/XESPoints.h"

XESCENE_NAMESPACE_BEGIN

class MessageDown : public Message {
    
public:
    
    enum DownType {
        NONE  = 1,          //  老协议
        ACTOR_PROPERTY = 2, //  属性控制
        ACTOR_MODEL  = 3,   // 模型
        ACTOR_PARTICLE = 4, // 粒子
        ACTOR_LIGHT = 5,    // 灯光
        ACTOR_CONTROL = 6,  // Actor
        ACTION = 7,         // 动作
        ACTION_CONTROL = 8, // 动作控制
        EVENT = 9,          // 事件开关
        GAME_MSG = 10       // 游戏消息
    };
    
    X_INLINE DownType GetDownType() const { return m_eType; }
    
protected:
    
    MessageDown(DownType eType);
    
    virtual ~MessageDown() override;
    virtual void Release() override;
    
    DownType   m_eType;
    
public:
    
    // 下行消息类型
    XString m_strName;
    // 消息左右对象
    XString m_strActorName;
    
    xint32  m_nTag;
    
    virtual xbool Parser(const XString& strMessage) override;
    
    virtual XString JSONString() final { return Message::JSONString(); };
    
};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGEHIDE_H_ */
