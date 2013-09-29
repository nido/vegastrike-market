#!/bin/bash -x

NAME="$1"

TESTS=$(cat "src/${NAME}.cpp" | 
	grep -Go "${NAME}::[^(\ ]\+" | 
	sed "s/${NAME}::/test/g" |
	sed "s/==/Equals/g" |
	sed "s/</LessThen/g")

TESTCODE=""
SUITECODE=""
HEADERCODE=""

for TEST in ${TESTS}
do
	TESTCODE="${TESTCODE}\nvoid ${NAME}Test::${TEST}()\n{\n}\n"

	HEADERCODE="${HEADERCODE}\n\tvoid ${TEST}();"

	SUITECODE="${SUITECODE}\n\tsuiteOfTests->addTest( new CppUnit::TestCaller<${NAME}Test>("
	SUITECODE="${SUITECODE}\n\t\t\t\"${TEST}\", \&${NAME}Test::${TEST}));\n"
done


cat doc/unittest.template.cpp | 
	sed "s/@template@/${NAME}Test/g" |
	sed "s/@suitecode@/${SUITECODE}/g" |
	sed "s/@testcode@/${TESTCODE}/g" > test/${NAME}Test.cpp

cat doc/unittest.template.hpp |
	sed "s/@template@/${NAME}Test/g" |
	sed "s/@headercode@/${HEADERCODE}/g" > test/${NAME}Test.hpp
