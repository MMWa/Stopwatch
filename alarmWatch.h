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
    void alarmEvery();
    void alarmKill();
    bool alarmRunning();

private:
    stopWatch internalTimer;
    std::thread *_alarmThread;
    std::atomic<bool> _running;

};


#endif //WATCHTIME_ALARMWATCH_H
