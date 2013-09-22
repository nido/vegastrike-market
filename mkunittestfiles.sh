#!/bin/bash
NAME="$1"
#
cat doc/unittest.template.cpp | sed "s/@template@/$NAME/g" > test/$NAME.cpp
cat doc/unittest.template.hpp | sed "s/@template@/$NAME/g" > test/$NAME.hpp
