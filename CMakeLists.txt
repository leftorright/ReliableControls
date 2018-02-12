cmake_minimum_required(VERSION 3.7)
project(ReliableControls)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp IEventCounter.h IEventCounterTests.cpp)
add_executable(ReliableControls ${SOURCE_FILES})
cmake_minimum_required(VERSION 2.8)
