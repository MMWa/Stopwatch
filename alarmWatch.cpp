//
// Created by wahba on 18/08/17.
//

#include <iostream>
#include "alarmWatch.h"

using namespace std::chrono_literals;

alarmWatch::alarmWatch() : _runningFlag(false) {}

//TODO: pass function with parameters
//TODO: pass interval time
//TODO: pass repeat iterations
void alarmWatch::alarmEvery(std::function<void()> callableFunc) {
    _callableFunc = callableFunc;
    _runningFlag = true;
    _alarmThread = new std::thread(
            [this]() {
                int x=0;
                while(true){
                    if (!_runningFlag){
                        _runningFlag = !_runningFlag;
                        return;
                    }
                    std::this_thread::sleep_for(100us);
                    _callableFunc();
                    x++;

                    //Quick Test - stops after 5 iterations
                    std::cout << "x is: " << x << std::endl;
                    if (x == 5){
                        _runningFlag = !_runningFlag;
                    }

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

        if(_alarmThread->joinable()){
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
