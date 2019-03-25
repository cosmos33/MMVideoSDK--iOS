//
// Created by momo783 on 09/05/2018.
//

#ifndef XES_XESGAMEMESSAGEHANDLER_H
#define XES_XESGAMEMESSAGEHANDLER_H

#include "core/XESObject.h"
#include "message/XESMessageManager.h"

XESCENE_NAMESPACE_BEGIN

class SceneGameFilter;
class GameMessageHandler
: public Object
, public MessageManager::ReceiveListener
{
public:

    GameMessageHandler(SceneGameFilter *pFilter);

    virtual ~GameMessageHandler() override;
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

    SceneGameFilter*   m_pFilter;
};

XESCENE_NAMESPACE_END


#endif //XES_XESGAMEMESSAGEHANDLER_H
