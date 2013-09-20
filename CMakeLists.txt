cmake_minimum_required(VERSION 2.8)
#include(FindEXPAT)
#find_package(EXPAT REQUIRED)
#include_directories(${EXPAT_INCLUDE_DIRS})

#set(CMAKE_CXX_FLAGS "\"-I${CMAKE_SOURCE_DIR}/scew\"")

#add_library(scew STATIC scew/attribute.c  scew/element.c  scew/error.c  scew/parser.c  scew/str.c  scew/tree.c  scew/writer.c  scew/xattribute.c  scew/xerror.c  scew/xhandler.c  scew/xparser.c  scew/xprint.c)

#add_executable(market_main market_main.cpp Market.cpp node.cpp btree_iterator.cpp)
#add_executable(factory_main factory_main.cpp ProductionOption.cpp Economy.cpp Factory.cpp Consumer.cpp Market.cpp Reserve.cpp node.cpp btree_iterator.cpp)
#add_executable(xmlfactory_main xmlfactory_main.cpp xmleconomy.cpp Economy.cpp Factory.cpp Consumer.cpp Market.cpp ProductionOption.cpp Reserve.cpp node.cpp btree_iterator.cpp)

#target_link_libraries(market_main scew)
#target_link_libraries(factory_main scew)
#target_link_libraries(xmlfactory_main scew ${EXPAT_LIBRARIES})
add_executable(testProductionOption testProductionOption.cpp ProductionOption.cpp)
