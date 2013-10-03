#!/bin/bash -x
COMMAND=$1
TESTNAME=$(basename $1)

valgrind --tool=callgrind --callgrind-out-file=${TESTNAME}.callgrind ${COMMAND} 10
gprof2dot -s -f callgrind -o ${TESTNAME}.dot ${TESTNAME}.callgrind
dot -Tpdf -o${TESTNAME}.pdf ${TESTNAME}.dot
dot -Tsvg -o${TESTNAME}.svg ${TESTNAME}.dot
dot -Tpng -o${TESTNAME}.png ${TESTNAME}.dot

#valgrind --tool=cachegrind --branch-sim=yes --cachegrind-out-file=unittest.cachegrind ./cppunittest
#valgrind --tool=massif --peak-inaccuracy=0 --stacks=yes --massif-out-file=unittest.massif ./cppunittest 

