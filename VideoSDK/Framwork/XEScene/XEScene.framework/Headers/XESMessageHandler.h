//
//  XESMessageHandler.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESMESSAGEHANDLER_H_
#define XESMESSAGEHANDLER_H_

#include "core/XESObject.h"
#include "scene/XESScene.h"
#include "message/XESMessageManager.h"

XESCENE_NAMESPACE_BEGIN

class Module;
class SceneVideoGameFilter;

class MessageHandler
: public Object
, public MessageManager::ReceiveListener
{
    
public:
    
    MessageHandler(SceneVideoGameFilter *pFilter);
    
    virtual ~MessageHandler() override;
    virtual void Release() override;
    
public:
    
    virtual xbool   OnReceivedMessage(Message *pMessage) override;
    void            SendScoreMessage(const XString &actorName, xbool bSuccess);
    
protected:
    
    void    ReceivedActorMessage(XEActor* pActor, Message *pMessage);
    void    ReceivedActionMessage(XEActor* pActor, Message *pMessage);
    void    ReceivedEventMessage(XEActor* pActor, Message *pMessage);
    
    void    ReceivedLowVersionMessage(XEActor *pActor, Message *pMessage);
    
private:
    
    SceneVideoGameFilter*   m_pFilter;

};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGEHANDLER_H_ */
