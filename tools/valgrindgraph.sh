#!/bin/bash
test -f CMakeLists.txt || 
	echo You wanna execute this from the directory containing CMakeLists.txt.
test -f CMakeLists.txt || 
	exit
test -f  CMakeCache.txt && rm CMakeCache.txt

COMMAND=./bigtest
TESTNAME=bigtest

test -d valgrind || mkdir valgrind
cd valgrind

#cmake -D"CMAKE_CXX_FLAGS:string=-pg" ..
cmake -DCMAKE_BUILD_TYPE=Release ..
make

valgrind --tool=callgrind --callgrind-out-file=${TESTNAME}.callgrind ${COMMAND} 10
gprof2dot -s -f callgrind -o ${TESTNAME}-callgrind.dot ${TESTNAME}.callgrind
dot -Tpng -o../${TESTNAME}-callgrind.png ${TESTNAME}-callgrind.dot
