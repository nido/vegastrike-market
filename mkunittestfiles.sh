#!/bin/bash

NAME="$1"

TESTS=$(cat "src/${NAME}.cpp" | 
	grep -Go "${NAME}::[^(\ ]\+" | 
	sed "s/${NAME}::/test/g" |
	sed "s/==/Equals/g" |
	sed "s/</LessThen/g")

FILES=$(ls test/*Test.hpp | sed "s/test\/\([a-zA-Z]*\).hpp/\1/g")

TESTCODE=""
SUITECODE=""
HEADERCODE=""
UNITTESTCODE=""
INCLUDECODE=""

for TEST in ${TESTS}
do
	TESTCODE="${TESTCODE}\nvoid ${NAME}Test::${TEST}()\n{\n}\n"

	HEADERCODE="${HEADERCODE}\n\tvoid ${TEST}();"

	SUITECODE="${SUITECODE}\n\tsuiteOfTests->addTest( new CppUnit::TestCaller<${NAME}Test>("
	SUITECODE="${SUITECODE}\n\t\t\t\"${TEST}\", \&${NAME}Test::${TEST}));\n"

done

for FILE in ${FILES}
do
	UNITTESTCODE="${UNITTESTCODE}\n\tif (argc == 1 || strcmp(argv[1], \"${FILE}\") == 0){"
	UNITTESTCODE="${UNITTESTCODE}\n\t\t runner.addTest( ${FILE}::suite());"
	UNITTESTCODE="${UNITTESTCODE}\n\t}"

	INCLUDECODE="${INCLUDECODE}\n#include \"${FILE}.hpp\""
done

cat doc/unittest.template.cpp | 
	sed "s/@template@/${NAME}Test/g" |
	sed "s/@suitecode@/${SUITECODE}/g" |
	sed "s/@testcode@/${TESTCODE}/g" > test/${NAME}Test.cpp

cat doc/unittest.template.hpp |
	sed "s/@template@/${NAME}Test/g" |
	sed "s/@headercode@/${HEADERCODE}/g" > test/${NAME}Test.hpp

cat doc/unittest.template.main.cpp |
	sed "s/@unittestcode@/${UNITTESTCODE}/g" |
	sed "s/@includecode@/${INCLUDECODE}/g" > "test/main.cpp"
