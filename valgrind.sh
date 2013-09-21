valgrind --tool=callgrind --callgrind-out-file=unittest.callgrind ./cppunittest
gprof2dot -f callgrind -o unittest-callgrind.dot unittest.callgrind
dot -Tpdf -ounittest-callgrind.pdf unittest-callgrind.dot

valgrind --tool=cachegrind --branch-sim=yes --cachegrind-out-file=unittest.cachegrind ./cppunittest
valgrind --tool=massif --peak-inaccuracy=0 --stacks=yes --massif-out-file=unittest.massif ./cppunittest 

