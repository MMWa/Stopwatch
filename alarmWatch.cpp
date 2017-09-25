//
// Created by wahba on 18/08/17.
//

#include "alarmWatch.h"


alarmWatch::alarmWatch() : _runningFlag(false), _whenDoneFlag(false) {}

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
    _runningFlag = true;
    _alarmThread = new std::thread(

            [this, __timeD, repeats]() {
                while (_runningFlag) {
                    //start timing
                    stopWatch_Start();
                    // for loop that handles the timing and calling
                    for (int x = 0; x <= repeats; x++) {
                        std::this_thread::sleep_for(__timeD);
                        _callableFunc();
                        //return if thread signalled off
                        if (!_runningFlag) {
                            stopWatch_Stop();
                            return;
                        }
                    }
                    //check if a function is to be called at the end
                    if (_whenDoneFlag) {
                        _whenDone();
                    }
                    //stop timing
                    stopWatch_Stop();
                    //stop stops the thread
                    _runningFlag = !_runningFlag;

                }
            });
}

/*!
 * alarmKill - If on it will change the running flag
 *             forcing the working thread to return
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
