cmake -DCMAKE_BUILD_TYPE:STRING=Debug ..
make

#gcov CMakeFiles/*.dir/*/*.gcno

lcov -z --directory . -o coverage.info
./cppunittest
lcov -c --directory . -o coverage.info
lcov -e coverage.info "/home/nido/code/market/*" -o codecoverage.info
genhtml codecoverage.info --output-directory coverage/
