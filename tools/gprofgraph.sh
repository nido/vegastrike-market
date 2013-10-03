#!/bin/bash
test -f CMakeLists.txt || 
	echo You wanna execute this from the directory containing CMakeLists.txt.
test -f CMakeLists.txt || 
	exit

test -d gprof || mkdir gprof
cd gprof

#TODO: cmake with -pg
cmake -D"CMAKE_CXX_FLAGS:string=-pg" ..
make
./bigtest
gprof bigtest gmon.out > bigtest.gprof
gprof2dot -s bigtest.gprof -o bigtest.dot
dot -Tpng -o ../bigtest-gprof.png bigtest.dot

