//
// Created by wahba on 17/08/17.
//

#ifndef WATCHTIME_STOPWATCH_H
#define WATCHTIME_STOPWATCH_H


#include <chrono>

class stopWatch {
public:

    stopWatch();

    void stopWatch_Start();

    void stopWatch_Stop();

    void stopWatch_Restart();

    bool stopWatch_isRunning();

    std::chrono::duration<double> &get_elapsed();
    std::chrono::duration<double> get_runTime();
private:
    bool _runningFlag;
    std::chrono::time_point<std::chrono::steady_clock> _startTime;
    std::chrono::time_point<std::chrono::steady_clock> _stopTime;
    std::chrono::duration<double> _elapsed;
};


#endif //WATCHTIME_STOPWATCH_H
