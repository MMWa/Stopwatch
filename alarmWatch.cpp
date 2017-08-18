//
// Created by wahba on 18/08/17.
//

#include <iostream>
#include "alarmWatch.h"
using namespace std::chrono_literals;

alarmWatch::alarmWatch() : _running(false) {
}
void alarmWatch::alarmEvery() {
    _running = true;
    _alarmThread = new std::thread(
            [this]() {
                int x=0;
                while(true){
                    if (!_running){
                        std::cout << "killed by _" << std::endl;
                        return;
                    }
                    std::this_thread::sleep_for(1ms);

                    x++;
                    std::cout << "x is: " << x << std::endl;

                }
            });
}

void alarmWatch::alarmKill() {
    if(_running){
        _running = !_running;
        if(!_alarmThread->joinable()){
            _alarmThread->join();
        }
    }
}

bool alarmWatch::alarmRunning() {
    return _alarmThread->joinable();
}
