#include <iostream>
#include "stopWatch.h"
#include "alarmWatch.h"
using namespace std::chrono_literals;

int main() {

    stopWatch timerTest{};

    alarmWatch alarm{};

    std::cout << "thread Running: " << alarm.alarmRunning() << std::endl;

    if (!alarm.alarmRunning()){
        alarm.alarmEvery();
        timerTest.start();
    }
    std::cout << alarm.alarmRunning() << std::endl;

    while (alarm.alarmRunning()){}
    timerTest.stop();

    alarm.alarmKill();
    std::cout << timerTest.get_elapsed().count() << std::endl;

    return 0;
}