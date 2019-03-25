//
//  XESMessageUp.h
//  Pods
//
//  Created by momo783 on 02/28/2018.
//
//

#ifndef XESMESSAGESCORE_H_
#define XESMESSAGESCORE_H_

#include "message/XESMessage.h"

XESCENE_NAMESPACE_BEGIN

class MessageUp : public Message {
    
public:
    
    enum UpType {
        NONE  = 0,
        SCORE = -1,
        FACE  = -2,
        TOUCH = -3,
        SENSOR= -4,
        OBJECT= -5
    };
    
    X_INLINE UpType GetType() const { return m_eType; }
    
    XString m_actName;
    
protected:
    
    MessageUp(UpType eType);
    
    virtual ~MessageUp() override;
    virtual void Release() override;
    
    UpType   m_eType;
    
};

class MessageScore : public MessageUp {
    
public:
    
    static MessageScore* Create();
    
    virtual XString JSONString() override;
    
public:
    
    xbool m_nValue;
    XString m_strName;
    
protected:
    
            MessageScore();
    virtual ~MessageScore() override {};
    virtual void Release() override {};
    
    virtual xbool Parser(const XString& strMessage) override;
};

class MessageUpScore : public MessageUp {
    
public:
    
    static MessageUpScore* Create();
    
    virtual XString JSONString() override;
    
public:
    
    xbool m_nValue;
    
protected:
    
    MessageUpScore();
    virtual ~MessageUpScore() override {};
    virtual void Release() override {};
    
    virtual xbool Parser(const XString& strMessage) override;
};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGESCORE_H_ */
