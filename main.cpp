#include <iostream>
#include "stopWatch.h"
#include "alarmWatch.h"
using namespace std::chrono_literals;

int main() {

    stopWatch timerTest{};

    alarmWatch alarm{};


    int x = 0;

    if (!alarm.alarmRunning()){
        alarm.alarmEvery();
        timerTest.start();
    }
    while ( x < 100000){
        std::cout << " hey "<< x << std::endl;
        x++;
    }
    timerTest.stop();

    alarm.alarmKill();

    std::cout << timerTest.get_elapsed().count() << std::endl;

    return 0;
}