cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

project(VegastrikeEconomy)

enable_testing()

include(FindCppUnit)
#find_package(CppUnit)

#include(FindEXPAT)
#find_package(EXPAT REQUIRED)
#include_directories(${EXPAT_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -Wall -Wextra -fprofile-arcs -ftest-coverage")
set(CMAKE_BUILD_TYPE "Debug")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(cppunittest
	test/cppunittest.cpp
	test/FactoryTest.cpp
	test/ProductionOptionTest.cpp
	test/CargoHoldTest.cpp
	test/CargoTest.cpp
	src/Factory.cpp
	src/ProductionOption.cpp
	src/CargoHold.cpp
	src/Cargo.cpp)

target_link_libraries(cppunittest ${CPPUNIT_LIBRARIES})

add_test(cppunittest cppunittest)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/coverage.sh.in ${CMAKE_CURRENT_BINARY_DIR}/coverage.sh @ONLY)

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(html ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
