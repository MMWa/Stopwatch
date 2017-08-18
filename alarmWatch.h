//
// Created by wahba on 18/08/17.
//

#ifndef WATCHTIME_ALARMWATCH_H
#define WATCHTIME_ALARMWATCH_H


#include <thread>
#include <atomic>
#include "stopWatch.h"

class alarmWatch {
public:
    alarmWatch();
    //alarmWatch(const stopWatch &internalTimer);
    void alarmEvery(std::function<void()> callableFunc);
    void alarmKill();
    bool alarmRunning();

private:
    std::function<void()> _callableFunc;

    int _parameter;

    std::thread *_alarmThread;
    std::atomic<bool> _runningFlag;

};


#endif //WATCHTIME_ALARMWATCH_H
