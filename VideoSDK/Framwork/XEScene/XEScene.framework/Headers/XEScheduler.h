//
// Created by HongjieFu on 2018/7/2.
//

#ifndef PODS_XESCHEDULER_H
#define PODS_XESCHEDULER_H


#import <functional>
#import <list>
#import <ctime>
#import "XESDefine.h"

XESCENE_NAMESPACE_BEGIN

    typedef int SchduleTaskId;
    typedef std::function<void(SchduleTaskId)> SchedulerFunc;

    XESS_HIDE_START struct Task {
        SchduleTaskId taskId;
        float interval;
        int repeat;
        float delay;
        SchedulerFunc callFunc;
        xuint64 nextCallTime;
        int repeated;
    };XESS_HIDE_END

    class Scheduler {

    public:

        XESS_MANUAL static SchduleTaskId schedule(
                SchedulerFunc callFunc,
                float interval = -1,
                int repeat = -1,
                float delay = 0);

        XESS_MANUAL static SchduleTaskId scheduleOnce(
                SchedulerFunc callFunc,
                float interval = -1,
                float delay = 0);

        static bool unschedule(SchduleTaskId);

        static void unscheduleAll();

        XESS_IGNORE static void doUpdate();

        static xuint64 time();

        XESS_HIDE_START class SchedulerTaskPool {

        public:
            SchedulerTaskPool();

            virtual ~SchedulerTaskPool();

        public:
            std::list<SchduleTaskId> _tasksShouldBeRemove;
            std::list<Task> _tasks;

            void doUpdate();

        };

        XESS_HIDE_END

    private:
        static SchedulerTaskPool *getSchedulerTaskPool();
    };

XESCENE_NAMESPACE_END

#endif //PODS_XESCHEDULER_H
