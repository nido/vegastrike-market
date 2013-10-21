#!/bin/bash
test -f CMakeLists.txt || 
	echo You wanna execute this from the directory containing CMakeLists.txt.
test -f CMakeLists.txt || 
	exit
test -f  CMakeCache.txt && rm CMakeCache.txt && echo "warning: removed CMakeCache file"

imageformat=png

test -d performance || mkdir performance
cd performance

function runtests(){
	for x in ${1}; do
		for y in ${2}; do
			for z in ${3}; do
				echo bigtest $x $y $z
				/usr/bin/time -a -o ${4}timing -f "${x}	${y}	${z}	%e	%M %K	%D	%F	%U	%R	%W	%F" ./bigtest ${x} ${y} ${z} >/dev/null
			done
		done
	done
}

for compiler in g++;
do

cmake -D"CMAKE_BUILD_TYPE=Release" -D"CMAKE_CXX_COMPILER=${compiler}" ..
make clean
make bigtest

rm ${compiler}turnstiming
runtests "`seq 0 1 100`" 10 100 ${compiler}turns
echo "set terminal ${imageformat}; set output '../turns-runtime-${compiler}.${imageformat}'; set xlabel 'turns'; set ylabel 'seconds'; plot '${compiler}turnstiming'  using 1:4 with lines title 'runtime', '' using 1:9 with lines title 'usertime';" | gnuplot
echo "set terminal ${imageformat}; set output '../turns-memory-${compiler}.${imageformat}'; set xlabel 'turns'; set ylabel 'seconds'; plot '${compiler}turnstiming' using 1:5 with lines title 'resident memory', '' using 1:10 with lines title 'soft pagefaults', '' using 1:12 with lines title 'hard pagefaults';" | gnuplot

rm ${compiler}basesizetiming
runtests 10 "`seq 1 1 100`" 100 ${compiler}basesize
echo "set terminal ${imageformat}; set output '../basesize-runtime-${compiler}.${imageformat}'; set xlabel 'basesize'; set ylabel 'seconds'; plot '${compiler}basesizetiming'  using 2:4 with lines title 'runtime', '' using 2:9 with lines title 'usertime';" | gnuplot
echo "set terminal ${imageformat}; set output '../basesize-memory-${compiler}.${imageformat}'; set xlabel 'basesize'; set ylabel 'seconds'; plot '${compiler}basesizetiming' using 2:5 with lines title 'resident memory', '' using 2:10 with lines title 'soft pagefaults', '' using 2:12 with lines title 'hard pagefaults';" | gnuplot

rm ${compiler}economysizetiming
runtests 10 100 "`seq 1 1 100`" ${compiler}economysize
echo "set terminal ${imageformat}; set output '../economysize-runtime-${compiler}.${imageformat}'; set xlabel 'economysize'; set ylabel 'seconds'; plot '${compiler}economysizetiming'  using 3:4 with lines title 'runtime', '' using 3:9 with lines title 'usertime';" | gnuplot
echo "set terminal ${imageformat}; set output '../economysize-memory-${compiler}.${imageformat}'; set xlabel 'economysize'; set ylabel 'seconds'; plot '${compiler}economysizetiming' using 3:5 with lines title 'resident memory', '' using 3:10 with lines title 'soft pagefaults', '' using 3:12 with lines title 'hard pagefaults';" | gnuplot

#for x in `seq 0 10 100`; do
#for y in `seq 0 100 1000`; do
#echo bigtest 10 $x $y
#/usr/bin/time -a -o ${compiler}timing -f "${x}	${y}	%e	%M	%K	%D	%F	%U	%R	%W" ./bigtest 10 ${x} ${y} >/dev/null
#done
#done
#echo "set terminal ${imageformat}; set output '../time-${compiler}.${imageformat}'; set dgrid3d; splot '${compiler}timing' using 1:2:3 with lines" | gnuplot
#10 echo "set terminal ${imageformat}; set output '../memory-${compiler}.${imageformat}'; set dgrid3d; splot '${compiler}timing' using 1:2:4 with lines" | gnuplot

done
