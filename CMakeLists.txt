cmake_minimum_required(VERSION 3.8)
project(Stopwatch)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp stopWatch.cpp stopWatch.h alarmWatch.cpp alarmWatch.h)
set(CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(Stopwatch ${SOURCE_FILES})
