//
//  XESMessage.h
//  Pods
//
//  Created by momo783 on 02/28/2018.
//
//

#ifndef XESMESSAGE_H_
#define XESMESSAGE_H_

#include "core/XESObject.h"

XESCENE_NAMESPACE_BEGIN

class Message : public Object
{
public:
    enum Type {
        UP,
        DOWN
    };
    
    X_INLINE Type GetType() const { return m_MsgType; }
    
public:
    
    Message(Type nType);
    
    virtual ~Message() override;

    virtual void Release() override;
    
public:
    // 解析成 Message 对象
    virtual xbool Parser(const XString& strMessage) = 0;
    
    // 获取 Message JSON 序列化数据
    virtual XString JSONString();
    
    template<typename castType> static castType* Create(const XString& strMessage);
    
    template<typename castType> castType* CastMessage();
    
protected:
    Type m_MsgType;
    
};

template <typename castType> castType* Message::Create(const XString& strMessage) {
    castType* msg = new castType();
    if (static_cast<Message*>(msg)->Parser(strMessage)) {
        return msg;
    }
    X_SAFEDELETE(msg);
    return nullptr;
};

template <typename castType> castType* Message::CastMessage() {
    return static_cast<castType*>(this);
};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGE_H_ */
