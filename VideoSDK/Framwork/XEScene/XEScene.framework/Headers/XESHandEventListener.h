//
// Created by momo783 on 20/08/2018.
//

#ifndef PODS_XESHANDEVENTLISTENER_H
#define PODS_XESHANDEVENTLISTENER_H

#include "core/events/XESEventListener.h"

XESCENE_NAMESPACE_BEGIN

    class Hand;

    class HandEventListener : public EventListener {

    XESCENE_CONSTRUCTOR_ACCESS:
        HandEventListener();
        xbool Init();

    public:
        static const ListenerID LISTENER_ID;

        static HandEventListener* Create();

        virtual ~HandEventListener() override;
        virtual void Release() override;

        virtual xbool CheckAvailable() override;
        virtual HandEventListener* Clone() override;

    public:

        typedef std::function<void(const XArray<xes::Hand*>&, Event*)> HandsCallback;
        
        HandsCallback OnHandTrackingCallback;

    private:

        friend class EventDispatcher;
    };

XESCENE_NAMESPACE_END


#endif //PODS_XESHANDEVENTLISTENER_H
