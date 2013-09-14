cmake_minimum_required(VERSION 2.8)
include(FindEXPAT)
find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "\"-I${CMAKE_SOURCE_DIR}/scew\"")
add_executable(market_main market_main.cpp)
add_executable(factory_main factory_main.cpp)
add_executable(xmlfacotry_main xmlfactory_main.cpp scew/attribute.c  scew/element.c  scew/error.c  scew/parser.c  scew/str.c  scew/tree.c  scew/writer.c  scew/xattribute.c  scew/xerror.c  scew/xhandler.c  scew/xparser.c  scew/xprint.c)

target_link_libraries(xmlfacotry_main ${EXPAT_LIBRARIES})
