cmake_minimum_required(VERSION 2.8)
enable_testing()
#include(FindEXPAT)
#find_package(EXPAT REQUIRED)
#include_directories(${EXPAT_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-ggdb -Og -Wall -Wextra -Weffc++ -I$(CMAKE_SOURCE_DIR)/src")

add_executable(testProductionOption test/testProductionOption.cpp src/ProductionOption.cpp)
add_test(testProductionOption testProductionOption)

add_executable(testFactory test/testFactory.cpp src/Factory.cpp src/ProductionOption.cpp)
add_test(testFactory testFactory)

