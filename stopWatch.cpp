//
// Created by wahba on 17/08/17.
//

#include "stopWatch.h"

stopWatch::stopWatch() : _runningFlag(false) {}

void stopWatch::start() {
    _runningFlag = true;
    _startTime = std::chrono::steady_clock::now();
}

void stopWatch::restart() {
    _runningFlag = true;
    _stopTime = std::chrono::steady_clock::now();
    _elapsed = _stopTime - _startTime;
    _startTime = std::chrono::steady_clock::now();
}

void stopWatch::stop() {
    _stopTime = std::chrono::steady_clock::now();
    _elapsed = _stopTime - _startTime;
    _runningFlag = false;
}

bool stopWatch::isRunning() {
    return _runningFlag;
}

const std::chrono::duration<double> &stopWatch::get_elapsed() const {
    return _elapsed;
}

std::chrono::duration<double> stopWatch::get_runTime() {
    return _stopTime - _startTime;
}



