#!/bin/bash -x
test -f CMakeLists.txt || 
	echo You wanna execute this from the directory containing CMakeLists.txt.
test -f CMakeLists.txt || 
	exit
test -f  CMakeCache.txt && rm CMakeCache.txt

BUILDDIR=coveragebuild
mkdir -p "${BUILDDIR}" 
cd "${BUILDDIR}"

cmake \
 -DCMAKE_CXX_COMPILER=/usr/lib64/clang-analyzer/scan-build/c++-analyzer \
 -DCMAKE_CXX_FLAGS="-std=c++11 -Wall -Wextra -Wpedantic -pedantic" ..
scan-build --use-analyzer /usr/bin/clang make

