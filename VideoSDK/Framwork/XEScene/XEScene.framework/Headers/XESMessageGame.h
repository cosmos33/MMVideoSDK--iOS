//
// Created by momo783 on 10/05/2018.
//

#ifndef XES_XESMESSAGEGAME_H
#define XES_XESMESSAGEGAME_H

#include "message/down/XESMessageDown.h"
#include "core/XESGeometry.h"

XESCENE_NAMESPACE_BEGIN

class MessageGameAction : public MessageDown {
public:
    MessageGameAction();

    xbool Parser(const XString &strMessage) override;

public:

    xbool m_bEnable;

    XString m_TargetName;
    
    XString m_Expression;
    
    Rect m_TriggerBounds;

protected:
    ~MessageGameAction() override;

    void Release() override;

    friend class Message;
};

XESCENE_NAMESPACE_END


#endif //XES_XESMESSAGEGAME_H
