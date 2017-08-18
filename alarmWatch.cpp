//
// Created by wahba on 18/08/17.
//

#include <iostream>
#include "alarmWatch.h"

using namespace std::chrono_literals;

alarmWatch::alarmWatch() : _runningFlag(false) {}

void alarmWatch::alarmEvery() {

    _runningFlag = true;
    _alarmThread = new std::thread(
            [this]() {
                int x=0;
                while(true){
                    if (!_runningFlag){
                        std::cout << "killed by _" << std::endl;
                        return;
                    }
                    std::this_thread::sleep_for(1ms);

                    x++;
                    std::cout << "x is: " << x << std::endl;

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
    if(alarmRunning()){
        _runningFlag = !_runningFlag;
        if(!_alarmThread->joinable()){
            _alarmThread->join();
        }
    }
}

/*!
 * indicates whether the alarm is on or off
 * @return thread's joinable status, thus telling us if its working or not
 */
bool alarmWatch::alarmRunning() {
    return !_alarmThread->joinable();
}
