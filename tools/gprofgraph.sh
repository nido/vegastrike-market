#!/bin/bash
test -f CMakeLists.txt || 
	echo You wanna execute this from the directory containing CMakeLists.txt.
test -f CMakeLists.txt || 
	exit
test -f  CMakeCache.txt && rm CMakeCache.txt

test -d gprof || mkdir gprof
cd gprof

#TODO: cmake with -pg
cmake -DCMAKE_BUILD_TYPE=Release -D"CMAKE_CXX_FLAGS:string=-pg" ..
make
./bigtest 100 30 1000
gprof bigtest gmon.out > bigtest.gprof
gprof2dot -s bigtest.gprof -o bigtest.dot
dot -Tpng -o ../bigtest-gprof.png bigtest.dot

