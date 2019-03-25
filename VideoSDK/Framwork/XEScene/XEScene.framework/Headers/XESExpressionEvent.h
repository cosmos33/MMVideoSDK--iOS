//
// Created by momo783 on 09/05/2018.
//

#ifndef XES_XESEXPRESSIONEVENT_H
#define XES_XESEXPRESSIONEVENT_H

#import "core/XESFace.h"
#import "core/events/XESEvent.h"

XESCENE_NAMESPACE_BEGIN

class ExpressionEvent : public  Event {
public:
    ExpressionEvent();

    ~ExpressionEvent() override;

    void Release() override;

    void SetExpressions(XArray<Expression*> mExpressions) { m_arrExpressions = mExpressions; };

    X_INLINE XArray<Expression*> GetExpressions() const { return m_arrExpressions; }

protected:

    XArray<Expression*> m_arrExpressions;
};

XESCENE_NAMESPACE_END


#endif //XES_XESEXPRESSIONEVENT_H
