#!/bin/bash -x

CLANG_ANALYZER="`ls /usr/lib*/clang-analyzer/scan-build/c++-analyzer | head -n 1`"

test -f CMakeLists.txt || 
	echo You wanna execute this from the directory containing CMakeLists.txt.
test -f CMakeLists.txt || 
	exit
test -f  CMakeCache.txt && rm CMakeCache.txt

BUILDDIR=coveragebuild
mkdir -p "${BUILDDIR}" 
cd "${BUILDDIR}"

cmake \
 -DCMAKE_CXX_COMPILER="${CLANG_ANALYZER}" \
 -DCMAKE_CXX_FLAGS="-std=c++11 -Wall -Wextra -Wpedantic -pedantic" ..
scan-build --use-analyzer /usr/bin/clang make

