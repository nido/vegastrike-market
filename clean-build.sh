#!/bin/bash
test -d ".git" -a -f "clean-build.sh" || exit
git clean -fdx
mkdir build && cd build || exit
cmake -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_CXX_FLAGS="-Wall -Wextra" ..
make
make test
