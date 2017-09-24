//
// Created by wahba on 18/08/17.
//

#include <iostream>
#include <utility>
#include <unordered_map>
#include "alarmWatch.h"

class duration;

using namespace std::chrono_literals;

alarmWatch::alarmWatch() : _runningFlag(false) {}

void alarmWatch::alarmEvery(int repeats, std::chrono::duration<float, std::ratio<1, 100000000>> __timeD,
                            std::function<void()> callableFunc) {
    //catch if we call for zero duration
    if (__timeD <= __timeD.zero()) {
        return;
    }

    _callableFunc = std::move(callableFunc);
    _runningFlag = true;
    _alarmThread = new std::thread(

            [this, __timeD, repeats]() {
                int x = 0;
                while (true) {
                    for (int x = 0; x <= repeats; x++) {
                        if (!_runningFlag) {
                            _runningFlag = !_runningFlag;
                            return;
                        }

                        std::this_thread::sleep_for(__timeD);
                        _callableFunc();
                        //Quick Test - stops after 5 iterations
                        //std::cout << "x is: " << x << std::endl;

                    }
                    _runningFlag = !_runningFlag;

                }
            });
}

/*!
 * If on it will change the running flag
 * forcing the working thread to return
 */
void alarmWatch::alarmKill() {
    //check if the thread is running and if so
    //join it
    if (alarmRunning()) {
        _runningFlag = !_runningFlag;

        if (_alarmThread->joinable()) {
            _alarmThread->join();
        }
    }
}

/*!
 * indicates whether the alarm is on or off
 * @return thread's joinable status, thus telling us if its working or not
 */
bool alarmWatch::alarmRunning() {
    return _runningFlag;
}
