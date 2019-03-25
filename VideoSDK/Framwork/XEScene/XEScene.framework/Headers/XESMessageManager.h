//
//  XESMessageManager.h
//  Pods
//
//  Created by momo783 on 02/28/2018.
//
//

#ifndef XESMESSAGEMANAGER_H_
#define XESMESSAGEMANAGER_H_

#include "core/XESObject.h"
#include "message/XESMessage.h"
#include <functional>

class XEActor;

XESCENE_NAMESPACE_BEGIN

class Module;
class MessageManager : public Object
{
    
public:
    static MessageManager* GetInstance();
    
    // 发送消息
    void Send(Message* pMessage);
    
    // 接收消息
    void Received(Message* pMessage);
    void Received(const XString& strMessage);
    
    
public:
    typedef std::function<void(const XString&)> MessageSendListener;
    
    // 添加消息监听
    MessageSendListener OnMessageSendEvent;
    
public:
    class   ReceiveListener {
    public:
        ReceiveListener() {};
        virtual ~ReceiveListener() {};
    public:
        virtual xbool OnReceivedMessage(Message *pMessage){return xfalse;};
    };
    
    void    AddMessageReciveListener(ReceiveListener* pListener);
    void    RemoveMessageReceiveListener(ReceiveListener* pListener);
    
private:
    
    MessageManager();
    virtual ~MessageManager() override;
    virtual void Release() override;
    
    Message* ParserMessage(const XString& strMessage);
    
protected:
    
    XArray<ReceiveListener*> m_arrListeners;
    
};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGEMANAGER_H_ */
