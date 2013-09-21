cmake_minimum_required(VERSION 2.8)

PROJECT(VegastrikeEconomy)

enable_testing()

#include(FindEXPAT)
#find_package(EXPAT REQUIRED)
#include_directories(${EXPAT_INCLUDE_DIRS})




set(CMAKE_CXX_FLAGS "-ggdb -Og -Wall -Wextra -I$(CMAKE_SOURCE_DIR)/src")

add_executable(testProductionOption test/testProductionOption.cpp src/ProductionOption.cpp)
add_test(testProductionOption testProductionOption)

add_executable(testFactory test/testFactory.cpp src/Factory.cpp src/ProductionOption.cpp)
add_test(testFactory testFactory)

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(html ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
