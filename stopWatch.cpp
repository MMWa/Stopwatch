//
// Created by wahba on 17/08/17.
//

#include "stopWatch.h"


stopWatch::stopWatch() : _runningFlag(false) {}

/*!
 * stores current time position and sets runningFlag
 */
void stopWatch::start() {
    _runningFlag = true;
    _startTime = std::chrono::steady_clock::now();
}

/*!
 * resets the start time to current time
 * if stopwatch is running
 */
void stopWatch::restart() {
    if (_runningFlag == true){
        _stopTime = std::chrono::steady_clock::now();
        _elapsed = _stopTime - _startTime;
        _startTime = std::chrono::steady_clock::now();
    }
}

/*!
 * stops the stopwatch
 */
void stopWatch::stop() {
    _stopTime = std::chrono::steady_clock::now();
    _elapsed = _stopTime - _startTime;
    _runningFlag = false;
}

bool stopWatch::isRunning() {
    return _runningFlag;
}

/*!
 * get the last elapsed time
 * @return the last start - stop duration
 */
const std::chrono::duration<double> &stopWatch::get_elapsed() const {
    return _elapsed;
}
/*!
 * ge the curent runtime
 * @return the time since start if stopwatch is running
 */
std::chrono::duration<double> stopWatch::get_runTime() {
    if (_runningFlag){
        return _stopTime - _startTime;
    } else {
        return std::chrono::microseconds(0);
    }
}



