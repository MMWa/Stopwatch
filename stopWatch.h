//
// Created by wahba on 17/08/17.
//

#ifndef WATCHTIME_STOPWATCH_H
#define WATCHTIME_STOPWATCH_H


#include <chrono>

class stopWatch {
public:

    stopWatch();

    void startWatch();

    void restartWatch();

    void watchStop();

    bool isRunning();

    const std::chrono::duration<double> &get_elapsed() const;
    std::chrono::duration<double> get_runTime();
private:
    bool _runningFlag;
    std::chrono::time_point<std::chrono::steady_clock> _startTime;
    std::chrono::time_point<std::chrono::steady_clock> _stopTime;
    std::chrono::duration<double> _elapsed;
};


#endif //WATCHTIME_STOPWATCH_H
