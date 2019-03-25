//
// Created by HongjieFu on 2018/7/14.
//

#ifndef PODS_XESLUASYSTEMHANDLER_H
#define PODS_XESLUASYSTEMHANDLER_H

#include "core/XESSystemEventDispatcher.h"

using namespace xes;

class LuaSystemHandler : public SystemEventHandler {

public:
    void onStart() override;

    void onResume() override;

    void onPause() override;

    void onEnd() override;

private :
    void callLuaLifeCycleMethod(const char *methodName);

};


#endif //PODS_XESLUASYSTEMHANDLER_H
