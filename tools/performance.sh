#!/bin/bash
test -f CMakeLists.txt || 
	echo You wanna execute this from the directory containing CMakeLists.txt.
test -f CMakeLists.txt || 
	exit
test -f  CMakeCache.txt && rm CMakeCache.txt && echo "warning: removed CMakeCache file"

test -d performance || mkdir performance
cd performance

cmake -D"CMAKE_BUILD_TYPE=Release" -D"CMAKE_CXX_COMPILER=g++" ..
cmake -D"CMAKE_BUILD_TYPE=Release" ..
make VERBOSE=1
/usr/bin/time -f "timing gcc %e" ./bigtest 10 100 1000

cmake -DCMAKE_BUILD_TYPE=Release "-DCMAKE_CXX_COMPILER=clang++" ..
cmake -DCMAKE_BUILD_TYPE=Release ..
make VERBOSE=1
/usr/bin/time -f "timing clang %e" ./bigtest 10 100 1000

