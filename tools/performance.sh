#!/bin/bash
test -f CMakeLists.txt || 
	echo You wanna execute this from the directory containing CMakeLists.txt.
test -f CMakeLists.txt || 
	exit
test -f  CMakeCache.txt && rm CMakeCache.txt && echo "warning: removed CMakeCache file"

test -d performance || mkdir performance
cd performance


for compiler in g++ clang++;
do

cmake -D"CMAKE_BUILD_TYPE=Release" -D"CMAKE_CXX_COMPILER=${compiler}" ..
make clean
make bigtest
rm ${compiler}timing
for x in `seq 0 10 100`; do
for y in `seq 0 100 1000`; do
echo bigtest 10 $x $y
/usr/bin/time -a -o ${compiler}timing -f "${x}	${y}	%e	%M	%K	%D	%F	%U	%R	%W" ./bigtest 10 ${x} ${y} >/dev/null

done
done
echo "set terminal svg; set output '../time-${compiler}.svg'; set dgrid3d; splot '${compiler}timing' using 1:2:3 with lines" | gnuplot
echo "set terminal svg; set output '../memory-${compiler}.svg'; set dgrid3d; splot '${compiler}timing' using 1:2:4 with lines" | gnuplot

done
