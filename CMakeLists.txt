cmake_minimum_required(VERSION 3.8)
project(watchTime)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp stopWatch.cpp stopWatch.h alarmWatch.cpp alarmWatch.h)
set(CMAKE_CXX_FLAGS "-pthread")
add_executable(watchTime ${SOURCE_FILES})