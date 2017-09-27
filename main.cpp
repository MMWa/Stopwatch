#include <iostream>
#include <chrono>
#include "stopWatch.h"
#include "alarmWatch.h"


using namespace std::chrono_literals;

int main() {

    alarmWatch alarmFunc{};
    std::cout << "Pass Function test: " << std::endl;

    //test use 1
    if (!alarmFunc.alarmRunning()) {
        int x = 0;
        //takes number of iterations and period
        //feed it a function or a lambda
        alarmFunc.alarmEvery(5, 1s, [&x]() {
            //std::this_thread::sleep_for(2ms);
            std::cout << "hello lambda " << x << std::endl;
            x++;
        });
    }

    //make thread sleep for less that operation time to prove its stoppable
    std::this_thread::sleep_for(2s);

    //use the kill function to stop
    //alarmFunc.alarmKill();
    //output elapsed time
    while (alarmFunc.alarmRunning()) {}
    std::cout << "Elapsed time: " << alarmFunc.get_runTime().count() << std::endl;


    //test use 2
    if (alarmFunc.whenDoneSet()) {
        std::cout << "when done Function set" << std::endl;
    } else {
        std::cout << "when done Function not set" << std::endl;
    }

    alarmFunc.whenDone(
            []() {
                std::cout << "when done function called" << std::endl;
            }
    );

    if (alarmFunc.whenDoneSet()) {
        std::cout << "when done Function set" << std::endl;
    } else {
        std::cout << "when done Function not set" << std::endl;
    }

    alarmFunc.alarmEvery(
            0, 20ms, []() {
                std::cout << "hello lambda for once" << std::endl;
            }
    );

    //wait till done executing
    while (alarmFunc.alarmRunning()) {}
    return 0;
}