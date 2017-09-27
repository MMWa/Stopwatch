//
// Created by wahba on 18/08/17.
//

#ifndef WATCHTIME_ALARMWATCH_H
#define WATCHTIME_ALARMWATCH_H


#include <thread>
#include <atomic>
#include <functional>
#include "stopWatch.h"

class alarmWatch : public stopWatch {
public:

    alarmWatch();
    void alarmEvery(int, std::chrono::duration<float, std::ratio<1, 100000000>>, std::function<void()> callableFunc);
    void alarmKill();
    bool alarmRunning();

    void whenDone(std::function<void()> callableFunc);
    void whenDoneClear();

    bool whenDoneSet();

private:
    void __Kill();
    std::function<void()> _callableFunc, _whenDone;
    std::thread *_alarmThread;
    std::atomic<bool> _thread_runningFlag, _whenDoneFlag;

};


#endif //WATCHTIME_ALARMWATCH_H
