cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

project(VegastrikeEconomy)

enable_testing()

include(FindCppUnit)
include_directories(${CPPUNIT_INCLUDE_DIRS})

include(FindEXPAT)
find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIRS})

add_library(market
	src/CargoType
	src/Cargo
	src/ProductionOption
	src/Factory
	src/Base
	src/XMLNode
	src/MPLParse
	src/Economy
	src/common/common
)

target_link_libraries(market stdc++ ${EXPAT_LIBRARIES})


include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(bigtest
	test/bigtest.cpp
)

target_link_libraries(bigtest market ${CPPUNIT_LIBRARIES} ${EXPAT_LIBRARIES})

add_executable(makestupidproductionoptions
	test/MakeStupidProductionOptions.cpp
)

target_link_libraries(makestupidproductionoptions market ${EXPAT_LIBRARIES})

add_executable(VSmarket
	src/VSmarket.cpp
)

target_link_libraries(VSmarket market ${EXPAT_LIBRARIES})

if(${CPPUNIT_FOUND})
add_executable(cppunittest
	test/main
	test/CargoTypeTest
	test/CargoTest
	test/ProductionOptionTest
	test/FactoryTest
	test/BaseTest
	test/XMLNodeTest
	test/MPLParseTest
	test/EconomyTest
	)

target_link_libraries(cppunittest market ${CPPUNIT_LIBRARIES} ${EXPAT_LIBRARIES})

add_test(cppunittest cppunittest)
endif(${CPPUNIT_FOUND})

if(${WIN32})
add_custom_command(TARGET market POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${EXPAT_LIBRARY}
        $<TARGET_FILE_DIR:market>)
endif(${WIN32})


add_custom_target(clang-analyze /usr/lib64/clang-analyzer/scan-build/c++-analyzer -c -std=c++11 -I ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/src/*.[ch]pp ${CMAKE_CURRENT_SOURCE_DIR}/test/*.[ch]pp
	COMMENT "Static analysis using clang-analyze"
)

add_custom_target(cppcheck cppcheck --suppress="unusedFunction:*Test.?pp" --suppress="duplicateExpression:*Test.?pp" --suppress="noConstructor:*Test.?pp" --enable=all --force ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/test/
	COMMENT "Static analysis using cppcheck"
)

find_package(Doxygen)
if(${DOXYGEN_FOUND})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(html ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 2>&1 | grep -v Test.[ch]pp
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(${DOXYGEN_FOUND})
