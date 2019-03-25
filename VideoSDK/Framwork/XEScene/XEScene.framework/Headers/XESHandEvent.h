//
// Created by momo783 on 20/08/2018.
//

#ifndef PODS_XESHANDEVENT_H
#define PODS_XESHANDEVENT_H

#include "core/events/XESEvent.h"
#include "core/XESHand.h"

XESCENE_NAMESPACE_BEGIN

class HandEvent : public Event {

public:
    HandEvent();

    virtual ~HandEvent() override;
    virtual void Release() override;

    X_INLINE XArray<xes::Hand*> GetHands() const { return m_arrHands; }

    void  SetHands(XArray<xes::Hand*> arrHands) { m_arrHands = arrHands; }


protected:

    XArray<xes::Hand*> m_arrHands;
};

XESCENE_NAMESPACE_END

#endif //PODS_XESHANDEVENT_H
