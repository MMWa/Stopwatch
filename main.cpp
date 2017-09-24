#include <iostream>
#include "stopWatch.h"
#include "alarmWatch.h"

using namespace std::chrono_literals;

int main() {

    stopWatch timerTest{};

    alarmWatch alarmFunc{};

    std::cout << "Pass Function test: " << std::endl;

    if (!alarmFunc.alarmRunning()) {
        alarmFunc.alarmEvery(50, 20ms, []() {
            std::cout << "hello lambda" << std::endl;
        });
        timerTest.start();
    }

    while (alarmFunc.alarmRunning()) {}
    timerTest.stop();

    alarmFunc.alarmKill();

    std::cout << timerTest.get_elapsed().count() << std::endl;

    return 0;
}