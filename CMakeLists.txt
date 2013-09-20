cmake_minimum_required(VERSION 2.8)
#include(FindEXPAT)
#find_package(EXPAT REQUIRED)
#include_directories(${EXPAT_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-ggdb -Og -Wall -Wextra")

add_executable(testProductionOption testProductionOption.cpp ProductionOption.cpp)
