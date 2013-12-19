cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

project(VegastrikeEconomy)

set(MARKET_SRCS
	src/CargoType.cpp
	src/Cargo.cpp
	src/ProductionOption.cpp
	src/Factory.cpp
	src/Base.cpp
	src/XMLNode.cpp
	src/MPLParse.cpp
	src/Economy.cpp
	src/common/common.cpp
)

set(CPPUNIT_SRCS
	test/CargoTypeTest.cpp
	test/CargoTest.cpp
	test/ProductionOptionTest.cpp
	test/FactoryTest.cpp
	test/BaseTest.cpp
	test/XMLNodeTest.cpp
	test/MPLParseTest.cpp
	test/EconomyTest.cpp
)
enable_testing()

include(FindCppUnit)
include_directories(${CPPUNIT_INCLUDE_DIRS})

include(FindEXPAT)
find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIRS})


add_library(market ${MARKET_SRCS})
add_library(cppunittest ${CPPUNIT_SRCS})

target_link_libraries(market stdc++)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(bigtest
	test/bigtest.cpp
)

target_link_libraries(bigtest market ${CPPUNIT_LIBRARIES} ${EXPAT_LIBRARIES})

add_executable(test_cppunit
	test/main.cpp
)

target_link_libraries(test_cppunit cppunittest market ${CPPUNIT_LIBRARIES} ${EXPAT_LIBRARIES})

add_test(cppunittest test_cppunit)

add_custom_target(clang-analyze /usr/lib64/clang-analyzer/scan-build/c++-analyzer -c -std=c++11 -I ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/src/*.[ch]pp ${CMAKE_CURRENT_SOURCE_DIR}/test/*.[ch]pp
	COMMENT "Static analysis using clang-analyze"
)

add_custom_target(cppcheck cppcheck --suppress="unusedFunction:*Test.?pp" --suppress="duplicateExpression:*Test.?pp" --suppress="noConstructor:*Test.?pp" --enable=all --force ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/test/
	COMMENT "Static analysis using cppcheck"
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(html ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 2>&1 | grep -v Test.[ch]pp
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
