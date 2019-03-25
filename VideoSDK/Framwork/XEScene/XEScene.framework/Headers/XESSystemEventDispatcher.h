//
// Created by HongjieFu on 2018/7/14.
//

#ifndef PODS_XESSYSTEMEVENTDISPATCHER_H
#define PODS_XESSYSTEMEVENTDISPATCHER_H

#import "XESDefine.h"

XESCENE_NAMESPACE_BEGIN

    class SystemEventHandler {

    public:

        virtual void onStart() = 0;

        virtual void onResume() = 0;

        virtual void onPause() = 0;

        virtual void onEnd() = 0;
    };

    class SystemEventDispatcher {

    public:
        static SystemEventDispatcher *GetInstance();

        void SetHandler(SystemEventHandler *handler);

        void RemoveHandler();

        void callStart();

        void callResume();

        void callPause();

        void callEnd();

    private:
        SystemEventHandler *_handler;

    };

XESCENE_NAMESPACE_END
#endif //PODS_XESSYSTEMEVENTDISPATCHER_H
