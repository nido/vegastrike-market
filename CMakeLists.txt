cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

project(VegastrikeEconomy)

enable_testing()

include(FindCppUnit)
#find_package(CppUnit)
include_directories(${CPPUNIT_INCLUDE_DIRS})

include(FindEXPAT)
find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIRS})



#include_directories(${EXPAT_INCLUDE_DIRS})
#include_directories(${EXPAT_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

#set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -Wall -Wextra")
#set(CMAKE_BUILD_TYPE "Debug")

add_library(market
	src/CargoType
	src/Cargo
	src/ProductionOption
	src/Factory
	src/Base
	src/XMLParse
	src/MPLParse
	src/Economy
	src/common/common
)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(bigtest
	test/bigtest.cpp
)

target_link_libraries(bigtest market ${CPPUNIT_LIBRARIES} ${EXPAT_LIBRARIES})

add_executable(cppunittest
	test/main
	test/CargoTypeTest
	test/CargoTest
	test/ProductionOptionTest
	test/FactoryTest
	test/BaseTest
	test/XMLParseTest
	test/MPLParseTest
	)

target_link_libraries(cppunittest market ${CPPUNIT_LIBRARIES} ${EXPAT_LIBRARIES})

add_test(cppunittest cppunittest)

add_custom_target(clang-analyze /usr/lib64/clang-analyzer/scan-build/c++-analyzer -c -I ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/src/*.[ch]pp ${CMAKE_CURRENT_SOURCE_DIR}/test/*.[ch]pp
	COMMENT "Static analysis using clang-analyze"
)

add_custom_target(cppcheck cppcheck --quiet --enable=all --force ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/test/
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Static analysis using cppcheck"
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(html ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
