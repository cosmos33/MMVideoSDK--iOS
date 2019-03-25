//
// Created by momo783 on 09/05/2018.
//

#ifndef XES_XESEXPRESSIONEVENTLISTENER_H
#define XES_XESEXPRESSIONEVENTLISTENER_H

#include "core/events/XESEventListener.h"

XESCENE_NAMESPACE_BEGIN

class Expression;

class ExpressionEventListener : public EventListener {

protected:
    ExpressionEventListener();
    xbool Init();

public:
    static const ListenerID LISTENER_ID;

    static ExpressionEventListener* Create();

    virtual ~ExpressionEventListener() override;
    virtual void Release() override;

    virtual xbool CheckAvailable() override;
    virtual ExpressionEventListener* Clone() override;

public:

    typedef std::function<void(const XArray<Expression*>&, Event*)> ExpressionsCallback;

    ExpressionsCallback OnExpressionEventCallback;

private:

    friend class EventDispatcher;

};

XESCENE_NAMESPACE_END


#endif //XES_XESEXPRESSIONEVENTLISTENER_H
