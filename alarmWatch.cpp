//
// Created by wahba on 18/08/17.
//

#include <iostream>
#include "alarmWatch.h"


alarmWatch::alarmWatch() : _thread_runningFlag(false), _whenDoneFlag(false) {}

/*!
 *
 * @param repeats the number of times the alarm is to run
 * @param __timeD the frequency at which the alarm function is called
 * @param callableFunc function to be called at every iteration
 * for now always pass a void
 */
void alarmWatch::alarmEvery(int repeats, std::chrono::duration<float, std::ratio<1, 100000000>> __timeD,
                            std::function<void()> callableFunc) {
    //catch if we call for zero duration
    if (__timeD <= __timeD.zero()) {
        return;
    }

    // internally store the function
    // preferably have everything passed by reference
    _callableFunc = std::move(callableFunc);
    _thread_runningFlag = true;
    stopWatch_Start();
    stopWatch_Stop();
    _alarmThread = new std::thread(

            [this, __timeD, repeats]() {
                while (_thread_runningFlag) {
                    //start timing
                    // for loop that handles the timing and calling
                    for (int x = 0; x <= repeats; x++) {
                        stopWatch_Start();
                        //return if thread signalled off
                        if (!_thread_runningFlag) {
                            return;
                        }
                        _callableFunc();
                        if (get_runTime() >= __timeD) {
                            std::cout << "taking too long" << get_runTime().count() << std::endl;
                        }
                        std::this_thread::sleep_for(__timeD - get_runTime());

                        //return if thread signalled off
                        if (!_thread_runningFlag) {
                            return;
                        }
                    }
                    //check if a function is to be called at the end
                    if (_whenDoneFlag) {
                        _whenDone();
                        _whenDoneFlag = !_whenDoneFlag;
                    }
                    //stop timing
                    stopWatch_Stop();

                    //stop stops the thread
                    _thread_runningFlag = false;
                }
            }

    );
}

void alarmWatch::__Kill() {
    _thread_runningFlag = false;
    if (_alarmThread->joinable()) {
        _alarmThread->join();
    }
}

/*!
 * alarmKill - If on it will change the running flag
 *             forcing the working thread to return
 */
void alarmWatch::alarmKill() {
    //check if the thread is running and if so
    //join it
    if (alarmRunning()) {
        _thread_runningFlag = !_thread_runningFlag;

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
    return _thread_runningFlag;
}

/*!
 * whenDone - calls adds a function to be called when alarm every is done
 *            this function also sets the whenDoneflag signaling the alarm
 *            to execute the passed function when done
 * @param callableFunc function to be executed
 */
void alarmWatch::whenDone(std::function<void()> callableFunc) {
    _whenDone = std::move(callableFunc);
    _whenDoneFlag = true;
}

/*!
 * whenDoneClear - clears the when done flag stopping the whenDone function
 *                 from executing
 */
void alarmWatch::whenDoneClear() {
    _whenDoneFlag = false;
}

/*!
 * whenDoneSet - checks if a callable function exists,
 *               if so sets the whenDoneFlag
 * @return bool if a function will be called after alarm
 */
bool alarmWatch::whenDoneSet() {
    //std::function - has a bool operator that checks for a callable
    if (_whenDone) {
        return _whenDoneFlag = true;
    } else {
        return _whenDoneFlag = false;
    }
}
